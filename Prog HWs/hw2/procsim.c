#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "FCFS.c"

int main( int argc, char *argv[] )  {
    // ptr = fopen("fileopen","mode");
    DEVICE* cpu =  buildResource("CPU");
    DEVICE* io = buildResource("IO");
    int clock = 0;
    int CPU_algorithm = argv[1] == "-f" ? 0 : 1;

    queue_t ready_queue = queue_create();
    queue_t io_queue = queue_create();

    //change to srandom on csif
    (void) srand(12345);
    
	FILE* fp = fopen(argv[1], "r");
    if (fp == NULL) {
        perror("fopen");
        exit(EXIT_FAILURE);
    }

    char  line[255];
    
    while (fgets(line, sizeof(line), fp) != NULL)
    {
        PROC* p;
        p = generateProcess(line);
        queue_enqueue(ready_queue,p);
    }

    printf(" queue length %d\n", ready_queue->count);
    int cpu_run = 0;
    int io_run = 0;
    PROC curr_cpu_proc;
    PROC curr_io_proc;
    PROC ptr;
    int i = 0;

    while (ready_queue->count != 0 || io_queue->count != 0) {
        printf("loop : %d\n", i++);
        FCFS_ready(&curr_cpu_proc, &cpu_run, &io_run, ready_queue, io_queue, cpu, io, &ptr, &clock);
        FCFS_io(&curr_io_proc, &cpu_run, &io_run, ready_queue, io_queue, cpu, io, &ptr);
        clock++;
    }

    
    return 0;
}
    