#!/usr/bin/env python3
"""
STL vs EASTL Compilation Benchmark Script

This script compiles and measures:
1. Compilation time (primary focus)
2. Binary size of the resulting executables

Usage: python3 benchmark.py [--build-type Debug|Release|RelWithDebInfo|MinSizeRel] [--output-format json|table]
"""

import os
import subprocess
import time
import json
import argparse
from pathlib import Path
import shutil

class BenchmarkRunner:
    def __init__(self, build_dir="build", results_dir="results", build_types=["Debug", "Release"], enable_ftime_trace=True, num_types=100):
        self.build_dir = Path(build_dir)
        self.results_dir = Path(results_dir)
        self.build_types = build_types if isinstance(build_types, list) else [build_types]
        self.enable_ftime_trace = enable_ftime_trace
        self.num_types = num_types
        self.results = {}
        
        # Ensure directories exist
        self.build_dir.mkdir(exist_ok=True)
        self.results_dir.mkdir(exist_ok=True)
        
        # Test configurations - now using single compilation benchmark test
        self.tests = [
            "compilation_benchmark_test"
        ]
        
        self.libraries = ["stl", "eastl"]
    
    def clean_build(self):
        """Clean the build directory"""
        print("Cleaning build directory...")
        if self.build_dir.exists():
            shutil.rmtree(self.build_dir)
        self.build_dir.mkdir(exist_ok=True)
    
    def run_cmake(self, build_type):
        """Configure the project with CMake"""
        ftime_trace_status = "enabled" if self.enable_ftime_trace else "disabled"
        print(f"Configuring with CMake (build type: {build_type}, generator: Ninja, ftime-trace: {ftime_trace_status}, num_types: {self.num_types})...")
        
        cmd = ["cmake", "-S", ".", "-B", str(self.build_dir), 
               f"-DCMAKE_BUILD_TYPE={build_type}", 
               f"-DENABLE_FTIME_TRACE={'ON' if self.enable_ftime_trace else 'OFF'}",
               f"-DNUM_TYPES={self.num_types}",
               "-G", "Ninja"]
        result = subprocess.run(cmd, capture_output=True, text=True)
        
        if result.returncode != 0:
            print(f"CMake configuration failed: {result.stderr}")
            return False
        return True
    
    def compile_target(self, target_name):
        """Compile a specific target and measure compilation time"""
        print(f"Compiling {target_name}...")
        
        # For fair comparison, clean only the specific target object files
        # This ensures we measure only the test file compilation, not library compilation
        target_obj_pattern = f"CMakeFiles/{target_name}.dir/"
        target_obj_dir = self.build_dir / target_obj_pattern
        if target_obj_dir.exists():
            import shutil
            shutil.rmtree(target_obj_dir)
        
        # Also remove the executable to force recompilation
        binary_path = self.build_dir / target_name
        if binary_path.exists():
            binary_path.unlink()
        
        # Clean any existing trace files for this target to ensure clean analysis
        if self.enable_ftime_trace:
            trace_pattern = f"CMakeFiles/{target_name}.dir/**/*.json"
            for trace_file in self.build_dir.glob(trace_pattern):
                trace_file.unlink()
        
        start_time = time.time()
        cmd = ["cmake", "--build", str(self.build_dir), "--target", target_name, "-j1"]
        result = subprocess.run(cmd, capture_output=True, text=True)
        end_time = time.time()
        
        compilation_time = end_time - start_time
        
        if result.returncode != 0:
            print(f"Compilation failed for {target_name}: {result.stderr}")
            return None, None
        
        # Get binary size
        if binary_path.exists():
            binary_size = binary_path.stat().st_size
        else:
            print(f"Binary not found: {binary_path}")
            binary_size = 0
        
        return compilation_time, binary_size
    
    def start_clang_build_analyzer(self):
        """Start Clang Build Analyzer session"""
        if not self.enable_ftime_trace:
            return False
            
        # Path to ClangBuildAnalyzer executable
        analyzer_path = self.build_dir / "_deps" / "clangbuildanalyzer-build" / "ClangBuildAnalyzer"
        if not analyzer_path.exists():
            print(f"ClangBuildAnalyzer not found at {analyzer_path}")
            return False
        
        try:
            print("Starting Clang Build Analyzer session...")
            result = subprocess.run([str(analyzer_path), "--start", str(self.build_dir)], 
                                  capture_output=True, text=True, timeout=30)
            
            if result.returncode == 0:
                print("  Clang Build Analyzer session started")
                return True
            else:
                print(f"Failed to start Clang Build Analyzer: {result.stderr}")
                return False
        except Exception as e:
            print(f"Error starting Clang Build Analyzer: {e}")
            return False
    
    def run_clang_build_analyzer(self, target_name, build_type):
        """Run Clang Build Analyzer on specific target trace files"""
        if not self.enable_ftime_trace:
            return None
            
        print(f"Running Clang Build Analyzer for {target_name}...")
        
        # Find trace files for this specific target only
        target_trace_dir = self.build_dir / f"CMakeFiles/{target_name}.dir"
        trace_files = list(target_trace_dir.glob("**/*.json"))
        
        if not trace_files:
            print(f"No trace files found for {target_name}")
            return None
        
        # Path to ClangBuildAnalyzer executable
        analyzer_path = self.build_dir / "_deps" / "clangbuildanalyzer-build" / "ClangBuildAnalyzer"
        if not analyzer_path.exists():
            print(f"ClangBuildAnalyzer not found at {analyzer_path}")
            return None
        
        try:
            # Create timestamp for unique filename
            timestamp = time.strftime("%Y%m%d_%H%M%S")
            analysis_file = self.results_dir / f"clang_analysis_{target_name}_{build_type}_{timestamp}.txt"
            trace_file = self.results_dir / f"clang_trace_{target_name}_{build_type}_{timestamp}.bin"
            
            # Use --all to process only this target's trace files
            print(f"Processing trace files for {target_name}...")
            all_result = subprocess.run([str(analyzer_path), "--all", str(target_trace_dir), str(trace_file)], 
                                      capture_output=True, text=True, timeout=30)
            
            if all_result.returncode != 0:
                print(f"Failed to process trace files: {all_result.stderr}")
                return None
            
            # Analyze the trace file
            print(f"Analyzing trace for {target_name}...")
            analyze_result = subprocess.run([str(analyzer_path), "--analyze", str(trace_file)], 
                                          capture_output=True, text=True, timeout=60)
            
            if analyze_result.returncode == 0:
                # Save analysis to results directory
                with open(analysis_file, 'w') as f:
                    f.write(f"Clang Build Analysis for {target_name} ({build_type})\n")
                    f.write("=" * 60 + "\n\n")
                    f.write(analyze_result.stdout)
                    if analyze_result.stderr:
                        f.write("\n\nStderr:\n")
                        f.write(analyze_result.stderr)
                
                print(f"  Clang analysis saved to: {analysis_file.name}")
                return analysis_file.name
            else:
                print(f"Clang Build Analyzer analysis failed: {analyze_result.stderr}")
                return None
        except subprocess.TimeoutExpired:
            print("Clang Build Analyzer timed out")
            return None
        except Exception as e:
            print(f"Error running Clang Build Analyzer: {e}")
            return None

    def run_benchmarks(self):
        """Run all compilation benchmarks for both Debug and Release"""
        print("Starting STL vs EASTL compilation benchmark...")
        
        # EASTL will be downloaded automatically via CMake FetchContent
        
        # Run benchmarks for each build type
        for build_type in self.build_types:
            print(f"\n{'='*60}")
            print(f"BENCHMARKING {build_type.upper()} BUILD")
            print(f"{'='*60}")
            
            # Clean and configure for this build type
            self.clean_build()
            if not self.run_cmake(build_type):
                return False
            
            # Pre-compile EASTL library to make fair comparison with pre-compiled STL
            print("Pre-compiling EASTL library for fair comparison...")
            result = subprocess.run(["cmake", "--build", str(self.build_dir), "--target", "EASTL"], 
                                  capture_output=True, text=True)
            if result.returncode != 0:
                print(f"EASTL pre-compilation failed: {result.stderr}")
                return False
            print("EASTL library pre-compiled successfully")
            
            # Build ClangBuildAnalyzer if ftime-trace is enabled
            if self.enable_ftime_trace:
                print("Building ClangBuildAnalyzer...")
                result = subprocess.run(["cmake", "--build", str(self.build_dir), "--target", "ClangBuildAnalyzer"], 
                                      capture_output=True, text=True)
                if result.returncode != 0:
                    print(f"ClangBuildAnalyzer build failed: {result.stderr}")
                    print("Continuing without ClangBuildAnalyzer...")
                    self.enable_ftime_trace = False
                else:
                    print("ClangBuildAnalyzer built successfully")
            
            # Initialize results for this build type
            if build_type not in self.results:
                self.results[build_type] = {}
            
            # Run benchmarks for each test and library
            for test in self.tests:
                print(f"\n--- Benchmarking {test} ({build_type}) ---")
                self.results[build_type][test] = {}
                
                for lib in self.libraries:
                    target_name = f"{lib}_{test}"
                    print(f"Processing {target_name}...")
                    
                    compilation_time, binary_size = self.compile_target(target_name)
                    
                    if compilation_time is not None:
                        # Run Clang Build Analyzer if enabled
                        analyzer_output = self.run_clang_build_analyzer(target_name, build_type)
                        
                        self.results[build_type][test][lib] = {
                            "compilation_time": round(compilation_time, 3),
                            "binary_size": binary_size,
                            "binary_size_kb": round(binary_size / 1024, 2),
                            "clang_analysis_file": analyzer_output
                        }
                        
                        print(f"  Compilation time: {compilation_time:.3f}s")
                        print(f"  Binary size: {binary_size} bytes ({binary_size/1024:.2f} KB)")
                        if analyzer_output:
                            print(f"  Clang analysis: {analyzer_output}")
                    else:
                        self.results[build_type][test][lib] = {
                            "compilation_time": None,
                            "binary_size": None,
                            "error": "Compilation failed"
                        }
        
        return True
    
    def save_results(self, format_type="json"):
        """Save results to file"""
        timestamp = time.strftime("%Y%m%d_%H%M%S")
        
        if format_type == "json":
            filename = self.results_dir / f"benchmark_results_{timestamp}.json"
            with open(filename, 'w') as f:
                json.dump(self.results, f, indent=2)
            print(f"\nResults saved to: {filename}")
        
        # Always save a human-readable summary
        summary_file = self.results_dir / f"benchmark_summary_{timestamp}.txt"
        self.save_summary(summary_file)
    
    def save_summary(self, filename):
        """Save a human-readable summary"""
        with open(filename, 'w') as f:
            f.write("STL vs EASTL Compilation Benchmark Results\n")
            f.write("=" * 50 + "\n\n")
            
            for build_type in self.build_types:
                if build_type not in self.results:
                    continue
                    
                f.write(f"BUILD TYPE: {build_type.upper()}\n")
                f.write("=" * (len(build_type) + 12) + "\n\n")
                
                for test in self.tests:
                    if test not in self.results[build_type]:
                        continue
                        
                    f.write(f"{test.upper()}\n")
                    f.write("-" * len(test) + "\n")
                    
                    stl_data = self.results[build_type][test].get("stl", {})
                    eastl_data = self.results[build_type][test].get("eastl", {})
                    
                    # Compilation time comparison
                    stl_time = stl_data.get("compilation_time")
                    eastl_time = eastl_data.get("compilation_time")
                    
                    if stl_time and eastl_time:
                        speedup = stl_time / eastl_time if eastl_time > 0 else float('inf')
                        f.write(f"Compilation Time:\n")
                        f.write(f"  STL:   {stl_time:.3f}s\n")
                        f.write(f"  EASTL: {eastl_time:.3f}s\n")
                        f.write(f"  Ratio: {speedup:.2f}x ({'STL faster' if speedup < 1 else 'EASTL faster'})\n\n")
                    
                    # Binary size comparison
                    stl_size = stl_data.get("binary_size")
                    eastl_size = eastl_data.get("binary_size")
                    
                    if stl_size and eastl_size:
                        size_ratio = stl_size / eastl_size if eastl_size > 0 else float('inf')
                        f.write(f"Binary Size:\n")
                        f.write(f"  STL:   {stl_size} bytes ({stl_size/1024:.2f} KB)\n")
                        f.write(f"  EASTL: {eastl_size} bytes ({eastl_size/1024:.2f} KB)\n")
                        f.write(f"  Ratio: {size_ratio:.2f}x ({'STL smaller' if size_ratio < 1 else 'EASTL smaller'})\n\n")
                    
                    f.write("\n")
                
                # Comparison between Debug and Release if both are available
                if len(self.build_types) > 1:
                    f.write("\n")
            
            # Cross-build-type comparison
            if len(self.build_types) > 1:
                f.write("BUILD TYPE COMPARISON\n")
                f.write("=" * 20 + "\n\n")
                
                for test in self.tests:
                    f.write(f"{test.upper()}\n")
                    f.write("-" * len(test) + "\n")
                    
                    for lib in self.libraries:
                        f.write(f"{lib.upper()}:\n")
                        for build_type in self.build_types:
                            if (build_type in self.results and 
                                test in self.results[build_type] and 
                                lib in self.results[build_type][test]):
                                data = self.results[build_type][test][lib]
                                comp_time = data.get("compilation_time", "N/A")
                                f.write(f"  {build_type}: {comp_time}s\n" if comp_time != "N/A" else f"  {build_type}: {comp_time}\n")
                        f.write("\n")
        
        print(f"Summary saved to: {filename}")
    
    def print_results(self):
        """Print results to console"""
        print("\n" + "=" * 60)
        print("COMPILATION BENCHMARK RESULTS")
        print("=" * 60)
        
        for build_type in self.build_types:
            if build_type not in self.results:
                continue
                
            print(f"\nBUILD TYPE: {build_type.upper()}")
            print("=" * (len(build_type) + 12))
            
            for test in self.tests:
                if test not in self.results[build_type]:
                    continue
                    
                print(f"\n{test.upper().replace('_', ' ')}")
                print("-" * 30)
                
                stl_data = self.results[build_type][test].get("stl", {})
                eastl_data = self.results[build_type][test].get("eastl", {})
                
                # Print compilation times
                stl_time = stl_data.get("compilation_time", "N/A")
                eastl_time = eastl_data.get("compilation_time", "N/A")
                
                print(f"Compilation Time:")
                print(f"  STL:   {stl_time}s" if isinstance(stl_time, (int, float)) else f"  STL:   {stl_time}")
                print(f"  EASTL: {eastl_time}s" if isinstance(eastl_time, (int, float)) else f"  EASTL: {eastl_time}")
                
                if isinstance(stl_time, (int, float)) and isinstance(eastl_time, (int, float)) and eastl_time > 0:
                    ratio = stl_time / eastl_time
                    print(f"  Ratio: {ratio:.2f}x ({'STL faster' if ratio < 1 else 'EASTL faster'})")
                
                # Print binary sizes
                stl_size = stl_data.get("binary_size_kb", "N/A")
                eastl_size = eastl_data.get("binary_size_kb", "N/A")
                
                print(f"Binary Size:")
                print(f"  STL:   {stl_size} KB" if isinstance(stl_size, (int, float)) else f"  STL:   {stl_size}")
                print(f"  EASTL: {eastl_size} KB" if isinstance(eastl_size, (int, float)) else f"  EASTL: {eastl_size}")
                
                if isinstance(stl_size, (int, float)) and isinstance(eastl_size, (int, float)) and eastl_size > 0:
                    ratio = stl_size / eastl_size
                    print(f"  Ratio: {ratio:.2f}x ({'STL smaller' if ratio < 1 else 'EASTL smaller'})")
        
        # Cross-build-type comparison
        if len(self.build_types) > 1:
            print(f"\n" + "=" * 60)
            print("BUILD TYPE COMPARISON")
            print("=" * 60)
            
            for test in self.tests:
                print(f"\n{test.upper().replace('_', ' ')}")
                print("-" * 30)
                
                for lib in self.libraries:
                    print(f"{lib.upper()}:")
                    for build_type in self.build_types:
                        if (build_type in self.results and 
                            test in self.results[build_type] and 
                            lib in self.results[build_type][test]):
                            data = self.results[build_type][test][lib]
                            comp_time = data.get("compilation_time", "N/A")
                            print(f"  {build_type}: {comp_time}s" if comp_time != "N/A" else f"  {build_type}: {comp_time}")
                    print()

def main():
    parser = argparse.ArgumentParser(description="STL vs EASTL Compilation Benchmark")
    parser.add_argument("--build-type", choices=["Debug", "Release", "RelWithDebInfo", "MinSizeRel"], 
                       default=None, help="Single CMake build type to test (default: both Debug and Release)")
    parser.add_argument("--debug-only", action="store_true",
                       help="Run only Debug build")
    parser.add_argument("--release-only", action="store_true",
                       help="Run only Release build")
    parser.add_argument("--output-format", choices=["json", "table"], default="json",
                       help="Output format for detailed results")
    parser.add_argument("--clean", action="store_true",
                       help="Clean build directory before running")
    parser.add_argument("--disable-ftime-trace", action="store_true",
                       help="Disable -ftime-trace and Clang Build Analyzer (enabled by default)")
    parser.add_argument("--num-types", type=int, default=100,
                       help="Number of types to instantiate in benchmark (default: 100)")
    
    args = parser.parse_args()
    
    # Determine build types to run
    if args.build_type:
        build_types = [args.build_type]
    elif args.debug_only:
        build_types = ["Debug"]
    elif args.release_only:
        build_types = ["Release"]
    else:
        # Default: run both Debug and Release
        build_types = ["Debug", "Release"]
    
    runner = BenchmarkRunner(build_types=build_types, enable_ftime_trace=not args.disable_ftime_trace, num_types=args.num_types)
    
    if args.clean:
        runner.clean_build()
    
    if runner.run_benchmarks():
        runner.print_results()
        runner.save_results(format_type=args.output_format)
        print("\nCompilation benchmark completed successfully!")
    else:
        print("Compilation benchmark failed!")
        return 1
    
    return 0

if __name__ == "__main__":
    exit(main())