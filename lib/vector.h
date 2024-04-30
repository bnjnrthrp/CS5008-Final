/**
 * A simple ArrayList/Vector implementation. Vector is more commonly
 * used for C, ArrayList for java, as they distinguish between 
 * Vector and ArrayList for synchronization purposes.
 * 
 * Both are the idea of a dynamically resizing array.
 * 
 * For this implementation, we will use the name Vector as it is more
 * commonly used in C. 
 * 
*/

#ifndef VECTOR_H
#define VECTOR_H

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "movie.h"


#define INITIAL_CAPACITY 100
#define RESIZE_FACTOR 2

typedef struct Vector {
    Movie ** movies;  
    int size;
    int capacity;
} MovieVector;


MovieVector * new_vector();
void free_vector(MovieVector * vector);
void clear_and_free_vector(MovieVector * vector);
void vector_insert(MovieVector *vector, Movie *movie, int index);
void vector_add_back(MovieVector * vector, Movie * movie); 
void vector_add_front(MovieVector * vector, Movie * movie);
Movie * vector_remove(MovieVector * vector, int index);
Movie * vector_remove_back(MovieVector *vector);
Movie * vector_remove_front(MovieVector * vector);
Movie * vector_get(MovieVector * vector, int index);
bool vector_is_empty(MovieVector * vector);
char* vector_to_str(MovieVector * vector);


/** Sorted Vector Functions*/
typedef MovieVector SortedMovieVector; // really doesn't need a change, or a layer of protection

// helper defines, just so the code is more clear, but really since 
// structure, the other functions work fine
#define new_sorted_vector new_vector
#define free_sorted_vector free_vector

void add_to_sorted_vector(SortedMovieVector * vector, Movie * movie);
Movie * find_in_sorted_vector(SortedMovieVector * vector, const char * title);
Movie * sorted_vector_remove(SortedMovieVector * vector, const char * title);





#endif // VECTOR_H