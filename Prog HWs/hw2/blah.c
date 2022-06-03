#include <stdio.h>
#include <stdlib.h>
#include "process.h"
#include "device.h"
#include "queue.h"


int dispatch(PROC* curr_cpu_proc, int* cpu_run, int* io_run, queue_t ready_queue, queue_t io_queue, DEVICE* cpu, DEVICE* io,  struct process* ptr, int* clock){
    float randnum;

    if(*cpu_run == 0){
        *curr_cpu_proc = *(PROC*)(ready_queue->head->value);
        randnum = ((float) rand() / (RAND_MAX));
    }

    if( randnum < curr_cpu_proc->block_probability){
        if(io_queue->count > 0) curr_cpu_proc->BlockedIO++;
        queue_dequeue(ready_queue, (void**)&ptr);
        queue_enqueue(io_queue, curr_cpu_proc);
        io->number++;
        *cpu_run = 0;
    }else{
        *cpu_run = 1;
    }
    return 0;
}
int run_cpu(PROC* curr_cpu_proc, int* cpu_run, int* io_run, queue_t ready_queue, queue_t io_queue, DEVICE* cpu, DEVICE* io,  struct process* ptr, int* clock){
    
    
    //if(ready_queue->count == 0) cpu->idle++;
    printf("\nready queue length %d\n", ready_queue->count);
    
    if(ready_queue->count == 0){
        printf("\nready queue empty\n");
        cpu->idle++;
        return 0;
    }
    
    printf("\nready queue length %d\n", ready_queue->count);
    if(*cpu_run == 1){
        if(curr_cpu_proc->runtime > 0){
            curr_cpu_proc->runtime--;
            curr_cpu_proc->totalCPU++;
            curr_cpu_proc->givenCPU++;
            cpu->busy++;
            *cpu_run = 1;
        }else{
            curr_cpu_proc->completeTime = *clock;
            queue_dequeue(ready_queue, (void**)&ptr);
            *cpu_run = 0;
        }
        printf("runtime: %d\n", curr_cpu_proc->runtime);
        printf("\ncurr cpu proc\n");
        displayProcess(curr_cpu_proc);
        printf("\n");
    }
    return 0;
}

int run_io(PROC* curr_io_proc, int* cpu_run, int* io_run, queue_t ready_queue, queue_t io_queue, DEVICE* cpu, DEVICE* io, struct process* ptr){

    if(io_queue->count == 0){
        io->idle++;
        return 0;
    }

    if(*io_run == 0){
        *curr_io_proc = *(PROC*)(io_queue->head->value);
        curr_io_proc->io_time = (rand() % (30 - 1 + 1)) + 1;
        printf("%s rand io time : %d\n", curr_io_proc->name, curr_io_proc->io_time );
    }
    
    if(curr_io_proc->io_time > 0){
        curr_io_proc->io_time--;
        curr_io_proc->doingIO++;
        io->busy++;
        *io_run = 1;   
    }
    
    else{
        *io_run = 0;
        queue_dequeue(io_queue, (void**)&ptr);
        queue_enqueue(ready_queue, curr_io_proc);
        cpu->number++;
    }
    printf("\ncurr io proc\n");
    displayProcess(curr_io_proc);
    printf("\n"); 
    return 0;
}

