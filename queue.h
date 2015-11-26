/*
 * Host Dispatcher Shell Project for SOFE 3950U / CSCI 3020U: Operating Systems
 *
 * Copyright (C) 2015, 100493227, 100451291, 100462413, 100522340
 * All rights reserved.
 *
 */
#ifndef QUEUE_H_
#define QUEUE_H_

//#include "utility.h"

// Your linked list structure for your queue
typedef struct {
	int arrival_time;
	int priority;
	int processor_time;
	int required_memory;
	int required_printers;
	int required_scanners;
	int required_modems;
	int required_cds;
} proc;

// node for the linked list
typedef struct node {
	proc val;
	struct node *next;
} node_t;


// Add a new process to the queue, returns the address of the next node added
// to the linked list

extern void print_list(node_t * head);
extern void push(node_t * head, proc val);
extern proc pop(node_t ** head);

#endif /* QUEUE_H_ */
