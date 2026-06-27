#ifndef NETWORK_H
#define NETWORK_H

#include <stdio.h>
#include "layer.h"

typedef struct network
{
    size_t num_layers;
    layer *layers;
} network;

void network_init(network *new_network, size_t num_layers, int *input_sizes, int *output_sizes, activation_func *funcs);

void network_free(network *net);

vector network_forward_prop(network *net, vector *inputs);

#endif 