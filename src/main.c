/* C Standard Libraries */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>

/* Neural Network Custom Headers */
#include "vector.h"
#include "matrix.h"
#include "activation.h"
#include "layer.h"
#include "network.h"
#include "loss.h"

int main(void)
{
    /* XOR Neural Network -- with forward pass */
    float data[4][2] = {
        {0.0f, 1.0f},
        {1.0f, 0.0f},
        {0.0f, 0.0f},
        {1.0f, 1.0f}};

    network xor_net;
    int input_sizes[] = {2, 4};
    int output_sizes[] = {4, 1};
    activation_func funcs[] = {activation_sigmoid, activation_sigmoid};

    network_init(&xor_net, 2, input_sizes, output_sizes, funcs);

    for (int i = 0; i < 4; i++)
    {
        vector input;
        allocateVector(&input, 2);
        input.elements[0] = data[i][0];
        input.elements[1] = data[i][1];

        vector predicted_vals = network_forward_prop(&xor_net, &input);

        printf("(%f, %f) -> %f\n",
               input.elements[0], input.elements[1], predicted_vals.elements[0]);

        freeVector(&input);
        freeVector(&predicted_vals);
    }

    network_free(&xor_net);

    /* Backpropagation Algorithm Implementation */

    return 0;
}