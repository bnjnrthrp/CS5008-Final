/**
 * File to test the BST implementation that holds movies.
 *
 * STUDENTS: you should feel free to modify this file! This is not checked, but here to help you.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "../lib/bst.h"
#include "../lib/movie.h"

#include "movie_globals.h"
#include "testing_util.h"

#define GROUP_GENERAL "GENERAL"
#define GROUP_ADD "ADD"
#define GROUP_REMOVE "REMOVE"
#define GROUP_GET "GET"
#define GROUP_TO_STRING "STRING"
// setup a different group for strings since it involves different traversals

/******************** TESTS ******************/

/**
 * Test the new_bst() function.
 * @returns true if the test passed, false otherwise
 */
bool test_new_bst()
{
    bool passed = true;
    BST *bst = new_bst();
    passed &= ASSERT_NOT_NULL(bst);
    passed &= ASSERT_NULL(bst->root);
    passed &= ASSERT_EQUAL(0, bst->size);
    free_bst(bst);
    return passed;
}

/**
 * Test the bst_add() function.
 *
 * Final tree by the end of the function should look like
 *
 *               movie2
 *              /      \
 *         movie1      movie3
 *        /      \     /    \
 *      NULL    NULL  NULL  NULL
 * Which with the BREADTH_FIRST ordering should look like
 * {title: B Movie Two, id: 2}, {title: A Movie One, id: 1}, {title: C Movie Three, id: 3}, NULL, NULL, NULL, NULL
 *
 * @returns true if the test passed, false otherwise
 */
bool test_bst_add()
{
    bool passed = true;
    BST *bst = new_bst();

    PRINT_DEBUG("Testing adding %s to the BST\n", movie_to_str(movie2));
    bst_add(bst, movie2);

    PRINT_DEBUG("Current tree (BREADTH_FIRST): %s\n", bst_to_str(bst, BREADTH_FIRST));

    passed &= ASSERT_EQUAL(1, bst->size);
    passed &= ASSERT_EQUAL(movie2, bst->root->movie);
    passed &= ASSERT_NULL(bst->root->left);
    passed &= ASSERT_NULL(bst->root->right);

    PRINT_DEBUG("Testing adding %s to the BST\n", movie_to_str(movie1));

    bst_add(bst, movie1);

    PRINT_DEBUG("Current tree (BREADTH_FIRST): %s; Current Size: %d\n",
                bst_to_str(bst, BREADTH_FIRST), bst->size);

    passed &= ASSERT_EQUAL(2, bst->size);
    passed &= ASSERT_EQUAL(movie2, bst->root->movie);
    passed &= ASSERT_EQUAL(movie1, bst->root->left->movie);
    passed &= ASSERT_NULL(bst->root->right);

    PRINT_DEBUG("Testing adding %s to the BST\n", movie_to_str(movie3));

    bst_add(bst, movie3);

    PRINT_DEBUG("Current tree (BREADTH_FIRST): %s; Current Size: %d\n",
                bst_to_str(bst, BREADTH_FIRST), bst->size);

    passed &= ASSERT_EQUAL(3, bst->size);
    passed &= ASSERT_EQUAL(movie2, bst->root->movie);
    passed &= ASSERT_EQUAL(movie1, bst->root->left->movie);
    passed &= ASSERT_EQUAL(movie3, bst->root->right->movie);

    free_bst(bst);
    return passed;
}

/** Testing add when it is down a single side only
 * @returns true if the test passed, false otherwise
 */
bool test_bst_add_single_side()
{
    bool passed = true;
    BST *bst = new_bst();

    PRINT_DEBUG("Testing down right side");
    PRINT_DEBUG("Testing adding %s to the BST\n", movie_to_str(movie2));
    bst_add(bst, movie2);

    PRINT_DEBUG("Current tree (BREADTH_FIRST): %s\n", bst_to_str(bst, BREADTH_FIRST));

    passed &= ASSERT_EQUAL(1, bst->size);
    passed &= ASSERT_EQUAL(movie2, bst->root->movie);
    passed &= ASSERT_NULL(bst->root->left);
    passed &= ASSERT_NULL(bst->root->right);

    PRINT_DEBUG("Testing adding %s to the BST\n", movie_to_str(movie3));

    bst_add(bst, movie3);

    PRINT_DEBUG("Current tree (BREADTH_FIRST): %s; Current Size: %d\n",
                bst_to_str(bst, BREADTH_FIRST), bst->size);

    passed &= ASSERT_EQUAL(2, bst->size);
    passed &= ASSERT_EQUAL(movie2, bst->root->movie);
    passed &= ASSERT_NULL(bst->root->left);
    passed &= ASSERT_EQUAL(movie3, bst->root->right->movie);

    PRINT_DEBUG("Testing adding %s to the BST\n", movie_to_str(movie4));

    bst_add(bst, movie4);

    PRINT_DEBUG("Current tree (BREADTH_FIRST): %s; Current Size: %d\n",
                bst_to_str(bst, BREADTH_FIRST), bst->size);

    passed &= ASSERT_EQUAL(3, bst->size);
    passed &= ASSERT_EQUAL(movie2, bst->root->movie);
    passed &= ASSERT_NULL(bst->root->left);
    passed &= ASSERT_EQUAL(movie3, bst->root->right->movie);
    passed &= ASSERT_EQUAL(movie4, bst->root->right->right->movie);

    free_bst(bst);
    bst = new_bst();
    // now testing down left side

    PRINT_DEBUG("Testing down left side");
    PRINT_DEBUG("Testing adding %s to the BST\n", movie_to_str(movie6));

    bst_add(bst, movie6);

    PRINT_DEBUG("Current tree (BREADTH_FIRST): %s\n", bst_to_str(bst, BREADTH_FIRST));

    passed &= ASSERT_EQUAL(1, bst->size);
    passed &= ASSERT_EQUAL(movie6, bst->root->movie);
    passed &= ASSERT_NULL(bst->root->left);
    passed &= ASSERT_NULL(bst->root->right);

    PRINT_DEBUG("Testing adding %s to the BST\n", movie_to_str(movie5));

    bst_add(bst, movie5);

    PRINT_DEBUG("Current tree (BREADTH_FIRST): %s; Current Size: %d\n",
                bst_to_str(bst, BREADTH_FIRST), bst->size);

    passed &= ASSERT_EQUAL(2, bst->size);
    passed &= ASSERT_EQUAL(movie6, bst->root->movie);
    passed &= ASSERT_EQUAL(movie5, bst->root->left->movie);
    passed &= ASSERT_NULL(bst->root->right);

    PRINT_DEBUG("Testing adding %s to the BST\n", movie_to_str(movie4));

    bst_add(bst, movie4);

    PRINT_DEBUG("Current tree (BREADTH_FIRST): %s; Current Size: %d\n",
                bst_to_str(bst, BREADTH_FIRST), bst->size);

    passed &= ASSERT_EQUAL(3, bst->size);
    passed &= ASSERT_EQUAL(movie6, bst->root->movie);
    passed &= ASSERT_EQUAL(movie5, bst->root->left->movie);
    passed &= ASSERT_EQUAL(movie4, bst->root->left->left->movie);

    free_bst(bst);
    return passed;
}

/**
 * Testing BST remove
 *
 * @returns true if the test passed, false otherwise
 */
bool test_bst_remove()
{
    bool passed = true;
    BST *bst = new_bst();

    bst_add(bst, movie2);
    bst_add(bst, movie1);
    bst_add(bst, movie3);

    PRINT_DEBUG("Current tree (BREADTH_FIRST): %s; Current Size: %d\n",
                bst_to_str(bst, BREADTH_FIRST), bst->size);

    PRINT_DEBUG("Testing removing %s from the BST\n", movie_to_str(movie2));

    bst_remove(bst, movie2);

    PRINT_DEBUG("Current tree (BREADTH_FIRST): %s; Current Size: %d\n",
                bst_to_str(bst, BREADTH_FIRST), bst->size);

    passed &= ASSERT_EQUAL(2, bst->size);
    passed &= ASSERT_EQUAL(movie3, bst->root->movie);
    passed &= ASSERT_EQUAL(movie1, bst->root->left->movie);

    PRINT_DEBUG("Testing removing %s from the BST\n", movie_to_str(movie1));

    bst_remove(bst, movie1);

    PRINT_DEBUG("Current tree (BREADTH_FIRST): %s; Current Size: %d\n",
                bst_to_str(bst, BREADTH_FIRST), bst->size);

    passed &= ASSERT_EQUAL(1, bst->size);
    passed &= ASSERT_EQUAL(movie3, bst->root->movie);

    PRINT_DEBUG("Testing removing %s from the BST\n", movie_to_str(movie3));

    bst_remove(bst, movie3);

    PRINT_DEBUG("Current tree (BREADTH_FIRST): %s; Current Size: %d\n",
                bst_to_str(bst, BREADTH_FIRST), bst->size);

    passed &= ASSERT_EQUAL(0, bst->size);
    passed &= ASSERT_NULL(bst->root);

    free_bst(bst);
    return passed;
}

/** Tests Remove when the tree is only one sided
 *
 * @returns true if the test passed, false otherwise
 */
bool test_bst_remove_single_side()
{
    bool passed = true;
    BST *bst = new_bst();

    bst_add(bst, movie2);
    bst_add(bst, movie3);
    bst_add(bst, movie4);

    PRINT_DEBUG("Current tree (BREADTH_FIRST): %s; Current Size: %d\n",
                bst_to_str(bst, BREADTH_FIRST), bst->size);

    PRINT_DEBUG("Testing removing %s from the BST\n", movie_to_str(movie2));

    bst_remove(bst, movie2);

    PRINT_DEBUG("Current tree (BREADTH_FIRST): %s; Current Size: %d\n",
                bst_to_str(bst, BREADTH_FIRST), bst->size);

    passed &= ASSERT_EQUAL(2, bst->size);
    passed &= ASSERT_EQUAL(movie3, bst->root->movie);
    passed &= ASSERT_EQUAL(movie4, bst->root->right->movie);

    PRINT_DEBUG("Testing removing %s from the BST\n", movie_to_str(movie3));

    bst_remove(bst, movie3);

    PRINT_DEBUG("Current tree (BREADTH_FIRST): %s; Current Size: %d\n",
                bst_to_str(bst, BREADTH_FIRST), bst->size);

    passed &= ASSERT_EQUAL(1, bst->size);
    passed &= ASSERT_EQUAL(movie4, bst->root->movie);

    PRINT_DEBUG("Testing removing %s from the BST\n", movie_to_str(movie4));

    bst_remove(bst, movie4);

    PRINT_DEBUG("Current tree (BREADTH_FIRST): %s; Current Size: %d\n",
                bst_to_str(bst, BREADTH_FIRST), bst->size);

    passed &= ASSERT_EQUAL(0, bst->size);
    passed &= ASSERT_NULL(bst->root);

    free_bst(bst);
    return passed;
}

/**
 * Testing remove when it is left sided only
 *
 * @returns true if the test passed, false otherwise
 */
bool test_bst_remove_left_side()
{
    bool passed = true;
    BST *bst = new_bst();

    bst_add(bst, movie6);
    bst_add(bst, movie5);
    bst_add(bst, movie4);

    PRINT_DEBUG("Current tree (BREADTH_FIRST): %s; Current Size: %d\n",
                bst_to_str(bst, BREADTH_FIRST), bst->size);

    PRINT_DEBUG("Testing removing %s from the BST\n", movie_to_str(movie6));

    bst_remove(bst, movie6);

    PRINT_DEBUG("Current tree (BREADTH_FIRST): %s; Current Size: %d\n",
                bst_to_str(bst, BREADTH_FIRST), bst->size);

    passed &= ASSERT_EQUAL(2, bst->size);
    passed &= ASSERT_EQUAL(movie5, bst->root->movie);
    passed &= ASSERT_EQUAL(movie4, bst->root->left->movie);

    PRINT_DEBUG("Testing removing %s from the BST\n", movie_to_str(movie5));

    bst_remove(bst, movie5);

    PRINT_DEBUG("Current tree (BREADTH_FIRST): %s; Current Size: %d\n",
                bst_to_str(bst, BREADTH_FIRST), bst->size);

    passed &= ASSERT_EQUAL(1, bst->size);
    passed &= ASSERT_EQUAL(movie4, bst->root->movie);

    PRINT_DEBUG("Testing removing %s from the BST\n", movie_to_str(movie4));

    bst_remove(bst, movie4);

    PRINT_DEBUG("Current tree (BREADTH_FIRST): %s; Current Size: %d\n",
                bst_to_str(bst, BREADTH_FIRST), bst->size);

    passed &= ASSERT_EQUAL(0, bst->size);
    passed &= ASSERT_NULL(bst->root);

    free_bst(bst);
    return passed;
}

/** Tests the bst_find() function
 *
 * @returns true if the test passed, false otherwise
 */
bool test_bst_find()
{
    bool passed = true;
    BST *bst = new_bst();

    bst_add(bst, movie2);
    bst_add(bst, movie1);
    bst_add(bst, movie3);

    PRINT_DEBUG("Current tree (BREADTH_FIRST): %s; Current Size: %d\n",
                bst_to_str(bst, BREADTH_FIRST), bst->size);

    PRINT_DEBUG("Testing finding %s in the BST\n", movie_to_str(movie2));

    Movie *found = bst_find(bst, movie2->title);

    passed &= ASSERT_EQUAL(movie2, found);

    PRINT_DEBUG("Testing finding %s in the BST\n", movie_to_str(movie1));

    found = bst_find(bst, movie1->title);

    passed &= ASSERT_EQUAL(movie1, found);

    PRINT_DEBUG("Testing finding %s in the BST\n", movie_to_str(movie3));

    found = bst_find(bst, movie3->title);

    passed &= ASSERT_EQUAL(movie3, found);

    PRINT_DEBUG("Testing finding %s in the BST\n", movie_to_str(movie4));

    found = bst_find(bst, movie4->title);

    passed &= ASSERT_NULL(found);

    free_bst(bst);
    return passed;
}

/**
 * Tests the bst_to_str() function for breadth first
 *
 * @returns true if the test passed, false otherwise
 */
bool test_bst_to_str_breadth_first()
{
    bool passed = true;
    BST *bst = new_bst();

    bst_add(bst, movie2);
    bst_add(bst, movie1);
    bst_add(bst, movie3);

    PRINT_DEBUG("Current tree (BREADTH_FIRST): %s; Current Size: %d\n",
                bst_to_str(bst, BREADTH_FIRST), bst->size);

    char *str = bst_to_str(bst, BREADTH_FIRST);

    passed &= ASSERT_STR_EQUAL("{title: B Movie Two, id: 2}, {title: A Movie One, id: 1}, {title: C Movie Three, id: 3}, NULL, NULL, NULL, NULL", str);

    free(str);
    free_bst(bst);
    return passed;
}

/**
 * Tests the bst_to_str() function for preordering
 *
 * @returns true if the test passed, false otherwise
 */
bool test_bst_to_str_preorder()
{
    bool passed = true;
    BST *bst = new_bst();

    bst_add(bst, movie2);
    bst_add(bst, movie1);
    bst_add(bst, movie3);

    PRINT_DEBUG("Current tree (PRE_ORDER): %s; Current Size: %d\n",
                bst_to_str(bst, PRE_ORDER), bst->size);

    char *str = bst_to_str(bst, PRE_ORDER);

    passed &= ASSERT_STR_EQUAL("{title: B Movie Two, id: 2}, {title: A Movie One, id: 1}, {title: C Movie Three, id: 3}", str);

    free(str);
    free_bst(bst);
    return passed;
}

/**
 * Tests the bst_to_str() function for inorder
 *
 * @returns true if the test passed, false otherwise
 */
bool test_bst_to_str_inorder()
{
    bool passed = true;
    BST *bst = new_bst();

    bst_add(bst, movie2);
    bst_add(bst, movie1);
    bst_add(bst, movie3);

    PRINT_DEBUG("Current tree (IN_ORDER): %s; Current Size: %d\n",
                bst_to_str(bst, IN_ORDER), bst->size);

    char *str = bst_to_str(bst, IN_ORDER);
    passed &= ASSERT_STR_EQUAL("{title: A Movie One, id: 1}, {title: B Movie Two, id: 2}, {title: C Movie Three, id: 3}", str);

    free(str);
    free_bst(bst);
    return passed;
}

/**
 * Tests the bst_to_str() function for postorder
 *
 * @returns true if the test passed, false otherwise
 */
bool test_bst_to_str_postorder()
{
    bool passed = true;
    BST *bst = new_bst();

    bst_add(bst, movie2);
    bst_add(bst, movie1);
    bst_add(bst, movie3);

    PRINT_DEBUG("Current tree (POST_ORDER): %s; Current Size: %d\n",
                bst_to_str(bst, POST_ORDER), bst->size);

    char *str = bst_to_str(bst, POST_ORDER);
    passed &= ASSERT_STR_EQUAL("{title: A Movie One, id: 1}, {title: C Movie Three, id: 3}, {title: B Movie Two, id: 2}", str);

    free(str);
    free_bst(bst);
    return passed;
}

/**
 * Tests converting the BST to a sorted array to make sure
 * it ends up properly sorted.
 *
 * @returns true if the test passed, false otherwise
 */
bool test_bst_to_sorted_array()
{
    bool passed = true;
    BST *bst = new_bst();

    bst_add(bst, movie2);
    bst_add(bst, movie1);
    bst_add(bst, movie3);
    bst_add(bst, movie4); // intentionally skipping 5
    bst_add(bst, movie6);

    PRINT_DEBUG("Current tree (BREADTH_FIRST): %s; Current Size: %d\n",
                bst_to_str(bst, BREADTH_FIRST), bst->size);

    Movie **array = bst_to_sorted_array(bst);

    passed &= ASSERT_EQUAL(movie1, array[0]);
    passed &= ASSERT_EQUAL(movie2, array[1]);
    passed &= ASSERT_EQUAL(movie3, array[2]);
    passed &= ASSERT_EQUAL(movie4, array[3]);
    passed &= ASSERT_EQUAL(movie6, array[4]);

    free(array);
    free_bst(bst);
    return passed;
}

/*************************** end tests ***********/

/**
 * Adds every testing function to the testing set.
 * Includes the name of the test, the group tag, and the function to run.
 */
TestingSet *init_testing_set()
{
    TestingSet *set = new_testing_set();
    add_test(set, "testing new_bst() creates an empty BST", GROUP_GENERAL, test_new_bst);
    add_test(set, "testing bst_add() adds multiple movies to the BST", GROUP_ADD, test_bst_add);
    add_test(set, "testing bst_add() adds multiple movies to the BST down a single side", GROUP_ADD, test_bst_add_single_side);
    add_test(set, "testing bst_remove() removes movies from the BST", GROUP_REMOVE, test_bst_remove);
    add_test(set, "testing bst_remove() removes movies from the BST down the right side", GROUP_REMOVE, test_bst_remove_single_side);
    add_test(set, "testing bst_remove() removes movies from the BST down the left side", GROUP_REMOVE, test_bst_remove_left_side);
    add_test(set, "testing bst_find() finds movies in the BST", GROUP_GET, test_bst_find);
    add_test(set, "testing bst_to_str() prints the BST in breadth first order", GROUP_TO_STRING, test_bst_to_str_breadth_first);
    add_test(set, "testing bst_to_str() prints the BST in preorder", GROUP_TO_STRING, test_bst_to_str_preorder);
    add_test(set, "testing bst_to_str() prints the BST in inorder", GROUP_TO_STRING, test_bst_to_str_inorder);
    add_test(set, "testing bst_to_str() prints the BST in postorder", GROUP_TO_STRING, test_bst_to_str_postorder);
    add_test(set, "testing bst_to_sorted_array() converts the BST to a sorted array", GROUP_GENERAL, test_bst_to_sorted_array);

    return set;
}

/**
 * Runs the tests for the linked list implementation.
 *
 * @param start_test the test to start running from
 * @param end_test the test to stop running at
 */
int main(const int argc, const char *argv[])
{
    init_movies(); // initialize a few movies to help us out

    TestingSet *set = init_testing_set(); // initialize the testing set

    // now proccess args and run the test program
    check_for_verbose(argc, argv); // check for verbose flag and set the global variable found in testing_util.h
    check_for_debug(argc, argv);   // check for debug flag and set the global variable found in testing_util.h

    const char *group_tag = check_for_group_tag(argc, argv); // check for group tag and set the global variable found in testing_util.h

    if (group_tag == NULL)
    {
        int test_start_loc = 1;                                                                          // the index to start looking for tests at, but may change if -v is there
        int start_test = get_int_arg(argc, argv, 1, 0, &test_start_loc);                                 // get the start test, default to 0
        int end_test = get_int_arg(argc, argv, test_start_loc + 1, set->num_tests - 1, &test_start_loc); // get the end test, default to 0
        PRINT_VERBOSE("Running tests %d through %d\n", start_test, end_test);
        run_tests(set, start_test, end_test);
    }
    else
    {
        PRINT_VERBOSE("Running tests for group %s\n", group_tag);
        run_tests_group(set, (char *)group_tag);
    }

    free_movies();
    free_testing_set(set);
    return 0;
}
