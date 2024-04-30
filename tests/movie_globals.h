/**
 * Contains some constant values to help with testing
 *
 * Written for CS 5008 @ Northeastern University
 *
 * @author Albert Lionelle
 */

#ifndef MOVIE_HELPERS_H
#define MOVIE_HELPERS_H

#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../lib/movie.h"

Movie *movie1;
Movie *movie2;
Movie *movie3;
Movie *movie4;
Movie *movie5;
Movie *movie6;

/**
 * Initializes the movies for testing.
 */
void init_movies()
{
    movie1 = new_movie("A Movie One", 1);
    movie2 = new_movie("B Movie Two", 2);
    movie3 = new_movie("C Movie Three", 3);
    movie4 = new_movie("D Movie Four", 4);
    movie5 = new_movie("E Movie Five", 5);
    movie6 = new_movie("F Movie Six", 6);
}

/**
 * Frees the movies for testing.
 */
void free_movies()
{
    free_movie(movie1);
    free_movie(movie2);
    free_movie(movie3);
    free_movie(movie4);
    free_movie(movie5);
    free_movie(movie6);
}

#endif // MOVIE_HELPERS_H