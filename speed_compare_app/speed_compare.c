/**
 * This program compares the speed of the
 * SortedLinkedList, SortedVector, and BST implementations
 *
 * This is the main driver for the program.
 *
 * Use it to help you answer the questions in the homework.
 *
 * @author Albert Lionelle
 *
 * Written for CS 5008 @ Northeastern University
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <ctype.h>

#include "logging.h"
#include "defaults.h"
#include "tests.h"
#include "file_handler.h"

/**
 * This is a helper function to print the help message
 */
void print_help()
{
    printf("Usage: ./speed_compare [OPTIONS] input_file\n");

    printf("This program compares the speed of the SortedLinkedList, SortedVector, and BST implementations\n");

    printf("Input file (required): a file with movie titles listed on each line.\n");

    printf("Options:\n");
    printf("  -h, --help\t\t\tPrints this help message. Ends the program.\n");
    printf("  -v, --verbose\t\t\tPrints extra information about the program.\n");
    printf("  -d, --debug\t\t\tPrints debug information about the program. Setting debug will also enable verbose.\n");
    printf("  -o, --output [FILE]\t\tPrints the test output to the given file, assumes CSV format. Defaults to %s if not provided.\n",
           OUTPUT_FILE);
    printf("  -i, --increment [NUM]\t\tSets the increment amount for the number of movies to test. Defaults to %d if not provided.\n",
           INCREMENT);

    printf("\n\n");
    printf("Example Usage:\n");
    printf("  ./speed_compare -v -o results.csv movie_titles_us_unique.txt\n");
}

/**
 * Checks for -h, or --help in the program arguments
 *
 * @param argc the number of arguments
 * @param argv the arguments
 * @return true if -h or --help is in the arguments, false otherwise
 */
bool check_for_help(const int argc, const char **argv)
{
    for (int i = 0; i < argc; i++)
    {
        if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0)
        {
            return true;
        }
    }
    return false;
}

/**
 * Checks to see if a string is an int value for parsing arguments
 * C does not have an easy built in way to do this, this is one option.
 *
 * @param str the string to check
 * @return true if the string is an int, false otherwise
 */
int is_int(const char *str)
{
    while (*str)
    {
        if (!isdigit(*str))
        {
            return false;
        }
        str++;
    }
    return true;
}

/**
 * Parse arguments.
 *  Looks for the flags, and set them, and returns the final input file
 *  If the input file is not found, returns NULL
 *
 * @param argc the number of arguments
 * @param argv the arguments
 * @return the input file if found, NULL otherwise
 *
 */
const char *process_args(const int argc, const char **argv)
{
    const char *input_file = NULL;
    for (int i = 0; i < argc; i++)
    {
        if (strcmp(argv[i], "-d") == 0 || strcmp(argv[i], "--debug") == 0)
        {
            LOG_LEVEL = LOG_LEVEL_DEBUG;
            LOG_DEBUG("Logging level set to Debug\n");
        }
        else if ((strcmp(argv[i], "-v") == 0 || strcmp(argv[i], "--verbose") == 0) && LOG_LEVEL != LOG_LEVEL_DEBUG)
        {
            LOG_LEVEL = LOG_LEVEL_INFO;
            LOG_DEBUG("Logging level set to info (verbose).\n");
        }
        else if (strcmp(argv[i], "-o") == 0 || strcmp(argv[i], "--output") == 0)
        {
            if (i + 1 < argc && argv[i + 1][0] != '-')
            {
                OUTPUT_FILE = argv[++i]; // force increment to get the next argument
                LOG_DEBUG("Output file set to %s\n", OUTPUT_FILE);
            }
            else
            {
                LOG_WARN("No output file provided, keeping default.\n");
            }
        }
        else if (strcmp(argv[i], "-i") == 0 || strcmp(argv[i], "--increment") == 0)
        {
            if (i + 1 < argc)
            {
                if (is_int(argv[i + 1]))
                {
                    INCREMENT = atoi(argv[++i]); // force increment to get the next argument
                    LOG_DEBUG("Increment set to %d\n", INCREMENT);
                }
                else
                {
                    LOG_WARN("Increment must be an integer, keeping default.\n");
                }
            }
            else
            {
                LOG_WARN("No increment provided, keeping default.\n");
            }
        }
        else
        {
            input_file = argv[i];
        }
    }
    return input_file;
}

/**
 * Main entry point. Checks arguments, loads the movies, and runs the tests.
 *
 * @param argc the number of arguments
 * @param argv the arguments
 */
int main(int argc, const char **argv)
{
    if (argc < 2)
    {
        LOG_ERROR("Missing input files\n");
        print_help();
        return 1; // ends with an error signal
    }
    if (check_for_help(argc, argv))
    {
        print_help();
        return 0; // ends the program early, but successfully
    }

    const char *input_file = process_args(argc, argv);
    if (input_file == NULL)
    {
        LOG_ERROR("No input file provided\n");
        print_help();
        return 1; // ends with an error signal
    }
    LOG_INFO("Starting Speed Compare: Input File: %s, Output File: %s, Testing Increments: %d\n",
             input_file, OUTPUT_FILE, INCREMENT);

    MovieVector *movies = load_movies(input_file);
    if (movies == NULL)
    {
        return 1; // error printed in load_movies, but ending program as vector needs to exist
    }

    // initialize output file
    bool check = initialize_results_file(OUTPUT_FILE, CSV_HEADER);
    if (!check)
    {
        LOG_ERROR("Error initializing output file\n");
        return 1;
    }
    srand(time(NULL)); // set random seed to current time, used by rand() in tests

    double *results = (double *)malloc(sizeof(double) * RESULTS_LENGTH);

    for (int n = INCREMENT; n < movies->size; n += INCREMENT)
    {
        memset(results, 0, sizeof(double) * RESULTS_LENGTH); // reset results array
        results[0] = n;
        run_tests(movies, n, results);                    // run the tests with the current number of movies
        write_line(OUTPUT_FILE, results, RESULTS_LENGTH); // write the number of movies to the file
    }

    memset(results, 0, sizeof(double) * RESULTS_LENGTH); // reset results array
    results[0] = movies->size - 1;                       // final run with the full vector as increment may skip the last one
    run_tests(movies, movies->size - 1, results);        // run the tests with the full movies vector
    write_line(OUTPUT_FILE, results, RESULTS_LENGTH);    // write the number of movies to the file

    LOG_INFO("Finished writing %s with %d lines\n", OUTPUT_FILE, movies->size / INCREMENT + 1);
    LOG_INFO("Testing completed successfully\n");

    // clean up memory
    clear_and_free_vector(movies);
    free(results);
}