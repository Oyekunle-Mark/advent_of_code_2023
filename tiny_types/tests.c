#include <stdio.h>

#include "CUnit/CUnit.h"
#include "CUnit/Basic.h"
#include "vec.h"
#include "list.h"

/* Test Suite setup and cleanup functions: */

int init_suite(void) { return 0; }
int clean_suite(void) { return 0; }

/************* Test case functions ****************/
void test_vector_initialization_and_free(void)
{
	struct vector vec = build();

	CU_ASSERT_EQUAL(vec.length, 0);
	CU_ASSERT_EQUAL(vec.capacity, DEFAULT_SIZE);

	drop(&vec);
	CU_ASSERT_EQUAL(vec.capacity, 0);
}

void test_len_and_capacity(void)
{
	struct vector vec = build();

	put(&vec, 1);
	put(&vec, 2);
	put(&vec, 3);

	CU_ASSERT_EQUAL(vec.length, 3);
	CU_ASSERT_EQUAL(vec.capacity, DEFAULT_SIZE);

	put(&vec, 4);
	put(&vec, 5);
	CU_ASSERT_EQUAL(vec.length, 5);

	put(&vec, 6);
	CU_ASSERT_EQUAL(vec.length, 6);
	CU_ASSERT_EQUAL(vec.capacity, DEFAULT_SIZE * 2);

	drop(&vec);
}

void test_get_and_put(void)
{
	struct vector vec = build();

	put(&vec, 1);
	put(&vec, -1);
	put(&vec, 32102);

	CU_ASSERT_EQUAL(get(&vec, 0), 1);
	CU_ASSERT_EQUAL(get(&vec, 1), -1);
	CU_ASSERT_EQUAL(get(&vec, 2), 32102);

	drop(&vec);
}

void test_linked_list(void)
{
	struct Node* head = NULL;

	add_to_tail(&head, "value_1", 1);
	add_to_tail(&head, "value_2", 2);

	int* temp = NULL;
	get_from_list(&head, "value_1", &temp);
	CU_ASSERT_EQUAL(*temp, 1);

	get_from_list(&head, "value_2", &temp);
	CU_ASSERT_EQUAL(*temp, 2);

	add_to_tail(&head, "value_3", 3);
	remove_from_list(&head, "value_2");
	get_from_list(&head, "value_2", &temp);
	CU_ASSERT_EQUAL(temp, NULL);

	get_from_list(&head, "value_3", &temp);
	CU_ASSERT_EQUAL(*temp, 3);
	get_from_list(&head, "value_1", &temp);
	CU_ASSERT_EQUAL(*temp, 1);

	// free_list(&head);
	// get_from_list(&head, "value_1", &temp);
	// CU_ASSERT_EQUAL(temp, NULL);
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
	if ((NULL == CU_add_test(pSuite, "test_vector_initialization_and_free", test_vector_initialization_and_free)) ||
			(NULL == CU_add_test(pSuite, "test_len_and_capacity", test_len_and_capacity)) ||
			(NULL == CU_add_test(pSuite, "test_get_and_put", test_get_and_put)) ||
			(NULL == CU_add_test(pSuite, "test_linked_list", test_linked_list)))
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
