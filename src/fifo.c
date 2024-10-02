#include "fifo.h"

void fifo_worker_handler(QueueHandle_t requests, QueueHandle_t results, int id)
{
    while (1)
    {
        struct request_msg msg;
        xQueueReceive(requests, &msg, portMAX_DELAY);
        msg.output = msg.input + 5;
        msg.handled_by = id;
        xQueueSendToBack(results, &msg, portMAX_DELAY);
    }
}