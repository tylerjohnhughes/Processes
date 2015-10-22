/**
 * readyQueue.c
 *
 * @author Tyler Hughes, Audrey Chavarria
 */

#include <stdio.h>
#include "readyQueue.h"


PCB *PriorityQueue_dequeue(PriorityQueue *queue) {
    int i = 0;
	while (i < PRIORITY_CLASSES) {
		while (queue->queues[i].head != NULL) {
            PCB *pcb = queue->queues[i].head;
			queue->queues[i].head = queue->queues[i].head->next;
			return pcb;
		}
		i++;
	}
	return NULL;
}

void PriorityQueue_enqueue(PriorityQueue *queue, PCB *pcb) {
	pcb->next = NULL;
	int i = pcb->priority;
	if (queue->queues[i].tail == NULL) {
        queue->queues[i].head = pcb;
        queue->queues[i].tail = pcb;
	} else {
		queue->queues[i].tail->next = pcb;
		queue->queues[i].tail = pcb;
	}
}

PCB *PriorityQueue_peekProcess(PriorityQueue *queue, int processID) {
    PCB *curr;
    for (int i = 0; i < PRIORITY_CLASSES; ++i) {
        curr = queue->queues[i].head;
        while (curr != NULL) {
            if (curr->processID == processID) {
                return curr;
            }
            curr = curr->next;
		}
    }
    return NULL;
}
