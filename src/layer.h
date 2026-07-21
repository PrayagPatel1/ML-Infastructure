#ifndef LAYER_H
#define LAYER_H

// POSIX header files
#include <stdlib.h>

// Custom-made header files
#include "vector.h"
#include "matrix.h"

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

void init_weight_basic(matrix *weights); // TODO: later create a header with just differnet weight initializer

layer layer_init(size_t input_size, size_t output_size, activation_func func);

void layer_free(layer *curr_layer);

void forward_prop_layer(vector inputs, layer *layer);

#endif // Layer_H