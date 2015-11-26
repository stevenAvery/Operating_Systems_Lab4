/*
 * Host Dispatcher Shell Project for SOFE 3950U / CSCI 3020U: Operating Systems
 *
 * Copyright (C) 2015, <GROUP MEMBERS>
 * All rights reserved.
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include "utility.h"
#include "queue.h"

// Define your utility functions here, you will likely need to add more...

// checks to see if the is the neccisary space for a resource
// if there is enough space, it will return the location
// other wise it will return -1
int check_res(int resource[], int amount) {
	int start_point = 0;
	int chain_amount = 0;
	// check the entire resource array
	for(int i = 0; i < sizeof(resource)/sizeof(int); i++) {
		// this part of the resource is free
		if(resource[i] == 0) {
			chain_amount++;
			if(chain_amount == amount)
				return start_point;
		} else {
			start_point = i+1;
		}
	}

	return -1;
}

// returns 1 if there are enough resources available
// returns 0 if there aren't enough
int res_available(proc process, res resources) {
	// if the isn't enough of any individual resources the prcoess can't run
	if(	check_res(resources.printers,  process.required_printers) == -1 ||
		check_res(resources.scanners,  process.required_scanners) == -1 ||
		check_res(resources.modems,    process.required_modems) == -1 ||
		check_res(resources.cd_drives, process.required_cds) == -1 ||
		check_res(resources.memory,    process.required_memory) == -1) {
			return 0;
	}
	return 1;
}

// allocates the given amount of resource from the starting point
int alloc_res(int *resource[], int amount) {
	int start_point = check_res(resource, amount);
	for(int i = start_point; i < start_point+amount; i++) {
		resource[i] = 1;
	}
	return start_point;
}

// frees the given amount of resource from the starting point
void free_res(int *resource[], int start_point, int amount) {
	for(int i = start_point; i < start_point+amount; i++) {
		resource[i] = 0;
	}
}

void load_dispatch(char *dispatch_file, node_t *queue) {
	static char line[1000] = "";
	char *token_str;

	// open the file
	FILE *f = fopen(dispatch_file, "r");
	if(f == NULL)
		fprintf(stderr, "unable to open file for reading");

	// read in each line
	while(fgets(line, 1000, f) != NULL) {

		// generate a process from the tokenized line
		proc tmp_proc;
		if ((token_str = strtok(line, ", ")) != NULL)
			tmp_proc.arrival_time = atoi(token_str);
		if ((token_str = strtok(NULL, ", ")) != NULL)
			tmp_proc.priority = atoi(token_str);
		if ((token_str = strtok(NULL, ", ")) != NULL)
			tmp_proc.processor_time = atoi(token_str);
		if ((token_str = strtok(NULL, ", ")) != NULL)
			tmp_proc.required_memory = atoi(token_str);
		if ((token_str = strtok(NULL, ", ")) != NULL)
			tmp_proc.required_printers = atoi(token_str);
		if ((token_str = strtok(NULL, ", ")) != NULL)
			tmp_proc.required_scanners = atoi(token_str);
		if ((token_str = strtok(NULL, ", ")) != NULL)
			tmp_proc.required_modems = atoi(token_str);
		if ((token_str = strtok(NULL, ", ")) != NULL)
			tmp_proc.required_cds = atoi(token_str);

		// add the process to the queue
		if(queue == NULL) {
			// if the queue head is still NULL, allocate space for it as the new head
			queue = malloc(sizeof(node_t));
			queue->val = tmp_proc;
		} else {
			// if there is already a head we can use push
			push(queue, tmp_proc);
		}

	}

	// close the file
	fclose(f);
}
