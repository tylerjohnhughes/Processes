/**
 * readyQueue.h
 *
 * @author Tyler Hughes, Audrey Chavarria
 */

#ifndef READY_QUEUE_H
#define READY_QUEUE_H

#define PRIORITY_CLASSES 64


typedef enum {
    NEW,
    READY,
    RUNNING,
    WAITING,
    HALTED
} StateType;


typedef struct pcb {
    struct pcb *next;
    int processID;
    int priority;
    StateType state;
} PCB;

typedef struct fifo_queue {
    PCB *head;
    PCB *tail;
} FIFOQueue;

typedef struct priority_queue {
    FIFOQueue queues[PRIORITY_CLASSES];
} PriorityQueue;


PCB *PriorityQueue_dequeue(PriorityQueue *queue);

void PriorityQueue_enqueue(PriorityQueue *queue, PCB *pcb);

PCB *PriorityQueue_peekProcess(PriorityQueue *queue, int processID);


#endif // READY_QUEUE_H
