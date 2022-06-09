#include <string.h>
typedef struct device {
    char *name; // CPU or IO
    int busy;
    int idle;
    double utilization; // = (double)busy / (double)(busy + idle);
    int number; // dispatches or IO time
    double throughput;
} DEVICE;

struct device* buildResource(char *name) {
    struct device* tmp = (struct device*)malloc(sizeof(struct device));
    tmp->name = name;
    tmp->busy = 0;
    tmp->idle = 0;
    tmp->utilization = 0;
    tmp->number = 0;
    tmp->throughput = 0;
    return tmp;
}

void displayResource(struct device* dev) {
    if(strcmp(dev->name, "CPU")==0) {
        printf("\n%s:\n", "CPU");
        double busy = (double) dev->busy;
        double idle = (double) dev->idle;
        double number = (double) dev->number;
        printf("Total time spent busy: %d\n", dev->busy);
        printf("Total time spent idle: %d\n", dev->idle);
        printf("CPU utilization: %.2f\n", busy/(busy + idle));
        printf("Number of dispatches: %d\n", dev->number);
        printf("Overall throughput: %.2f\n",dev->throughput);
    }
    else if(strcmp(dev->name, "IO")==0) {
        printf("\n%s:\n", "I/O device");
        double busy = (double) dev->busy;
        double idle = (double) dev->idle;
        double number = (double) dev->number;
        printf("Total time spent busy: %d\n", dev->busy);
        printf("Total time spent idle: %d\n", dev->idle);
        printf("I/O utilization: %.2f\n", busy/(busy + idle));
        printf("Number of dispatches: %d\n", dev->number);
        printf("Overall throughput: %.2f\n", dev->throughput);
    }
    else {
        printf("Error Resource Type");
    }
}