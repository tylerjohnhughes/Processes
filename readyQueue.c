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
		PCB *pcb = PriorityQueue_dequeueFrom(queue, i);
		if (pcb != NULL) {
		    return pcb;
		}
		++i;
	}
	return NULL;
}

PCB *PriorityQueue_dequeueFrom(PriorityQueue *queue, int priority) {
    if (queue->queues[priority].head != NULL) {
        PCB *pcb = queue->queues[priority].head;
        queue->queues[priority].head = queue->queues[priority].head->next;
        if (queue->queues[priority].head == NULL) {
            queue->queues[priority].tail = NULL;
        }
        --queue->processes;
        return pcb;
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
	++queue->processes;
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
