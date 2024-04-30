/**
 * A AVL tree implementation designed
 * to hold Movie structs.
 *
 * @author: Benjamin Northrop
 * @class: CS 5008
 * @term: SP2024
 */

#ifndef AVL_H
#define AVL_H

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "movie.h"

#define POST_ORDER 0
#define IN_ORDER 1
#define PRE_ORDER 2
#define BREADTH_FIRST 3

typedef struct avl_node
{
    Movie *movie;
    struct avl_node *left;
    struct avl_node *right;
    int height;
} AVLNode;

typedef struct avl
{
    AVLNode *root;
    int size;
    int rotations;
} AVL;

AVL *new_avl();
void free_avl(AVL *avl);
void clear_and_free_avl(AVL *avl);
void avl_add(AVL *avl, Movie *movie);
void avl_remove(AVL *avl, Movie *movie);
AVLNode *rotate_left(AVLNode *node, int *rotations);
AVLNode *rotate_right(AVLNode *node, int *rotations);
Movie *avl_find(AVL *avl, const char *title);
char *avl_to_str(AVL *avl, int ordering);
int getHeight(AVL *avl);
void adjustHeight(AVLNode *node);
int getBalance(AVLNode *node);
AVLNode *rebalance_tree(AVLNode *node, int *rotations);

Movie **avl_to_sorted_array(AVL *avl);

#endif // AVL_H