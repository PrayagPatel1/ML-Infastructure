#ifndef VECTOR_H
#define VECTOR_H

#include <stddef.h>

typedef struct vector
{
    float *elements;
    size_t length;
    int owner;
} vector;

void allocateVector(vector *vec, size_t length);
void freeVector(vector *vec);

vector addVector(vector *vec1, vector *vec2);
vector subVector(vector *vec1, vector *vec2);
void scaleVector(vector *vec, float scalar);

void normalizeVector(vector *vec);

#endif