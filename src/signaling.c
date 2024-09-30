#include "signaling.h"

QueueHandle_t queue;

/**
 * Takes in data from signal_request_calculate(), adds 5 to the input, 
 * and sends modified data back.
 */
void signal_handle_calculation(SemaphoreHandle_t request, SemaphoreHandle_t response, struct signal_data *data)
{
    xSemaphoreTake(request, portMAX_DELAY);
    data->output = data->input + 5;
    xSemaphoreGive(response);
    xSemaphoreGive(request);
}

/**
 * This is the function that is getting called
 * This function will take in the semaphores and the data, and pass it off to
 * signal_handle_calculation(). 
 */
BaseType_t signal_request_calculate(SemaphoreHandle_t request, SemaphoreHandle_t response, struct signal_data *data)
{
    int32_t input = data->input;
    xSemaphoreGive(request);
    signal_handle_calculation(request, response, data);
    xSemaphoreTake(response, portMAX_DELAY);
    xSemaphoreGive(response);
}