/*
 * Host Dispatcher Shell Project for SOFE 3950U / CSCI 3020U: Operating Systems
 *
 * Copyright (C) 2015, <GROUP MEMBERS>
 * All rights reserved.
 *
 */
#ifndef UTILITY_H_
#define UTILITY_H_

#include "queue.h"

// The amount of available memory
#define MEMORY 1024

// our resources
typedef struct {
	int printers[2];
	int scanners[1];
	int modems[1];
	int cd_drives[2];
	int memory[MEMORY];
} res;

// checks to see if the is the neccisary space for a resource
// if there is enough space, it will return the location
// other wise it will return -1
extern int check_res(int resource[], int amount);

// returns 1 if there are enough resources available
// returns 0 if there aren't enough
extern int res_available(proc process, res resources);

// allocates the given amount of resource
// returns start point
extern int alloc_res(int *resource[], int amount);

// frees the given amount of resource from the starting point
extern void free_res(int *resource[], int start_point, int amount);

// Function to parse the file and initialize each process structure and add
// it to your job dispatch list queue (linked list)
extern void load_dispatch(char *dispatch_file, node_t *queue);

#endif /* UTILITY_H_ */
