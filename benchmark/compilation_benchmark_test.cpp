#include <cstdio>
#include <cstdlib>
#include <ctime>

// Number of types to instantiate (can be defined at compile time)
#ifndef NUM_TYPES
#define NUM_TYPES 100
#endif

#ifdef USE_STL
#include <vector>
#include <string>
#include <list>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <deque>
#include <queue>
#include <stack>
#include <algorithm>
using namespace std;
#define VECTOR_TYPE vector
#define STRING_TYPE string
#define LIST_TYPE list
#define MAP_TYPE map
#define SET_TYPE set
#define UNORDERED_MAP_TYPE unordered_map
#define UNORDERED_SET_TYPE unordered_set
#define DEQUE_TYPE deque
#define QUEUE_TYPE queue
#define STACK_TYPE stack
#define NAMESPACE_PREFIX std
#elif USE_EASTL
#include <EASTL/vector.h>
#include <EASTL/string.h>
#include <EASTL/list.h>
#include <EASTL/map.h>
#include <EASTL/set.h>
#include <EASTL/hash_map.h>
#include <EASTL/hash_set.h>
#include <EASTL/deque.h>
#include <EASTL/queue.h>
#include <EASTL/stack.h>
#include <EASTL/algorithm.h>
#include <EASTL/sort.h>
using namespace eastl;
#define VECTOR_TYPE vector
#define STRING_TYPE string
#define LIST_TYPE list
#define MAP_TYPE map
#define SET_TYPE set
#define UNORDERED_MAP_TYPE hash_map
#define UNORDERED_SET_TYPE hash_set
#define DEQUE_TYPE deque
#define QUEUE_TYPE queue
#define STACK_TYPE stack
#define NAMESPACE_PREFIX eastl
#endif

// Include test types
#include "test_types_randomized.inc"

// Hash functions for custom types (needed for unordered containers)
#ifdef USE_STL
namespace std {
    // Generic hash for all types
    #define DEFINE_HASH_FOR_TYPE(N) \
    template<> struct hash<TestType##N> { \
        size_t operator()(const TestType##N& t) const { return hash<int>{}(t.id); } \
    };
    
    // Define hash for types 1-10
    DEFINE_HASH_FOR_TYPE(1)
    DEFINE_HASH_FOR_TYPE(2)
    DEFINE_HASH_FOR_TYPE(3)
    DEFINE_HASH_FOR_TYPE(4)
    DEFINE_HASH_FOR_TYPE(5)
    DEFINE_HASH_FOR_TYPE(6)
    DEFINE_HASH_FOR_TYPE(7)
    DEFINE_HASH_FOR_TYPE(8)
    DEFINE_HASH_FOR_TYPE(9)
    DEFINE_HASH_FOR_TYPE(10)
    
    // Define hash functions for types 11 to NUM_TYPES
    #if NUM_TYPES >= 11
    DEFINE_HASH_FOR_TYPE(11)
    #endif
    #if NUM_TYPES >= 12
    DEFINE_HASH_FOR_TYPE(12)
    #endif
    #if NUM_TYPES >= 13
    DEFINE_HASH_FOR_TYPE(13)
    #endif
    #if NUM_TYPES >= 14
    DEFINE_HASH_FOR_TYPE(14)
    #endif
    #if NUM_TYPES >= 15
    DEFINE_HASH_FOR_TYPE(15)
    #endif
    #if NUM_TYPES >= 16
    DEFINE_HASH_FOR_TYPE(16)
    #endif
    #if NUM_TYPES >= 17
    DEFINE_HASH_FOR_TYPE(17)
    #endif
    #if NUM_TYPES >= 18
    DEFINE_HASH_FOR_TYPE(18)
    #endif
    #if NUM_TYPES >= 19
    DEFINE_HASH_FOR_TYPE(19)
    #endif
    #if NUM_TYPES >= 20
    DEFINE_HASH_FOR_TYPE(20)
    #endif
    #if NUM_TYPES >= 21
    DEFINE_HASH_FOR_TYPE(21)
    #endif
    #if NUM_TYPES >= 22
    DEFINE_HASH_FOR_TYPE(22)
    #endif
    #if NUM_TYPES >= 23
    DEFINE_HASH_FOR_TYPE(23)
    #endif
    #if NUM_TYPES >= 24
    DEFINE_HASH_FOR_TYPE(24)
    #endif
    #if NUM_TYPES >= 25
    DEFINE_HASH_FOR_TYPE(25)
    #endif
    #if NUM_TYPES >= 26
    DEFINE_HASH_FOR_TYPE(26)
    #endif
    #if NUM_TYPES >= 27
    DEFINE_HASH_FOR_TYPE(27)
    #endif
    #if NUM_TYPES >= 28
    DEFINE_HASH_FOR_TYPE(28)
    #endif
    #if NUM_TYPES >= 29
    DEFINE_HASH_FOR_TYPE(29)
    #endif
    #if NUM_TYPES >= 30
    DEFINE_HASH_FOR_TYPE(30)
    #endif
    #if NUM_TYPES >= 31
    DEFINE_HASH_FOR_TYPE(31)
    #endif
    #if NUM_TYPES >= 32
    DEFINE_HASH_FOR_TYPE(32)
    #endif
    #if NUM_TYPES >= 33
    DEFINE_HASH_FOR_TYPE(33)
    #endif
    #if NUM_TYPES >= 34
    DEFINE_HASH_FOR_TYPE(34)
    #endif
    #if NUM_TYPES >= 35
    DEFINE_HASH_FOR_TYPE(35)
    #endif
    #if NUM_TYPES >= 36
    DEFINE_HASH_FOR_TYPE(36)
    #endif
    #if NUM_TYPES >= 37
    DEFINE_HASH_FOR_TYPE(37)
    #endif
    #if NUM_TYPES >= 38
    DEFINE_HASH_FOR_TYPE(38)
    #endif
    #if NUM_TYPES >= 39
    DEFINE_HASH_FOR_TYPE(39)
    #endif
    #if NUM_TYPES >= 40
    DEFINE_HASH_FOR_TYPE(40)
    #endif
    #if NUM_TYPES >= 41
    DEFINE_HASH_FOR_TYPE(41)
    #endif
    #if NUM_TYPES >= 42
    DEFINE_HASH_FOR_TYPE(42)
    #endif
    #if NUM_TYPES >= 43
    DEFINE_HASH_FOR_TYPE(43)
    #endif
    #if NUM_TYPES >= 44
    DEFINE_HASH_FOR_TYPE(44)
    #endif
    #if NUM_TYPES >= 45
    DEFINE_HASH_FOR_TYPE(45)
    #endif
    #if NUM_TYPES >= 46
    DEFINE_HASH_FOR_TYPE(46)
    #endif
    #if NUM_TYPES >= 47
    DEFINE_HASH_FOR_TYPE(47)
    #endif
    #if NUM_TYPES >= 48
    DEFINE_HASH_FOR_TYPE(48)
    #endif
    #if NUM_TYPES >= 49
    DEFINE_HASH_FOR_TYPE(49)
    #endif
    #if NUM_TYPES >= 50
    DEFINE_HASH_FOR_TYPE(50)
    #endif
    #if NUM_TYPES >= 51
    DEFINE_HASH_FOR_TYPE(51)
    #endif
    #if NUM_TYPES >= 52
    DEFINE_HASH_FOR_TYPE(52)
    #endif
    #if NUM_TYPES >= 53
    DEFINE_HASH_FOR_TYPE(53)
    #endif
    #if NUM_TYPES >= 54
    DEFINE_HASH_FOR_TYPE(54)
    #endif
    #if NUM_TYPES >= 55
    DEFINE_HASH_FOR_TYPE(55)
    #endif
    #if NUM_TYPES >= 56
    DEFINE_HASH_FOR_TYPE(56)
    #endif
    #if NUM_TYPES >= 57
    DEFINE_HASH_FOR_TYPE(57)
    #endif
    #if NUM_TYPES >= 58
    DEFINE_HASH_FOR_TYPE(58)
    #endif
    #if NUM_TYPES >= 59
    DEFINE_HASH_FOR_TYPE(59)
    #endif
    #if NUM_TYPES >= 60
    DEFINE_HASH_FOR_TYPE(60)
    #endif
    #if NUM_TYPES >= 61
    DEFINE_HASH_FOR_TYPE(61)
    #endif
    #if NUM_TYPES >= 62
    DEFINE_HASH_FOR_TYPE(62)
    #endif
    #if NUM_TYPES >= 63
    DEFINE_HASH_FOR_TYPE(63)
    #endif
    #if NUM_TYPES >= 64
    DEFINE_HASH_FOR_TYPE(64)
    #endif
    #if NUM_TYPES >= 65
    DEFINE_HASH_FOR_TYPE(65)
    #endif
    #if NUM_TYPES >= 66
    DEFINE_HASH_FOR_TYPE(66)
    #endif
    #if NUM_TYPES >= 67
    DEFINE_HASH_FOR_TYPE(67)
    #endif
    #if NUM_TYPES >= 68
    DEFINE_HASH_FOR_TYPE(68)
    #endif
    #if NUM_TYPES >= 69
    DEFINE_HASH_FOR_TYPE(69)
    #endif
    #if NUM_TYPES >= 70
    DEFINE_HASH_FOR_TYPE(70)
    #endif
    #if NUM_TYPES >= 71
    DEFINE_HASH_FOR_TYPE(71)
    #endif
    #if NUM_TYPES >= 72
    DEFINE_HASH_FOR_TYPE(72)
    #endif
    #if NUM_TYPES >= 73
    DEFINE_HASH_FOR_TYPE(73)
    #endif
    #if NUM_TYPES >= 74
    DEFINE_HASH_FOR_TYPE(74)
    #endif
    #if NUM_TYPES >= 75
    DEFINE_HASH_FOR_TYPE(75)
    #endif
    #if NUM_TYPES >= 76
    DEFINE_HASH_FOR_TYPE(76)
    #endif
    #if NUM_TYPES >= 77
    DEFINE_HASH_FOR_TYPE(77)
    #endif
    #if NUM_TYPES >= 78
    DEFINE_HASH_FOR_TYPE(78)
    #endif
    #if NUM_TYPES >= 79
    DEFINE_HASH_FOR_TYPE(79)
    #endif
    #if NUM_TYPES >= 80
    DEFINE_HASH_FOR_TYPE(80)
    #endif
    #if NUM_TYPES >= 81
    DEFINE_HASH_FOR_TYPE(81)
    #endif
    #if NUM_TYPES >= 82
    DEFINE_HASH_FOR_TYPE(82)
    #endif
    #if NUM_TYPES >= 83
    DEFINE_HASH_FOR_TYPE(83)
    #endif
    #if NUM_TYPES >= 84
    DEFINE_HASH_FOR_TYPE(84)
    #endif
    #if NUM_TYPES >= 85
    DEFINE_HASH_FOR_TYPE(85)
    #endif
    #if NUM_TYPES >= 86
    DEFINE_HASH_FOR_TYPE(86)
    #endif
    #if NUM_TYPES >= 87
    DEFINE_HASH_FOR_TYPE(87)
    #endif
    #if NUM_TYPES >= 88
    DEFINE_HASH_FOR_TYPE(88)
    #endif
    #if NUM_TYPES >= 89
    DEFINE_HASH_FOR_TYPE(89)
    #endif
    #if NUM_TYPES >= 90
    DEFINE_HASH_FOR_TYPE(90)
    #endif
    #if NUM_TYPES >= 91
    DEFINE_HASH_FOR_TYPE(91)
    #endif
    #if NUM_TYPES >= 92
    DEFINE_HASH_FOR_TYPE(92)
    #endif
    #if NUM_TYPES >= 93
    DEFINE_HASH_FOR_TYPE(93)
    #endif
    #if NUM_TYPES >= 94
    DEFINE_HASH_FOR_TYPE(94)
    #endif
    #if NUM_TYPES >= 95
    DEFINE_HASH_FOR_TYPE(95)
    #endif
    #if NUM_TYPES >= 96
    DEFINE_HASH_FOR_TYPE(96)
    #endif
    #if NUM_TYPES >= 97
    DEFINE_HASH_FOR_TYPE(97)
    #endif
    #if NUM_TYPES >= 98
    DEFINE_HASH_FOR_TYPE(98)
    #endif
    #if NUM_TYPES >= 99
    DEFINE_HASH_FOR_TYPE(99)
    #endif
    #if NUM_TYPES >= 100
    DEFINE_HASH_FOR_TYPE(100)
    #endif
    #if NUM_TYPES >= 101
    DEFINE_HASH_FOR_TYPE(101)
    #endif
    #if NUM_TYPES >= 102
    DEFINE_HASH_FOR_TYPE(102)
    #endif
    #if NUM_TYPES >= 103
    DEFINE_HASH_FOR_TYPE(103)
    #endif
    #if NUM_TYPES >= 104
    DEFINE_HASH_FOR_TYPE(104)
    #endif
    #if NUM_TYPES >= 105
    DEFINE_HASH_FOR_TYPE(105)
    #endif
    #if NUM_TYPES >= 106
    DEFINE_HASH_FOR_TYPE(106)
    #endif
    #if NUM_TYPES >= 107
    DEFINE_HASH_FOR_TYPE(107)
    #endif
    #if NUM_TYPES >= 108
    DEFINE_HASH_FOR_TYPE(108)
    #endif
    #if NUM_TYPES >= 109
    DEFINE_HASH_FOR_TYPE(109)
    #endif
    #if NUM_TYPES >= 110
    DEFINE_HASH_FOR_TYPE(110)
    #endif
    #if NUM_TYPES >= 111
    DEFINE_HASH_FOR_TYPE(111)
    #endif
    #if NUM_TYPES >= 112
    DEFINE_HASH_FOR_TYPE(112)
    #endif
    #if NUM_TYPES >= 113
    DEFINE_HASH_FOR_TYPE(113)
    #endif
    #if NUM_TYPES >= 114
    DEFINE_HASH_FOR_TYPE(114)
    #endif
    #if NUM_TYPES >= 115
    DEFINE_HASH_FOR_TYPE(115)
    #endif
    #if NUM_TYPES >= 116
    DEFINE_HASH_FOR_TYPE(116)
    #endif
    #if NUM_TYPES >= 117
    DEFINE_HASH_FOR_TYPE(117)
    #endif
    #if NUM_TYPES >= 118
    DEFINE_HASH_FOR_TYPE(118)
    #endif
    #if NUM_TYPES >= 119
    DEFINE_HASH_FOR_TYPE(119)
    #endif
    #if NUM_TYPES >= 120
    DEFINE_HASH_FOR_TYPE(120)
    #endif
    #if NUM_TYPES >= 121
    DEFINE_HASH_FOR_TYPE(121)
    #endif
    #if NUM_TYPES >= 122
    DEFINE_HASH_FOR_TYPE(122)
    #endif
    #if NUM_TYPES >= 123
    DEFINE_HASH_FOR_TYPE(123)
    #endif
    #if NUM_TYPES >= 124
    DEFINE_HASH_FOR_TYPE(124)
    #endif
    #if NUM_TYPES >= 125
    DEFINE_HASH_FOR_TYPE(125)
    #endif
    #if NUM_TYPES >= 126
    DEFINE_HASH_FOR_TYPE(126)
    #endif
    #if NUM_TYPES >= 127
    DEFINE_HASH_FOR_TYPE(127)
    #endif
    #if NUM_TYPES >= 128
    DEFINE_HASH_FOR_TYPE(128)
    #endif
    #if NUM_TYPES >= 129
    DEFINE_HASH_FOR_TYPE(129)
    #endif
    #if NUM_TYPES >= 130
    DEFINE_HASH_FOR_TYPE(130)
    #endif
    #if NUM_TYPES >= 131
    DEFINE_HASH_FOR_TYPE(131)
    #endif
    #if NUM_TYPES >= 132
    DEFINE_HASH_FOR_TYPE(132)
    #endif
    #if NUM_TYPES >= 133
    DEFINE_HASH_FOR_TYPE(133)
    #endif
    #if NUM_TYPES >= 134
    DEFINE_HASH_FOR_TYPE(134)
    #endif
    #if NUM_TYPES >= 135
    DEFINE_HASH_FOR_TYPE(135)
    #endif
    #if NUM_TYPES >= 136
    DEFINE_HASH_FOR_TYPE(136)
    #endif
    #if NUM_TYPES >= 137
    DEFINE_HASH_FOR_TYPE(137)
    #endif
    #if NUM_TYPES >= 138
    DEFINE_HASH_FOR_TYPE(138)
    #endif
    #if NUM_TYPES >= 139
    DEFINE_HASH_FOR_TYPE(139)
    #endif
    #if NUM_TYPES >= 140
    DEFINE_HASH_FOR_TYPE(140)
    #endif
    #if NUM_TYPES >= 141
    DEFINE_HASH_FOR_TYPE(141)
    #endif
    #if NUM_TYPES >= 142
    DEFINE_HASH_FOR_TYPE(142)
    #endif
    #if NUM_TYPES >= 143
    DEFINE_HASH_FOR_TYPE(143)
    #endif
    #if NUM_TYPES >= 144
    DEFINE_HASH_FOR_TYPE(144)
    #endif
    #if NUM_TYPES >= 145
    DEFINE_HASH_FOR_TYPE(145)
    #endif
    #if NUM_TYPES >= 146
    DEFINE_HASH_FOR_TYPE(146)
    #endif
    #if NUM_TYPES >= 147
    DEFINE_HASH_FOR_TYPE(147)
    #endif
    #if NUM_TYPES >= 148
    DEFINE_HASH_FOR_TYPE(148)
    #endif
    #if NUM_TYPES >= 149
    DEFINE_HASH_FOR_TYPE(149)
    #endif
    #if NUM_TYPES >= 150
    DEFINE_HASH_FOR_TYPE(150)
    #endif
}
#elif USE_EASTL
// EASTL hash functions
namespace eastl {
    // Generic hash for all types
    #define DEFINE_EASTL_HASH_FOR_TYPE(N) \
    template<> struct hash<TestType##N> { \
        size_t operator()(const TestType##N& t) const { return eastl::hash<int>{}(t.id); } \
    };
    
    // Define hash for types 1-10
    DEFINE_EASTL_HASH_FOR_TYPE(1)
    DEFINE_EASTL_HASH_FOR_TYPE(2)
    DEFINE_EASTL_HASH_FOR_TYPE(3)
    DEFINE_EASTL_HASH_FOR_TYPE(4)
    DEFINE_EASTL_HASH_FOR_TYPE(5)
    DEFINE_EASTL_HASH_FOR_TYPE(6)
    DEFINE_EASTL_HASH_FOR_TYPE(7)
    DEFINE_EASTL_HASH_FOR_TYPE(8)
    DEFINE_EASTL_HASH_FOR_TYPE(9)
    DEFINE_EASTL_HASH_FOR_TYPE(10)
    
    // Define EASTL hash functions for types 11 to NUM_TYPES
    #if NUM_TYPES >= 11
    DEFINE_EASTL_HASH_FOR_TYPE(11)
    #endif
    #if NUM_TYPES >= 12
    DEFINE_EASTL_HASH_FOR_TYPE(12)
    #endif
    #if NUM_TYPES >= 13
    DEFINE_EASTL_HASH_FOR_TYPE(13)
    #endif
    #if NUM_TYPES >= 14
    DEFINE_EASTL_HASH_FOR_TYPE(14)
    #endif
    #if NUM_TYPES >= 15
    DEFINE_EASTL_HASH_FOR_TYPE(15)
    #endif
    #if NUM_TYPES >= 16
    DEFINE_EASTL_HASH_FOR_TYPE(16)
    #endif
    #if NUM_TYPES >= 17
    DEFINE_EASTL_HASH_FOR_TYPE(17)
    #endif
    #if NUM_TYPES >= 18
    DEFINE_EASTL_HASH_FOR_TYPE(18)
    #endif
    #if NUM_TYPES >= 19
    DEFINE_EASTL_HASH_FOR_TYPE(19)
    #endif
    #if NUM_TYPES >= 20
    DEFINE_EASTL_HASH_FOR_TYPE(20)
    #endif
    #if NUM_TYPES >= 21
    DEFINE_EASTL_HASH_FOR_TYPE(21)
    #endif
    #if NUM_TYPES >= 22
    DEFINE_EASTL_HASH_FOR_TYPE(22)
    #endif
    #if NUM_TYPES >= 23
    DEFINE_EASTL_HASH_FOR_TYPE(23)
    #endif
    #if NUM_TYPES >= 24
    DEFINE_EASTL_HASH_FOR_TYPE(24)
    #endif
    #if NUM_TYPES >= 25
    DEFINE_EASTL_HASH_FOR_TYPE(25)
    #endif
    #if NUM_TYPES >= 26
    DEFINE_EASTL_HASH_FOR_TYPE(26)
    #endif
    #if NUM_TYPES >= 27
    DEFINE_EASTL_HASH_FOR_TYPE(27)
    #endif
    #if NUM_TYPES >= 28
    DEFINE_EASTL_HASH_FOR_TYPE(28)
    #endif
    #if NUM_TYPES >= 29
    DEFINE_EASTL_HASH_FOR_TYPE(29)
    #endif
    #if NUM_TYPES >= 30
    DEFINE_EASTL_HASH_FOR_TYPE(30)
    #endif
    #if NUM_TYPES >= 31
    DEFINE_EASTL_HASH_FOR_TYPE(31)
    #endif
    #if NUM_TYPES >= 32
    DEFINE_EASTL_HASH_FOR_TYPE(32)
    #endif
    #if NUM_TYPES >= 33
    DEFINE_EASTL_HASH_FOR_TYPE(33)
    #endif
    #if NUM_TYPES >= 34
    DEFINE_EASTL_HASH_FOR_TYPE(34)
    #endif
    #if NUM_TYPES >= 35
    DEFINE_EASTL_HASH_FOR_TYPE(35)
    #endif
    #if NUM_TYPES >= 36
    DEFINE_EASTL_HASH_FOR_TYPE(36)
    #endif
    #if NUM_TYPES >= 37
    DEFINE_EASTL_HASH_FOR_TYPE(37)
    #endif
    #if NUM_TYPES >= 38
    DEFINE_EASTL_HASH_FOR_TYPE(38)
    #endif
    #if NUM_TYPES >= 39
    DEFINE_EASTL_HASH_FOR_TYPE(39)
    #endif
    #if NUM_TYPES >= 40
    DEFINE_EASTL_HASH_FOR_TYPE(40)
    #endif
    #if NUM_TYPES >= 41
    DEFINE_EASTL_HASH_FOR_TYPE(41)
    #endif
    #if NUM_TYPES >= 42
    DEFINE_EASTL_HASH_FOR_TYPE(42)
    #endif
    #if NUM_TYPES >= 43
    DEFINE_EASTL_HASH_FOR_TYPE(43)
    #endif
    #if NUM_TYPES >= 44
    DEFINE_EASTL_HASH_FOR_TYPE(44)
    #endif
    #if NUM_TYPES >= 45
    DEFINE_EASTL_HASH_FOR_TYPE(45)
    #endif
    #if NUM_TYPES >= 46
    DEFINE_EASTL_HASH_FOR_TYPE(46)
    #endif
    #if NUM_TYPES >= 47
    DEFINE_EASTL_HASH_FOR_TYPE(47)
    #endif
    #if NUM_TYPES >= 48
    DEFINE_EASTL_HASH_FOR_TYPE(48)
    #endif
    #if NUM_TYPES >= 49
    DEFINE_EASTL_HASH_FOR_TYPE(49)
    #endif
    #if NUM_TYPES >= 50
    DEFINE_EASTL_HASH_FOR_TYPE(50)
    #endif
    #if NUM_TYPES >= 51
    DEFINE_EASTL_HASH_FOR_TYPE(51)
    #endif
    #if NUM_TYPES >= 52
    DEFINE_EASTL_HASH_FOR_TYPE(52)
    #endif
    #if NUM_TYPES >= 53
    DEFINE_EASTL_HASH_FOR_TYPE(53)
    #endif
    #if NUM_TYPES >= 54
    DEFINE_EASTL_HASH_FOR_TYPE(54)
    #endif
    #if NUM_TYPES >= 55
    DEFINE_EASTL_HASH_FOR_TYPE(55)
    #endif
    #if NUM_TYPES >= 56
    DEFINE_EASTL_HASH_FOR_TYPE(56)
    #endif
    #if NUM_TYPES >= 57
    DEFINE_EASTL_HASH_FOR_TYPE(57)
    #endif
    #if NUM_TYPES >= 58
    DEFINE_EASTL_HASH_FOR_TYPE(58)
    #endif
    #if NUM_TYPES >= 59
    DEFINE_EASTL_HASH_FOR_TYPE(59)
    #endif
    #if NUM_TYPES >= 60
    DEFINE_EASTL_HASH_FOR_TYPE(60)
    #endif
    #if NUM_TYPES >= 61
    DEFINE_EASTL_HASH_FOR_TYPE(61)
    #endif
    #if NUM_TYPES >= 62
    DEFINE_EASTL_HASH_FOR_TYPE(62)
    #endif
    #if NUM_TYPES >= 63
    DEFINE_EASTL_HASH_FOR_TYPE(63)
    #endif
    #if NUM_TYPES >= 64
    DEFINE_EASTL_HASH_FOR_TYPE(64)
    #endif
    #if NUM_TYPES >= 65
    DEFINE_EASTL_HASH_FOR_TYPE(65)
    #endif
    #if NUM_TYPES >= 66
    DEFINE_EASTL_HASH_FOR_TYPE(66)
    #endif
    #if NUM_TYPES >= 67
    DEFINE_EASTL_HASH_FOR_TYPE(67)
    #endif
    #if NUM_TYPES >= 68
    DEFINE_EASTL_HASH_FOR_TYPE(68)
    #endif
    #if NUM_TYPES >= 69
    DEFINE_EASTL_HASH_FOR_TYPE(69)
    #endif
    #if NUM_TYPES >= 70
    DEFINE_EASTL_HASH_FOR_TYPE(70)
    #endif
    #if NUM_TYPES >= 71
    DEFINE_EASTL_HASH_FOR_TYPE(71)
    #endif
    #if NUM_TYPES >= 72
    DEFINE_EASTL_HASH_FOR_TYPE(72)
    #endif
    #if NUM_TYPES >= 73
    DEFINE_EASTL_HASH_FOR_TYPE(73)
    #endif
    #if NUM_TYPES >= 74
    DEFINE_EASTL_HASH_FOR_TYPE(74)
    #endif
    #if NUM_TYPES >= 75
    DEFINE_EASTL_HASH_FOR_TYPE(75)
    #endif
    #if NUM_TYPES >= 76
    DEFINE_EASTL_HASH_FOR_TYPE(76)
    #endif
    #if NUM_TYPES >= 77
    DEFINE_EASTL_HASH_FOR_TYPE(77)
    #endif
    #if NUM_TYPES >= 78
    DEFINE_EASTL_HASH_FOR_TYPE(78)
    #endif
    #if NUM_TYPES >= 79
    DEFINE_EASTL_HASH_FOR_TYPE(79)
    #endif
    #if NUM_TYPES >= 80
    DEFINE_EASTL_HASH_FOR_TYPE(80)
    #endif
    #if NUM_TYPES >= 81
    DEFINE_EASTL_HASH_FOR_TYPE(81)
    #endif
    #if NUM_TYPES >= 82
    DEFINE_EASTL_HASH_FOR_TYPE(82)
    #endif
    #if NUM_TYPES >= 83
    DEFINE_EASTL_HASH_FOR_TYPE(83)
    #endif
    #if NUM_TYPES >= 84
    DEFINE_EASTL_HASH_FOR_TYPE(84)
    #endif
    #if NUM_TYPES >= 85
    DEFINE_EASTL_HASH_FOR_TYPE(85)
    #endif
    #if NUM_TYPES >= 86
    DEFINE_EASTL_HASH_FOR_TYPE(86)
    #endif
    #if NUM_TYPES >= 87
    DEFINE_EASTL_HASH_FOR_TYPE(87)
    #endif
    #if NUM_TYPES >= 88
    DEFINE_EASTL_HASH_FOR_TYPE(88)
    #endif
    #if NUM_TYPES >= 89
    DEFINE_EASTL_HASH_FOR_TYPE(89)
    #endif
    #if NUM_TYPES >= 90
    DEFINE_EASTL_HASH_FOR_TYPE(90)
    #endif
    #if NUM_TYPES >= 91
    DEFINE_EASTL_HASH_FOR_TYPE(91)
    #endif
    #if NUM_TYPES >= 92
    DEFINE_EASTL_HASH_FOR_TYPE(92)
    #endif
    #if NUM_TYPES >= 93
    DEFINE_EASTL_HASH_FOR_TYPE(93)
    #endif
    #if NUM_TYPES >= 94
    DEFINE_EASTL_HASH_FOR_TYPE(94)
    #endif
    #if NUM_TYPES >= 95
    DEFINE_EASTL_HASH_FOR_TYPE(95)
    #endif
    #if NUM_TYPES >= 96
    DEFINE_EASTL_HASH_FOR_TYPE(96)
    #endif
    #if NUM_TYPES >= 97
    DEFINE_EASTL_HASH_FOR_TYPE(97)
    #endif
    #if NUM_TYPES >= 98
    DEFINE_EASTL_HASH_FOR_TYPE(98)
    #endif
    #if NUM_TYPES >= 99
    DEFINE_EASTL_HASH_FOR_TYPE(99)
    #endif
    #if NUM_TYPES >= 100
    DEFINE_EASTL_HASH_FOR_TYPE(100)
    #endif
    #if NUM_TYPES >= 101
    DEFINE_EASTL_HASH_FOR_TYPE(101)
    #endif
    #if NUM_TYPES >= 102
    DEFINE_EASTL_HASH_FOR_TYPE(102)
    #endif
    #if NUM_TYPES >= 103
    DEFINE_EASTL_HASH_FOR_TYPE(103)
    #endif
    #if NUM_TYPES >= 104
    DEFINE_EASTL_HASH_FOR_TYPE(104)
    #endif
    #if NUM_TYPES >= 105
    DEFINE_EASTL_HASH_FOR_TYPE(105)
    #endif
    #if NUM_TYPES >= 106
    DEFINE_EASTL_HASH_FOR_TYPE(106)
    #endif
    #if NUM_TYPES >= 107
    DEFINE_EASTL_HASH_FOR_TYPE(107)
    #endif
    #if NUM_TYPES >= 108
    DEFINE_EASTL_HASH_FOR_TYPE(108)
    #endif
    #if NUM_TYPES >= 109
    DEFINE_EASTL_HASH_FOR_TYPE(109)
    #endif
    #if NUM_TYPES >= 110
    DEFINE_EASTL_HASH_FOR_TYPE(110)
    #endif
    #if NUM_TYPES >= 111
    DEFINE_EASTL_HASH_FOR_TYPE(111)
    #endif
    #if NUM_TYPES >= 112
    DEFINE_EASTL_HASH_FOR_TYPE(112)
    #endif
    #if NUM_TYPES >= 113
    DEFINE_EASTL_HASH_FOR_TYPE(113)
    #endif
    #if NUM_TYPES >= 114
    DEFINE_EASTL_HASH_FOR_TYPE(114)
    #endif
    #if NUM_TYPES >= 115
    DEFINE_EASTL_HASH_FOR_TYPE(115)
    #endif
    #if NUM_TYPES >= 116
    DEFINE_EASTL_HASH_FOR_TYPE(116)
    #endif
    #if NUM_TYPES >= 117
    DEFINE_EASTL_HASH_FOR_TYPE(117)
    #endif
    #if NUM_TYPES >= 118
    DEFINE_EASTL_HASH_FOR_TYPE(118)
    #endif
    #if NUM_TYPES >= 119
    DEFINE_EASTL_HASH_FOR_TYPE(119)
    #endif
    #if NUM_TYPES >= 120
    DEFINE_EASTL_HASH_FOR_TYPE(120)
    #endif
    #if NUM_TYPES >= 121
    DEFINE_EASTL_HASH_FOR_TYPE(121)
    #endif
    #if NUM_TYPES >= 122
    DEFINE_EASTL_HASH_FOR_TYPE(122)
    #endif
    #if NUM_TYPES >= 123
    DEFINE_EASTL_HASH_FOR_TYPE(123)
    #endif
    #if NUM_TYPES >= 124
    DEFINE_EASTL_HASH_FOR_TYPE(124)
    #endif
    #if NUM_TYPES >= 125
    DEFINE_EASTL_HASH_FOR_TYPE(125)
    #endif
    #if NUM_TYPES >= 126
    DEFINE_EASTL_HASH_FOR_TYPE(126)
    #endif
    #if NUM_TYPES >= 127
    DEFINE_EASTL_HASH_FOR_TYPE(127)
    #endif
    #if NUM_TYPES >= 128
    DEFINE_EASTL_HASH_FOR_TYPE(128)
    #endif
    #if NUM_TYPES >= 129
    DEFINE_EASTL_HASH_FOR_TYPE(129)
    #endif
    #if NUM_TYPES >= 130
    DEFINE_EASTL_HASH_FOR_TYPE(130)
    #endif
    #if NUM_TYPES >= 131
    DEFINE_EASTL_HASH_FOR_TYPE(131)
    #endif
    #if NUM_TYPES >= 132
    DEFINE_EASTL_HASH_FOR_TYPE(132)
    #endif
    #if NUM_TYPES >= 133
    DEFINE_EASTL_HASH_FOR_TYPE(133)
    #endif
    #if NUM_TYPES >= 134
    DEFINE_EASTL_HASH_FOR_TYPE(134)
    #endif
    #if NUM_TYPES >= 135
    DEFINE_EASTL_HASH_FOR_TYPE(135)
    #endif
    #if NUM_TYPES >= 136
    DEFINE_EASTL_HASH_FOR_TYPE(136)
    #endif
    #if NUM_TYPES >= 137
    DEFINE_EASTL_HASH_FOR_TYPE(137)
    #endif
    #if NUM_TYPES >= 138
    DEFINE_EASTL_HASH_FOR_TYPE(138)
    #endif
    #if NUM_TYPES >= 139
    DEFINE_EASTL_HASH_FOR_TYPE(139)
    #endif
    #if NUM_TYPES >= 140
    DEFINE_EASTL_HASH_FOR_TYPE(140)
    #endif
    #if NUM_TYPES >= 141
    DEFINE_EASTL_HASH_FOR_TYPE(141)
    #endif
    #if NUM_TYPES >= 142
    DEFINE_EASTL_HASH_FOR_TYPE(142)
    #endif
    #if NUM_TYPES >= 143
    DEFINE_EASTL_HASH_FOR_TYPE(143)
    #endif
    #if NUM_TYPES >= 144
    DEFINE_EASTL_HASH_FOR_TYPE(144)
    #endif
    #if NUM_TYPES >= 145
    DEFINE_EASTL_HASH_FOR_TYPE(145)
    #endif
    #if NUM_TYPES >= 146
    DEFINE_EASTL_HASH_FOR_TYPE(146)
    #endif
    #if NUM_TYPES >= 147
    DEFINE_EASTL_HASH_FOR_TYPE(147)
    #endif
    #if NUM_TYPES >= 148
    DEFINE_EASTL_HASH_FOR_TYPE(148)
    #endif
    #if NUM_TYPES >= 149
    DEFINE_EASTL_HASH_FOR_TYPE(149)
    #endif
    #if NUM_TYPES >= 150
    DEFINE_EASTL_HASH_FOR_TYPE(150)
    #endif
}
#endif

// Macro to force instantiation and prevent optimization
#define FORCE_INSTANTIATION(container) \
    do { \
        volatile void* ptr = &container; \
        (void)ptr; \
        if (!container.empty()) { \
            volatile void* it_ptr = (void*)&(*container.begin()); \
            (void)it_ptr; \
        } \
    } while(0)

// Template function to force container instantiations
template<typename T>
void force_container_instantiations() {
#ifdef USE_STL
    // Vector instantiations with random elements and address printing
    std::vector<T> vec;
    for(int i = 0; i < rand(); ++i) {
        vec.push_back(T());
    }
    for(auto it = vec.begin(); it != vec.end(); ++it) {
        printf("Vector element address: %p\n", (void*)&(*it));
    }
    FORCE_INSTANTIATION(vec);
    
    // Map instantiations with multiple random insertions
    std::map<T, void*> map_ti;
    std::map<void*, T> map_it;
    for(int i = 0; i < rand(); ++i) {
        map_ti[T()] = (void*)(rand());
        map_it[(void*)(rand())] = T();
    }
    for(auto it = map_ti.begin(); it != map_ti.end(); ++it) {
        printf("Map key address: %p, value: %p\n", (void*)&(it->first), it->second);
    }
    for(auto it = map_it.begin(); it != map_it.end(); ++it) {
        printf("Map key: %p, value address: %p\n", it->first, (void*)&(it->second));
    }
    FORCE_INSTANTIATION(map_ti);
    FORCE_INSTANTIATION(map_it);
    
    // Set instantiations with random elements and address printing
    std::set<T> set_t;
    for(int i = 0; i < rand(); ++i) {
        set_t.insert(T());
    }
    for(auto it = set_t.begin(); it != set_t.end(); ++it) {
        printf("Set element address: %p\n", (void*)&(*it));
    }
    FORCE_INSTANTIATION(set_t);
    
    // Unordered map instantiations with multiple random insertions
    std::unordered_map<T, void*> umap_ti;
    std::unordered_map<void*, T> umap_it;
    for(int i = 0; i < rand(); ++i) {
        umap_ti[T()] = (void*)(rand());
        umap_it[(void*)(rand())] = T();
    }
    for(auto it = umap_ti.begin(); it != umap_ti.end(); ++it) {
        printf("Unordered map key address: %p, value: %p\n", (void*)&(it->first), it->second);
    }
    for(auto it = umap_it.begin(); it != umap_it.end(); ++it) {
        printf("Unordered map key: %p, value address: %p\n", it->first, (void*)&(it->second));
    }
    FORCE_INSTANTIATION(umap_ti);
    FORCE_INSTANTIATION(umap_it);
    
    // Unordered set instantiations with random elements and address printing
    std::unordered_set<T> uset_t;
    for(int i = 0; i < rand(); ++i) {
        uset_t.insert(T());
    }
    for(auto it = uset_t.begin(); it != uset_t.end(); ++it) {
        printf("Unordered set element address: %p\n", (void*)&(*it));
    }
    FORCE_INSTANTIATION(uset_t);
    
    // List instantiations with random elements and address printing
    std::list<T> list_t;
    for(int i = 0; i < rand(); ++i) {
        list_t.push_back(T());
    }
    for(auto it = list_t.begin(); it != list_t.end(); ++it) {
        printf("List element address: %p\n", (void*)&(*it));
    }
    FORCE_INSTANTIATION(list_t);
    
    // Deque instantiations with random elements and address printing
    std::deque<T> deque_t;
    for(int i = 0; i < rand(); ++i) {
        deque_t.push_back(T());
    }
    for(auto it = deque_t.begin(); it != deque_t.end(); ++it) {
        printf("Deque element address: %p\n", (void*)&(*it));
    }
    FORCE_INSTANTIATION(deque_t);
    
    // Queue instantiations (adapter) with random elements
    std::queue<T> queue_t;
    for(int i = 0; i < rand(); ++i) {
        queue_t.push(T());
    }
    printf("Queue size: %zu, front address: %p\n", queue_t.size(), (void*)&queue_t.front());
    volatile void* queue_ref = &queue_t;
    (void)queue_ref;
    
    // Stack instantiations (adapter) with random elements
    std::stack<T> stack_t;
    for(int i = 0; i < rand(); ++i) {
        stack_t.push(T());
    }
    printf("Stack size: %zu, top address: %p\n", stack_t.size(), (void*)&stack_t.top());
    volatile void* stack_ref = &stack_t;
    (void)stack_ref;
#elif USE_EASTL
    // Vector instantiations with random elements and address printing
    eastl::vector<T> vec;
    for(int i = 0; i < rand(); ++i) {
        vec.push_back(T());
    }
    for(auto it = vec.begin(); it != vec.end(); ++it) {
        printf("Vector element address: %p\n", (void*)&(*it));
    }
    FORCE_INSTANTIATION(vec);
    
    // Map instantiations with multiple random insertions
    eastl::map<T, void*> map_ti;
    eastl::map<void*, T> map_it;
    for(int i = 0; i < rand(); ++i) {
        map_ti[T()] = (void*)(rand());
        map_it[(void*)(rand())] = T();
    }
    for(auto it = map_ti.begin(); it != map_ti.end(); ++it) {
        printf("Map key address: %p, value: %p\n", (void*)&(it->first), it->second);
    }
    for(auto it = map_it.begin(); it != map_it.end(); ++it) {
        printf("Map key: %p, value address: %p\n", it->first, (void*)&(it->second));
    }
    FORCE_INSTANTIATION(map_ti);
    FORCE_INSTANTIATION(map_it);
    
    // Set instantiations with random elements and address printing
    eastl::set<T> set_t;
    for(int i = 0; i < rand(); ++i) {
        set_t.insert(T());
    }
    for(auto it = set_t.begin(); it != set_t.end(); ++it) {
        printf("Set element address: %p\n", (void*)&(*it));
    }
    FORCE_INSTANTIATION(set_t);
    
    // Unordered map instantiations with multiple random insertions
    eastl::hash_map<T, void*> umap_ti;
    eastl::hash_map<void*, T> umap_it;
    for(int i = 0; i < rand(); ++i) {
        umap_ti[T()] = (void*)(rand());
        umap_it[(void*)(rand())] = T();
    }
    for(auto it = umap_ti.begin(); it != umap_ti.end(); ++it) {
        printf("Unordered map key address: %p, value: %p\n", (void*)&(it->first), it->second);
    }
    for(auto it = umap_it.begin(); it != umap_it.end(); ++it) {
        printf("Unordered map key: %p, value address: %p\n", it->first, (void*)&(it->second));
    }
    FORCE_INSTANTIATION(umap_ti);
    FORCE_INSTANTIATION(umap_it);
    
    // Unordered set instantiations with random elements and address printing
    eastl::hash_set<T> uset_t;
    for(int i = 0; i < rand(); ++i) {
        uset_t.insert(T());
    }
    for(auto it = uset_t.begin(); it != uset_t.end(); ++it) {
        printf("Unordered set element address: %p\n", (void*)&(*it));
    }
    FORCE_INSTANTIATION(uset_t);
    
    // List instantiations with random elements and address printing
    eastl::list<T> list_t;
    for(int i = 0; i < rand(); ++i) {
        list_t.push_back(T());
    }
    for(auto it = list_t.begin(); it != list_t.end(); ++it) {
        printf("List element address: %p\n", (void*)&(*it));
    }
    FORCE_INSTANTIATION(list_t);
    
    // Deque instantiations with random elements and address printing
    eastl::deque<T> deque_t;
    for(int i = 0; i < rand(); ++i) {
        deque_t.push_back(T());
    }
    for(auto it = deque_t.begin(); it != deque_t.end(); ++it) {
        printf("Deque element address: %p\n", (void*)&(*it));
    }
    FORCE_INSTANTIATION(deque_t);
    
    // Queue instantiations (adapter) with random elements
    eastl::queue<T> queue_t;
    for(int i = 0; i < rand(); ++i) {
        queue_t.push(T());
    }
    printf("Queue size: %zu, front address: %p\n", queue_t.size(), (void*)&queue_t.front());
    volatile void* queue_ref = &queue_t;
    (void)queue_ref;
    
    // Stack instantiations (adapter) with random elements
    eastl::stack<T> stack_t;
    for(int i = 0; i < rand(); ++i) {
        stack_t.push(T());
    }
    printf("Stack size: %zu, top address: %p\n", stack_t.size(), (void*)&stack_t.top());
    volatile void* stack_ref = &stack_t;
    (void)stack_ref;
#endif
}

// Macro to conditionally instantiate types based on NUM_TYPES
#define INSTANTIATE_TYPE_IF_ENABLED(N) \
    do { \
        if (NUM_TYPES >= N) { \
            force_container_instantiations<TestType##N>(); \
        } \
    } while(0)

// Main function to instantiate all containers with all types
int main() {
    srand((unsigned int)time(nullptr));  // Initialize random seed
    printf("Starting compilation benchmark test with %d types...\n", NUM_TYPES);
    
    // Force instantiation of all containers with types 1-10 (always enabled)
    force_container_instantiations<TestType1>();
    force_container_instantiations<TestType2>();
    force_container_instantiations<TestType3>();
    force_container_instantiations<TestType4>();
    force_container_instantiations<TestType5>();
    force_container_instantiations<TestType6>();
    force_container_instantiations<TestType7>();
    force_container_instantiations<TestType8>();
    force_container_instantiations<TestType9>();
    force_container_instantiations<TestType10>();
    
    // Conditionally instantiate types 11 to 150 based on NUM_TYPES
    #if NUM_TYPES >= 11
    force_container_instantiations<TestType11>();
    #endif
    #if NUM_TYPES >= 12
    force_container_instantiations<TestType12>();
    #endif
    #if NUM_TYPES >= 13
    force_container_instantiations<TestType13>();
    #endif
    #if NUM_TYPES >= 14
    force_container_instantiations<TestType14>();
    #endif
    #if NUM_TYPES >= 15
    force_container_instantiations<TestType15>();
    #endif
    #if NUM_TYPES >= 16
    force_container_instantiations<TestType16>();
    #endif
    #if NUM_TYPES >= 17
    force_container_instantiations<TestType17>();
    #endif
    #if NUM_TYPES >= 18
    force_container_instantiations<TestType18>();
    #endif
    #if NUM_TYPES >= 19
    force_container_instantiations<TestType19>();
    #endif
    #if NUM_TYPES >= 20
    force_container_instantiations<TestType20>();
    #endif
    #if NUM_TYPES >= 21
    force_container_instantiations<TestType21>();
    #endif
    #if NUM_TYPES >= 22
    force_container_instantiations<TestType22>();
    #endif
    #if NUM_TYPES >= 23
    force_container_instantiations<TestType23>();
    #endif
    #if NUM_TYPES >= 24
    force_container_instantiations<TestType24>();
    #endif
    #if NUM_TYPES >= 25
    force_container_instantiations<TestType25>();
    #endif
    #if NUM_TYPES >= 26
    force_container_instantiations<TestType26>();
    #endif
    #if NUM_TYPES >= 27
    force_container_instantiations<TestType27>();
    #endif
    #if NUM_TYPES >= 28
    force_container_instantiations<TestType28>();
    #endif
    #if NUM_TYPES >= 29
    force_container_instantiations<TestType29>();
    #endif
    #if NUM_TYPES >= 30
    force_container_instantiations<TestType30>();
    #endif
    #if NUM_TYPES >= 31
    force_container_instantiations<TestType31>();
    #endif
    #if NUM_TYPES >= 32
    force_container_instantiations<TestType32>();
    #endif
    #if NUM_TYPES >= 33
    force_container_instantiations<TestType33>();
    #endif
    #if NUM_TYPES >= 34
    force_container_instantiations<TestType34>();
    #endif
    #if NUM_TYPES >= 35
    force_container_instantiations<TestType35>();
    #endif
    #if NUM_TYPES >= 36
    force_container_instantiations<TestType36>();
    #endif
    #if NUM_TYPES >= 37
    force_container_instantiations<TestType37>();
    #endif
    #if NUM_TYPES >= 38
    force_container_instantiations<TestType38>();
    #endif
    #if NUM_TYPES >= 39
    force_container_instantiations<TestType39>();
    #endif
    #if NUM_TYPES >= 40
    force_container_instantiations<TestType40>();
    #endif
    #if NUM_TYPES >= 41
    force_container_instantiations<TestType41>();
    #endif
    #if NUM_TYPES >= 42
    force_container_instantiations<TestType42>();
    #endif
    #if NUM_TYPES >= 43
    force_container_instantiations<TestType43>();
    #endif
    #if NUM_TYPES >= 44
    force_container_instantiations<TestType44>();
    #endif
    #if NUM_TYPES >= 45
    force_container_instantiations<TestType45>();
    #endif
    #if NUM_TYPES >= 46
    force_container_instantiations<TestType46>();
    #endif
    #if NUM_TYPES >= 47
    force_container_instantiations<TestType47>();
    #endif
    #if NUM_TYPES >= 48
    force_container_instantiations<TestType48>();
    #endif
    #if NUM_TYPES >= 49
    force_container_instantiations<TestType49>();
    #endif
    #if NUM_TYPES >= 50
    force_container_instantiations<TestType50>();
    #endif
    #if NUM_TYPES >= 51
    force_container_instantiations<TestType51>();
    #endif
    #if NUM_TYPES >= 52
    force_container_instantiations<TestType52>();
    #endif
    #if NUM_TYPES >= 53
    force_container_instantiations<TestType53>();
    #endif
    #if NUM_TYPES >= 54
    force_container_instantiations<TestType54>();
    #endif
    #if NUM_TYPES >= 55
    force_container_instantiations<TestType55>();
    #endif
    #if NUM_TYPES >= 56
    force_container_instantiations<TestType56>();
    #endif
    #if NUM_TYPES >= 57
    force_container_instantiations<TestType57>();
    #endif
    #if NUM_TYPES >= 58
    force_container_instantiations<TestType58>();
    #endif
    #if NUM_TYPES >= 59
    force_container_instantiations<TestType59>();
    #endif
    #if NUM_TYPES >= 60
    force_container_instantiations<TestType60>();
    #endif
    #if NUM_TYPES >= 61
    force_container_instantiations<TestType61>();
    #endif
    #if NUM_TYPES >= 62
    force_container_instantiations<TestType62>();
    #endif
    #if NUM_TYPES >= 63
    force_container_instantiations<TestType63>();
    #endif
    #if NUM_TYPES >= 64
    force_container_instantiations<TestType64>();
    #endif
    #if NUM_TYPES >= 65
    force_container_instantiations<TestType65>();
    #endif
    #if NUM_TYPES >= 66
    force_container_instantiations<TestType66>();
    #endif
    #if NUM_TYPES >= 67
    force_container_instantiations<TestType67>();
    #endif
    #if NUM_TYPES >= 68
    force_container_instantiations<TestType68>();
    #endif
    #if NUM_TYPES >= 69
    force_container_instantiations<TestType69>();
    #endif
    #if NUM_TYPES >= 70
    force_container_instantiations<TestType70>();
    #endif
    #if NUM_TYPES >= 71
    force_container_instantiations<TestType71>();
    #endif
    #if NUM_TYPES >= 72
    force_container_instantiations<TestType72>();
    #endif
    #if NUM_TYPES >= 73
    force_container_instantiations<TestType73>();
    #endif
    #if NUM_TYPES >= 74
    force_container_instantiations<TestType74>();
    #endif
    #if NUM_TYPES >= 75
    force_container_instantiations<TestType75>();
    #endif
    #if NUM_TYPES >= 76
    force_container_instantiations<TestType76>();
    #endif
    #if NUM_TYPES >= 77
    force_container_instantiations<TestType77>();
    #endif
    #if NUM_TYPES >= 78
    force_container_instantiations<TestType78>();
    #endif
    #if NUM_TYPES >= 79
    force_container_instantiations<TestType79>();
    #endif
    #if NUM_TYPES >= 80
    force_container_instantiations<TestType80>();
    #endif
    #if NUM_TYPES >= 81
    force_container_instantiations<TestType81>();
    #endif
    #if NUM_TYPES >= 82
    force_container_instantiations<TestType82>();
    #endif
    #if NUM_TYPES >= 83
    force_container_instantiations<TestType83>();
    #endif
    #if NUM_TYPES >= 84
    force_container_instantiations<TestType84>();
    #endif
    #if NUM_TYPES >= 85
    force_container_instantiations<TestType85>();
    #endif
    #if NUM_TYPES >= 86
    force_container_instantiations<TestType86>();
    #endif
    #if NUM_TYPES >= 87
    force_container_instantiations<TestType87>();
    #endif
    #if NUM_TYPES >= 88
    force_container_instantiations<TestType88>();
    #endif
    #if NUM_TYPES >= 89
    force_container_instantiations<TestType89>();
    #endif
    #if NUM_TYPES >= 90
    force_container_instantiations<TestType90>();
    #endif
    #if NUM_TYPES >= 91
    force_container_instantiations<TestType91>();
    #endif
    #if NUM_TYPES >= 92
    force_container_instantiations<TestType92>();
    #endif
    #if NUM_TYPES >= 93
    force_container_instantiations<TestType93>();
    #endif
    #if NUM_TYPES >= 94
    force_container_instantiations<TestType94>();
    #endif
    #if NUM_TYPES >= 95
    force_container_instantiations<TestType95>();
    #endif
    #if NUM_TYPES >= 96
    force_container_instantiations<TestType96>();
    #endif
    #if NUM_TYPES >= 97
    force_container_instantiations<TestType97>();
    #endif
    #if NUM_TYPES >= 98
    force_container_instantiations<TestType98>();
    #endif
    #if NUM_TYPES >= 99
    force_container_instantiations<TestType99>();
    #endif
    #if NUM_TYPES >= 100
    force_container_instantiations<TestType100>();
    #endif
    #if NUM_TYPES >= 101
    force_container_instantiations<TestType101>();
    #endif
    #if NUM_TYPES >= 102
    force_container_instantiations<TestType102>();
    #endif
    #if NUM_TYPES >= 103
    force_container_instantiations<TestType103>();
    #endif
    #if NUM_TYPES >= 104
    force_container_instantiations<TestType104>();
    #endif
    #if NUM_TYPES >= 105
    force_container_instantiations<TestType105>();
    #endif
    #if NUM_TYPES >= 106
    force_container_instantiations<TestType106>();
    #endif
    #if NUM_TYPES >= 107
    force_container_instantiations<TestType107>();
    #endif
    #if NUM_TYPES >= 108
    force_container_instantiations<TestType108>();
    #endif
    #if NUM_TYPES >= 109
    force_container_instantiations<TestType109>();
    #endif
    #if NUM_TYPES >= 110
    force_container_instantiations<TestType110>();
    #endif
    #if NUM_TYPES >= 111
    force_container_instantiations<TestType111>();
    #endif
    #if NUM_TYPES >= 112
    force_container_instantiations<TestType112>();
    #endif
    #if NUM_TYPES >= 113
    force_container_instantiations<TestType113>();
    #endif
    #if NUM_TYPES >= 114
    force_container_instantiations<TestType114>();
    #endif
    #if NUM_TYPES >= 115
    force_container_instantiations<TestType115>();
    #endif
    #if NUM_TYPES >= 116
    force_container_instantiations<TestType116>();
    #endif
    #if NUM_TYPES >= 117
    force_container_instantiations<TestType117>();
    #endif
    #if NUM_TYPES >= 118
    force_container_instantiations<TestType118>();
    #endif
    #if NUM_TYPES >= 119
    force_container_instantiations<TestType119>();
    #endif
    #if NUM_TYPES >= 120
    force_container_instantiations<TestType120>();
    #endif
    #if NUM_TYPES >= 121
    force_container_instantiations<TestType121>();
    #endif
    #if NUM_TYPES >= 122
    force_container_instantiations<TestType122>();
    #endif
    #if NUM_TYPES >= 123
    force_container_instantiations<TestType123>();
    #endif
    #if NUM_TYPES >= 124
    force_container_instantiations<TestType124>();
    #endif
    #if NUM_TYPES >= 125
    force_container_instantiations<TestType125>();
    #endif
    #if NUM_TYPES >= 126
    force_container_instantiations<TestType126>();
    #endif
    #if NUM_TYPES >= 127
    force_container_instantiations<TestType127>();
    #endif
    #if NUM_TYPES >= 128
    force_container_instantiations<TestType128>();
    #endif
    #if NUM_TYPES >= 129
    force_container_instantiations<TestType129>();
    #endif
    #if NUM_TYPES >= 130
    force_container_instantiations<TestType130>();
    #endif
    #if NUM_TYPES >= 131
    force_container_instantiations<TestType131>();
    #endif
    #if NUM_TYPES >= 132
    force_container_instantiations<TestType132>();
    #endif
    #if NUM_TYPES >= 133
    force_container_instantiations<TestType133>();
    #endif
    #if NUM_TYPES >= 134
    force_container_instantiations<TestType134>();
    #endif
    #if NUM_TYPES >= 135
    force_container_instantiations<TestType135>();
    #endif
    #if NUM_TYPES >= 136
    force_container_instantiations<TestType136>();
    #endif
    #if NUM_TYPES >= 137
    force_container_instantiations<TestType137>();
    #endif
    #if NUM_TYPES >= 138
    force_container_instantiations<TestType138>();
    #endif
    #if NUM_TYPES >= 139
    force_container_instantiations<TestType139>();
    #endif
    #if NUM_TYPES >= 140
    force_container_instantiations<TestType140>();
    #endif
    #if NUM_TYPES >= 141
    force_container_instantiations<TestType141>();
    #endif
    #if NUM_TYPES >= 142
    force_container_instantiations<TestType142>();
    #endif
    #if NUM_TYPES >= 143
    force_container_instantiations<TestType143>();
    #endif
    #if NUM_TYPES >= 144
    force_container_instantiations<TestType144>();
    #endif
    #if NUM_TYPES >= 145
    force_container_instantiations<TestType145>();
    #endif
    #if NUM_TYPES >= 146
    force_container_instantiations<TestType146>();
    #endif
    #if NUM_TYPES >= 147
    force_container_instantiations<TestType147>();
    #endif
    #if NUM_TYPES >= 148
    force_container_instantiations<TestType148>();
    #endif
    #if NUM_TYPES >= 149
    force_container_instantiations<TestType149>();
    #endif
    #if NUM_TYPES >= 150
    force_container_instantiations<TestType150>();
    #endif
    
    printf("Compilation benchmark test completed successfully.\n");
    
#ifdef USE_STL
    printf("Library: STL\n");
#elif USE_EASTL
    printf("Library: EASTL\n");
#endif
    
    return 0;
}