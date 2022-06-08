void displayProcessHeader(char* name) {
    printf("%15s%15s%15s%15s%15s%15s%15s%15s%15s%15s%15s\n", 
        name,
        "blockProb",
        "runtime",
        "switchTime",
        "io_time",
        "completeTime",
        "totalCPU",
        "givenCPU",
        "blockedIO",
        "doingIO",
        "order");
}

void displayProcess(struct process* p) {
    printf("%15s%15f%15d%15d%15d%15d%15d%15d%15d%15d%15d\n", 
            p->name,
            p->block_probability,
            p->runtime,
            p->switchTime,
            p->io_time,
            p->completeTime,
            p->totalCPU,
            p->givenCPU,
            p->blockedIO,
            p->doingIO,
            p->order);
}

void print_header(char* name) {
    char divider[] = "---------------------------------------------------------------------------------------------------------------------------------------------------------------------";
    printf("%s\n", divider);
    displayProcessHeader(name);
    printf("%s\n", divider);
}

void print_queue(char* name, queue_t queue) {
	print_header(name);

	struct node* currentNode = queue->head;
	if (currentNode == NULL) goto END;

	struct node* nextNode = queue->head->next;

	while (currentNode != NULL) {
		displayProcess(currentNode->value);

		currentNode = currentNode->next;
		if(nextNode != NULL && nextNode->next != NULL)
			nextNode = nextNode->next;
	}

	END:
    printf("\n\n");
}

void print_cpu(char* name, int cpu_running, PROC* cpu_proccess) {
    print_header(name);
	if (cpu_running == 1) displayProcess(cpu_proccess);
    printf("\n\n");
}