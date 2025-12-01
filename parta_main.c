// Daniel Guerrero
// W00427795
#include "parta.h"
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("ERROR: Missing arguments\n");
        return 1;
    }

    char* mode = argv[1];

    if (strcmp(mode, "fcfs") == 0) {
        if (argc < 3) {
            printf("ERROR: Missing arguments\n");
            return 1;
        }

        int plen = argc - 2;
        int* bursts = (int*)malloc(sizeof(int) * plen);
        for (int i = 0; i < plen; ++i) bursts[i] = atoi(argv[2 + i]);

        struct pcb* procs = init_procs(bursts, plen);

        printf("Using FCFS\n\n");
        for (int i = 0; i < plen; ++i) {
            printf("Accepted P%d: Burst %d\n", i, bursts[i]);
        }

        int total = fcfs_run(procs, plen);

        double sumwait = 0.0;
        for (int i = 0; i < plen; ++i) sumwait += procs[i].wait;
        double avg = plen > 0 ? (sumwait / (double)plen) : 0.0;
        printf("Average wait time: %.2f\n", avg);

        free(bursts);
        free(procs);
        return 0;
    } else if (strcmp(mode, "rr") == 0) {
        if (argc < 4) {
            printf("ERROR: Missing arguments\n");
            return 1;
        }

        int quantum = atoi(argv[2]);
        int plen = argc - 3;
        int* bursts = (int*)malloc(sizeof(int) * plen);
        for (int i = 0; i < plen; ++i) bursts[i] = atoi(argv[3 + i]);

        struct pcb* procs = init_procs(bursts, plen);

        printf("Using RR(%d)\n\n", quantum);
        for (int i = 0; i < plen; ++i) {
            printf("Accepted P%d: Burst %d\n", i, bursts[i]);
        }

        int total = rr_run(procs, plen, quantum);

        double sumwait = 0.0;
        for (int i = 0; i < plen; ++i) sumwait += procs[i].wait;
        double avg = plen > 0 ? (sumwait / (double)plen) : 0.0;
        printf("Average wait time: %.2f\n", avg);

        free(bursts);
        free(procs);
        return 0;
    } else {
        printf("ERROR: Missing arguments\n");
        return 1;
    }
}
