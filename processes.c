#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include "readyQueue.h"

/* These constants define the percent of randomly generated processes that will
 * be generated for each priority. Low priority takes whatever is not high or
 * medium priority. */
#define HIGH_PRIORITY_PERCENT 10
#define MEDIUM_PRIORITY_PERCENT 70

/* These constants describe how many priority classes are devoted to each of
 * high, medium, and low priority objects. These indicate how the scheduler
 * will treat priorities by their integer value. */
#define HIGH_PRIORITY_CLASSES 2
#define MEDIUM_PRIORITY_CLASSES (PRIORITY_CLASSES - HIGH_PRIORITY_CLASSES\
        - LOW_PRIORITY_CLASSES)
#define LOW_PRIORITY_CLASSES 2

/* Indicates how many processes should be generated to populate the priority
 * queue. */
#define PROCESS_COUNT 1000

/**
 * Generates a process with a pseudo-random priority.
 * @return The generated process.
 */
PCB *generateProcess(void);


int main(int argc, char *argv[]) {
    PriorityQueue queue = {};
    
    // Seed rand before generating processes.
    srand(time(NULL));
    
    // Populate the priority queue with random processes.
    PCB *pcb;
    for (int i = 0; i < PROCESS_COUNT; ++i) {
        pcb = generateProcess();
        PriorityQueue_enqueue(&queue, pcb);
    }
    
    return 0;
}

PCB *generateProcess(void) {
    PCB *pcb = (PCB *)malloc(sizeof(PCB));
    
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