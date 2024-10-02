#include "signaling.h"

QueueHandle_t queue;

/**
 * Takes in data from signal_request_calculate(), adds 5 to the input,
 * and sends modified data back.
 */
void signal_handle_calculation(SemaphoreHandle_t request, SemaphoreHandle_t response, struct signal_data *data)
{
    xSemaphoreTake(request, portMAX_DELAY); // Wait for semaphore to stop blocking
    data->output = data->input + 5;         // Add 5 to input, save to output
    vTaskDelay(10);                         // Delay cuz idk why
    xSemaphoreGive(response);               // Unblock semaphore to finish response
}

/**
 * This is the function that is getting called
 * This function will take in the semaphores and the data, and pass it off to
 * signal_handle_calculation().
 */
BaseType_t signal_request_calculate(SemaphoreHandle_t request, SemaphoreHandle_t response, struct signal_data *data)
{
    xSemaphoreGive(request);                           // Unblock semaphore to finish request
    BaseType_t result = xSemaphoreTake(response, 100); // Wait for other function to finish logic
    return result;
}