
#include "movie.h"

/**
 * Creates a new movie struct
 *
 * @param title the title of the movie
 * @return a pointer to the new movie struct
 */
Movie *new_movie(const char *title, int id)
{
    Movie *newMovie = (Movie *)malloc(sizeof(Movie));
    newMovie->title = strcpy((char *)malloc(strlen(title) + 1), title); // to keep the titles unique
    newMovie->id = id;
    return newMovie;
}

/**
 * Frees the memory allocated for a movie struct
 *
 * @param movie the movie struct to free
 */
void free_movie(Movie *movie)
{
    free((char *)movie->title);
    free(movie);
}

/**
 * Compares two movie structs based on movie title
 *
 * @param movie1 the first movie to compare
 * @param movie2 the second movie to compare
 * @return -1 if the movie1 comes before movie2, 0 if they are equal, 1 if movie1 comes after movie2
 */
int compare_movies(Movie *movie1, Movie *movie2)
{
    int titles_cmp = strcasecmp(movie1->title, movie2->title);
    if (titles_cmp == 0)
    {
        int id_cmp = movie1->id - movie2->id;
        if (id_cmp < 0)
        {
            return -1;
        }
        else if (id_cmp > 0)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
    return titles_cmp;
}

/**
 * returns a string value representing the movie
 *
 * @param movie the movie to convert to a string
 * @return a string representation of the movie
 */
char *movie_to_str(Movie *movie)
{
    char *str = (char *)malloc(MAX_MOVIE_STR_LEN);
    sprintf(str, "{title: %s, id: %d}", movie->title, movie->id);
    return str;
}