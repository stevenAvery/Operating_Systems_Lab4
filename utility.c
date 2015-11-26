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

// int alloc_mem(resources res, int size)
// {
//      ...
// }

// free_mem(resources res, int index, int size)
// {
//      ...
// }

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
			queue = malloc(sizeof(node_t));
			queue->val = tmp_proc;
		} else {
			push(queue, tmp_proc);
		}

	}

	// close the file
	fclose(f);
}

/*
void load_file_to_queues(char *file_name) {
	static char line[1000] = "";
	char *token_str;

	// open the file
	FILE *f = fopen(file_name, "r");
	if(f == NULL)
		fprintf(stderr, "unable to open file for reading");

	// read in each line
	while(fgets(line, 1000, f) != NULL) {
		proc tmp_proc;

		if ((token_str = strtok(line, ", ")) != NULL)
			strcpy(tmp_proc.name, token_str);
		if ((token_str = strtok(NULL, ", ")) != NULL)
			tmp_proc.priority = atoi(token_str);
		if ((token_str = strtok(NULL, ", ")) != NULL)
			tmp_proc.memory = atoi(token_str);
		if ((token_str = strtok(NULL, ", ")) != NULL)
			tmp_proc.runtime = atoi(token_str);

		// some default values
		tmp_proc.address = 0;
		tmp_proc.pid = 0;
		tmp_proc.suspended = false;

		// add high priority elements to priority queue
		if(tmp_proc.priority == 0) {
			if(head_priority == NULL) {
				head_priority = malloc(sizeof(node_t));
				head_priority->val = tmp_proc;
			} else {
				push(head_priority, tmp_proc);
			}

		// add all other elements to the secondary queue
		} else {
			if(head_secondary == NULL) {
				head_secondary = malloc(sizeof(node_t));
				head_secondary->val = tmp_proc;
			} else {
				push(head_secondary, tmp_proc);
			}
		}
	}

	fclose(f);
}
*/
