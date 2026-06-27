#include "loss.h"

float mean_squared_error(vector *predicted_outputs, vector *true_outputs)
{
    size_t total_samples_avg = 1.0f / (true_outputs->length);

    float err = 0.0f;
    for (size_t idx = 0; idx < true_outputs->length; idx++)
    {
        err += powf((true_outputs->elements[idx] - predicted_outputs->elements[idx]), 2);
    }

    return err * total_samples_avg;
}