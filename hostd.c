/*
 * Host Dispatcher Shell Project for SOFE 3950U / CSCI 3020U: Operating Systems
 *
 * Copyright (C) 2015, 100493227, 100451291, 100462413, 100522340, 100523158
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
node_t *head_dispatch_queues[4] = { NULL }; // 4 dispatch queue from priority 0 to 3
// TODO: error with this(^) pointer arithmatic

// our resources (initialized all resources to 0)
res resources = {
	.printers  = {0},
	.scanners  = {0},
	.modems    = {0},
	.cd_drives = {0},
	.memory    = {0}
};

// Define functions declared in hostd.h here
// ...

int main(int argc, char *argv[])
{
	// Load the dispatchlist
	// Add each process structure instance to the job dispatch list queue
	node_t *tmp_head = NULL;
	printf("Dispatch list: \n");
	load_dispatch("dispatchlist", &tmp_head);
	print_list(tmp_head);

	// Iterate through each item in the job dispatch list, add each process
	// to the appropriate queues
	node_t *test = NULL;
	while(tmp_head != NULL) {
		proc current = pop(&tmp_head);

		// get a segfault, so this is currently commented out
		push(&head_dispatch_queues[current.priority], current);
	}

	// go through the queues from highest to lowest priority
	for(int i = 0; i < 4; i++) {
		// while this queue isn't empty
		// it will keep pushing resources to the end of the queue until this on is completely empty
		while(head_dispatch_queues[i] != NULL) {
			proc current = pop(head_dispatch_queues[i]);
			if(res_available(current, resources)) {
				// Allocate the resources for each process before it's executed
				int printer_start = alloc_res(&resources.printers,  current.required_printers);
				int scanner_start = alloc_res(&resources.scanners,  current.required_scanners);
				int modem_start   = alloc_res(&resources.modems,    current.required_modems);
				int cd_start      = alloc_res(&resources.cd_drives, current.required_cds);
				int memory_start  = alloc_res(&resources.memory,    current.required_memory);

				// Execute the process binary using fork and exec
				// Perform the appropriate signal handling
				// decrease the current.processor_time by the amount of time this process ran
				run_for_time(&current);

				// Deallocate the resources
				free_res(&resources.printers,  printer_start, current.required_printers);
				free_res(&resources.scanners,  scanner_start, current.required_scanners);
				free_res(&resources.modems,    modem_start,   current.required_modems);
				free_res(&resources.cd_drives, cd_start,      current.required_cds);
				free_res(&resources.memory,    memory_start,  current.required_memory);
			}

			// if the process needs more time to run, add it back to the queue
			if(current.processor_time > 0) {
				push(head_dispatch_queues[i], current);
			}
		}
	}


	// make sure the queues are clear to avoid memory leaks
	for(int i = 0; i < 4; i++)
		while(head_dispatch_queues[i] != NULL)
			pop(head_dispatch_queues[i]);

	return EXIT_SUCCESS;
}
