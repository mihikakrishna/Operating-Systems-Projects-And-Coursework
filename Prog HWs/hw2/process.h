typedef struct process {
    char* name[10];
    float block_probability;
    int runtime;
    int io_time;
    int completeTime;
    int totalCPU;
    int givenCPU;
    int BlockedIO;
    int doingIO;
} PROC;

PROC* generateProcess(char *line) {
    struct process* tmp = (struct process*)malloc(sizeof(struct process));
    sscanf(line, "%10s %d %f", &tmp->name, &tmp->runtime, &tmp->block_probability);
    printf(" printr ya %10s %d %f\n", tmp->name, tmp->runtime, tmp->block_probability);
    tmp->io_time = 0;
    tmp->completeTime = 0;
    tmp->totalCPU = 0;
	tmp->givenCPU = 0;
	tmp->BlockedIO = 0;
    tmp->doingIO = 0;
    return tmp;
}

void displayProcess(struct process* p) {
    printf("name\ttotalCPU\tcompleteTime\tgivenCPU\tBlockedIO\tdoingIO\n");
    printf("%s\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", p->name, p->totalCPU, p->completeTime, p->givenCPU, p->BlockedIO, p->doingIO);
}