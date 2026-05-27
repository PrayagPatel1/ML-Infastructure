#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "vector.h"

void allocateVector(vector *vec, size_t length)
{
    float *elements = malloc(length * sizeof(float));
    if (!elements)
    {
        perror("ERROR: element field has not been assigned properly");
        return;
    }
    vec->elements = elements;
    memset(vec->elements, 0, length * sizeof(float));
    vec->length = length;
}

void freeVector(vector *vec)
{
    if (!vec)
        return;
    free(vec->elements);
    vec->elements = NULL;
    vec->length = 0;
}

vector addVector(vector *vec1, vector *vec2)
{
    vector result;
    if (vec1->length != vec2->length)
    {
        return (vector){NULL, 0};
    }
    allocateVector(&result, vec1->length);

    for (size_t idx = 0; idx < result.length; idx++)
    {
        result.elements[idx] = vec1->elements[idx] + vec2->elements[idx];
    }

    return result;
}

vector subVector(vector *vec1, vector *vec2)
{
    vector result;
    if (vec1->length != vec2->length)
    {
        return (vector){NULL, 0};
    }
    allocateVector(&result, vec1->length);

    for (size_t idx = 0; idx < result.length; idx++)
    {
        result.elements[idx] = vec1->elements[idx] - vec2->elements[idx];
    }

    return result;
}

void scaleVector(vector *vec, float scalar)
{
    for (size_t idx = 0; idx < vec->length; idx++)
    {
        vec->elements[idx] *= scalar;
    }
}