# Tests

This directory contains testing code for the data structures being built. As you build the data structures, you should run these tests. It is also worth noting that these tests are not exhaustive, and you should write your own tests to ensure that your code is working properly.

> STUDENT NOTE:   
> These files are not graded. You should write your own tests to ensure that your code is working properly, and it is highly recommend you spend time reviewing the code and understanding the tests. If you your code passes all these tests, there is a high probability that your code will pass the autograder. 

## Running Tests

There are three different testing programs, one for bst, one for linked list, and one for vector. Each one
tests the data structure in isolation, and it setup using the same test util format (see below). Here are example runs for each.

The following commands are if you are on linux or macOS, for windows, replace .out with .exe.


```bash
$ make avl-test
$ ./avl-test.out -v
```


```bash
$ make bst-test
$ ./bst-test.out -v
```

The `-v` flag is optional, but will enable feedback. For example, sample output for the above command is blow:

```
////////////////TODO: Update printout
$ make avl-test
gcc    -Wall   -O3 -o list-test.out tests/linked_list_tester.c lib/linked_list.c lib/sorted_list.c lib/movie.c
$ ./list-test.out -v
Running tests 0 through 15
1. new_linked_list() creates an empty linked list: PASSED
2. ll_add_front() adds a node to the front of the list: PASSED
3. ll_add_back() adds a node to the back of the list: PASSED
4. ll_insert() adds a node to the list at the given index: PASSED
5. ll_insert() does nothing if the index is out of bounds: PASSED
6. ll_remove_front() removes a node from the front of the list: PASSED
7. ll_remove_back() removes a node from the back of the list: PASSED
8. ll_remove() removes a node from the list at the given index: PASSED
9. ll_remove() does nothing if the index is out of bounds: PASSED
10. ll_get() gets a node from the list at the given index: PASSED
11. ll_get() does nothing if the index is out of bounds: PASSED
12. ll_is_empty() returns true if the list is empty: PASSED
13. ll_to_str() returns a string representation of the list: PASSED
14. add_to_sorted_list() adds a movie to the sorted list: PASSED
15. find_in_sorted_list() finds a movie in the sorted list: PASSED
16. sorted_list_remove() properly removes movies based on title: PASSED
```

If you run without the `-v` flag, it will only print tests that have failed, so a correct run will 
show nothing.


> Note: The commands assume the directory structure is preserved. As such, the Makefile assumes the files are in the tests directory,and you are executing `make` at the level of the Makefile. If you move the files, you will need to update the Makefile. However, moving the files can also break the autograder... so please don't move them!
>


## Options
There are multiple options for running tests. Here are the options for the test util:

* `-v` or `--verbose` - verbose, prints all tests, even if they pass
* `-d` or `--debug` - debug, prints copious details about the tests - you rarely want to run this on all tests
* `-g` or `--group` - runs tests for a specific group. For example `-g add` will run tests that add to the data structure. To see the groups, look at the define at the top of each test file. 
* n to n  - adding two numbers will run the tests from the first number to the second number. For example `./test-vector.out 0 5` will run the first 5 tests. or more commonly, you may want to run `./test-vector.out 5 5 -d` to run the 5 test, and print all debug information while that single test is running. You can then add your own debug messages to help you track down the error.


## Writing Tests
Use the example provided in the file, but you will notice for every test, you also add to the TestSet. This is how the driver knows what tests to run. You can add as many tests as you want, but you must add them to the TestSet. 

```c

bool test_my_linked_list() { // all tests must return a bool
    // Create a new linked list
    LinkedList *list = new_linked_list();

    // Check that the list is empty
    if (!ll_is_empty(list)) {
        return false;
    }
    return true;
}
TestingSet *init_testing_set() { // this is already in every file above the main
    TestingSet *set = new_testing_set();
    ///already 15 other add_test calls
    add_test(set, "tests to see if is_empty works", GROUP_GENERAL, test_my_linked_list);

    return set;
}
```


## Debugging Tests

You can add `PRINT_DEBUG("message")` to your tests to print out debug messages. This is useful if you want to see what is happening in your tests. Look at [testing_util.h](testing_util.h) for more information on defines setup to make testing easier. 
