#include "tests.h"
#include "x86_desc.h"
#include "lib.h"
#include "paging.h"

#define PASS 1
#define FAIL 0

/* format these macros as you see fit */
#define TEST_HEADER 	\
	printf("[TEST %s] Running %s at %s:%d\n", __FUNCTION__, __FUNCTION__, __FILE__, __LINE__)
#define TEST_OUTPUT(name, result)	\
	printf("[TEST %s] Result = %s\n", name, (result) ? "PASS" : "FAIL");

static inline void assertion_failure(){
	/* Use exception #15 for assertions, otherwise
	   reserved by Intel */
	asm volatile("int $15");
}


/* Checkpoint 1 tests */

/* IDT Test - Example
 * 
 * Asserts that first 10 IDT entries are not NULL
 * Inputs: None
 * Outputs: PASS/FAIL
 * Side Effects: None
 * Coverage: Load IDT, IDT definition
 * Files: x86_desc.h/S
 */
int idt_test(){
	TEST_HEADER;

	int i;
	int result = PASS;
	for (i = 0; i < 10; ++i){
		if ((idt[i].offset_15_00 == NULL) && 
			(idt[i].offset_31_16 == NULL)){
			assertion_failure();
			result = FAIL;
		}
	}

	return result;
}

// add more tests here

int idt_div_zero_trigger_test() {
    TEST_HEADER;

    int a, zero, b;
    a = 2;
    zero = 0;
    b = a / zero;
    return b;
}

// Test to see if we can access the kernel memory at its location
// Expected return value: PASS
int kernelexist() {
	TEST_HEADER;
	int* location0 = (int*)0x400000;
	int testing0;
	testing0 = *location0;
	return PASS;
}

// Test to see if we can access the video memory at its location
// Expected return value: PASS
int videomemexist() {
	TEST_HEADER;
	int* location1 = (int*)0xb8000;
	int testing1;
	testing1 = *location1;
	return PASS;
}

// Test to see if we can access a page which does not exist yet
// Expected return value: FAIL
int imaginemem() {
	TEST_HEADER;
	int* location2 = (int*)0x200000;
	int testing2;
	testing2 = *location2;
	return FAIL;
}

/* Checkpoint 2 tests */
/* Checkpoint 3 tests */
/* Checkpoint 4 tests */
/* Checkpoint 5 tests */


/* Test suite entry point */
void launch_tests() {
	TEST_OUTPUT("idt_test: ", idt_test());
	TEST_OUTPUT("kernel test: ", kernelexist());
	TEST_OUTPUT("videomemexist test: ", videomemexist());
	TEST_OUTPUT("imaginemem test: ", imaginemem());
	// launch your tests here
//	TEST_OUTPUT("idt_div_zero_trigger_test", idt_div_zero_trigger_test());
}
