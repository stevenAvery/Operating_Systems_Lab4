/*
 * Host Dispatcher Shell Project for SOFE 3950U / CSCI 3020U: Operating Systems
 *
 * Copyright (C) 2015, <GROUP MEMBERS>
 * All rights reserved.
 *
 */
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "queue.h"
#include "utility.h"
#include "hostd.h"

// Put macros or constants here using #define
#define MEMORY 1024

// Put global environment variables here
node_t *head_dispatch_queues[4] = { NULL };

// Define functions declared in hostd.h here

int main(int argc, char *argv[])
{
    // ==================== YOUR CODE HERE ==================== //

    // Load the dispatchlist
	// Add each process structure instance to the job dispatch list queue
	node_t *tmp_head = NULL;
	load_dispatch("dispatchlist", tmp_head);

    // Iterate through each item in the job dispatch list, add each process
    // to the appropriate queues
	while(tmp_head != NULL) {
		proc current = pop(&tmp_head);
		push(head_dispatch_queues[current.priority], current);
	}

    // Allocate the resources for each process before it's executed

    // Execute the process binary using fork and exec

    // Perform the appropriate signal handling / resource allocation and de-alloaction

    // Repeat until all processes have been executed, all queues are empty


	// make sure the queues are clear to avoid memory leaks
	for(int i = 0; i < 4; i++)
		while(head_dispatch_queues[i] != NULL)
			pop(&head_dispatch_queues[i]);

    return EXIT_SUCCESS;
}
