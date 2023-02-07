#include <stdio.h>


/** init
* Initialize the pointer to the client code.
*/
void (*callback) (int *);
void init(void (*ptr)(int *)) {
	callback = ptr;
}

/** transmit_bytewise
* Transmit the array back to the python harness
* one byte at a time.  This is similar to how bytes
* are 'clocked out' of a microcontroller.
*/
void transmit_bytewise(int array[], int length) {
	for(int i = 0 ; i < length ; i++) {
		(*callback)(&array[i]);
	}
}

/** transmit
* Call this to transmit a value to the controller.
* Note that there are no enforcement mechanisms to ensure
* that the pointer value was set.
*/
void transmit(int value) {
	(*callback)(&value);
}

/** process
* This function receives values from the test harness.
* The necessity of this is to use a signed integer, and
* for program 2, the value should be cast to unit16_t.
* This demo program will execute on the harness's thread.
* We're simply taking the input value from the harness
* and echoing it right back over the callback into the harness.
*/
void process(int value) {
	transmit(value);
}

/** receive
* This function takes in arbitrary sized arrays from
* the test harness.  As before, cast elements in the
* message to uint16_t before using them. 
*/ 
void receive(int message[], int length) {
    transmit_bytewise(message, length);
}
