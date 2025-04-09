#include <stdio.h>

/** init
* Initialize the pointer to the client code.
*/
void (*callback)(int *);
void init(void (*ptr)(int *)) {
	callback = ptr;

	// The following two lines shows how to call a callback 
	// Here I'm making a variable to pass the address throug.
	// int j = 10;
	// (*ptr)(&j);
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
