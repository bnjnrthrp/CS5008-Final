/**
 * Implementation of MovieVector (vector.h)
 *
 * All functions are provided, but read through the code, make sure you
 * understand and answer questions in the comments.
 */

#include "vector.h"

/**
 * Creates a new MovieVector.
 *
 * @return a pointer to the new MovieVector
 */
MovieVector *new_vector()
{
    MovieVector *vector = (MovieVector *)malloc(sizeof(MovieVector));
    vector->movies = (Movie **)malloc(sizeof(Movie *) * INITIAL_CAPACITY);
    vector->capacity = INITIAL_CAPACITY;
    vector->size = 0;
    return vector;
}

/**
 * Frees the memory associated with a MovieVector.
 * This does not free the movie structs, just the vector itself.
 *
 * @param vector the MovieVector to free
 */
void free_vector(MovieVector *vector)
{
    free(vector->movies);
    free(vector);
}

/**
 * Frees the memory associated with a MovieVector, including the movies.
 *
 * @param vector the MovieVector to free
 */
void clear_and_free_vector(MovieVector *vector)
{
    for (int i = 0; i < vector->size; i++)
    {
        free_movie(vector->movies[i]);
    }
    free(vector->movies);
    free(vector);
}

/**
 * Doubles the size of the vector for reallocation.
 *
 * Using __ to indicate this is a private function, and should not be
 * used outside of this file.
 * It is simply a hint, not a requirement, as C doesn't have the notation of
 * public and private functions.
 * @param vector the vector to double
 */
void __double_vector(MovieVector *vector)
{
    vector->capacity *= RESIZE_FACTOR; // STUDENT: Think about this resize factor, you will have to answer a question about it in your report
    vector->movies = (Movie **)realloc(vector->movies, sizeof(Movie *) * vector->capacity);
    // realloc copies the data from the old array to the new array, read more here
    // https: // www.gnu.org/software/libc/manual/html_node/Changing-Block-Size.html
}

/**
 * Shift the contents from the given index to the end of the vector to the right.
 * Used for inserts and adds to the front
 * @param vector the vector to shift
 * @param index the index to start shifting from
 */
void __shift_right(MovieVector *vector, int index)
{
    for (int i = vector->size; i > index; i--)
    { // STUDENT: What is the BigO of this operation? O(n)
        vector->movies[i] = vector->movies[i - 1];
    }
}

/**
 * Shift the contents from the given index to the end of the vector to the left.
 * Used for deletes and removes from the front
 * @param vector the vector to shift
 * @param index the index to start shifting from
 */
void __shift_left(MovieVector *vector, int index)
{
    for (int i = index; i < vector->size - 1; i++)
    {
        vector->movies[i] = vector->movies[i + 1];
    }
}

/**
 * Inserts a movie into a MovieVector at a given index.
 *
 * May add at the end by passing in the size of the vector.
 *
 * Does nothing if the index is out of bounds.
 *
 * @param vector the MovieVector to insert into
 * @param movie the movie to insert
 * @param n the index to insert at
 *
 */
void vector_insert(MovieVector *vector, Movie *movie, int n)
{
    if (n < 0 || n > vector->size)
    {
        return;
    }
    if (vector->size == vector->capacity)
    {
        __double_vector(vector);
    }
    __shift_right(vector, n);
    vector->movies[n] = movie;
    vector->size++;
}

/**
 * Adds a movie to the back of a MovieVector.
 *
 * @param vector the MovieVector to add to
 * @param movie the movie to add
 */
void vector_add_back(MovieVector *vector, Movie *movie)
{
    vector_insert(vector, movie, vector->size);
}

/***
 * Adds to the front of a vector (often called push)
 *
 * @param vector the vector to add to
 * @param movie the movie to add
 */
void vector_add_front(MovieVector *vector, Movie *movie)
{
    vector_insert(vector, movie, 0); // STUDENT: when inserting at the front, what helper function is *always* called in addition to vector_insert?
}

/**
 * Remove an element from from the vector at the given index.
 *
 * @param vector the vector to remove from
 * @param n the index to remove from
 * @return the movie removed
 */
Movie *vector_remove(MovieVector *vector, int n)
{
    if (n < 0 || n >= vector->size)
    {
        return NULL;
    }
    Movie *movie = vector->movies[n];
    __shift_left(vector, n);
    vector->size--;
    return movie;
}

/**
 * Remove the first element from the vector.
 *
 * @param vector the vector to remove from
 * @return the movie removed
 */
Movie *vector_remove_front(MovieVector *vector)
{
    return vector_remove(vector, 0);
}

/**
 * Remove the last element from the vector.
 *
 * @param vector the vector to remove from
 * @return the movie removed
 */
Movie *vector_remove_back(MovieVector *vector)
{
    return vector_remove(vector, vector->size - 1);
}

/**
 * Gets the movie at the given index.
 *
 * @param vector the vector to get from
 * @param n the index to get
 * @return the movie at the given index
 */
Movie *vector_get(MovieVector *vector, int n)
{
    if (n < 0 || n >= vector->size)
    {
        return NULL;
    }
    return vector->movies[n];
}

/**
 * Checks if the vector is empty.
 *
 * @param vector the vector to check
 * @return true if the vector is empty, false otherwise
 */
bool vector_is_empty(MovieVector *vector)
{
    return vector->size == 0;
}

/**
 * Converts the vector to a string representation.
 *
 * @param vector the vector to convert
 * @return the string representation
 */
char *vector_to_str(MovieVector *vector)
{
    char *str = (char *)malloc(sizeof(char) * (MAX_MOVIE_STR_LEN + 3) * vector->size);
    if (vector->size == 0)
    {
        strcpy(str, "[]");
        return str; // early exit
    }
    // implied else
    strcpy(str, "[");
    for (int i = 0; i < vector->size; i++)
    {
        char *movie_str = movie_to_str(vector->movies[i]);
        strcat(str, movie_str);
        if (i != vector->size - 1)
        {
            strcat(str, ", ");
        }
        free(movie_str);
    }
    strcat(str, "]");
    return str;
}