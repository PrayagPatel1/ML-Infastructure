#ifndef TEST_FRAMEWORK_H
#define TEST_FRAMEWORK_H

#include <stdio.h>
#include <math.h>

static int total_tests = 0;
static int tests_pass = 0;
static int tests_failed = 0;

// Compares two floats by determining if the difference between the two floats
// are less than a small epsilon.
static inline int float_eq(float a, float b)
{
    return fabs(a - b) < 1e-5f;
}

#define CHECK(cond, msg)                                           \
    do                                                             \
    {                                                              \
        total_tests++;                                             \
        if (cond)                                                  \
        {                                                          \
            tests_pass++;                                          \
            printf("    [PASS] %s\n", msg);                        \
        }                                                          \
        else                                                       \
        {                                                          \
            tests_failed++;                                        \
            printf("    [FAILED] %s (line: %d)\n", msg, __LINE__); \
        }                                                          \
    } while (0)

static inline void test_sperator(const char *msg)
{
    printf("=== %s ===\n", msg);
}

#endif