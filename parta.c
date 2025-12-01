// Daniel Guerrero
// W00427795
#include "parta.h"
#include <stdlib.h>
#include <stdio.h>

/**
 * TODO: Describe what the function does
 */
struct pcb* init_procs(int* bursts, int blen) {
    if (blen <= 0) return NULL;
    struct pcb* procs = (struct pcb*)malloc(sizeof(struct pcb) * blen);
    if (procs == NULL) return NULL;
    for (int i = 0; i < blen; ++i) {
        procs[i].pid = i;
        procs[i].burst_left = bursts[i];
        procs[i].wait = 0;
    }
    return procs;
}

/**
 * TODO: Describe what the function does
 */
void printall(struct pcb* procs, int plen) {

    if (procs == NULL || plen <= 0) return;
    for (int i = 0; i < plen; ++i) {
        printf("P%d: burst=%d wait=%d\n", procs[i].pid, procs[i].burst_left, procs[i].wait);
    }
}

/**
 * TODO: Describe what the function does
 */
void run_proc(struct pcb* procs, int plen, int current, int amount) {
    if (procs == NULL || plen <= 0) return;
    if (current < 0 || current >= plen) return;

    int actual = amount;
    if (actual < 0) actual = 0;
    if (procs[current].burst_left < actual) {
        actual = procs[current].burst_left;
    }

    
    procs[current].burst_left -= actual;
    if (procs[current].burst_left < 0) procs[current].burst_left = 0;


    for (int i = 0; i < plen; ++i) {
        if (i == current) continue;
        if (procs[i].burst_left > 0) {
            procs[i].wait += actual;
        }
    }
}

/**
 * TODO: Describe what the function does
 */
int fcfs_run(struct pcb* procs, int plen) {
    if (procs == NULL || plen <= 0) return 0;
    int time = 0;
    for (int i = 0; i < plen; ++i) {
        if (procs[i].burst_left <= 0) continue;
        int amount = procs[i].burst_left;
        run_proc(procs, plen, i, amount);
        time += amount;
    }
    return time;
}

/**
 * TODO: Describe what the function does
 */
int rr_next(int current, struct pcb* procs, int plen) {
    if (procs == NULL || plen <= 0) return -1;

    
    int any = 0;
    for (int i = 0; i < plen; ++i) {
        if (procs[i].burst_left > 0) { any = 1; break; }
    }
    if (!any) return -1;


    int start = (current + 1) % plen;
    for (int i = 0; i < plen; ++i) {
        int idx = (start + i) % plen;
        if (procs[idx].burst_left > 0) return idx;
    }


    if (current >= 0 && current < plen && procs[current].burst_left > 0) return current;
    return -1;
}
/**
 * TODO: Describe what the function does
 */
int rr_run(struct pcb* procs, int plen, int quantum) {
    if (procs == NULL || plen <= 0 || quantum <= 0) return 0;

    int time = 0;
    int current = 0;

    
    if (procs[current].burst_left == 0) {
        current = rr_next(current, procs, plen);
        if (current == -1) return 0;
    }

    while (1) {
    
        int any = 0;
        for (int i = 0; i < plen; ++i) if (procs[i].burst_left > 0) { any = 1; break; }
        if (!any) break;

        if (procs[current].burst_left == 0) {
            int nx = rr_next(current, procs, plen);
            if (nx == -1) break;
            current = nx;
            continue;
        }

        int amount = quantum;
        if (procs[current].burst_left < amount) amount = procs[current].burst_left;

        run_proc(procs, plen, current, amount);
        time += amount;

        int nx = rr_next(current, procs, plen);
        if (nx == -1) break;
        current = nx;
    }

    return time;
}

