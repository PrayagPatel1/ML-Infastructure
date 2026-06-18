#include "activation.h"

void activation_sigmoid(vector *vec)
{
    for (size_t idx = 0; idx < vec->length; idx++)
    {
        vec->elements[idx] = 1.0f / (1.0f + expf(-1.0f * (vec->elements[idx])));
    }
}
void activation_sigmoid_derivative(vector *vec)
{
    activation_sigmoid(vec);
    for (size_t idx = 0; idx < vec->length; idx++)
    {
        vec->elements[idx] = vec->elements[idx] * (1 - vec->elements[idx]);
    }
}

void activation_relu(vector *vec)
{
    for (size_t idx = 0; idx < vec->length; idx++)
    {
        vec->elements[idx] = fmax(0.0f, vec->elements[idx]);
    }
}
void activation_relu_derivative(vector *vec)
{
    for (size_t idx = 0; idx < vec->length; idx++)
    {
        vec->elements[idx] = vec->elements[idx] < 0.0f ? 0.0f : 1.0f;
    }
}

void activation_softmax(vector *vec)
{
    float sum = 0;
    for (size_t idx = 0; idx < vec->length; idx++)
    {
        vec->elements[idx] = expf(vec->elements[idx]);
        sum += vec->elements[idx];
    }
    for (size_t idx = 0; idx < vec->length; idx++)
    {
        vec->elements[idx] /= sum;
    }
}