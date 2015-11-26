

# Dispatch Design Document

- [x] initialize each of the following resources, and make sure they're empty:
	- 2 printers
	- 1 scanner
	- 1 modem
	- 2 cd drives
	- 1024 Megabytes of memory
- [x] initialize job queues
- [x] load dispatchlist into process structs as:
	- arrival time, priority, processor time, Mbytes, #printers, #scanners, #modems, #CDs
- [x] add each process to dispatch queues based on given arrival times (priority 0 -> realtime, priority 1, 2, 3 -> job queue 1, 2, 3)

- [x] while there are more processes to run do the following:
	- [x] check that all of the required resources are fee
	- [x] allocate as much resources as possible, following priority order of queues
		- note: memory must be allocated in a contiguous block
	- [ ] execute process (with fork and exec)
	- [ ] perform signal handling
		- only allows priority 1 to 3 to run for one second before suspending
