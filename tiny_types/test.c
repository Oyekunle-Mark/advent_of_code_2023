#include <stdio.h>

#include "CUnit/CUnit.h"
#include "CUnit/Basic.h"
#include "vec.h"

/* Test Suite setup and cleanup functions: */

int init_suite(void) { return 0; }
int clean_suite(void) { return 0; }

/************* Test case functions ****************/
void test_vector_initialization(void)
{
	struct vector vec = build();

	CU_ASSERT_EQUAL(vec.length, 0);
	CU_ASSERT_EQUAL(vec.capacity, DEFAULT_SIZE);
}

/************* Test Runner Code goes here **************/

int main(void)
{
	CU_pSuite pSuite = NULL;

	/* initialize the CUnit test registry */
	if (CUE_SUCCESS != CU_initialize_registry())
		return CU_get_error();

	/* add a suite to the registry */
	pSuite = CU_add_suite("tiny types tests", init_suite, clean_suite);
	if (NULL == pSuite)
	{
		CU_cleanup_registry();
		return CU_get_error();
	}

	/* add the tests to the suite */
	if ((NULL == CU_add_test(pSuite, "test_vector_initialization", test_vector_initialization)))
	{
		CU_cleanup_registry();
		return CU_get_error();
	}

	// Run all tests using the basic interface
	CU_basic_set_mode(CU_BRM_VERBOSE);
	CU_basic_run_tests();
	printf("\n");
	CU_basic_show_failures(CU_get_failure_list());
	printf("\n\n");

	/* Clean up registry and return */
	CU_cleanup_registry();
	return CU_get_error();
}
