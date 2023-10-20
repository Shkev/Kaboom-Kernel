#include "tests.h"
#include "x86_desc.h"
#include "lib.h"
#include "filesystems/filesystem.h"

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
	   //original value was int $15
	asm volatile("int $15");
}

//=================================================================================
/* Checkpoint 1 tests */
//=================================================================================
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

int overflow_test() {
    TEST_HEADER;

    int a;
    a = 0xFFFFFFFF;
    int one;
	one = 1;
    a = a + one;
    return FAIL;
}

// Test to see if we can access the kernel memory at its location
// Expected return value: PASS
int kernelexist_test() {
	TEST_HEADER;
	char* location0 = (char*)0x400000; //physical address where kernel starts
	char testing0;
	testing0 = *location0;
	return PASS;
}

// Test to see if we can access the kernel memory at its location
// Expected return value: PASS
int kernelexistdone_test() {
	TEST_HEADER;
	char* location0 = (char*)0x7FFFFF; //physical address where kernel ends
	char testing0;
	testing0 = *location0;
	return PASS;
}

// Test to see if we can access the video memory at its location
// Expected return value: PASS
int videomemexist_test() {
	TEST_HEADER;
	char* location1 = (char*)0xB8000; //physical address where video memory starts
	char testing1;
	testing1 = *location1;
	return PASS;
}

// Test to see if we can access the video memory at its location
// Expected return value: PASS
int videomemexistdone_test() {
	TEST_HEADER;
	char* location1 = (char*)0xB8FFF; //physical address where video memory starts
	char testing1;
	testing1 = *location1;
	return PASS;
}

// Test to see if we can access the one below the lower bound of kernel memory address
// Expected return value: FAIL
int kernelexistlower_test() {
	TEST_HEADER;
	char* location0 = (char*)0x3FFFFF; //physical address where kernel starts
	char testing0;
	testing0 = *location0;
	return FAIL;
}

// Test to see if we can access the one above the higher bound of kernel memory address
// Expected return value: FAIL
int kernelexisthigher_test() {
	TEST_HEADER;
	char* location0 = (char*)0x800000; //physical address one above kernel ending
	char testing0;
	testing0 = *location0;
	return FAIL;
}

// Test lowerbound of videomemory
// Expected return value: FAIL
int videomemexistlower_test() {
	TEST_HEADER;
	char* location2 = (char*)0xB7FFF;//physical address one below video memory start
	char testing2;
	testing2 = *location2;
	return FAIL;
}

// Test upperbound of videomemory
// Expected return value: FAIL
int videomemexisthigher_test() {
	TEST_HEADER;
	char* location3 = (char*)0xB9000;//physical address one above video memory ending
	char testing3;
	testing3 = *location3;
	return FAIL;
}

// // Test location zero
// // Expected return value: FAIL
// int zero() {
// 	TEST_HEADER;
// 	char* location3 = (char*)0x0;//physical address of 0
// 	char testing3;
// 	testing3 = *location3;
// 	return FAIL;
// }

// // Test location 1 above 4 GiB bound
// // Expected return value: FAIL
// int max() {
// 	TEST_HEADER;
// 	char* location3 = (char*)0x100000000;//physical address one above 4 GiB bound
// 	char testing3;
// 	testing3 = *location3;
// 	return FAIL;
// }


// Test to see if we can access a page which does not exist yet
// will FAIL if page fault not thrown
int imaginemem_test() {
	TEST_HEADER;
	char* location4 = (char*)0x30000;//physical address of random spot
	char testing4;
	testing4 = *location4;
	return FAIL;
}

// Test random exception on IDT
// Expected return value: raise exception
int assertion_failure1_test() {
	asm volatile("int $7"); // raise device_na exception
	return 1;
}

// Test random exception on IDT
// Expected return value: raise exception
int assertion_failure2_test(){
	asm volatile("int $12"); //raise stack_segfault exception
	return 1;
}

// Test system call 0x80
int system_call_fail_test(){
	asm volatile("int $0x80"); //raise stack_segfault exception
	return 1;
}
//====================================================================

//====================================================================
/* Checkpoint 2 tests */
//====================================================================
// void test_dir_read(){
// 	char fname[1] = ".";
// 	return directory_read(fname)
// }
// void test_dir_open(){
// 	char fname[1] = ".";
// 	return directory_open(fname);
// }

// /*these functions don't really do anything for directories*/
// int test_dir_write(){
// 	return directory_write();
// }
// int test_dir_close(){
// 	return directory_close();
// }


// void test_file_read();
// void test_file_write();
// void test_file_close();
// void test_file_open();

//=====================================================================

/* Checkpoint 3 tests */
/* Checkpoint 4 tests */
/* Checkpoint 5 tests */


/* Test suite entry point */
void launch_tests() {
	// TEST_OUTPUT("idt_test: ", idt_test());
	// TEST_OUTPUT("kernel starting: ", kernelexist_test());
	// TEST_OUTPUT("kernel ending: ", kernelexistdone_test());
	// TEST_OUTPUT("videomemexist starting: ", videomemexist_test());
	// TEST_OUTPUT("videomemexist ending: ", videomemexistdone_test());
	// TEST_OUTPUT("kernel test lower: ", kernelexistlower_test());
	// TEST_OUTPUT("kernel test higher: ", kernelexisthigher_test());
	// TEST_OUTPUT("videomemexist test lower: ", videomemexistlower_test());
	// TEST_OUTPUT("videomemexist test higher: ", videomemexisthigher_test());
	// TEST_OUTPUT("imaginemem test: ", imaginemem_test());
	// TEST_OUTPUT("idt exception device_na: ", assertion_failure1_test());
	// TEST_OUTPUT("idt exception stack_segfault: ", assertion_failure2_test());
	// TEST_OUTPUT("idt_div_zero_trigger_test", idt_div_zero_trigger_test());
	// TEST_OUTPUT("overflow test: ", overflow_test());
	// TEST_OUTPUT("System call:", system_call_fail_test());

	//TEST_OUTPUT("zero test: ", zero());
	//TEST_OUTPUT("max test: ", max());
}
