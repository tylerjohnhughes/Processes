/**
 * processes.c
 *
 * @author Tyler Hughes, Audrey Chavarria
 */

#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "readyQueue.h"

/* These constants define the percent of randomly generated processes that will
 * be generated for each priority. Low priority takes whatever is not high or
 * medium priority. */
#define HIGH_PRIORITY_PERCENT 5
#define MEDIUM_PRIORITY_PERCENT 65

/* These constants describe how many priority classes are devoted to each of
 * high, medium, and low priority objects. These indicate how the scheduler
 * will treat priorities by their integer value. */
#define HIGH_PRIORITY_CLASSES 2
#define MEDIUM_PRIORITY_CLASSES (PRIORITY_CLASSES - HIGH_PRIORITY_CLASSES\
        - LOW_PRIORITY_CLASSES)
#define LOW_PRIORITY_CLASSES 2

/* These constants indicate the chance (of 100) that a process of a given
 * priority class will terminate after being given CPU time. */
#define HIGH_PRIORITY_TERM 5
#define MEDIUM_PRIORITY_TERM 1
#define LOW_PRIORITY_TERM 1

/* 
 * */
#define HIGH_PRIORITY_SCALE 4
#define MEDIUM_PRIORITY_SCALE 2
#define LOW_PRIORITY_SCALE 1

/* Indicates how many processes should be generated to populate the priority
 * queue. */
#define PROCESS_COUNT 100

// The amount of time (microseconds) given to a process when it is scheduled.
#define QUANTUM 1

/**
 * Generates a process with a pseudo-random priority.
 * @return The generated process.
 */
PCB *generateProcess(void);

/**
 * Pseudo-randomly indicates whether a process should terminate.
 * @param pcb The process that may be terminated.
 * @return Returns 1 if the process should terminate, otherwise 0.
 */
int terminate(PCB *pcb);

void dispatch(int scale);


int main(int argc, char *argv[]) {
    PriorityQueue queue = {};
    PCB *pcb;
    
    // Seed rand before generating processes.
    srand(time(NULL));
    
    // Populate the priority queue with random processes.
    for (int i = 0; i < PROCESS_COUNT; ++i) {
        pcb = generateProcess();
        pcb->processID = i;
        printf("Creating: Process(PID=%d, Priority=%d)\n", pcb->processID,
                pcb->priority);
        PriorityQueue_enqueue(&queue, pcb);
    }
    
    // Schedule processes until none exist.
    int class = 0;
    while (queue.processes > 0) {
        if (class >= PRIORITY_CLASSES) {
            class = 0;
        }
        pcb = PriorityQueue_dequeueFrom(&queue, class);
        if (pcb == NULL) {
            ++class;
            continue;
        }
        printf("Dequeuing: Process(PID=%d, Priority=%d)\n", pcb->processID,
                pcb->priority);
        
        /* Give the process a variable amount of time depending on its priority
         * class */
        if (pcb->priority < HIGH_PRIORITY_CLASSES) {
            dispatch(HIGH_PRIORITY_SCALE);
        } else if (pcb->priority < HIGH_PRIORITY_CLASSES + MEDIUM_PRIORITY_CLASSES) {
            dispatch(MEDIUM_PRIORITY_SCALE);
        } else {
            dispatch(LOW_PRIORITY_SCALE);
        }
        
        if (terminate(pcb)) {
            printf("Terminating: Process(PID=%d, Priority=%d)\n",
                pcb->processID, pcb->priority);
            free(pcb);
        } else {
            printf("Enqueuing: Process(PID=%d, Priority=%d)\n",
                pcb->processID, pcb->priority);
            PriorityQueue_enqueue(&queue, pcb);
        }
        
        ++class;
    }
    
    return 0;
}

PCB *generateProcess(void) {
    PCB *pcb = (PCB *) malloc(sizeof(PCB));
    
    // Determine which priority class the process will belong to.
    int class = rand() % 100;
    
    /* High priority is assigned to the lowest priority values, medium to the
     * next highest, and low to the very highest. */
    if (class < HIGH_PRIORITY_PERCENT) {
        pcb->priority = rand() % HIGH_PRIORITY_CLASSES;
    } else if (class < HIGH_PRIORITY_PERCENT + MEDIUM_PRIORITY_PERCENT) {
        pcb->priority = HIGH_PRIORITY_CLASSES +
                (rand() % MEDIUM_PRIORITY_CLASSES);
    } else {
        pcb->priority = HIGH_PRIORITY_CLASSES + MEDIUM_PRIORITY_CLASSES +
                (rand() % LOW_PRIORITY_CLASSES);
    }
    
    return pcb;
}

int terminate(PCB *pcb) {
    /* Generate a value that will be used to determine if the process should
     * terminate. */
    int terminateValue = rand() % 100;

    /* Depending on the process's priority class, determine whether it should
     * terminate. */
    if (pcb->priority < HIGH_PRIORITY_CLASSES) {
        return terminateValue < HIGH_PRIORITY_TERM;
    } else if (pcb->priority < HIGH_PRIORITY_CLASSES + MEDIUM_PRIORITY_CLASSES) {
        return terminateValue < MEDIUM_PRIORITY_TERM;
    } else {
        return terminateValue < LOW_PRIORITY_TERM;
    }
}

void dispatch(int scale) {
    usleep(scale * QUANTUM);
}
