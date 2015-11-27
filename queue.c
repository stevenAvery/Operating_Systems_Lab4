/*
 * Host Dispatcher Shell Project for SOFE 3950U / CSCI 3020U: Operating Systems
 *
 * Copyright (C) 2015, 100493227, 100451291, 100462413, 100522340, 100523158
 * All rights reserved.
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include "queue.h"


// outputs the linked list
// heavily based on code from http://www.learn-c.org/en/Linked_lists
void print_list(node_t * head) {
	node_t * current = head;

	printf("%-10s %-10s %-10s %-10s %-10s %-10s %-10s %-10s\n",
		"arrival",
		"priority",
		"proc_time",
		"#memory",
		"#printers",
		"#scanners",
		"#modems",
		"#cds"
	);
	while (current != NULL) {
		printf("%-10d %-10d %-10d %-10d %-10d %-10d %-10d %-10d\n",
			current->val.arrival_time,
			current->val.priority,
			current->val.processor_time,
			current->val.required_memory,
			current->val.required_printers,
			current->val.required_scanners,
			current->val.required_modems,
			current->val.required_cds
		);

		current = current->next;
	}
}

// adds an element to the end of the linked list
// heavily based on code from http://www.learn-c.org/en/Linked_lists
void push(node_t * head, proc val) {
	node_t * current = head;
	while (current->next != NULL) {
		current = current->next;
	}

	// now we can add a new variable
	current->next = malloc(sizeof(node_t));

	// update pointer
	current->next->val = val;
	current->next->next = NULL;
}

// pops the last node off of the end of the list
// heavily based on code from http://www.learn-c.org/en/Linked_lists
proc pop(node_t ** head) {
	proc retval;
	node_t * next_node = NULL;

	if (*head == NULL) {
		proc ret_proc;
		return ret_proc;
	}

	// take out the head, and change the pointer to the next node
	next_node = (*head)->next;
	retval = (*head)->val;
	free(*head);
	*head = next_node;

	return retval;
}
