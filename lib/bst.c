/**
 * Basic BST implementation.
 *
 * @author: Benjamin Northrop
 * @class: CS 5008
 * @term: SP2024
 */

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "bst.h"
#include "movie.h"

/**
 * Creates a new BSTNode with the given movie.
 *
 * @param movie the movie to store in the node
 * @return a pointer to the new node
 */
BSTNode *__bst__new_node(Movie *movie)
{
    BSTNode *node = malloc(sizeof(BSTNode));
    node->movie = movie;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;
    return node;
}

/**
 * Creates a new BST with the given movie.
 *
 * @param movie the movie to store in the node
 * @return a pointer to the new node
 */
BST *new_bst()
{
    BST *bst = malloc(sizeof(BST));
    bst->root = NULL;
    bst->size = 0;
    return bst;
}

/**
 * Frees the given node and all of its children.
 * This helps with the recursive nature of freeing a BST.
 *
 * @param node the node to free
 */
void __bst__free_node(BSTNode *node, bool clear)
{
    if (node == NULL)
    {
        return;
    }
    // STUDENT TODO: update this comment - is this, pre, post, or in order traversal?
    // Post Order traversal - goes to the left child (and subtree), then the right child (and subtree) then finally frees the node.
    __bst__free_node(node->left, clear);
    __bst__free_node(node->right, clear);
    if (clear)
    {
        free_movie(node->movie);
    }
    free(node);
}

/**
 * Frees the given BST and all of its nodes.
 *
 * @param bst the BST to free
 */
void free_bst(BST *bst)
{
    __bst__free_node(bst->root, false);
    free(bst);
}

/**
 * Frees the given BST and all of its nodes contents.
 *
 * @param bst the BST to free
 */
void clear_and_free_bst(BST *bst)
{
    __bst__free_node(bst->root, true);
    bst->root = NULL;
}

/**
 * Add helper for adding recursively to BST
 *
 * will keep calling recursively until it finds the correct spot to add the movie.
 * Makes use of __bst_new_node(movie) and compare_movies(movie, curr->movie)
 *
 * @param curr the current node
 * @param movie the movie to add
 */
void __bst__add(BSTNode *curr, Movie *movie)
{
    // STUDENT TODO: implement this function
    // Compare the movie to the root, determine if its smaller or larger
    int cmp = compare_movies(movie, curr->movie);
    // If its smaller, check if curr's left child is NULL -
    if (cmp < 0)
    {
        // If NULL, create new node and have curr left point to new node
        if (curr->left == NULL)
        {
            BSTNode *new = __bst__new_node(movie);
            curr->left = new;
        }
        //  else call __bst__add with curr's left child as new curr.
        else
        {
            __bst__add(curr->left, movie);
        }
    }
    else // Takes greater or equal to
    {
        // Else, check if curr's right child is NULL
        if (curr->right == NULL)
        {
            // If NULL, create new node and have curr right child point to new node
            BSTNode *new = __bst__new_node(movie);
            curr->right = new;
        }
        else
        // Else call __bst_add with curr's right child as new curr.
        {
            __bst__add(curr->right, movie);
        }
    }
    adjust_bst_height(curr);
}
/**
 * Adds the given movie into the BST.
 * Handles the root case, but then calls the recursive helper
 * for anything after the root.
 *
 * Increments the size of the BST once a movie is added.
 *
 * @param bst the BST to insert into
 * @param movie the movie to insert
 */
void bst_add(BST *bst, Movie *movie)
{
    // Ensures the movie isn't null
    if (movie == NULL)
    {
        return;
    }
    if (bst->root == NULL)
    {
        bst->root = __bst__new_node(movie);
        bst->size++;
        return;
    }
    BSTNode *curr = bst->root;
    __bst__add(curr, movie);
    bst->size++;
    adjust_bst_height(bst->root);
}

/**
 * Helper function that gets the height from any given BST Node
 * @param root the root node of any BST tree or subtree
 */
int __bst__getHeight(BSTNode *root)
{
    if (root == NULL)
    {
        return 0;
    }
    return root->height;
}

/**
 * Gets the height of a BST tree
 * @param bst the bst tree in question
 */
int get_bst_height(BST *bst)
{
    // If the tree is empty, height is 0;
    if (bst->root == NULL)
    {
        return 0;
    }
    // Otherwise, get the height of the root node.
    BSTNode *curr = bst->root;
    return __bst__getHeight(curr);
}

void adjust_bst_height(BSTNode *root)
{
    // Null check - early return
    if (root == NULL)
    {
        return;
    }
    // Get the heights of the two children nodes
    int height_left = __bst__getHeight(root->left);
    int height_right = __bst__getHeight(root->right);
    // Set the root height to 1 + the max of the children.
    if (height_left > height_right)
    {
        root->height = height_left + 1;
        return;
    }
    root->height = height_right + 1;
}

/**
 * Helper function for removing a node from the BST.
 *
 * @param curr the current node
 * @param movie the movie to remove
 * @return the new root/parent node
 */
BSTNode *__bst__remove(BSTNode *curr, Movie *movie)
{
    if (curr == NULL)
    {
        return NULL;
    }
    if (compare_movies(movie, curr->movie) == 0)
    {
        if (curr->left == NULL && curr->right == NULL)
        {
            free(curr);
            return NULL;
        }
        if (curr->left == NULL)
        {
            BSTNode *right = curr->right;
            free(curr);
            return right;
        }
        if (curr->right == NULL)
        {
            BSTNode *left = curr->left;
            free(curr);
            return left;
        }
        BSTNode *min = curr->right;
        while (min->left != NULL)
        {
            min = min->left;
        }
        curr->movie = min->movie;
        curr->right = __bst__remove(curr->right, min->movie);
        return curr;
    }
    else if (compare_movies(movie, curr->movie) < 0)
    {
        curr->left = __bst__remove(curr->left, movie);
    }
    else
    {
        curr->right = __bst__remove(curr->right, movie);
    }
    return curr;
}

/**
 * Removes the given movie from the BST.
 *
 * @param bst the BST to remove from
 * @param movie the movie to remove
 */
void bst_remove(BST *bst, Movie *movie)
{
    if (bst->root == NULL || movie == NULL)
    {
        return;
    }
    BSTNode *returned = __bst__remove(bst->root, movie);
    bst->root = returned; // incase the root needs updated, often will be the same.
    bst->size--;
}

/**
 * Helper function for getting a node from the BST.
 * Only returns the first movie with that title, does not look at ids.
 *
 * Makes use of strcasecmp to compare the titles. for example:
 *
   if (strcasecmp(title, curr->movie->title) == 0) {
       return curr;
   }
 *
 * @param curr the current node
 * @param title the title of the movie to get, if
 * @return the node that was found
*/
BSTNode *__bst__find(BSTNode *curr, const char *title)
{
    // STUDENT TODO: implement this function
    // Uses a pre-order depth first search to find it
    if (curr == NULL)
    {
        return NULL;
    }
    // Compare title to current node's movie.
    int cmp = strcasecmp(title, curr->movie->title);

    // If the movies match, return this current node.
    if (cmp == 0)
    {
        return curr;
    }

    // If the title comes before the movie, then determine which side of the BST to continue searching
    if (cmp < 0)
    {
        return __bst__find(curr->left, title);
    }
    return __bst__find(curr->right, title); // Implied else cmp > 0.
}

/**
 * Finds the given movie from the BST.
 *
 * Only returns the first movie with that title, does not look at ids.
 *
 * @param bst the BST to get from
 * @param title the title of the movie to get
 * @return the movie that was found
 */
Movie *bst_find(BST *bst, const char *title)
{
    BSTNode *node = __bst__find(bst->root, title);
    if (node == NULL)
    {
        return NULL;
    }
    return node->movie;
}

/**
 * Helper function that updates the given string with the given movie.
 *
 * This function should be called in based on the order of traversal,
 *
 * for example with inorder it may be
 * inorder(...) (with dots being the parameters)
 * __bst__update_str(curr->movie, str);
 * inorder(...)
 *
 * @param movie the movie to add to the string
 * @param str the string to append to
 */
char *__bst__update_str(Movie *movie, char *str)
{
    char *movie_str;
    if (movie == NULL)
    {
        movie_str = (char *)"NULL"; // used by BREATH_FIRST to print null nodes, others ignore this.
    }
    else
    {
        movie_str = movie_to_str(movie);
    }
    str = realloc(str, sizeof(char) * (strlen(str) + strlen(movie_str) + 5));
    if (strlen(str) > 0)
    {
        strcat(str, ", ");
    }
    strcat(str, movie_str);
    if (movie != NULL)
    {
        free(movie_str); // since "NULL" is on the stack, we don't need to free directly
    }
    return str;
}

/**
 * Post order traversal helper function for converting a BST to a string.
 * Similar to printing from the team activity, but instead of printf, you will be calling __bst__update_str
 *
 * if (curr == NULL)  - just return the str, don't add NULL to the string
 *
 * @param curr the current node
 * @param str the string to append to
 * @return the string that was appended to
 */
char *__bst__to_str_postorder(BSTNode *curr, char *str)
{
    // if root is null then exit immediately
    if (curr == NULL)
    {
        return str;
    }
    // go to the left node
    str = __bst__to_str_postorder(curr->left, str); // recursively print the left subtree

    // go to the right node
    str = __bst__to_str_postorder(curr->right, str); // recursively print the right subtree

    // print root node
    str = __bst__update_str(curr->movie, str);

    return str;
}

/**
 * Pre order traversal helper function for converting a BST to a string.
 * Similar to printing from the team activity, but instead of printf, you will be calling __bst__update_str
 *
 * if (curr == NULL)  - just return the str, don't add NULL to the string
 *
 * @param curr the current node
 * @param str the string to append to
 * @return the string that was appended to
 *
 */
char *__bst__to_str_preorder(BSTNode *curr, char *str)
{
    // if root is null then exit immediately
    if (curr == NULL)
    {
        return str;
    }
    // print root node
    str = __bst__update_str(curr->movie, str);

    // check if left is not null
    str = __bst__to_str_preorder(curr->left, str); // recursively print the left subtree

    // check if right child is not null
    str = __bst__to_str_preorder(curr->right, str); // recursively print the right subtree

    // STUDENT TODO: implement this function
    return str;
}

/**
 * In order traversal helper function for converting a BST to a string.
 *
 * Similar to printing from the team activity, but instead of printf, you will be calling __bst__update_str
 *
 * if (curr == NULL)  - just return the str, don't add NULL to the string
 *
 * @param curr the current node
 * @param str the string to append to
 * @return the string that was appended to
 */
char *__bst__to_str_inorder(BSTNode *curr, char *str)
{
    // if root is null then exit immediately
    if (curr == NULL)
    {
        return str;
    }
    // check if left is not null
    str = __bst__to_str_inorder(curr->left, str); // recursively print the left subtree

    // print root node
    str = __bst__update_str(curr->movie, str);
    // check if right child is not null
    str = __bst__to_str_inorder(curr->right, str); // recursively print the right subtree

    // STUDENT TODO: implement this function
    return str;
}

/**
 * Helper function for converting a BST to a string using breadth first traversal.
 *
 * Unlike post/pre/in order traversal, this is not recursive. It also does print NULL
 * nodes, as we want to print the structure of the tree to help us with debugging.
 *
 * @param tree the BST to convert
 * @param str the string to append to
 * @return the string that was appended to
 */
char *__bst__to_str_breadth_first(BST *tree, char *str)
{
    if (tree->root == NULL)
    {
        return str;
    }
    BSTNode **queue = malloc(sizeof(BSTNode) * tree->size + 1);
    queue[0] = tree->root;
    int front = 0;
    int back = 1;
    while (front < back)
    {
        BSTNode *node = queue[front++];
        if (node == NULL)
        { // as we still want to print the null nodes
            str = __bst__update_str(NULL, str);
            continue;
        }
        str = __bst__update_str(node->movie, str);
        queue[back++] = node->left;
        queue[back++] = node->right;
    }
    free(queue);
    return str;
}

/**
 * Converts the given BST to a string using the given traversal method.
 *
 * @param tree the BST to convert
 * @param traversal the traversal method to use
 * @return the string that was appended to
 */
char *bst_to_str(BST *tree, int traversal)
{
    char *str = malloc(sizeof(char));
    str[0] = '\0';
    switch (traversal)
    {
    case PRE_ORDER:
        return __bst__to_str_preorder(tree->root, str);
    case IN_ORDER:
        return __bst__to_str_inorder(tree->root, str);
    case POST_ORDER:
        return __bst__to_str_postorder(tree->root, str);
    case BREADTH_FIRST:
        return __bst__to_str_breadth_first(tree, str);
    default:
        return str;
    }
}

/**
 * Helper function for converting a BST to a sorted array.
 *
 * a major question is what type of traversal do you need to
 * take a tree and sort it from smallest to largest?
 *
 * Once you figure out the type of traversal, you can update the
 * array and index parameters to help store the movie. For example
 *
 * array[*index] = curr->movie;
 * (*index)++;
 *
 * It is good to draw this out with some simple trees (and actually very similar
 * to a common leetcode questions)
 *
 * @param curr the current node
 * @param array the array to store the movies in, you can safely assume it is the correct size
 * @param index the current index in the array, used as a pointer to be updated across all recursive calls
 *
 */
void __bst__to_sorted_array(BSTNode *curr, Movie **array, int *index)
{
    if (curr == NULL)
    {
        return;
    }

    // Insert the left node.
    __bst__to_sorted_array(curr->left, array, index);

    // Insert the root.
    array[*index] = curr->movie;
    (*index)++;

    // Insert the right node
    __bst__to_sorted_array(curr->right, array, index);
}

/**
 * Converts the given BST to a sorted array.
 *
 * @param tree the BST to convert
 * @return the array that was created
 */
Movie **bst_to_sorted_array(BST *tree)
{
    Movie **array = malloc(sizeof(Movie *) * tree->size);
    int index = 0;
    __bst__to_sorted_array(tree->root, array, &index);
    return array;
}
