#include <stdio.h>
#include "vector.h"

int main(void)
{
    vector vec1;
    vector vec2;

    allocateVector(&vec1, 4);
    vec1.elements[0] = 1.0f;
    vec1.elements[1] = 2.0f;
    vec1.elements[2] = 3.0f;
    vec1.elements[3] = 4.0f;

    allocateVector(&vec2, 4);
    vec2.elements[0] = 1.0f;
    vec2.elements[1] = 4.0f;
    vec2.elements[2] = 6.0f;
    vec2.elements[3] = 8.0f;

    vector result = addVector(&vec1, &vec2);

    printf("Vector Length: %zu \n", result.length);
    for (size_t idx = 0; idx < result.length; idx++)
    {
        printf("Vector Element [%zu]: %f (Memory Address: %p)\n", idx, result.elements[idx], (void *)&result.elements[idx]);
    }

    freeVector(&vec1);
    freeVector(&vec2);
    return 0;
}