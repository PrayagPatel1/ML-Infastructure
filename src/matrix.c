
#include <string.h>
#include "matrix.h"

void matrix_allocate(matrix *matrix, size_t rows, size_t cols)
{
    matrix->elements = malloc(rows * cols * sizeof(float));
    if (!matrix->elements)
    {
        matrix->elements = NULL;
        matrix->rows = 0;
        matrix->cols = 0;
        perror("ERROR: Cannot allocate memory to a matrix type");
        return;
    }
    memset(matrix->elements, 0, rows * cols * sizeof(float));
    matrix->cols = cols;
    matrix->rows = rows;
}

void matrix_free(matrix *matrix)
{
    if (!matrix || !matrix->elements)
        return;

    free(matrix->elements);
    matrix->elements = NULL;
    matrix->cols = 0;
    matrix->rows = 0;
}

/* Element-wise Addition, Subtraction, Multiplication, and Divison */
matrix matrix_add(matrix *mat1, matrix *mat2)
{
    assert(
        mat1->rows == mat2->rows &&
        mat1->cols == mat2->cols &&
        "ERROR: Two matrices must be the same size");

    matrix sum_matrix = {0};
    matrix_allocate(&sum_matrix, mat1->rows, mat1->cols);

    for (size_t row_idx = 0; row_idx < sum_matrix.rows * sum_matrix.cols; row_idx++)
    {
        sum_matrix.elements[row_idx] = mat1->elements[row_idx] + mat2->elements[row_idx];
    }
    return sum_matrix;
}

matrix matrix_sub(matrix *mat1, matrix *mat2)
{
    assert(
        mat1->rows == mat2->rows &&
        mat1->cols == mat2->cols &&
        "ERROR: Two matrices must be the same size");

    matrix diff_matrix = {0};
    matrix_allocate(&diff_matrix, mat1->rows, mat1->cols);

    for (size_t row_idx = 0; row_idx < diff_matrix.rows * diff_matrix.cols; row_idx++)
    {
        diff_matrix.elements[row_idx] = mat1->elements[row_idx] - mat2->elements[row_idx];
    }
    return diff_matrix;
}

matrix matrix_mul(matrix *mat1, matrix *mat2)
{
    assert(
        mat1->rows == mat2->rows &&
        mat1->cols == mat2->cols &&
        "ERROR: Two matrices must be the same size");

    matrix mul_matrix = {0};
    matrix_allocate(&mul_matrix, mat1->rows, mat1->cols);

    for (size_t row_idx = 0; row_idx < mul_matrix.rows * mul_matrix.cols; row_idx++)
    {
        mul_matrix.elements[row_idx] = mat1->elements[row_idx] * mat2->elements[row_idx];
    }
    return mul_matrix;
}

/* Matrix by Matrix Multiplication */
matrix matrix_matrix_mul(matrix *mat1, matrix *mat2)
{
    assert(mat1->cols == mat2->rows && "ERROR: Number of columns of mat1 must be the same as the number of rows of mat2");

    matrix result = {0};
    matrix_allocate(&result, mat1->rows, mat2->cols);

    for (size_t row_idx = 0; row_idx < mat1->rows; row_idx++)
    {
        for (size_t col_idx = 0; col_idx < mat2->cols; col_idx++)
        {
            size_t sum = 0;

            for (size_t idx = 0; idx < mat1->cols; idx++)
            {
                sum += mat1->elements[(row_idx * mat1->cols) + idx] * mat2->elements[(idx * mat2->cols) + col_idx];
            }
            result.elements[(row_idx * mat2->cols) + col_idx] = sum;
        }
    }

    return result;
}