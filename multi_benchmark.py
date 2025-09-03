#!/usr/bin/env python3
"""
Multi-run STL vs EASTL Benchmark Script with Graph Generation

This script performs multiple benchmark runs and generates statistical graphs.
It measures compilation time and binary size across multiple runs to provide
more reliable statistics with confidence intervals.

Usage: python3 multi_benchmark.py [--runs N] [--build-type Debug|Release] [--output-dir DIR]
"""

import os
import subprocess
import time
import json
import argparse
import statistics
import numpy as np
import matplotlib.pyplot as plt
import matplotlib.patches as mpatches
from pathlib import Path
import shutil
from datetime import datetime
from benchmark import BenchmarkRunner

class MultiBenchmarkRunner:
    def __init__(self, num_runs=5, build_types=["Debug", "Release"], output_dir="multi_results", num_types_mode=False):
        self.num_runs = num_runs
        self.build_types = build_types if isinstance(build_types, list) else [build_types]
        self.output_dir = Path(output_dir)
        self.output_dir.mkdir(exist_ok=True)
        self.num_types_mode = num_types_mode
        
        # NUM_TYPES values to test (from 25 to 150 with step 25)
        self.num_types_values = list(range(25, 151, 25)) if num_types_mode else [100]
        
        # Store all runs data
        self.all_runs = []
        self.statistics = {}
        
        # Graph settings
        plt.style.use('seaborn-v0_8' if 'seaborn-v0_8' in plt.style.available else 'default')
        self.colors = {
            'stl': '#1f77b4',      # Blue
            'eastl': '#ff7f0e',    # Orange
            'debug': '#2ca02c',    # Green
            'release': '#d62728'   # Red
        }
    
    def run_multiple_benchmarks(self):
        """Run benchmark multiple times and collect statistics"""
        if self.num_types_mode:
            print(f"Starting NUM_TYPES benchmark mode...")
            print(f"Build types: {', '.join(self.build_types)}")
            print(f"NUM_TYPES values: {self.num_types_values}")
            
            for num_types in self.num_types_values:
                print(f"\n{'='*60}")
                print(f"NUM_TYPES = {num_types}")
                print(f"{'='*60}")
                
                # Create a fresh benchmark runner for each NUM_TYPES value
                runner = BenchmarkRunner(build_types=self.build_types, enable_ftime_trace=False, num_types=num_types)
                
                if runner.run_benchmarks():
                    # Store results with num_types info
                    result_data = runner.results.copy()
                    result_data['num_types'] = num_types
                    self.all_runs.append(result_data)
                    print(f"NUM_TYPES={num_types} completed successfully")
                else:
                    print(f"NUM_TYPES={num_types} failed!")
                    return False
            
            print(f"\nAll NUM_TYPES tests completed!")
            return True
        else:
            print(f"Starting multi-run benchmark with {self.num_runs} runs...")
            print(f"Build types: {', '.join(self.build_types)}")
            
            for run_num in range(1, self.num_runs + 1):
                print(f"\n{'='*60}")
                print(f"RUN {run_num}/{self.num_runs}")
                print(f"{'='*60}")
                
                # Create a fresh benchmark runner for each run (disable ftime-trace for clean statistics)
                runner = BenchmarkRunner(build_types=self.build_types, enable_ftime_trace=False)
                
                if runner.run_benchmarks():
                    self.all_runs.append(runner.results)
                    print(f"Run {run_num} completed successfully")
                else:
                    print(f"Run {run_num} failed!")
                    return False
            
            print(f"\nAll {self.num_runs} runs completed!")
            return True
    
    def calculate_statistics(self):
        """Calculate statistics from all runs"""
        print("Calculating statistics...")
        
        if self.num_types_mode:
            # In NUM_TYPES mode, organize data by num_types
            self.statistics = {}
            for run_data in self.all_runs:
                num_types = run_data.get('num_types', 100)
                if num_types not in self.statistics:
                    self.statistics[num_types] = {}
                
                for build_type in self.build_types:
                    if build_type not in run_data:
                        continue
                    if build_type not in self.statistics[num_types]:
                        self.statistics[num_types][build_type] = {}
                    
                    for test_name, test_data in run_data[build_type].items():
                        if test_name not in self.statistics[num_types][build_type]:
                            self.statistics[num_types][build_type][test_name] = {}
                        
                        for lib in ['stl', 'eastl']:
                            if lib in test_data and test_data[lib].get('compilation_time') is not None:
                                comp_time = test_data[lib]['compilation_time']
                                bin_size = test_data[lib]['binary_size']
                                
                                self.statistics[num_types][build_type][test_name][lib] = {
                                    'compilation_time': comp_time,
                                    'binary_size': bin_size
                                }
        else:
            # Initialize statistics structure for regular mode
            for build_type in self.build_types:
                self.statistics[build_type] = {}
                
                # Get test names from first run
                if self.all_runs and build_type in self.all_runs[0]:
                    for test_name in self.all_runs[0][build_type].keys():
                        self.statistics[build_type][test_name] = {}
                        
                        for lib in ['stl', 'eastl']:
                            self.statistics[build_type][test_name][lib] = {
                                'compilation_time': {'values': [], 'mean': 0, 'median': 0, 'std': 0, 'min': 0, 'max': 0},
                                'binary_size': {'values': [], 'mean': 0, 'median': 0, 'std': 0, 'min': 0, 'max': 0}
                            }
            
            # Collect all values
            for run_data in self.all_runs:
                for build_type in self.build_types:
                    if build_type not in run_data:
                        continue
                        
                    for test_name, test_data in run_data[build_type].items():
                        for lib in ['stl', 'eastl']:
                            if lib in test_data and test_data[lib].get('compilation_time') is not None:
                                comp_time = test_data[lib]['compilation_time']
                                bin_size = test_data[lib]['binary_size']
                                
                                self.statistics[build_type][test_name][lib]['compilation_time']['values'].append(comp_time)
                                self.statistics[build_type][test_name][lib]['binary_size']['values'].append(bin_size)
            
            # Calculate statistics
            for build_type in self.statistics:
                for test_name in self.statistics[build_type]:
                    for lib in ['stl', 'eastl']:
                        for metric in ['compilation_time', 'binary_size']:
                            values = self.statistics[build_type][test_name][lib][metric]['values']
                            if values:
                                self.statistics[build_type][test_name][lib][metric].update({
                                    'mean': statistics.mean(values),
                                    'median': statistics.median(values),
                                    'std': statistics.stdev(values) if len(values) > 1 else 0,
                                    'min': min(values),
                                    'max': max(values)
                                })
    
    def generate_graphs(self):
        """Generate compilation time line graphs"""
        print("Generating graphs...")
        
        timestamp = datetime.now().strftime("%Y%m%d_%H%M%S")
        
        if self.num_types_mode:
            self._plot_num_types_comparison(timestamp)
        else:
            # Only compilation time line graphs
            self._plot_compilation_time_comparison(timestamp)
        
        print(f"Graphs saved to {self.output_dir}/")
    
    def _plot_compilation_time_comparison(self, timestamp):
        """Plot compilation time comparison as line graphs showing progression across runs"""
        fig, axes = plt.subplots(1, len(self.build_types), figsize=(10*len(self.build_types), 6))
        if len(self.build_types) == 1:
            axes = [axes]
        
        for i, build_type in enumerate(self.build_types):
            ax = axes[i]
            
            # Get data for this build type
            test_names = list(self.statistics[build_type].keys())
            
            for test_name in test_names:
                stl_values = self.statistics[build_type][test_name]['stl']['compilation_time']['values']
                eastl_values = self.statistics[build_type][test_name]['eastl']['compilation_time']['values']
                
                # X axis: run numbers (1, 2, 3, ...)
                run_numbers = list(range(1, len(stl_values) + 1))
                
                # Plot lines for STL and EASTL
                ax.plot(run_numbers, stl_values, 'o-', label='STL', 
                       color=self.colors['stl'], linewidth=2, markersize=6)
                ax.plot(run_numbers, eastl_values, 's-', label='EASTL', 
                       color=self.colors['eastl'], linewidth=2, markersize=6)
                

            
            ax.set_xlabel('Compilation Run Number')
            ax.set_ylabel('Compilation Time (seconds)')
            ax.set_title(f'Compilation Time Across Runs - {build_type}')
            ax.legend()
            ax.grid(True, alpha=0.3)
            
            # Set integer ticks for x-axis
            ax.set_xticks(run_numbers)
            
            # Add some padding to y-axis
            y_min, y_max = ax.get_ylim()
            ax.set_ylim(y_min * 0.95, y_max * 1.05)
        
        plt.tight_layout()
        plt.savefig(self.output_dir / f'compilation_time_comparison_{timestamp}.png', dpi=300, bbox_inches='tight')
        plt.close()
    
    def _plot_num_types_comparison(self, timestamp):
        """Plot compilation time vs NUM_TYPES"""
        fig, axes = plt.subplots(1, len(self.build_types), figsize=(10*len(self.build_types), 6))
        if len(self.build_types) == 1:
            axes = [axes]
        
        for i, build_type in enumerate(self.build_types):
            ax = axes[i]
            
            # Extract data for this build type
            num_types_sorted = sorted(self.num_types_values)
            stl_times = []
            eastl_times = []
            
            for num_types in num_types_sorted:
                if num_types in self.statistics and build_type in self.statistics[num_types]:
                    # Assuming we have a single test (compilation_benchmark_test)
                    test_name = list(self.statistics[num_types][build_type].keys())[0]
                    test_data = self.statistics[num_types][build_type][test_name]
                    
                    stl_time = test_data.get('stl', {}).get('compilation_time', 0)
                    eastl_time = test_data.get('eastl', {}).get('compilation_time', 0)
                    
                    stl_times.append(stl_time)
                    eastl_times.append(eastl_time)
                else:
                    stl_times.append(0)
                    eastl_times.append(0)
            
            # Plot lines for STL and EASTL
            ax.plot(num_types_sorted, stl_times, 'o-', label='STL', 
                   color=self.colors['stl'], linewidth=2, markersize=6)
            ax.plot(num_types_sorted, eastl_times, 's-', label='EASTL', 
                   color=self.colors['eastl'], linewidth=2, markersize=6)
            
            ax.set_xlabel('Number of Types')
            ax.set_ylabel('Compilation Time (seconds)')
            ax.set_title(f'Compilation Time vs NUM_TYPES - {build_type}')
            ax.legend()
            ax.grid(True, alpha=0.3)
            
            # Set x-axis ticks to NUM_TYPES values
            ax.set_xticks(num_types_sorted)
            
            # Add some padding to y-axis
            y_min, y_max = ax.get_ylim()
            ax.set_ylim(y_min * 0.95, y_max * 1.05)
        
        plt.tight_layout()
        plt.savefig(self.output_dir / f'num_types_comparison_{timestamp}.png', dpi=300, bbox_inches='tight')
        plt.close()

    def save_statistics(self):
        """Save detailed statistics to JSON file"""
        timestamp = datetime.now().strftime("%Y%m%d_%H%M%S")
        
        # Save raw data
        raw_data = {
            'metadata': {
                'num_runs': self.num_runs,
                'build_types': self.build_types,
                'timestamp': timestamp
            },
            'all_runs': self.all_runs,
            'statistics': self.statistics
        }
        
        filename = self.output_dir / f'multi_benchmark_data_{timestamp}.json'
        with open(filename, 'w') as f:
            json.dump(raw_data, f, indent=2)
        
        print(f"Detailed statistics saved to: {filename}")
        
        # Save human-readable summary
        self._save_summary(timestamp)
    
    def _save_summary(self, timestamp):
        """Save human-readable summary"""
        filename = self.output_dir / f'multi_benchmark_summary_{timestamp}.txt'
        
        with open(filename, 'w') as f:
            f.write(f"Multi-Run STL vs EASTL Benchmark Results\n")
            f.write(f"{'='*50}\n\n")
            
            if self.num_types_mode:
                f.write(f"Mode: NUM_TYPES comparison\n")
                f.write(f"NUM_TYPES values: {self.num_types_values}\n")
                f.write(f"Build types: {', '.join(self.build_types)}\n")
                f.write(f"Timestamp: {timestamp}\n\n")
                
                for build_type in self.build_types:
                    f.write(f"BUILD TYPE: {build_type.upper()}\n")
                    f.write(f"{'='*(len(build_type) + 12)}\n\n")
                    
                    f.write(f"{'NUM_TYPES':<10} {'STL Time':<12} {'EASTL Time':<12} {'STL/EASTL Ratio':<15} {'STL Size (KB)':<15} {'EASTL Size (KB)':<15}\n")
                    f.write(f"{'-'*10} {'-'*12} {'-'*12} {'-'*15} {'-'*15} {'-'*15}\n")
                    
                    for num_types in sorted(self.num_types_values):
                        if num_types in self.statistics and build_type in self.statistics[num_types]:
                            # Get first (and likely only) test name
                            test_name = list(self.statistics[num_types][build_type].keys())[0]
                            test_data = self.statistics[num_types][build_type][test_name]
                            
                            stl_time = test_data.get('stl', {}).get('compilation_time', 0)
                            eastl_time = test_data.get('eastl', {}).get('compilation_time', 0)
                            stl_size = test_data.get('stl', {}).get('binary_size', 0) / 1024
                            eastl_size = test_data.get('eastl', {}).get('binary_size', 0) / 1024
                            
                            ratio = stl_time / eastl_time if eastl_time > 0 else 0
                            
                            f.write(f"{num_types:<10} {stl_time:<12.2f} {eastl_time:<12.2f} {ratio:<15.2f} {stl_size:<15.2f} {eastl_size:<15.2f}\n")
                    
                    f.write("\n")
            else:
                f.write(f"Number of runs: {self.num_runs}\n")
                f.write(f"Build types: {', '.join(self.build_types)}\n")
                f.write(f"Timestamp: {timestamp}\n\n")
                
                for build_type in self.build_types:
                    f.write(f"BUILD TYPE: {build_type.upper()}\n")
                    f.write(f"{'='*(len(build_type) + 12)}\n\n")
                    
                    for test_name in self.statistics[build_type]:
                        f.write(f"{test_name.upper().replace('_', ' ')}\n")
                        f.write(f"{'-'*len(test_name)}\n")
                        
                        # Compilation time statistics
                        stl_comp = self.statistics[build_type][test_name]['stl']['compilation_time']
                        eastl_comp = self.statistics[build_type][test_name]['eastl']['compilation_time']
                        
                        f.write(f"Compilation Time (seconds):\n")
                        f.write(f"  STL:   Mean={stl_comp['mean']:.3f}, Std={stl_comp['std']:.3f}, Range=[{stl_comp['min']:.3f}, {stl_comp['max']:.3f}]\n")
                        f.write(f"  EASTL: Mean={eastl_comp['mean']:.3f}, Std={eastl_comp['std']:.3f}, Range=[{eastl_comp['min']:.3f}, {eastl_comp['max']:.3f}]\n")
                        
                        if eastl_comp['mean'] > 0:
                            ratio = stl_comp['mean'] / eastl_comp['mean']
                            f.write(f"  Ratio: {ratio:.2f}x ({'STL faster' if ratio < 1 else 'EASTL faster'})\n\n")
                        
                        # Binary size statistics
                        stl_size = self.statistics[build_type][test_name]['stl']['binary_size']
                        eastl_size = self.statistics[build_type][test_name]['eastl']['binary_size']
                        
                        f.write(f"Binary Size (KB):\n")
                        f.write(f"  STL:   Mean={stl_size['mean']/1024:.2f}, Std={stl_size['std']/1024:.2f}, Range=[{stl_size['min']/1024:.2f}, {stl_size['max']/1024:.2f}]\n")
                        f.write(f"  EASTL: Mean={eastl_size['mean']/1024:.2f}, Std={eastl_size['std']/1024:.2f}, Range=[{eastl_size['min']/1024:.2f}, {eastl_size['max']/1024:.2f}]\n")
                        
                        if eastl_size['mean'] > 0:
                            ratio = stl_size['mean'] / eastl_size['mean']
                            f.write(f"  Ratio: {ratio:.2f}x ({'STL smaller' if ratio < 1 else 'EASTL smaller'})\n\n")
                        
                        f.write("\n")
        
        print(f"Summary saved to: {filename}")

def main():
    parser = argparse.ArgumentParser(description="Multi-run STL vs EASTL Benchmark with Graph Generation")
    parser.add_argument("--runs", type=int, default=5, help="Number of benchmark runs (default: 5)")
    parser.add_argument("--build-type", choices=["Debug", "Release", "RelWithDebInfo", "MinSizeRel"],
                       default=None, help="Single CMake build type to test (default: both Debug and Release)")
    parser.add_argument("--debug-only", action="store_true", help="Run only Debug build")
    parser.add_argument("--release-only", action="store_true", help="Run only Release build")
    parser.add_argument("--output-dir", default="multi_results", help="Output directory for results and graphs")
    parser.add_argument("--num-types-mode", action="store_true", help="Run NUM_TYPES comparison mode (25 to 150 with step 25)")
    
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
    
    # Check if required packages are available
    try:
        import matplotlib.pyplot as plt
        import numpy as np
    except ImportError as e:
        print(f"Error: Required package not found: {e}")
        print("Please install required packages: pip install matplotlib numpy")
        return 1
    
    runner = MultiBenchmarkRunner(num_runs=args.runs, build_types=build_types, output_dir=args.output_dir, num_types_mode=args.num_types_mode)
    
    if runner.run_multiple_benchmarks():
        runner.calculate_statistics()
        runner.generate_graphs()
        runner.save_statistics()
        print(f"\nMulti-run benchmark completed successfully!")
        print(f"Results and graphs saved to: {runner.output_dir}/")
    else:
        print("Multi-run benchmark failed!")
        return 1
    
    return 0

if __name__ == "__main__":
    exit(main())