/**
 * Various functions for handling files.
 *
 * @author Albert Lionelle
 */

#ifndef FILE_HANDLER_H
#define FILE_HANDLER_H

#include <stdio.h>
#include "logging.h"
#include "../lib/movie.h"

/**
 * Loads the input file into a vector of Movies.
 *
 * It assumes that the input file is a movie title on each line.
 *
 *
 * For IDs, it will just use the line number.
 *
 * @param filename The name of the file to load.
 * @return A vector of Movies. NULL if there is an error
 */
MovieVector *load_movies(const char *filename)
{
    LOG_INFO("Loading movies from file: %s into a MovieVector\n", filename);
    MovieVector *movies = new_vector();
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        LOG_ERROR("Could not open file: %s", filename);
        return NULL;
    }
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    int id = 0;
    while ((read = getline(&line, &len, file)) != -1)
    {
        // remove the newline character
        line[read - 1] = '\0';
        Movie *movie = new_movie(line, id);
        vector_add_back(movies, movie);
        id++;
    }
    fclose(file);
    LOG_INFO("Loaded %d movies from file: %s\n", movies->size, filename)
    if (line)
    {
        free(line);
    }
    return movies;
}

/**
 * Initializes the results file with a header. This will either create
 * or overwrite the file if one already exists.
 *
 * @param filename The name of the file to write to.
 * @param header The header to write to the file.
 * @return true if the file was created successfully, false otherwise.
 */
bool initialize_results_file(const char *filename, const char *header)
{
    FILE *file = fopen(filename, "w");
    if (file == NULL)
    {
        LOG_ERROR("Could not open file: %s", filename);
        return false;
    }
    fprintf(file, "%s", header);
    fclose(file);
    return true;
}

/**
 * Writes a line to the results file. This appends to the filename,
 * so assumes it is already created with a header.
 *
 * @param filename The name of the file to write to.
 * @param line The line to write to the file. Double value array.
 *
 * @return true if the line was written successfully, false otherwise.
 */
bool write_line(const char *filename, double *line, int length)
{
    FILE *file = fopen(filename, "a");
    if (file == NULL)
    {
        LOG_ERROR("Could not open file: %s", filename);
        return false;
    }
    for (int i = 0; i < length; i++)
    {
        if (i > 0)
        {
            fprintf(file, ",");
        }
        fprintf(file, "%f", line[i]);
    }
    fprintf(file, "\n");
    fclose(file);
    return true;
}

#endif // FILE_HANDLER_H