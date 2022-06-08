#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "process.h"
#include "device.h"
#include "queue.h"
#include "debug.h"

int cmpfunc(const void *a, const void *b) {
  return (((PROC*)b)->order) - (((PROC*)a)->order);
}

void readInput(char* filename, queue_t queue){
    FILE* file_ptr = fopen(filename, "r");
    if (file_ptr == NULL) {
        perror("fopen");
        exit(EXIT_FAILURE);
    }

    char  line[255];
    unsigned order = 0;
    while (fgets(line, sizeof(line), file_ptr) != NULL)
    {
        PROC* process = generateProcess(line, order++);
        queue_enqueue(queue, process);
    }

    fclose(file_ptr);
}

// If CPU not running, send 1st process in ready queue to CPU
// When sending to CPU, determine whether or not you block for IO
void dispatch(queue_t ready_q, queue_t io_q, int* cpu_running, PROC** cpu_proccess) {
    if(ready_q->count == 0 || *cpu_running) return;

    PROC* tmp;
    PROC* curr_process = ready_q->head->value;

    queue_dequeue(ready_q, (void**)&tmp);

    if (curr_process->runtime == 1) {
        curr_process->runtime = 1;
        curr_process->switchTime = -1;
        goto END_DISPATCH;
    }

    float random_probability = (float)random() / (float)RAND_MAX; // Random Float [0,1]
    printf("\nrand num %f\n",random_probability );
    if (random_probability < curr_process->block_probability) {
        curr_process->switchTime = 
            (curr_process->runtime < 2) 
                ? -1 
                : (random() % (curr_process->runtime)) + 1; // Random Integer [1,runtime]
        if (curr_process->runtime >= 2)
            printf("\nrand switch time: %d\n",curr_process->switchTime );
    } else {
        curr_process->switchTime = -1;
    }

    END_DISPATCH:
    *cpu_running = 1;
    *cpu_proccess = curr_process;
}

// When SwitchTime is up, then move process to IO Queue
// When RunTime is up, move process to completed array
void run_cpu(queue_t io_q, int* cpu_running, PROC* cpu_proccess, PROC** completed_processes, int* completed_processes_length, int clock_cycle, int* switching_to_io) {
    if (*cpu_running == 0) return;

    cpu_proccess->totalCPU += 1;
    cpu_proccess->runtime -= 1;
    cpu_proccess->switchTime -= 1;

    if (cpu_proccess->switchTime == 0) {
        *switching_to_io = cpu_proccess->order;
        cpu_proccess->io_time = -1;
        queue_enqueue(io_q, cpu_proccess);
        *cpu_running = 0;
    } else if (cpu_proccess->runtime == 0) {
        cpu_proccess->completeTime = clock_cycle + 1;
        completed_processes[(*completed_processes_length)++] = cpu_proccess;

        *cpu_running = 0;
    }
}

// Set IO time upon first seeing the item
// Every subsequent cycle, decrement io_time
// When IO time is up, send to ready queue
void run_io(queue_t ready_q, queue_t io_q, int* switching_to_io) {
    if (io_q->count == 0) return;
    

    PROC* curr_process = io_q->head->value;

    // if this process just came into io, skip it
    if(*switching_to_io == curr_process->order){
        *switching_to_io = -1;
        return;
    } else { 
        *switching_to_io = -1;
    }

    if (curr_process->runtime == 0) { // bishops edge case
        curr_process->io_time = 1;
        curr_process->runtime = 1;
    } else if (curr_process->io_time == -1) { // if 1st time seeing it, generate random iotime

        curr_process->io_time = (random() % (30) + 1); // Random Integer [1,30]
        printf("io rand time : %d\n",curr_process->io_time);
    }

    curr_process->io_time -= 1;

    if (curr_process->io_time == 0) {
        PROC* tmp;
        queue_dequeue(io_q, (void**)&tmp);
        queue_enqueue(ready_q, curr_process);
    }
}

int main( int argc, char *argv[]) {
    (void) srandom(12345);

    queue_t ready_q = queue_create();
    queue_t io_q = queue_create();

    DEVICE* cpu = buildResource("CPU");
    DEVICE* io = buildResource("IO");

    int cpu_running = 0;
    PROC* cpu_proccess;

    readInput(argv[1], ready_q);

    int total_processes = ready_q->count;

    PROC* completed_processes[total_processes];
    int completed_processes_length = 0;

    int switching_to_io = -1;

    int clock_cycle = 1;
    while(total_processes > completed_processes_length) {
        // Debug Statements
        printf("\nTICK %d\n", clock_cycle);
        print_queue("READY QUEUE", ready_q);
        print_queue("IO QUEUE", io_q);
        print_cpu("CPU", cpu_running, cpu_proccess);

        dispatch(ready_q, io_q, &cpu_running, &cpu_proccess);
        run_cpu(io_q, &cpu_running, cpu_proccess, completed_processes, &completed_processes_length, clock_cycle++, &switching_to_io);
        run_io(ready_q, io_q, &switching_to_io);

        printf("\n\n\n\n\n");
    }

    printf("The total cycles are %d\n\n\n", clock_cycle);

    qsort(completed_processes, completed_processes_length, sizeof(PROC*), cmpfunc);

    //displayProcessHeader("Processes");
    for (int i=0; i<completed_processes_length; i++) {
        displayProcess2(completed_processes[i]);
    }
    displayResource(cpu);
    displayResource(io);

} 
