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
    network_init(&net, 3, 2, 1, activation_sigmoid);

    CHECK(net.num_layers == 2, "Number of layers properly set");
    CHECK(net.layers != NULL, "Layers of network allocated");

    network_free(&net);

    CHECK(net.num_layers == 0, "Number of layers set properly after freeing");
    CHECK(net.layers == NULL, "Layers of network are freed");
}

static test_network_forward_pass(void)
{
}

int main(void)
{
    test_network_init_and_free();
    test_network_free();
    // test_network_forward_pass();

    test_result();
}