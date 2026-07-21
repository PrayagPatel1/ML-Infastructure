#include "network.h"

void network_init(network *new_network, size_t num_layers, int *input_sizes, int *output_sizes, activation_func *funcs)
{
    new_network->layers = calloc(num_layers, sizeof(layer));
    if (!new_network->layers)
    {
        fprintf(stderr, "ERROR: Cannot allocate heap memory to array of layers->\n");
        new_network->num_layers = 0;
        new_network->layers = NULL;
        return;
    }

    new_network->num_layers = num_layers;
    for (size_t idx = 0; idx < num_layers; idx++)
    {
        new_network->layers[idx] = layer_init(input_sizes[idx], output_sizes[idx], funcs[idx]);
    }
}

void network_free(network *net)
{
    if (!net)
        return;
    if (net->layers)
    {
        for (size_t i = 0; i < net->num_layers; i++)
        {
            freeVector(&net->layers[i].biases);
            freeVector(&net->layers[i].prev_input);
            freeVector(&net->layers[i].prev_output);
            freeVector(&net->layers[i].prev_z);

            matrix_free(&net->layers[i].weights);

            net->layers[i].func = NULL;
            net->layers[i].input_size = 0;
            net->layers[i].output_size = 0;
        }

        free(net->layers);
    }
    net->layers = NULL;
    net->layers = 0;
}

vector network_forward_prop(network *net, vector *inputs)
{
    vector current;
    allocateVector(&current, inputs->length);
    vector_copy_into(&current, inputs);

    for (size_t idx = 0; idx < net->num_layers; idx++)
    {
        forward_prop_layer(current, &(net->layers[idx]));
        vector_copy_into(&current, &(net->layers[idx].prev_output));
    }

    return current;
}