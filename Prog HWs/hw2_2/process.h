typedef struct process {
    char name[10];
    float block_probability;
    int runtime;
    int switchTime;
    int io_time;

    int completeTime;
    int totalCPU;
    int givenCPU;
    int blockedIO;
    int doingIO;

    int order;
    int blocksForIO;
    
} PROC;

PROC* generateProcess(char *line, int order) {
    PROC* process = (PROC*)malloc(sizeof(PROC));

    sscanf(line, "%10s %d %f", 
            process->name, 
            &(process->runtime), 
            &(process->block_probability));

    process->switchTime = 0;
    process->io_time = 0;
    process->completeTime = 0;
    process->totalCPU = 0;
	process->givenCPU = 0;
	process->blockedIO = 0;
    process->doingIO = 0;
    process->order = order;
    process->blocksForIO = 0;

    return process;
}

void displayProcess2(struct process* p) {
    printf("name\ttotalCPU\tcompleteTime\tgivenCPU\tBlockedIO\tdoingIO\n");
    printf("%s\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", p->name, p->totalCPU, p->completeTime, p->givenCPU, p->blockedIO, p->doingIO);
}