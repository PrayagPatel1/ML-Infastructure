#ifndef MATRIX_H
#define MATRIX_H

typedef struct matrix
{
    float *elements;
    size_t rows, cols;
} matrix;

void matrix_allocate(matrix *matrix, size_t rows, size_t cols);
void matrix_free(matrix *matrix);

/* Element-wise Addition, Subtraction, Multiplication, and Divison */
matrix matrix_add(matrix *mat1, matrix *mat2);
matrix matrix_sub(matrix *mat1, matrix *mat2);
matrix matrix_mul(matrix *mat1, matrix *mat2);

/* Matrix by Matrix Multiplication */
matrix matrix_matrix_mul(matrix *mat1, matrix *mat2);

#endif 