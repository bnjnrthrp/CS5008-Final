/**
 *
 * A series of tests to run on each data structure to compare their speed.
 *
 * @author Albert Lionelle
 * Modified by Benjamin Northrop
 */

#ifndef TESTS_H
#define TESTS_H

#include <stdlib.h>
#include <time.h>
#include <stdio.h>

#include "logging.h"
#include "../lib/movie.h"
#include "../lib/avl.h"
#include "../lib/bst.h"
#include "../lib/vector.h"

#define CSV_HEADER "N,AVL Add,BST Add,AVL Add Rotations,AVL Add Height,BST Add Height,AVL Search,BST Search,AVL Save,BST Save,AVL Remove,BST Remove,AVL Remove Rotations\n"
#define RESULTS_LENGTH 13

#define ADD_START 1
#define ADD_HEIGHTS 4
#define SEARCH_START 6
#define WRITE_START 8
#define REMOVE_START 10

#define AVL_LOC 0
#define BST_LOC 1
#define AVL_ROTATIONS 2

#define SAMPLE_SPLIT .7 // 70% of the movies will exist, 30% may or may not exist

#define AVL_OUT "speed_test_files/avl.txt"
#define BST_OUT "speed_test_files/bst.txt"

/**
 * Adds movies to each data structure, and records the time it takes to add them
 *
 * @param movies the MovieVector to act as the TestSet
 * @param total the total number of movies to pull from MovieVector
 * @param results array of doubles to store the results in
 * @param avl the AVL to add movies to
 * @param bst the BST to add movies to
 */
void add_movies(MovieVector *movies, int total, double *results, AVL *avl, BST *bst)
{
    // add movies to each data structure
    LOG_INFO("Adding movies %d to each data structure\n", total);

    LOG_DEBUG("Adding to avl\n");
    clock_t start = clock();
    for (int i = 0; i < total; i++)
    {
        avl_add(avl, movies->movies[i]);
    }
    clock_t end = clock();
    results[ADD_START + AVL_LOC] = (double)(end - start) / CLOCKS_PER_SEC;
    LOG_DEBUG("...result was %f\n", results[ADD_START + AVL_LOC]);

    LOG_DEBUG("Adding to bst\n");
    start = clock();
    for (int i = 0; i < total; i++)
    {
        bst_add(bst, movies->movies[i]);
    }
    end = clock();
    results[ADD_START + BST_LOC] = (double)(end - start) / CLOCKS_PER_SEC;
    LOG_DEBUG("..result was %f\n", results[ADD_START + BST_LOC]);

    LOG_DEBUG("Adding the AVL rotations\n");
    results[ADD_START + AVL_ROTATIONS] = avl->rotations;

    LOG_DEBUG("Adding the AVL and BST heights\n");
    results[ADD_HEIGHTS + AVL_LOC] = avl->root->height;
    results[ADD_HEIGHTS + BST_LOC] = bst->root->height;
}

/**
 * Build sample indexes - builds an array of indexes to pull from the MovieVector
 *
 * The sample uses SAMPLE_SPLIT to ensure that 70% of the movies will exist in the data structures
 * While the remaining 30% may or may not exist in the data structures (forcing worst case search/remove)
 *
 * @param split_max Every number in sample split must be under this number
 * @param total_movies the size of the MovieVector, all indexes must be under this
 * @param sample_size the total number of movies to pull from MovieVector
 *
 * @return an array of indexes to pull from the MovieVector
 */
int *build_sample_indexes(int split_max, int total_movies, int sample_size)
{
    int *sample_indexes = malloc(sizeof(int) * sample_size);
    LOG_DEBUG("Building sample indexes\n");
    for (int i = 0; i < sample_size; i++)
    {
        int index = rand() % total_movies;
        while (index > split_max && i < (sample_size * SAMPLE_SPLIT))
        {
            index = rand() % total_movies;
        }
        sample_indexes[i] = index;
    }
    float percent_under_split_max = 0;
    for (int i = 0; i < sample_size; i++)
    {
        if (sample_indexes[i] <= split_max)
        {
            percent_under_split_max++;
        }
    }
    LOG_DEBUG("... Percent that are findable: %f\n", percent_under_split_max / sample_size);

    return sample_indexes;
}

/**
 * Searches for movies in each data structure, and records the time it takes to search for them
 *
 *
 * @param movies the MovieVector to act as the TestSet
 * @param total the total number of movies to pull from MovieVector
 * @param results array of doubles to store the results in
 * @param avl the AVL to search for movies in
 * @param bst the BST to search for movies in
 */
void search_movies(MovieVector *movies, int total, double *results, AVL *avl, BST *bst)
{

    LOG_INFO("Searching for movies %d in each data structure\n", total);

    int *random_sample = build_sample_indexes(total, movies->size - 1, total);

    LOG_DEBUG("Searching avl\n");
    clock_t start = clock();
    for (int i = 0; i < total; i++)
    {
        avl_find(avl, movies->movies[random_sample[i]]->title);
    }
    clock_t end = clock();
    results[SEARCH_START + AVL_LOC] = (double)(end - start) / CLOCKS_PER_SEC;
    LOG_DEBUG("...result was %f\n", results[SEARCH_START + AVL_LOC]);

    LOG_DEBUG("Searching bst\n");
    start = clock();
    for (int i = 0; i < total; i++)
    {
        bst_find(bst, movies->movies[random_sample[i]]->title);
    }
    end = clock();
    results[SEARCH_START + BST_LOC] = (double)(end - start) / CLOCKS_PER_SEC;
    LOG_DEBUG("...result was %f\n", results[SEARCH_START + BST_LOC]);

    free(random_sample);
}

/**
 * Tests that involve writing the data structures out to a file in sorted order.
 *
 * @param movies the MovieVector to act as the TestSet
 * @param total the total number of movies to pull from MovieVector
 * @param results array of doubles to store the results in
 * @param avl the AVL to search for movies in
 * @param bst the BST to search for movies in
 */
void write_tests(MovieVector *movies, int total, double *results, AVL *avl, BST *bst)
{

    LOG_INFO("Writing movies %d in each data structure\n", total);

    LOG_DEBUG("Writing avl\n");
    FILE *file = fopen(AVL_OUT, "w");

    clock_t start = clock();
    Movie **avl_sorted_array = avl_to_sorted_array(avl);
    for (int i = 0; i < total; i++)
    {
        fprintf(file, "%s\n", avl_sorted_array[i]->title);
    }
    clock_t end = clock();
    fclose(file);
    free(avl_sorted_array);

    results[WRITE_START + AVL_LOC] = (double)(end - start) / CLOCKS_PER_SEC;
    LOG_DEBUG("...result was %f\n", results[WRITE_START + AVL_LOC]);

    LOG_DEBUG("Writing bst\n");
    file = fopen(BST_OUT, "w");
    start = clock();
    Movie **bst_sorted_array = bst_to_sorted_array(bst); // extra step for BST
    for (int i = 0; i < total; i++)
    {
        fprintf(file, "%s\n", bst_sorted_array[i]->title);
    }
    end = clock();
    fclose(file);
    free(bst_sorted_array);

    results[WRITE_START + BST_LOC] = (double)(end - start) / CLOCKS_PER_SEC;
    LOG_DEBUG("...result was %f\n", results[WRITE_START + BST_LOC]);
}

/**
 * Removes movies from each data structure, and records the time it takes to remove them
 *
 *
 * @param movies the MovieVector to act as the TestSet
 * @param total the total number of movies to pull from MovieVector
 * @param results array of doubles to store the results in
 * @param avl the AVL to search for movies in
 * @param bst the BST to search for movies in
 */
void remove_tests(MovieVector *movies, int total, double *results, AVL *avl, BST *bst)
{
    LOG_INFO("Removing movies %d in each data structure\n", total);

    int *random_sample = build_sample_indexes(total, movies->size - 1, total);
    avl->rotations = 0; // Reset the rotations counter
    LOG_DEBUG("Removing sorted vector\n");
    clock_t start = clock();
    for (int i = 0; i < total; i++)
    {
        avl_remove(avl, movies->movies[random_sample[i]]);
    }
    clock_t end = clock();
    results[REMOVE_START + AVL_LOC] = (double)(end - start) / CLOCKS_PER_SEC;
    LOG_DEBUG("...result was %f\n", results[REMOVE_START + AVL_LOC]);

    LOG_DEBUG("Removing bst\n");
    start = clock();
    for (int i = 0; i < total; i++)
    {
        bst_remove(bst, movies->movies[random_sample[i]]);
    }
    end = clock();
    results[REMOVE_START + BST_LOC] = (double)(end - start) / CLOCKS_PER_SEC;
    LOG_DEBUG("...result was %f\n", results[REMOVE_START + BST_LOC]);

    LOG_DEBUG("Adding the AVL rotations\n");
    results[REMOVE_START + AVL_ROTATIONS] = avl->rotations;

    free(random_sample);
}

/**
 * Runs all tests, entry function to running the tests
 *
 * @param movies the MovieVector to act as the TestSet
 * @param total the total number of movies to pull from MovieVector
 * @param results array of doubles to store the results in
 */
void run_tests(MovieVector *movies, int total, double *results)
{
    // initialize the data structures

    LOG_INFO("Running Tests on %d movies\n", total);
    AVL *avl = new_avl();
    BST *bst = new_bst();

    // add movies to each data structure
    add_movies(movies, total, results, avl, bst);

    // search for movies in each data structure
    search_movies(movies, total, results, avl, bst);

    // write out to files
    write_tests(movies, total, results, avl, bst);

    // remove movies from each data structure
    remove_tests(movies, total, results, avl, bst);

    // free data structures (just free, no need to remove movies from them)
    free_avl(avl);
    free_bst(bst);
    LOG_INFO("Finished running tests\n\n");
}

#endif // TESTS_H