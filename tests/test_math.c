/**
 * A manual test suite for vector.c and matrix.c
 */

#include <stdlib.h>
#include <assert.h>
#include <stddef.h>

#include "../src/matrix.h"
#include "../src/vector.h"
#include "test_framework.h"

/* Vector Test Unit Cases*/

static void test_vector_allocation_and_free(void)
{
    test_sperator("Vector: Allocation and Free Test");

    vector vec;
    allocateVector(&vec, 4);

    CHECK(vec.elements != NULL, "element pointer is non-NULL after alloc");
    CHECK(vec.length == 4, "length is set correctly");
    CHECK(vec.owner == 1, "owner flag is 1 (owning memory)");

    int all_zero = 1;
    for (size_t idx = 0; idx < vec.length; idx++)
    {
        if (vec.elements[idx] != 0.0f)
        {
            all_zero = 0;
            break;
        }
    }
    CHECK(all_zero, "all elements are zero after allocation");

    freeVector(&vec);
    CHECK(vec.elements == NULL, "element pointer is NULL after free");
    CHECK(vec.length == 0, "length is 0 after free");
    CHECK(vec.owner == 0, "owner flag is 0 (does not own any memory)");

    freeVector(&vec);
    CHECK(1, "double-free does not crash");
}

static void test_vector_add(void)
{
    test_sperator("Vector: Addition between two Vectors Test");

    vector vec1, vec2;
    allocateVector(&vec1, 3);
    allocateVector(&vec2, 3);

    vec1.elements[0] = 1.0f;
    vec1.elements[1] = 2.0f;
    vec1.elements[2] = 3.0f;
    vec2.elements[0] = 2.0f;
    vec2.elements[1] = 4.0f;
    vec2.elements[2] = 6.0f;

    vector result = addVector(&vec1, &vec2);

    CHECK(float_eq(result.elements[0], 3.0f), "add: element 0 == 3");
    CHECK(float_eq(result.elements[1], 6.0f), "add: element 1 == 6");
    CHECK(float_eq(result.elements[2], 9.0f), "add: element 2 == 9");

    freeVector(&vec1);
    freeVector(&vec2);
    freeVector(&result);
}

static void test_vector_sub(void)
{
    test_sperator("Vector: Subtraction between two Vectors Test");

    vector vec1, vec2;
    allocateVector(&vec1, 3);
    allocateVector(&vec2, 3);

    vec1.elements[0] = 1.0f;
    vec1.elements[1] = 2.0f;
    vec1.elements[2] = 3.0f;
    vec2.elements[0] = 2.0f;
    vec2.elements[1] = 4.0f;
    vec2.elements[2] = 6.0f;

    vector result = subVector(&vec1, &vec2);

    CHECK(float_eq(result.elements[0], -1.0f), "sub: element 0 == -1");
    CHECK(float_eq(result.elements[1], -2.0f), "sub: element 1 == -2");
    CHECK(float_eq(result.elements[2], -3.0f), "sub: element 2 == -3");

    freeVector(&vec1);
    freeVector(&vec2);
    freeVector(&result);
}

static void test_vector_scale(void)
{
    test_sperator("Vector: Scalar Scaling a Vector Test");

    vector vec;
    float scalar = 5.0f;

    allocateVector(&vec, 3);
    vec.elements[0] = 1.0f;
    vec.elements[1] = 2.0f;
    vec.elements[2] = 3.0f;

    scaleVector(&vec, scalar);

    CHECK(float_eq(vec.elements[0], 5.0f), "scale: element 0 == 5");
    CHECK(float_eq(vec.elements[1], 10.0f), "scale: element 1 == 10");
    CHECK(float_eq(vec.elements[2], 15.0f), "scale: element 2 == 15");

    freeVector(&vec);
}

static void test_vector_normalize(void)
{
    test_sperator("Vector: Normalize a Vector Test");

    vector vec;
    allocateVector(&vec, 3);

    vec.elements[0] = 1.0f;
    vec.elements[1] = 2.0f;
    vec.elements[2] = 3.0f;

    normalizeVector(&vec);

    CHECK(float_eq(vec.elements[0], 0.26f), "normalize: element 0 == 0.26");
    CHECK(float_eq(vec.elements[1], 0.53f), "normalize: element 1 == 0.53");
    CHECK(float_eq(vec.elements[2], 0.80f), "normalize: element 2 == 0.80");

    freeVector(&vec);
}

/* Main Test Registry Entry Point */

int main(void)
{
    test_vector_allocation_and_free();
    test_vector_add();
    test_vector_sub();
    test_vector_scale();
    test_vector_normalize();

    test_result();
}
