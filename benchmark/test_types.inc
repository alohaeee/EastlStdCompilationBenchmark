// Test types for container instantiation
// Each type has UNIQUE size and characteristics to prevent compiler optimizations

// Macro to generate types with VERY different characteristics
#define DEFINE_UNIQUE_TYPE(N, SIZE) \
struct TestType##N { \
    char unique_data[SIZE]; \
    int id; \
    double padding[N % 3 + 1]; /* Variable padding (1-3 elements) to make types really different */ \
    long long extra_field##N; /* Unique field name per type */ \
    TestType##N() : id(N), extra_field##N(N * 1000) { \
        for(int i=0; i<SIZE; ++i) unique_data[i] = (i+N) % 256; \
        for(int i=0; i<N%3+1; ++i) padding[i] = N + i * 0.1; \
    } \
    /* Make copy operations expensive and unique */ \
    TestType##N(const TestType##N& other) : id(other.id), extra_field##N(other.extra_field##N) { \
        for(int i=0; i<SIZE; ++i) unique_data[i] = other.unique_data[i] + N; \
        for(int i=0; i<N%3+1; ++i) padding[i] = other.padding[i] + 0.01; \
    } \
    TestType##N& operator=(const TestType##N& other) { \
        if(this != &other) { \
            id = other.id + N; \
            extra_field##N = other.extra_field##N + N; \
            for(int i=0; i<SIZE; ++i) unique_data[i] = other.unique_data[i]; \
            for(int i=0; i<N%3+1; ++i) padding[i] = other.padding[i]; \
        } \
        return *this; \
    } \
    bool operator<(const TestType##N& other) const { return id < other.id; } \
    bool operator==(const TestType##N& other) const { return id == other.id; } \
};

// Generate types 1-100 with unique sizes (each type has different size)
DEFINE_UNIQUE_TYPE(1, 1)    // 1 + 4 = 5 bytes
DEFINE_UNIQUE_TYPE(2, 2)    // 2 + 4 = 6 bytes  
DEFINE_UNIQUE_TYPE(3, 3)    // 3 + 4 = 7 bytes
DEFINE_UNIQUE_TYPE(4, 4)    // 4 + 4 = 8 bytes
DEFINE_UNIQUE_TYPE(5, 5)    // 5 + 4 = 9 bytes
DEFINE_UNIQUE_TYPE(6, 6)    // 6 + 4 = 10 bytes
DEFINE_UNIQUE_TYPE(7, 7)    // 7 + 4 = 11 bytes
DEFINE_UNIQUE_TYPE(8, 8)    // 8 + 4 = 12 bytes
DEFINE_UNIQUE_TYPE(9, 9)    // 9 + 4 = 13 bytes
DEFINE_UNIQUE_TYPE(10, 10)  // 10 + 4 = 14 bytes

#if NUM_TYPES >= 11
DEFINE_UNIQUE_TYPE(11, 11)
#endif
#if NUM_TYPES >= 12
DEFINE_UNIQUE_TYPE(12, 12)
#endif
#if NUM_TYPES >= 13
DEFINE_UNIQUE_TYPE(13, 13)
#endif
#if NUM_TYPES >= 14
DEFINE_UNIQUE_TYPE(14, 14)
#endif
#if NUM_TYPES >= 15
DEFINE_UNIQUE_TYPE(15, 15)
#endif
#if NUM_TYPES >= 16
DEFINE_UNIQUE_TYPE(16, 16)
#endif
#if NUM_TYPES >= 17
DEFINE_UNIQUE_TYPE(17, 17)
#endif
#if NUM_TYPES >= 18
DEFINE_UNIQUE_TYPE(18, 18)
#endif
#if NUM_TYPES >= 19
DEFINE_UNIQUE_TYPE(19, 19)
#endif
#if NUM_TYPES >= 20
DEFINE_UNIQUE_TYPE(20, 20)
#endif
#if NUM_TYPES >= 21
DEFINE_UNIQUE_TYPE(21, 21)
#endif
#if NUM_TYPES >= 22
DEFINE_UNIQUE_TYPE(22, 22)
#endif
#if NUM_TYPES >= 23
DEFINE_UNIQUE_TYPE(23, 23)
#endif
#if NUM_TYPES >= 24
DEFINE_UNIQUE_TYPE(24, 24)
#endif
#if NUM_TYPES >= 25
DEFINE_UNIQUE_TYPE(25, 25)
#endif
#if NUM_TYPES >= 26
DEFINE_UNIQUE_TYPE(26, 26)
#endif
#if NUM_TYPES >= 27
DEFINE_UNIQUE_TYPE(27, 27)
#endif
#if NUM_TYPES >= 28
DEFINE_UNIQUE_TYPE(28, 28)
#endif
#if NUM_TYPES >= 29
DEFINE_UNIQUE_TYPE(29, 29)
#endif
#if NUM_TYPES >= 30
DEFINE_UNIQUE_TYPE(30, 30)
#endif
#if NUM_TYPES >= 31
DEFINE_UNIQUE_TYPE(31, 31)
#endif
#if NUM_TYPES >= 32
DEFINE_UNIQUE_TYPE(32, 32)
#endif
#if NUM_TYPES >= 33
DEFINE_UNIQUE_TYPE(33, 33)
#endif
#if NUM_TYPES >= 34
DEFINE_UNIQUE_TYPE(34, 34)
#endif
#if NUM_TYPES >= 35
DEFINE_UNIQUE_TYPE(35, 35)
#endif
#if NUM_TYPES >= 36
DEFINE_UNIQUE_TYPE(36, 36)
#endif
#if NUM_TYPES >= 37
DEFINE_UNIQUE_TYPE(37, 37)
#endif
#if NUM_TYPES >= 38
DEFINE_UNIQUE_TYPE(38, 38)
#endif
#if NUM_TYPES >= 39
DEFINE_UNIQUE_TYPE(39, 39)
#endif
#if NUM_TYPES >= 40
DEFINE_UNIQUE_TYPE(40, 40)
#endif
#if NUM_TYPES >= 41
DEFINE_UNIQUE_TYPE(41, 41)
#endif
#if NUM_TYPES >= 42
DEFINE_UNIQUE_TYPE(42, 42)
#endif
#if NUM_TYPES >= 43
DEFINE_UNIQUE_TYPE(43, 43)
#endif
#if NUM_TYPES >= 44
DEFINE_UNIQUE_TYPE(44, 44)
#endif
#if NUM_TYPES >= 45
DEFINE_UNIQUE_TYPE(45, 45)
#endif
#if NUM_TYPES >= 46
DEFINE_UNIQUE_TYPE(46, 46)
#endif
#if NUM_TYPES >= 47
DEFINE_UNIQUE_TYPE(47, 47)
#endif
#if NUM_TYPES >= 48
DEFINE_UNIQUE_TYPE(48, 48)
#endif
#if NUM_TYPES >= 49
DEFINE_UNIQUE_TYPE(49, 49)
#endif
#if NUM_TYPES >= 50
DEFINE_UNIQUE_TYPE(50, 50)
#endif
#if NUM_TYPES >= 51
DEFINE_UNIQUE_TYPE(51, 51)
#endif
#if NUM_TYPES >= 52
DEFINE_UNIQUE_TYPE(52, 52)
#endif
#if NUM_TYPES >= 53
DEFINE_UNIQUE_TYPE(53, 53)
#endif
#if NUM_TYPES >= 54
DEFINE_UNIQUE_TYPE(54, 54)
#endif
#if NUM_TYPES >= 55
DEFINE_UNIQUE_TYPE(55, 55)
#endif
#if NUM_TYPES >= 56
DEFINE_UNIQUE_TYPE(56, 56)
#endif
#if NUM_TYPES >= 57
DEFINE_UNIQUE_TYPE(57, 57)
#endif
#if NUM_TYPES >= 58
DEFINE_UNIQUE_TYPE(58, 58)
#endif
#if NUM_TYPES >= 59
DEFINE_UNIQUE_TYPE(59, 59)
#endif
#if NUM_TYPES >= 60
DEFINE_UNIQUE_TYPE(60, 60)
#endif
#if NUM_TYPES >= 61
DEFINE_UNIQUE_TYPE(61, 61)
#endif
#if NUM_TYPES >= 62
DEFINE_UNIQUE_TYPE(62, 62)
#endif
#if NUM_TYPES >= 63
DEFINE_UNIQUE_TYPE(63, 63)
#endif
#if NUM_TYPES >= 64
DEFINE_UNIQUE_TYPE(64, 64)
#endif
#if NUM_TYPES >= 65
DEFINE_UNIQUE_TYPE(65, 65)
#endif
#if NUM_TYPES >= 66
DEFINE_UNIQUE_TYPE(66, 66)
#endif
#if NUM_TYPES >= 67
DEFINE_UNIQUE_TYPE(67, 67)
#endif
#if NUM_TYPES >= 68
DEFINE_UNIQUE_TYPE(68, 68)
#endif
#if NUM_TYPES >= 69
DEFINE_UNIQUE_TYPE(69, 69)
#endif
#if NUM_TYPES >= 70
DEFINE_UNIQUE_TYPE(70, 70)
#endif
#if NUM_TYPES >= 71
DEFINE_UNIQUE_TYPE(71, 71)
#endif
#if NUM_TYPES >= 72
DEFINE_UNIQUE_TYPE(72, 72)
#endif
#if NUM_TYPES >= 73
DEFINE_UNIQUE_TYPE(73, 73)
#endif
#if NUM_TYPES >= 74
DEFINE_UNIQUE_TYPE(74, 74)
#endif
#if NUM_TYPES >= 75
DEFINE_UNIQUE_TYPE(75, 75)
#endif
#if NUM_TYPES >= 76
DEFINE_UNIQUE_TYPE(76, 76)
#endif
#if NUM_TYPES >= 77
DEFINE_UNIQUE_TYPE(77, 77)
#endif
#if NUM_TYPES >= 78
DEFINE_UNIQUE_TYPE(78, 78)
#endif
#if NUM_TYPES >= 79
DEFINE_UNIQUE_TYPE(79, 79)
#endif
#if NUM_TYPES >= 80
DEFINE_UNIQUE_TYPE(80, 80)
#endif
#if NUM_TYPES >= 81
DEFINE_UNIQUE_TYPE(81, 81)
#endif
#if NUM_TYPES >= 82
DEFINE_UNIQUE_TYPE(82, 82)
#endif
#if NUM_TYPES >= 83
DEFINE_UNIQUE_TYPE(83, 83)
#endif
#if NUM_TYPES >= 84
DEFINE_UNIQUE_TYPE(84, 84)
#endif
#if NUM_TYPES >= 85
DEFINE_UNIQUE_TYPE(85, 85)
#endif
#if NUM_TYPES >= 86
DEFINE_UNIQUE_TYPE(86, 86)
#endif
#if NUM_TYPES >= 87
DEFINE_UNIQUE_TYPE(87, 87)
#endif
#if NUM_TYPES >= 88
DEFINE_UNIQUE_TYPE(88, 88)
#endif
#if NUM_TYPES >= 89
DEFINE_UNIQUE_TYPE(89, 89)
#endif
#if NUM_TYPES >= 90
DEFINE_UNIQUE_TYPE(90, 90)
#endif
#if NUM_TYPES >= 91
DEFINE_UNIQUE_TYPE(91, 91)
#endif
#if NUM_TYPES >= 92
DEFINE_UNIQUE_TYPE(92, 92)
#endif
#if NUM_TYPES >= 93
DEFINE_UNIQUE_TYPE(93, 93)
#endif
#if NUM_TYPES >= 94
DEFINE_UNIQUE_TYPE(94, 94)
#endif
#if NUM_TYPES >= 95
DEFINE_UNIQUE_TYPE(95, 95)
#endif
#if NUM_TYPES >= 96
DEFINE_UNIQUE_TYPE(96, 96)
#endif
#if NUM_TYPES >= 97
DEFINE_UNIQUE_TYPE(97, 97)
#endif
#if NUM_TYPES >= 98
DEFINE_UNIQUE_TYPE(98, 98)
#endif
#if NUM_TYPES >= 99
DEFINE_UNIQUE_TYPE(99, 99)
#endif
#if NUM_TYPES >= 100
DEFINE_UNIQUE_TYPE(100, 100)
#endif