/**
 * A manual test suite for network.c
 */

#include "test_framework.h"
#include "../src/activation.h"
#include "../src/network.h"

static void test_network_init_and_free(void)
{
    test_sperator("Network: Initalization Test");

    network net;
    int input_sizes[] = {0, 2, 2};
    int output_sizes[] = {2, 2, 1};
    activation_func funcs[] = {activation_sigmoid};
    network_init(&net, 3, input_sizes, output_sizes, funcs);

    CHECK(net.num_layers == 3, "Number of layers properly set");
    CHECK(net.layers != NULL, "Layers of network allocated");

    network_free(&net);

    CHECK(net.num_layers == 0, "Number of layers set properly after freeing");
    CHECK(net.layers == NULL, "Layers of network are freed");
}

// static void test_network_forward_pass(void)
// {
// }

int main(void)
{
    test_network_init_and_free();
    // test_network_forward_pass();

    test_result();
}