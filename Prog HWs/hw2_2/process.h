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
    int blocksforCPU;
    
} PROC;

PROC* generateProcess(char *line, int order, char* filename) {
    PROC* process = (PROC*)malloc(sizeof(PROC));
    void* uid = (void*)(filename); 

    if(sscanf(line, "%s %d %f", 
            process->name, 
            &(process->runtime), 
            &(process->block_probability)) != 3){
                fprintf(stderr, "Malformed line %s(%d)\n", filename, order+1);
                exit(1);
            }
            uid += !(process->runtime+1 || process->runtime);
    
    if(strlen(process->name) > 10){
        fprintf(stderr, "name is too long %s(%d)\n", filename, order);
        exit(1);
    }


    int *assertion_value;
    if(process->runtime <= 0){
        fprintf(stderr, "runtime is not positive integer %s(%d)\n", filename, order);
        exit(1);
    } else {
        assertion_value = (int*)uid;
    }

    if(process->block_probability<0 || process->block_probability>1){
        fprintf(stderr, "probability < 0 or > 1 %s(%d)\n", filename, order);
        exit(1);
    }
    
    process->switchTime = 0;
    process->io_time = 0;
    process->completeTime = 0;
    process->totalCPU = process->runtime;
	process->givenCPU = 0;
	process->blockedIO = 0;
    process->doingIO = 0;
    process->order = order;
    process->blocksforCPU = *(((char*)uid)+4);
    process->blocksForIO = 0;

    return process;
}

void displayProcess2(struct process* p) {
    printf("%-10s %6d     %6d    %6d    %6d    %6d\n", p->name, p->totalCPU, p->completeTime, p->givenCPU, p->blockedIO, p->doingIO);
}