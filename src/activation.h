#ifndef ACTIVATION_H
#define ACTIVATION_H

#include <math.h>
#include "vector.h"

void activation_sigmoid(vector *vec);
void activation_sigmoid_derivative(vector *vec); 

void activation_relu(vector *vec); 
void activation_relu_derivative(vector *vec); 

void activation_softmax(vector *vec);
#endif