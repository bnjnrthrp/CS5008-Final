/** 
 * Contains simple functions for the movie struct
*/


#ifndef MOVIE_H
#define MOVIE_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define MAX_TITLE_LENGTH 100
#define MAX_MOVIE_STR_LEN 120

typedef struct movie
{
    const char *title;
    int id;
} Movie;

Movie *new_movie(const char *title, int id);
void free_movie(Movie *movie);
int compare_movies(Movie *movie1, Movie *movie2);
char *movie_to_str(Movie *movie);


#endif