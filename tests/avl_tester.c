/**
 * File to test the AVL implementation that holds movies.
 *
 * STUDENTS: you should feel free to modify this file! This is not checked, but here to help you.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "../lib/avl.h"
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
 * Test the new_avl() function.
 * @returns true if the test passed, false otherwise
 */
bool test_new_avl()
{
    bool passed = true;
    AVL *avl = new_avl();
    passed &= ASSERT_NOT_NULL(avl);
    passed &= ASSERT_NULL(avl->root);
    passed &= ASSERT_EQUAL(0, avl->size);
    free_avl(avl);
    return passed;
}

/**
 * Test the avl_add() function.
 *
 * Final tree by the end of the function should look like.
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
bool test_avl_add()
{
    bool passed = true;
    AVL *avl = new_avl();

    PRINT_DEBUG("Testing adding %s to the AVL\n", movie_to_str(movie2));
    avl_add(avl, movie2);

    PRINT_DEBUG("Current tree (BREADTH_FIRST): %s\n", avl_to_str(avl, BREADTH_FIRST));

    passed &= ASSERT_EQUAL(1, avl->size);
    passed &= ASSERT_EQUAL(movie2, avl->root->movie);
    passed &= ASSERT_NULL(avl->root->left);
    passed &= ASSERT_NULL(avl->root->right);

    PRINT_DEBUG("Testing adding %s to the AVL\n", movie_to_str(movie1));

    avl_add(avl, movie1);

    PRINT_DEBUG("Current tree (BREADTH_FIRST): %s; Current Size: %d, Rotations: %d\n",
                avl_to_str(avl, BREADTH_FIRST), avl->size, avl->rotations);

    passed &= ASSERT_EQUAL(2, avl->size);
    passed &= ASSERT_EQUAL(movie2, avl->root->movie);
    passed &= ASSERT_EQUAL(movie1, avl->root->left->movie);
    passed &= ASSERT_NULL(avl->root->right);

    PRINT_DEBUG("Testing adding %s to the AVL\n", movie_to_str(movie3));

    avl_add(avl, movie3);

    PRINT_DEBUG("Current tree (BREADTH_FIRST): %s; Current Size: %d, Rotations: %d\n",
                avl_to_str(avl, BREADTH_FIRST), avl->size, avl->rotations);

    passed &= ASSERT_EQUAL(3, avl->size);
    passed &= ASSERT_EQUAL(movie2, avl->root->movie);
    passed &= ASSERT_EQUAL(movie1, avl->root->left->movie);
    passed &= ASSERT_EQUAL(movie3, avl->root->right->movie);

    PRINT_DEBUG("Freeing the test avl\n");
    free_avl(avl);
    return passed;
}

/** Testing add when the list is sorted (ascending and descending).
 * Ascending is 6 in a row, resulting tree looks like, rather than a linked list on the right side
 *
 *                 movie4
 *              /         \
 *         movie2         movie5
 *        /      \        /    \
 *     movie1   movie3  NULL  movie6
 *
 * Passes when the tree automatically balances.
 * @returns true if the test passed, false otherwise
 */
bool test_avl_add_single_side()
{
    bool passed = true;
    AVL *avl = new_avl();

    PRINT_DEBUG("Testing down right side");
    PRINT_DEBUG("Testing adding %s to the AVL\n", movie_to_str(movie1));
    avl_add(avl, movie1);

    PRINT_DEBUG("Current tree (BREADTH_FIRST): %s\n", avl_to_str(avl, BREADTH_FIRST));

    passed &= ASSERT_EQUAL(1, avl->size);
    passed &= ASSERT_EQUAL(movie1, avl->root->movie);
    passed &= ASSERT_NULL(avl->root->left);
    passed &= ASSERT_NULL(avl->root->right);

    PRINT_DEBUG("Testing adding %s to the AVL\n", movie_to_str(movie2));

    avl_add(avl, movie2);

    PRINT_DEBUG("Current tree (BREADTH_FIRST): %s; Current Size: %d, Rotations: %d\n",
                avl_to_str(avl, BREADTH_FIRST), avl->size, avl->rotations);

    passed &= ASSERT_EQUAL(2, avl->size);
    passed &= ASSERT_EQUAL(movie1, avl->root->movie);
    passed &= ASSERT_NULL(avl->root->left);
    passed &= ASSERT_EQUAL(movie2, avl->root->right->movie);
    passed &= ASSERT_EQUAL(0, avl->rotations);

    PRINT_DEBUG("Testing adding %s to the AVL\n", movie_to_str(movie3));

    avl_add(avl, movie3);

    PRINT_DEBUG("Current tree (BREADTH_FIRST): %s; Current Size: %d, Rotations: %d\n",
                avl_to_str(avl, BREADTH_FIRST), avl->size, avl->rotations);

    passed &= ASSERT_EQUAL(3, avl->size);
    passed &= ASSERT_EQUAL(movie2, avl->root->movie);
    passed &= ASSERT_EQUAL(movie1, avl->root->left->movie);
    passed &= ASSERT_EQUAL(movie3, avl->root->right->movie);
    passed &= ASSERT_EQUAL(1, avl->rotations);

    PRINT_DEBUG("Testing adding %s to the AVL\n", movie_to_str(movie4));

    avl_add(avl, movie4);

    PRINT_DEBUG("Current tree (BREADTH_FIRST): %s; Current Size: %d, Rotations: %d\n",
                avl_to_str(avl, BREADTH_FIRST), avl->size, avl->rotations);

    passed &= ASSERT_EQUAL(4, avl->size);
    passed &= ASSERT_EQUAL(movie2, avl->root->movie);
    passed &= ASSERT_EQUAL(movie1, avl->root->left->movie);
    passed &= ASSERT_EQUAL(movie3, avl->root->right->movie);
    passed &= ASSERT_EQUAL(movie4, avl->root->right->right->movie);
    passed &= ASSERT_EQUAL(1, avl->rotations);

    PRINT_DEBUG("Testing adding %s to the AVL\n", movie_to_str(movie5));

    avl_add(avl, movie5);

    PRINT_DEBUG("Current tree (BREADTH_FIRST): %s; Current Size: %d, Rotations: %d\n",
                avl_to_str(avl, BREADTH_FIRST), avl->size, avl->rotations);

    passed &= ASSERT_EQUAL(5, avl->size);
    passed &= ASSERT_EQUAL(movie2, avl->root->movie);
    passed &= ASSERT_EQUAL(movie1, avl->root->left->movie);
    passed &= ASSERT_EQUAL(movie4, avl->root->right->movie);
    passed &= ASSERT_EQUAL(movie3, avl->root->right->left->movie);
    passed &= ASSERT_EQUAL(movie5, avl->root->right->right->movie);
    passed &= ASSERT_EQUAL(2, avl->rotations);

    PRINT_DEBUG("Testing adding %s to the AVL\n", movie_to_str(movie6));

    avl_add(avl, movie6);

    PRINT_DEBUG("Current tree (BREADTH_FIRST): %s; Current Size: %d, Rotations: %d\n",
                avl_to_str(avl, BREADTH_FIRST), avl->size, avl->rotations);

    passed &= ASSERT_EQUAL(6, avl->size);
    passed &= ASSERT_EQUAL(movie4, avl->root->movie);
    passed &= ASSERT_EQUAL(movie2, avl->root->left->movie);
    passed &= ASSERT_EQUAL(movie5, avl->root->right->movie);
    passed &= ASSERT_EQUAL(movie1, avl->root->left->left->movie);
    passed &= ASSERT_EQUAL(movie3, avl->root->left->right->movie);
    passed &= ASSERT_EQUAL(movie6, avl->root->right->right->movie);
    passed &= ASSERT_EQUAL(3, avl->rotations);

    free_avl(avl);
    avl = new_avl();
    // now testing down left side

    PRINT_DEBUG("Testing down left side");
    PRINT_DEBUG("Testing adding %s to the AVL\n", movie_to_str(movie6));

    avl_add(avl, movie6);

    PRINT_DEBUG("Current tree (BREADTH_FIRST): %s\n", avl_to_str(avl, BREADTH_FIRST));

    passed &= ASSERT_EQUAL(1, avl->size);
    passed &= ASSERT_EQUAL(movie6, avl->root->movie);
    passed &= ASSERT_NULL(avl->root->left);
    passed &= ASSERT_NULL(avl->root->right);

    PRINT_DEBUG("Testing adding %s to the AVL\n", movie_to_str(movie5));

    avl_add(avl, movie5);

    PRINT_DEBUG("Current tree (BREADTH_FIRST): %s; Current Size: %d, Rotations: %d\n",
                avl_to_str(avl, BREADTH_FIRST), avl->size, avl->rotations);

    passed &= ASSERT_EQUAL(2, avl->size);
    passed &= ASSERT_EQUAL(movie6, avl->root->movie);
    passed &= ASSERT_EQUAL(movie5, avl->root->left->movie);
    passed &= ASSERT_NULL(avl->root->right);

    PRINT_DEBUG("Testing adding %s to the AVL\n", movie_to_str(movie4));

    avl_add(avl, movie4);

    PRINT_DEBUG("Current tree (BREADTH_FIRST): %s; Current Size: %d, Rotations: %d\n",
                avl_to_str(avl, BREADTH_FIRST), avl->size, avl->rotations);

    passed &= ASSERT_EQUAL(3, avl->size);
    passed &= ASSERT_EQUAL(movie5, avl->root->movie);
    passed &= ASSERT_EQUAL(movie4, avl->root->left->movie);
    passed &= ASSERT_EQUAL(movie6, avl->root->right->movie);

    free_avl(avl);
    avl = new_avl();
    // Test a double rotation
    PRINT_DEBUG("Testing down a double rotation");

    PRINT_DEBUG("Testing adding %s to the AVL\n", movie_to_str(movie4));
    avl_add(avl, movie4);

    passed &= ASSERT_EQUAL(1, avl->size);
    passed &= ASSERT_EQUAL(movie4, avl->root->movie);
    passed &= ASSERT_NULL(avl->root->left);
    passed &= ASSERT_NULL(avl->root->right);
    passed &= ASSERT_EQUAL(0, avl->rotations);

    PRINT_DEBUG("Testing adding %s to the AVL\n", movie_to_str(movie2));
    avl_add(avl, movie2);

    passed &= ASSERT_EQUAL(2, avl->size);
    passed &= ASSERT_EQUAL(movie4, avl->root->movie);
    passed &= ASSERT_EQUAL(movie2, avl->root->left->movie);
    passed &= ASSERT_NULL(avl->root->right);
    passed &= ASSERT_EQUAL(0, avl->rotations);

    PRINT_DEBUG("Testing adding %s to the AVL\n", movie_to_str(movie3));
    avl_add(avl, movie3);

    passed &= ASSERT_EQUAL(3, avl->size);
    passed &= ASSERT_EQUAL(movie3, avl->root->movie);
    passed &= ASSERT_EQUAL(movie2, avl->root->left->movie);
    passed &= ASSERT_EQUAL(movie4, avl->root->right->movie);
    passed &= ASSERT_EQUAL(2, avl->rotations);

    free_avl(avl);
    return passed;
}

/**
 * Testing AVL removal of a leaf node
 *
 * @returns true if the test passed, false otherwise
 */
bool test_avl_remove()
{
    bool passed = true;
    AVL *avl = new_avl();

    avl_add(avl, movie2);
    avl_add(avl, movie1);
    avl_add(avl, movie3);

    PRINT_DEBUG("Current tree (BREADTH_FIRST): %s; Current Size: %d, Rotations: %d\n",
                avl_to_str(avl, BREADTH_FIRST), avl->size, avl->rotations);

    PRINT_DEBUG("Testing removing %s from the AVL\n", movie_to_str(movie2));

    avl_remove(avl, movie2);

    PRINT_DEBUG("Current tree (BREADTH_FIRST): %s; Current Size: %d, Rotations: %d\n",
                avl_to_str(avl, BREADTH_FIRST), avl->size, avl->rotations);

    passed &= ASSERT_EQUAL(2, avl->size);
    passed &= ASSERT_EQUAL(movie3, avl->root->movie);
    passed &= ASSERT_EQUAL(movie1, avl->root->left->movie);

    PRINT_DEBUG("Testing removing %s from the AVL\n", movie_to_str(movie1));

    avl_remove(avl, movie1);

    PRINT_DEBUG("Current tree (BREADTH_FIRST): %s; Current Size: %d, Rotations: %d\n",
                avl_to_str(avl, BREADTH_FIRST), avl->size, avl->rotations);

    passed &= ASSERT_EQUAL(1, avl->size);
    passed &= ASSERT_EQUAL(movie3, avl->root->movie);

    PRINT_DEBUG("Testing removing %s from the AVL\n", movie_to_str(movie3));

    avl_remove(avl, movie3);

    PRINT_DEBUG("Current tree (BREADTH_FIRST): %s; Current Size: %d, Rotations: %d\n",
                avl_to_str(avl, BREADTH_FIRST), avl->size, avl->rotations);

    passed &= ASSERT_EQUAL(0, avl->size);
    passed &= ASSERT_NULL(avl->root);

    free_avl(avl);
    return passed;
}

/** Tests removal of a subtree root node, causing a forced rebalance
 *
 * @returns true if the test passed, false otherwise
 */
bool test_avl_remove_single_side()
{
    bool passed = true;
    AVL *avl = new_avl();

    avl_add(avl, movie3);
    avl_add(avl, movie2);
    avl_add(avl, movie4);
    avl_add(avl, movie5);

    PRINT_DEBUG("Current tree (BREADTH_FIRST): %s; Current Size: %d, Rotations: %d\n",
                avl_to_str(avl, BREADTH_FIRST), avl->size, avl->rotations);

    PRINT_DEBUG("Testing removing %s from the AVL\n", movie_to_str(movie2));

    avl_remove(avl, movie2);

    PRINT_DEBUG("Current tree (BREADTH_FIRST): %s; Current Size: %d, Rotations: %d\n",
                avl_to_str(avl, BREADTH_FIRST), avl->size, avl->rotations);

    passed &= ASSERT_EQUAL(3, avl->size);
    passed &= ASSERT_EQUAL(movie4, avl->root->movie);
    passed &= ASSERT_EQUAL(movie3, avl->root->left->movie);
    passed &= ASSERT_EQUAL(movie5, avl->root->right->movie);
    passed &= ASSERT_EQUAL(1, avl->rotations);

    PRINT_DEBUG("Testing removing %s from the AVL\n", movie_to_str(movie3));

    avl_remove(avl, movie3);

    PRINT_DEBUG("Current tree (BREADTH_FIRST): %s; Current Size: %d, Rotations: %d\n",
                avl_to_str(avl, BREADTH_FIRST), avl->size, avl->rotations);

    passed &= ASSERT_EQUAL(2, avl->size);
    passed &= ASSERT_EQUAL(movie4, avl->root->movie);
    passed &= ASSERT_EQUAL(movie5, avl->root->right->movie);

    PRINT_DEBUG("Testing removing %s from the AVL\n", movie_to_str(movie4));

    avl_remove(avl, movie4);

    PRINT_DEBUG("Current tree (BREADTH_FIRST): %s; Current Size: %d, Rotations: %d\n",
                avl_to_str(avl, BREADTH_FIRST), avl->size, avl->rotations);

    passed &= ASSERT_EQUAL(1, avl->size);
    passed &= ASSERT_EQUAL(movie5, avl->root->movie);

    PRINT_DEBUG("Testing removing %s from the AVL\n", movie_to_str(movie5));

    avl_remove(avl, movie5);

    PRINT_DEBUG("Current tree (BREADTH_FIRST): %s; Current Size: %d, Rotations: %d\n",
                avl_to_str(avl, BREADTH_FIRST), avl->size, avl->rotations);

    passed &= ASSERT_EQUAL(0, avl->size);
    passed &= ASSERT_NULL(avl->root);

    free_avl(avl);
    return passed;
}

/**
 * Testing remove causing a double rotation rebalance
 *
 *                 movie4          remove          movie3
 *              /         \        movie 5       /       \
 *         movie2         movie5   ---->     movie2      movie4
 *        /      \        /    \             /    \     /     \
 *      NULL   movie3  NULL  NULL          NULL  NULL   NULL   NULL
 *
 *
 *
 *
 * @returns true if the test passed, false otherwise
 */
bool test_avl_remove_double_rotation()
{
    bool passed = true;
    AVL *avl = new_avl();

    avl_add(avl, movie4);
    avl_add(avl, movie2);
    avl_add(avl, movie5);
    avl_add(avl, movie3);

    PRINT_DEBUG("Current tree (BREADTH_FIRST): %s; Current Size: %d, Rotations: %d\n",
                avl_to_str(avl, BREADTH_FIRST), avl->size, avl->rotations);

    PRINT_DEBUG("Testing removing %s from the AVL\n", movie_to_str(movie5));

    avl_remove(avl, movie5);
    PRINT_DEBUG("Current tree (BREADTH_FIRST): %s; Current Size: %d, Rotations: %d\n",
                avl_to_str(avl, BREADTH_FIRST), avl->size, avl->rotations);

    passed &= ASSERT_EQUAL(3, avl->size);
    passed &= ASSERT_EQUAL(movie3, avl->root->movie);
    passed &= ASSERT_EQUAL(movie2, avl->root->left->movie);
    passed &= ASSERT_EQUAL(movie4, avl->root->right->movie);
    passed &= ASSERT_EQUAL(2, avl->rotations);

    free_avl(avl);
    return passed;
}

/** Tests the avl_find() function
 *
 * @returns true if the test passed, false otherwise
 */
bool test_avl_find()
{
    bool passed = true;
    AVL *avl = new_avl();

    avl_add(avl, movie2);
    avl_add(avl, movie1);
    avl_add(avl, movie3);

    PRINT_DEBUG("Current tree (BREADTH_FIRST): %s; Current Size: %d, Rotations: %d\n",
                avl_to_str(avl, BREADTH_FIRST), avl->size, avl->rotations);

    PRINT_DEBUG("Testing finding %s in the AVL\n", movie_to_str(movie2));

    Movie *found = avl_find(avl, movie2->title);

    passed &= ASSERT_EQUAL(movie2, found);

    PRINT_DEBUG("Testing finding %s in the AVL\n", movie_to_str(movie1));

    found = avl_find(avl, movie1->title);

    passed &= ASSERT_EQUAL(movie1, found);

    PRINT_DEBUG("Testing finding %s in the AVL\n", movie_to_str(movie3));

    found = avl_find(avl, movie3->title);

    passed &= ASSERT_EQUAL(movie3, found);

    PRINT_DEBUG("Testing finding %s in the AVL\n", movie_to_str(movie4));

    found = avl_find(avl, movie4->title);

    passed &= ASSERT_NULL(found);

    free_avl(avl);
    return passed;
}

/**
 * Tests the avl_to_str() function for breadth first
 *
 * @returns true if the test passed, false otherwise
 */
bool test_avl_to_str_breadth_first()
{
    bool passed = true;
    AVL *avl = new_avl();

    avl_add(avl, movie2);
    avl_add(avl, movie1);
    avl_add(avl, movie3);

    PRINT_DEBUG("Current tree (BREADTH_FIRST): %s; Current Size: %d, Rotations: %d\n",
                avl_to_str(avl, BREADTH_FIRST), avl->size, avl->rotations);

    char *str = avl_to_str(avl, BREADTH_FIRST);

    passed &= ASSERT_STR_EQUAL("{title: B Movie Two, id: 2}, {title: A Movie One, id: 1}, {title: C Movie Three, id: 3}, NULL, NULL, NULL, NULL", str);

    free(str);
    free_avl(avl);
    return passed;
}

/**
 * Tests the avl_to_str() function for preordering
 *
 * @returns true if the test passed, false otherwise
 */
bool test_avl_to_str_preorder()
{
    bool passed = true;
    AVL *avl = new_avl();

    avl_add(avl, movie2);
    avl_add(avl, movie1);
    avl_add(avl, movie3);

    PRINT_DEBUG("Current tree (PRE_ORDER): %s; Current Size: %d, Rotations: %d\n",
                avl_to_str(avl, PRE_ORDER), avl->size, avl->rotations);

    char *str = avl_to_str(avl, PRE_ORDER);

    passed &= ASSERT_STR_EQUAL("{title: B Movie Two, id: 2}, {title: A Movie One, id: 1}, {title: C Movie Three, id: 3}", str);

    free(str);
    free_avl(avl);
    return passed;
}

/**
 * Tests the avl_to_str() function for inorder
 *
 * @returns true if the test passed, false otherwise
 */
bool test_avl_to_str_inorder()
{
    bool passed = true;
    AVL *avl = new_avl();

    avl_add(avl, movie2);
    avl_add(avl, movie1);
    avl_add(avl, movie3);

    PRINT_DEBUG("Current tree (IN_ORDER): %s; Current Size: %d, Rotations: %d\n",
                avl_to_str(avl, IN_ORDER), avl->size, avl->rotations);

    char *str = avl_to_str(avl, IN_ORDER);
    passed &= ASSERT_STR_EQUAL("{title: A Movie One, id: 1}, {title: B Movie Two, id: 2}, {title: C Movie Three, id: 3}", str);

    free(str);
    free_avl(avl);
    return passed;
}

/**
 * Tests the avl_to_str() function for postorder
 *
 * @returns true if the test passed, false otherwise
 */
bool test_avl_to_str_postorder()
{
    bool passed = true;
    AVL *avl = new_avl();

    avl_add(avl, movie2);
    avl_add(avl, movie1);
    avl_add(avl, movie3);

    PRINT_DEBUG("Current tree (POST_ORDER): %s; Current Size: %d, Rotations: %d\n",
                avl_to_str(avl, POST_ORDER), avl->size, avl->rotations);

    char *str = avl_to_str(avl, POST_ORDER);
    passed &= ASSERT_STR_EQUAL("{title: A Movie One, id: 1}, {title: C Movie Three, id: 3}, {title: B Movie Two, id: 2}", str);

    free(str);
    free_avl(avl);
    return passed;
}

/**
 * Tests converting the AVL to a sorted array to make sure
 * it ends up properly sorted.
 *
 * @returns true if the test passed, false otherwise
 */
bool test_avl_to_sorted_array()
{
    bool passed = true;
    AVL *avl = new_avl();

    avl_add(avl, movie2);
    avl_add(avl, movie1);
    avl_add(avl, movie3);
    avl_add(avl, movie4); // intentionally skipping 5
    avl_add(avl, movie6);

    PRINT_DEBUG("Current tree (BREADTH_FIRST): %s; Current Size: %d, Rotations: %d\n",
                avl_to_str(avl, BREADTH_FIRST), avl->size, avl->rotations);

    Movie **array = avl_to_sorted_array(avl);

    passed &= ASSERT_EQUAL(movie1, array[0]);
    passed &= ASSERT_EQUAL(movie2, array[1]);
    passed &= ASSERT_EQUAL(movie3, array[2]);
    passed &= ASSERT_EQUAL(movie4, array[3]);
    passed &= ASSERT_EQUAL(movie6, array[4]);

    free(array);
    free_avl(avl);
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
    add_test(set, "testing new_avl() creates an empty AVL", GROUP_GENERAL, test_new_avl);
    add_test(set, "testing avl_add() adds multiple movies to the AVL", GROUP_ADD, test_avl_add);
    add_test(set, "testing avl_add() adds multiple movies to the AVL down a single side", GROUP_ADD, test_avl_add_single_side);
    add_test(set, "testing avl_remove() removes movies from the AVL", GROUP_REMOVE, test_avl_remove);
    add_test(set, "testing avl_remove() removes movies from the AVL causing single rotation", GROUP_REMOVE, test_avl_remove_single_side);
    add_test(set, "testing avl_remove() removes movies from AVL causing double rotation", GROUP_REMOVE, test_avl_remove_double_rotation);
    add_test(set, "testing avl_find() finds movies in the AVL", GROUP_GET, test_avl_find);
    add_test(set, "testing avl_to_str() prints the AVL in breadth first order", GROUP_TO_STRING, test_avl_to_str_breadth_first);
    add_test(set, "testing avl_to_str() prints the AVL in preorder", GROUP_TO_STRING, test_avl_to_str_preorder);
    add_test(set, "testing avl_to_str() prints the AVL in inorder", GROUP_TO_STRING, test_avl_to_str_inorder);
    add_test(set, "testing avl_to_str() prints the AVL in postorder", GROUP_TO_STRING, test_avl_to_str_postorder);
    add_test(set, "testing avl_to_sorted_array() converts the AVL to a sorted array", GROUP_GENERAL, test_avl_to_sorted_array);

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
