#include "fifo.h"

void fifo_worker_handler(QueueHandle_t requests, QueueHandle_t results, int id)
{
    while (1)
    {
        struct request_msg msg;                         // Setup struct
        xQueueReceive(requests, &msg, portMAX_DELAY);   // Get data from queue
        msg.output = msg.input + 5;                     // Add 5 to input, save to output
        msg.handled_by = id;                            // Save worker thread id
        xQueueSendToBack(results, &msg, portMAX_DELAY); // Send data back
    }
}