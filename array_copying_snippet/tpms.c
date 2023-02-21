/**
* Copyright 2023 Carnegie Mellon University
* For use only in course 17648 Sensor Based Systems.
*/
#include <stdlib.h>
#include <stdint.h>

#define EVENTLOG_SZ 10
#define PRESSURELOG_SZ 126


// Buffer allocation and initialization
// This syntax is only valid on gcc compilers!
// Initialize both log buffers to zero.
uint8_t pressure_log[PRESSURELOG_SZ] = { [0 ... PRESSURELOG_SZ - 1] = 0 };
uint32_t event_log[EVENTLOG_SZ] = { [0 ... EVENTLOG_SZ - 1] = 0};


/** process
* This function receives values from the test harness.
* The necessity of this is to use a signed integer, and
* for program 2, the value should be cast to unit16_t.
* This demo program will execute on the harness's thread.
* We're simply taking the input value from the harness
* and echoing it right back over the callback into the harness.
*/
int pindex = 0;
int eindex = 0;
void process(int value) {
	pressure_log[pindex++] = value;
	if(pindex >= PRESSURELOG_SZ) {
		pindex = 0;
	}
	event_log[eindex++] = value;
	if(eindex >= EVENTLOG_SZ) {
		eindex = 0;
	}
}

/* get_pressure_log
* This function does the work of copying the pressure log buffer
* into the `input` array.  The caller is responsible for ensuring 
* that the input array length is the same as `PRESSURELOG_SZ`.
*/
void get_pressure_log(uint8_t* input) {
	// do the work of copying in the data from our log
	uint8_t* p = (uint8_t*) malloc (PRESSURELOG_SZ);
  	for(int i = 0 ; i < PRESSURELOG_SZ ; i++) {
    	input[i] = pressure_log[i];
    }
}

/* get_event_log
* This function does the work of copying the event log buffer
* into the `input` array.  The caller is responsible for endusuring
* that the input array length is the same as `EVENTLOG_SZ`.
*/
void get_event_log(uint32_t* input) {
	// do the work of copying in the data from our log
	uint8_t* p = (uint8_t*) malloc (EVENTLOG_SZ);
  	for(int i = 0 ; i < EVENTLOG_SZ ; i++) {
    	input[i] = event_log[i];
    }
}
