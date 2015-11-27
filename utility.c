/*
 * Host Dispatcher Shell Project for SOFE 3950U / CSCI 3020U: Operating Systems
 *
 * Copyright (C) 2015, 100493227, 100451291, 100462413, 100522340
 * All rights reserved.
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <sys/wait.h>
#include <unistd.h>
#include <dirent.h>
#include "utility.h"
#include "queue.h"

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
// TODO make sure the last 64 are always free for realtime processes
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
	int start_point = check_res(*resource, amount);
	for(int i = start_point; i < start_point+amount; i++) {
		*resource[i] = 1;
	}
	return start_point;
}

// frees the given amount of resource from the starting point
void free_res(int *resource[], int start_point, int amount) {
	for(int i = start_point; i < start_point+amount; i++) {
		resource[i] = 0;
	}
}

// loads the dispatch list and puts it into a queue
void load_dispatch(char *dispatch_file, node_t ** queue) {
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

		tmp_proc.suspended = 0;
		tmp_proc.pid = 0;

		// add the process to the queue
		if((*queue) == NULL) {
			// if the queue head is still NULL, allocate space for it as the new head
			(*queue) = malloc(sizeof(node_t));
			(*queue)->val = tmp_proc;
		} else {
			// if there is already a head we can use push
			push((*queue), tmp_proc);
		}

	}

	// close the file
	fclose(f);
}

// run the process in the given resources for the given appropriate amount of time
void run_for_time(proc *process) {

	//pid_t process.pid = 0;
	process->pid = fork();

	// the first child process
	if(process->pid == 0) {

		if(process->suspended == 0) {
			// exec our process
			execl("./process", NULL);
		} else {
			// continue the process
			kill(process->pid, SIGCONT);
		}


		return;

	// the parent process
	} else {
		int status;

		// real time can run as it likes
		if(process->priority == 0) {
			wait(&status);
			process->processor_time = 0;

		// priority 1 to 3
		} else {
			// only let lower priorities run for 1 second
			sleep(1);
			kill(process->pid, SIGTSTP);
			wait(&status);

			// update our process
			process->suspended == 1;
			process->processor_time--;
		}

		if(process->processor_time == 0) {
			kill(process->pid, SIGINT);
		}
	}
	return;
}
