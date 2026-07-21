/**
 * A manual unit test suite for vector.c and matrix.c
 */

#include <stdlib.h>
#include <assert.h>
#include <stddef.h>

#include "test_framework.h"
#include "../src/vector.h"
#include "../src/matrix.h"

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

    CHECK(float_eq(vec.elements[0], 0.267261f), "normalize: element 0 == 0.26");
    CHECK(float_eq(vec.elements[1], 0.534522f), "normalize: element 1 == 0.53");
    CHECK(float_eq(vec.elements[2], 0.801784f), "normalize: element 2 == 0.80");

    freeVector(&vec);
}

/* Matrix Unit Tests */
static void test_matrix_alloc_and_free(void)
{
    test_sperator("Matrix: Allocate and Free Matrix Test");

    /* Allocation Test */
    matrix mat;
    matrix_allocate(&mat, 2, 3);

    CHECK(mat.rows == 2, "Number of rows is 2");
    CHECK(mat.cols == 3, "Number of columns is 3");

    size_t num_elem = 0;
    for (size_t i = 0; i < 6; ++i)
    {
        if (mat.elements[i] == 0)
        {
            num_elem++;
        }
        else
        {
            break;
        }
    }
    CHECK(num_elem == 6, "All elements in the matrix are zero after initalization");

    /* Free Test */
    matrix_free(&mat);
    CHECK(mat.rows == 0, "Rows set to zero after free");
    CHECK(mat.cols == 0, "Cols set to zero after free");
    CHECK(mat.elements == NULL, "Elements of a matrix is null after free.");

    matrix_free(&mat);
    CHECK(1, "Double free doesn't crash the program");
}

static void test_matrix_addition(void)
{
    test_sperator("Matrix: Element-wise Matrix Addition Test");

    matrix mat1;
    matrix mat2;
    matrix_allocate(&mat1, 2, 2);
    matrix_allocate(&mat2, 2, 2);

    for (size_t y = 0; y < mat1.cols; y++)
    {
        for (size_t x = 0; x < mat1.rows; x++)
        {
            mat1.elements[x * mat1.cols + y] = (float)x;
        }
    }

    for (size_t y = 0; y < mat1.cols; y++)
    {
        for (size_t x = 0; x < mat1.rows; x++)
        {
            mat2.elements[x * mat1.cols + y] = 2.0f;
        }
    }

    matrix result = matrix_add(&mat1, &mat2);

    CHECK(result.rows == 2, "Rows are not modified");
    CHECK(result.cols == 2, "Cols are not modified");
    CHECK(result.elements[0] == 2.0f, "Row 1 Col 1 == 2");
    CHECK(result.elements[1] == 2.0f, "Row 1 Col 2 == 2");
    CHECK(result.elements[2] == 3.0f, "Row 2 Col 1 == 3");
    CHECK(result.elements[3] == 3.0f, "Row 2 Col 2 == 3");

    matrix_free(&mat1);
    matrix_free(&mat2);
    matrix_free(&result);
}

static void test_matrix_subtraction(void)
{
    test_sperator("Matrix: Element-wise Matrix Subtraction Test");

    matrix mat1;
    matrix mat2;
    matrix_allocate(&mat1, 2, 2);
    matrix_allocate(&mat2, 2, 2);

    for (size_t y = 0; y < mat1.cols; y++)
    {
        for (size_t x = 0; x < mat1.rows; x++)
        {
            mat1.elements[x * mat1.cols + y] = (float)x;
        }
    }

    for (size_t y = 0; y < mat1.cols; y++)
    {
        for (size_t x = 0; x < mat1.rows; x++)
        {
            mat2.elements[x * mat1.cols + y] = 2.0f;
        }
    }

    matrix result = matrix_sub(&mat1, &mat2);

    CHECK(result.rows == 2, "Rows are not modified");
    CHECK(result.cols == 2, "Cols are not modified");
    CHECK(result.elements[0] == -2.0f, "Row 1 Col 1 == -2");
    CHECK(result.elements[1] == -2.0f, "Row 1 Col 2 == -2");
    CHECK(result.elements[2] == -1.0f, "Row 2 Col 1 == -1");
    CHECK(result.elements[3] == -1.0f, "Row 2 Col 2 == -1");

    matrix_free(&mat1);
    matrix_free(&mat2);
    matrix_free(&result);
}

static void test_matrix_multiplication(void)
{
    test_sperator("Matrix: Element-wise Matrix Multiplication Test");

    matrix mat1;
    matrix mat2;
    matrix_allocate(&mat1, 2, 2);
    matrix_allocate(&mat2, 2, 2);

    for (size_t y = 0; y < mat1.cols; y++)
    {
        for (size_t x = 0; x < mat1.rows; x++)
        {
            mat1.elements[x * mat1.cols + y] = (float)x;
        }
    }

    for (size_t y = 0; y < mat1.cols; y++)
    {
        for (size_t x = 0; x < mat1.rows; x++)
        {
            mat2.elements[x * mat1.cols + y] = 2.0f;
        }
    }

    matrix result = matrix_mul(&mat1, &mat2);

    CHECK(result.rows == 2, "Rows are not modified");
    CHECK(result.cols == 2, "Cols are not modified");
    CHECK(result.elements[0] == 0.0f, "Row 1 Col 1 == 0");
    CHECK(result.elements[1] == 0.0f, "Row 1 Col 2 == 0");
    CHECK(result.elements[2] == 2.0f, "Row 2 Col 1 == 2");
    CHECK(result.elements[3] == 2.0f, "Row 2 Col 2 == 2");

    matrix_free(&mat1);
    matrix_free(&mat2);
    matrix_free(&result);
}

static void test_matrix_matrix_multiplication(void)
{
    test_sperator("Matrix: Matrix-Matrix Multiplication Test");

    matrix mat1;
    matrix mat2;
    matrix_allocate(&mat1, 2, 2);
    matrix_allocate(&mat2, 2, 2);

    for (size_t y = 0; y < mat1.cols; y++)
    {
        for (size_t x = 0; x < mat1.rows; x++)
        {
            mat1.elements[x * mat1.cols + y] = (float)x;
        }
    }

    for (size_t y = 0; y < mat1.cols; y++)
    {
        for (size_t x = 0; x < mat1.rows; x++)
        {
            mat2.elements[x * mat1.cols + y] = 2.0f;
        }
    }

    matrix result = matrix_matrix_mul(&mat1, &mat2);

    CHECK(result.rows == mat1.rows, "Number of rows is the same as matrix 1 rows.");
    CHECK(result.cols == mat2.cols, "Number of cols is the same as matrix 2 rows.");
    CHECK(result.elements[0] == 0.0f, "Row 1 Col 1 == 0");
    CHECK(result.elements[1] == 0.0f, "Row 1 Col 2 == 0");
    CHECK(result.elements[2] == 4.0f, "Row 2 Col 1 == 4");
    CHECK(result.elements[3] == 4.0f, "Row 2 Col 2 == 4");

    matrix_free(&mat1);
    matrix_free(&mat2);
    matrix_free(&result);
}

/* Main Test Registry Entry Point */

int main(void)
{
    test_vector_allocation_and_free();
    test_vector_add();
    test_vector_sub();
    test_vector_scale();
    test_vector_normalize();

    test_matrix_alloc_and_free();
    test_matrix_addition();
    test_matrix_multiplication();
    test_matrix_subtraction();
    test_matrix_matrix_multiplication();

    test_result();
}
