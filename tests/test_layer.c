/**
 * A manual unit test for layer.c
 */

#include "test_framework.h"
#include "../src/layer.h"
#include "../src/activation.h"

static test_weight_init(void)
{
    test_sperator("Layer: Weight Initialization Test");

    matrix mat;
    matrix_allocate(&mat, 3, 3);
    init_weight_basic(&mat);

    int dup_cnt = 0;
    for (size_t i = 0; i < mat.cols * mat.rows; i++)
    {
        if (mat.elements[i] == mat.elements[i + 1])
            dup_cnt++;
    }

    CHECK(dup_cnt < (int)(mat.cols * mat.rows) / 2, "Weight matrix randomly initalized.");
    free(&mat);
}

static test_layer_alloc_and_free(void)
{
    test_sperator("Layer: Allocation and Free Test");

    size_t input_size = 2;
    size_t output_size = 1;
    layer layer = layer_init(input_size, output_size, activation_sigmoid);

    CHECK(layer.input_size == input_size, "Input size allocated");
    CHECK(layer.output_size == output_size, "Output size allocated");
    CHECK(layer.biases.length == output_size, "Biases allocated");
    CHECK(layer.prev_input.length == output_size, "Previous Input allocated");
    CHECK(layer.prev_output.length == output_size, "Previous output allocated");
    CHECK(layer.prev_z.length == input_size, "Previous z allocated");
    CHECK(layer.weights.elements != NULL, "Weights have been allocated");

    layer_free(&layer);

    CHECK(layer.input_size == 0, "Input size freed");
    CHECK(layer.output_size == 0, "Output size freed");
    CHECK(layer.biases.length == 0, "Biases freed");
    CHECK(layer.prev_input.length == 0, "Previous Input freed");
    CHECK(layer.prev_output.length == 0, "Previous output freed");
    CHECK(layer.prev_z.length == 0, "Previous z freed");
    CHECK(layer.weights.elements == NULL, "Weights have been freed");
}

static test_forward_prop(void)
{
    size_t input_size = 2;
    size_t output_size = 1;
    layer layer = layer_init(input_size, output_size, activation_sigmoid);

    vector inputs;
    allocateVector(&inputs, 2);
    inputs.elements[0] = 1.0f;
    inputs.elements[1] = 2.0f;

    forward_prop_layer(inputs, &layer);

    CHECK(layer.prev_input.elements != NULL, "Prev input vector allocated");
    CHECK(layer.prev_input.length == 2, "Prev input size properly set");
    CHECK(layer.prev_input.elements[0] == 1.0f, "");
    CHECK(layer.prev_input.elements[1] == 2.0f, "");

    CHECK(layer.prev_output.elements != NULL, "Prev output vector allocated");
    CHECK(layer.prev_output.length == 1, "Prev output size properly set");

    CHECK(layer.prev_z.elements != NULL, "Prev z vector allocated");
    CHECK(layer.prev_z.length == 1, "Length of prev z vector is properly set");

    printf("Previous Z: %f", layer.prev_z.elements[0]);
}

int main(void)
{
    test_weight_init();
    test_layer_alloc_and_free();
    test_forward_prop();

    test_result();
}