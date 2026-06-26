#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>

#include "vector.h"
#include "matrix.h"
// #include "activation.h"

typedef void (*activation_func)(vector *);

typedef struct layer
{
    size_t input_size;
    size_t output_size; // same as the number of neurons

    matrix weights; // shape: output_size * input_size
    vector biases;  // shape: output_size

    vector prev_z;      // cached for backpropagation
    vector prev_input;  // cached for backpropagation
    vector prev_output; // cached for backpropagation

    activation_func func;
} layer;

void init_weight_basic(matrix *weights)
{
    for (size_t idx = 0; idx < weights->cols * weights->rows; idx++)
    {
        // Generates a random value between -0.5 to 0.5
        weights->elements[idx] = -0.5f + ((float)rand() / RAND_MAX);
    }
}

layer layer_init(size_t input_size, size_t output_size, activation_func func)
{
    layer layer;

    layer.input_size = input_size;
    layer.output_size = output_size;

    allocateVector(&(layer.biases), output_size);
    matrix_allocate(&(layer.weights), output_size, input_size);

    init_weight_basic(&layer.weights);

    allocateVector(&(layer.prev_input), output_size);
    allocateVector(&(layer.prev_output), output_size);
    allocateVector(&(layer.prev_z), input_size);

    layer.func = func;

    return layer;
}

void layer_free(layer *curr_layer)
{
    curr_layer->input_size = 0;
    curr_layer->output_size = 0;

    freeVector(&(curr_layer->biases));
    matrix_free(&(curr_layer->weights));

    freeVector(&(curr_layer->prev_z));
    freeVector(&(curr_layer->prev_input));
    freeVector(&(curr_layer->prev_output));

    curr_layer->func = NULL;
}

void forward_prop_layer(vector inputs, layer *layer)
{
    assert(inputs.length == layer->weights.cols && "Input Vector Rows and Weight Matrix Cols Must be the Same");

    vector activations;
    allocateVector(&activations, layer->output_size);
    float dot_prod = 0.0f;

    // Pre-Activation Stage: Weights * Inputs + Biases
    for (size_t row = 0; row < layer->weights.rows; row++)
    {
        for (size_t col = 0; col < layer->weights.cols; col++)
        {
            dot_prod += layer->weights.elements[(row * layer->weights.cols) + col] * inputs.elements[col];
        }

        activations.elements[row] = dot_prod;
        dot_prod = 0.0f;
    }
    vector z = addVector(&activations, &(layer->biases));

    freeVector(&activations);

    vector_copy_into(&layer->prev_z, &z);
    vector_copy_into(&layer->prev_input, &inputs);

    // Activation Stage: Activation_func(activations)
    layer->func(&z);
    vector_copy_into(&layer->prev_output, &z);

    freeVector(&z);
}

int main(void)
{
    return 0;
}