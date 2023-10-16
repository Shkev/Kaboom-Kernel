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
	int* location0 = (int*)0x400000; //physical address where kernel starts
	int testing0;
	testing0 = *location0;
	return PASS;
}

// Test to see if we can access the video memory at its location
// Expected return value: PASS
int videomemexist() {
	TEST_HEADER;
	int* location1 = (int*)0xB8000; //physical address where video memory starts
	int testing1;
	testing1 = *location1;
	return PASS;
}

// Test to see if we can access the one below the lower bound of kernel memory address
// Expected return value: FAIL
int kernelexistlower() {
	TEST_HEADER;
	int* location0 = (int*)0x3FFFFF; //physical address where kernel starts
	int testing0;
	testing0 = *location0;
	return FAIL;
}

// Test to see if we can access the one above the higher bound of kernel memory address
// Expected return value: FAIL
int kernelexisthigher() {
	TEST_HEADER;
	int* location0 = (int*)0x800001; //physical address one above kernel ending
	int testing0;
	testing0 = *location0;
	return FAIL;
}

// Test lowerbound of videomemory
// Expected return value: FAIL
int videomemexistlower() {
	TEST_HEADER;
	int* location2 = (int*)0xB7FFF;//physical address one below video memory start
	int testing2;
	testing2 = *location2;
	return FAIL;
}

// Test upperbound of videomemory
// Expected return value: FAIL
int videomemexisthigher() {
	TEST_HEADER;
	int* location3 = (int*)0xB9001;//physical address one above video memory ending
	int testing3;
	testing3 = *location3;
	return FAIL;
}

// // Test location zero
// // Expected return value: FAIL
// int zero() {
// 	TEST_HEADER;
// 	int* location3 = (int*)0x0;//physical address of 0
// 	int testing3;
// 	testing3 = *location3;
// 	return FAIL;
// }

// // Test location 1 above 4 GiB bound
// // Expected return value: FAIL
// int max() {
// 	TEST_HEADER;
// 	int* location3 = (int*)0x100000000;//physical address one above 4 GiB bound
// 	int testing3;
// 	testing3 = *location3;
// 	return FAIL;
// }


// Test to see if we can access a page which does not exist yet
// Expected return value: FAIL
int imaginemem() {
	TEST_HEADER;
	int* location4 = (int*)0xB9000;//physical address of random spot
	int testing4;
	testing4 = *location4;
	return FAIL;
}

// Test random exception on IDT
// Expected return value: raise exception
int assertion_failure1(){
	/* Use exception #7 for assertions, otherwise
	   reserved by Intel */
	asm volatile("int $7"); //raise device_na exception
	return 1;
}

// Test random exception on IDT
// Expected return value: raise exception
int assertion_failure2(){
	/* Use exception #7 for assertions, otherwise
	   reserved by Intel */
	asm volatile("int $12"); //raise stack_segfault exception
	return 1;
}


/* Checkpoint 2 tests */
/* Checkpoint 3 tests */
/* Checkpoint 4 tests */
/* Checkpoint 5 tests */


/* Test suite entry point */
void launch_tests() {
	TEST_OUTPUT("idt_test: ", idt_test());
	TEST_OUTPUT("kernel test: ", kernelexist());
	// TEST_OUTPUT("kernel test lower: ", kernelexistlower());
	// TEST_OUTPUT("kernel test higher: ", kernelexisthigher());
	TEST_OUTPUT("videomemexist test: ", videomemexist());
	// TEST_OUTPUT("videomemexist test lower: ", videomemexistlower());
	// TEST_OUTPUT("videomemexist test higher: ", videomemexisthigher());
	// TEST_OUTPUT("imaginemem test: ", imaginemem());
	// TEST_OUTPUT("zero test: ", zero());
	// TEST_OUTPUT("max test: ", max());
	// TEST_OUTPUT("idt exception device_na: ", assertion_failure1());
	// TEST_OUTPUT("idt exception stack_segfault: ", assertion_failure2());
	// launch your tests here
//	TEST_OUTPUT("idt_div_zero_trigger_test", idt_div_zero_trigger_test());
}
