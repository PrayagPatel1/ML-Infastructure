/*
    A unit test suite for activation.h
*/

#include "test_framework.h"
#include "../src/vector.h"
#include "../src/activation.h"

static void test_activation_sigmoid(void)
{
    test_seprator("Sigmoid Test");
    vector vec;
    allocateVector(&vec, 3);

    vec.elements[0] = 1.0f;
    vec.elements[1] = 2.0f;
    vec.elements[2] = 3.0f;

    activation_sigmoid(&vec);

    CHECK(float_eq(vec.elements[0], 0.731059f), "element 0: 0.731059");
    CHECK(float_eq(vec.elements[1], 0.880797f), "element 1: 0.880797");
    CHECK(float_eq(vec.elements[2], 0.952574f), "element 2: 0.952574");

    freeVector(&vec);
}

static void test_activation_sigmoid_derivative(void)
{
    test_seprator("Sigmoid Derivative Test");

    vector vec;
    allocateVector(&vec, 3);
    vec.elements[0] = 1.0f;
    vec.elements[1] = 2.0f;
    vec.elements[2] = 3.0f;

    activation_sigmoid_derivative(&vec);

    CHECK(float_eq(vec.elements[0], 0.196612f), "element 0: 0.196612");
    CHECK(float_eq(vec.elements[1], 0.104994f), "element 1: 0.104994");
    CHECK(float_eq(vec.elements[2], 0.045177f), "element 2: 0.045177");

    freeVector(&vec);
}

static void test_activation_relu(void)
{
    test_sperator("RELU Test");

    vector vec;
    allocateVector(&vec, 3);
    vec.elements[0] = 1.0f;
    vec.elements[1] = 2.0f;
    vec.elements[2] = 3.0f;

    activation_relu(&vec);

    CHECK(float_eq(vec.elements[0], 1.0f), "element 0: 1.0");
    CHECK(float_eq(vec.elements[1], 2.0f), "element 1: 2.0");
    CHECK(float_eq(vec.elements[2], 3.0f), "element 2: 3.0");

    freeVector(&vec);
}

static void test_activation_relu_derivative(void)
{
    test_sperator("RELU Derivative Test");

    vector vec;
    allocateVector(&vec, 3);
    vec.elements[0] = 1.0f;
    vec.elements[1] = 2.0f;
    vec.elements[2] = 3.0f;

    activation_relu_derivative(&vec);

    CHECK(float_eq(vec.elements[0], 1.0f), "element 0: 1.0");
    CHECK(float_eq(vec.elements[1], 1.0f), "element 1: 1.0");
    CHECK(float_eq(vec.elements[2], 1.0f), "element 2: 1.0");

    freeVector(&vec);
}

static void test_activation_softmax(void)
{
    test_sperator("Softmax Tests");

    vector vec;
    allocateVector(&vec, 3);
    vec.elements[0] = 1.0f;
    vec.elements[1] = 2.0f;
    vec.elements[2] = 3.0f;

    activation_softmax(&vec);

    CHECK(float_eq(vec.elements[0], 0.090031f), "element 0: 1.0");
    CHECK(float_eq(vec.elements[1], 0.244728f), "element 1: 1.0");
    CHECK(float_eq(vec.elements[2], 0.665241f), "element 2: 1.0");

    freeVector(&vec);
}

/* Main Test Entry Registry Point */

int main(void)
{
    test_activation_sigmoid();
    test_activation_sigmoid_derivative();

    test_activation_relu();
    test_activation_relu_derivative();

    test_activation_softmax();

    test_result();
}