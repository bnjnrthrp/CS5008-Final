/**
 * Basic AVL tree implementation.
 *
 * @author: Benjamin Northrop
 * @class: CS 5008
 * @term: SP2024
 */

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "avl.h"
#include "movie.h"

/**
 * Creates a new AVLNode with the given movie.
 *
 * @param movie the movie to store in the node
 * @return a pointer to the new node
 */
AVLNode *__avl__new_node(Movie *movie)
{
    AVLNode *node = malloc(sizeof(AVLNode));
    node->movie = movie;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;
    return node;
}

/**
 * Creates a new AVL with the given movie.
 *
 * @param movie the movie to store in the node
 * @return a pointer to the new node
 */
AVL *new_avl()
{
    AVL *avl = malloc(sizeof(AVL));
    avl->root = NULL;
    avl->size = 0;
    avl->rotations = 0;
    return avl;
}

/**
 * Frees the given node and all of its children.
 * This helps with the recursive nature of freeing a AVL.
 *
 * @param node the node to free
 */
void __avl__free_node(AVLNode *node, bool clear)
{
    // if the node is already null, early return
    if (node == NULL)
    {
        return;
    }
    // Otherwise, return the two children
    __avl__free_node(node->left, clear);
    __avl__free_node(node->right, clear);
    if (clear)
    {
        free_movie(node->movie);
    }
    free(node);
}

/**
 * Frees the given AVL and all of its nodes.
 *
 * @param avl the AVL to free
 */
void free_avl(AVL *avl)
{
    __avl__free_node(avl->root, false);
    free(avl);
}

/**
 * Frees the given AVL and all of its nodes contents.
 *
 * @param avl the AVL to free
 */
void clear_and_free_avl(AVL *avl)
{
    __avl__free_node(avl->root, true);
    avl->root = NULL;
}

/**
 * Add helper for adding recursively to AVL
 *
 * will keep calling recursively until it finds the correct spot to add the movie.
 * Makes use of __avl_new_node(movie) and compare_movies(movie, curr->movie)
 *
 * @param curr the current node
 * @param movie the movie to add
 */
AVLNode *__avl__add(AVLNode *curr, Movie *movie, int *size, int *rotations)
{
    // If curr is NULL, make a new node
    if (curr == NULL)
    {
        // printf("Creating new node in null position\n");
        // Increase size of avl
        (*size)++;
        return __avl__new_node(movie);
    }
    // Compare the movie to the root, determine if its smaller or larger
    int cmp = compare_movies(movie, curr->movie);

    // If its smaller, check if curr's left child is NULL -
    // If it's the same movie, return the same node.
    if (cmp == 0)
    {
        // printf("Movie matched, returning current node\n");
        return curr;
    }
    else if (cmp < 0)
    {
        // If less than the root, insert on the left side
        // printf("Movie is before, so adding left side\n");
        curr->left = __avl__add(curr->left, movie, size, rotations);
        // printf("Attempting to rebalance the left side\n");
    }
    else if (cmp > 0) // else check if it goes to the right side
    {
        // printf("Movie is after, so adding right side\n");
        curr->right = __avl__add(curr->right, movie, size, rotations);
        // printf("Attempting to rebalance the right side\n");
    }
    curr = rebalance_tree(curr, rotations);
    return curr;
}
/**
 * Adds the given movie into the AVL.
 * Handles the root case, but then calls the recursive helper
 * for anything after the root.
 *
 * Increments the size of the AVL once a movie is added.
 *
 * @param avl the AVL to insert into
 * @param movie the movie to insert
 */
void avl_add(AVL *avl, Movie *movie)
{
    // Ensures the movie isn't null
    if (movie == NULL)
    {
        return;
    }
    // printf("Going into the root to add a movie\n");
    avl->root = __avl__add(avl->root, movie, &avl->size, &avl->rotations);
}

/**
 * Performs a left rotation at the current node, shifting it so the root becomes the left child,
 * the right child is the root, and the right child's right child moves up one.
 * @param avl_node the original root node
 */
AVLNode *rotate_left(AVLNode *root, int *rotations)
{
    // Temp hold right child (new root)
    AVLNode *newRoot = root->right;
    // Set the original root->right->left to be the future root->left->right
    root->right = root->right->left;
    // Make the new root's left child the original root.
    newRoot->left = root;
    // Correct the heights of the original root and temp
    adjustHeight(root);
    adjustHeight(newRoot);
    (*rotations)++;
    // Add to rotation counter
    // Change the root pointer to point to the temp.
    return newRoot;
}

/**
 * Performs a left rotation at the current node, shifting it so the root becomes the left child,
 * the right child is the root, and the right child's right child moves up one.
 * @param avl_node the original root node
 */
AVLNode *rotate_right(AVLNode *root, int *rotations)
{
    // Temp hold the left child (new root)
    AVLNode *newRoot = root->left;
    // Set the original root->left->right to be the future root->right->left
    root->left = root->left->right;
    // Make the new root's right child the original root
    newRoot->right = root;
    // Correct the heights of the original root and temp
    adjustHeight(root);
    adjustHeight(newRoot);
    (*rotations)++; // Add to rotation counter
    // Change the root pointer to point to the temp
    return newRoot;
}

/**
 * Helper function that gets the height from any given AVL Node
 * @param root the root node of any AVL tree or subtree
 */
int __avl__getHeight(AVLNode *root)
{
    if (root == NULL)
    {
        return 0;
    }
    return root->height;
}

/**
 * Gets the height of a avl tree
 * @param avl the avl tree in question
 */
int getHeight(AVL *avl)
{
    // If the tree is empty, height is 0;
    if (avl->root == NULL)
    {
        return 0;
    }
    // Otherwise, get the height of the root node.
    AVLNode *curr = avl->root;
    return __avl__getHeight(curr);
}

void adjustHeight(AVLNode *root)
{
    // Null check - early return
    if (root == NULL)
    {
        return;
    }
    // Get the heights of the two children nodes
    int height_left = __avl__getHeight(root->left);
    int height_right = __avl__getHeight(root->right);
    // Set the root height to 1 + the max of the children.
    if (height_left > height_right)
    {
        root->height = height_left + 1;
        return;
    }
    root->height = height_right + 1;
}

int getBalance(AVLNode *node)
{
    if (node == NULL)
    {
        return 0;
    }
    return __avl__getHeight(node->left) - __avl__getHeight(node->right);
}

/**
 * Rebalances a subtree by looking if the right or left side is unbalance via the height variant. Rotates accordingly.
 * @param root the root of the subtree to balance
 */
AVLNode *rebalance_tree(AVLNode *root, int *rotations)
{
    // Determine if rebalance is required. Positive means heavier on the left, negative means heavier on the right.
    // printf("Getting balance\n");
    int balance = getBalance(root);
    // If unbalanced to the left
    if (balance > 1)
    {
        // Determine if we need to do a single or double rotation. If left is higher than the right, then single rotation.
        // From the left child, if ITS  left is higher than the right, rotate to the right
        // printf("Balance is >1\n");
        int subTreeBalance = getBalance(root->left);
        if (subTreeBalance > 0)
        {
            root = rotate_right(root, rotations);
        }
        else
        {
            // Otherwise, the tree is zig-zagging, so we rotate left first to put it all on the left side
            // Then double rotate
            root->left = rotate_left(root->left, rotations);
            root = rotate_right(root, rotations);
        }
    }
    else if (balance < -1)
    {
        // printf("Balance is -1\n");
        // Determine if we need to do a single or double rotation. If right is higher than the left, then single rotation.
        // From the right child, if ITS right is higher than the left, rotate to the left
        int subTreeBalance = getBalance(root->right);
        // printf("subtree balance is %d\n", subTreeBalance);
        if (subTreeBalance < 0)
        {
            // printf("trying to rotate left\n");
            root = rotate_left(root, rotations);
        }
        else
        {
            // Otherwise, the tree is zig-zagging, so we rotate left first to put it all on the left side
            // Then double rotate
            root->right = rotate_right(root->right, rotations);
            root = rotate_left(root, rotations);
        }
    }
    else
    {
        // else no rotation required, check/adjust height
        adjustHeight(root);
    }
    return root;
}

/**
 * Helper function for removing a node from the AVL.
 *
 * @param curr the current node
 * @param movie the movie to remove
 * @return the new root/parent node
 */
AVLNode *__avl__remove(AVLNode *curr, Movie *movie, int *size, int *rotations)
{

    // If the provided node is null, abort and early return.
    if (curr == NULL)
    {
        // printf("Current node is null\n");
        return NULL;
    }
    // If the node is found
    if (compare_movies(movie, curr->movie) == 0)
    {
        // printf("Match was found\n");
        // If there is one or zero children
        if (curr->left == NULL || curr->right == NULL)
        {
            // Check for left child, otherwise assume there's a right child
            AVLNode *tmp;
            if (curr->left != NULL)
            {
                tmp = curr->left;
            }
            else
            {
                tmp = curr->right;
            }
            // Check if tmp is null, signifying zero children
            if (tmp == NULL)
            {
                // printf("There were no children\n");
                // Set tmp to be the current node and nullify current
                tmp = curr;
                curr = NULL;
                free(curr);
            }
            else
            {
                // Otherwise, set curr to be the tmp child
                *curr = *tmp;
            }
            // Free the tmp (old curr)
            // printf("Freeing the temp\n");
            free(tmp);
        }
        else // We have 2 children.
        {
            // printf("Node has two children\n");
            // Otherwise, set the minimum in order starting from the right subtree
            AVLNode *min = curr->right;
            // Travel down the left side of the right subtree until getting to a leaf (minimum inorder)
            while (min->left != NULL)
            {
                min = min->left;
            }
            // printf("Replacing the deleted node\n");
            // Move the data from this leaf into the current node
            curr->movie = min->movie;
            // Go down to the leaf with the original movie and remove it.
            curr->right = __avl__remove(curr->right, min->movie, size, rotations);
        }
    }
    // If the movie is less than current, go down the left subtree
    else if (compare_movies(movie, curr->movie) < 0)
    {
        // printf("Not a match, go left side\n");
        curr->left = __avl__remove(curr->left, movie, size, rotations);
    }
    // Else go down the right subtree to continue the search.
    else
    {
        // printf("Not a match, go right side\n");
        curr->right = __avl__remove(curr->right, movie, size, rotations);
    }

    // Otherwise, rebalance the tree
    curr = rebalance_tree(curr, rotations);
    // If the current node is still null, it was the only node in the tree, so return.
    if (curr == NULL)
    {
        return NULL;
    }
    (*size)--;
    // Return the now balanced subtree
    return curr;
}

/**
 * Removes the given movie from the AVL.
 *
 * @param avl the AVL to remove from
 * @param movie the movie to remove
 */
void avl_remove(AVL *avl, Movie *movie)
{
    if (avl->root == NULL || movie == NULL)
    {
        return;
    }
    AVLNode *returned = __avl__remove(avl->root, movie, &avl->size, &avl->rotations);
    if (returned == NULL)
    {
        avl->size--;
    }
    avl->root = returned; // incase the root needs updated, often will be the same.
}

/**
 * Helper function for getting a node from the AVL.
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
AVLNode *__avl__find(AVLNode *curr, const char *title)
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

    // If the title comes before the movie, then determine which side of the AVL to continue searching
    if (cmp < 0)
    {
        return __avl__find(curr->left, title);
    }
    return __avl__find(curr->right, title); // Implied else cmp > 0.
}

/**
 * Finds the given movie from the AVL.
 *
 * Only returns the first movie with that title, does not look at ids.
 *
 * @param avl the AVL to get from
 * @param title the title of the movie to get
 * @return the movie that was found
 */
Movie *avl_find(AVL *avl, const char *title)
{
    AVLNode *node = __avl__find(avl->root, title);
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
 * __avl__update_str(curr->movie, str);
 * inorder(...)
 *
 * @param movie the movie to add to the string
 * @param str the string to append to
 */
char *__avl__update_str(Movie *movie, char *str)
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
    if (str == NULL)
    {
        free(str);
        // printf("Realloc failed\n");
        exit(1);
    }
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
 * Post order traversal helper function for converting a AVL to a string.
 * Similar to printing from the team activity, but instead of printf, you will be calling __avl__update_str
 *
 * if (curr == NULL)  - just return the str, don't add NULL to the string
 *
 * @param curr the current node
 * @param str the string to append to
 * @return the string that was appended to
 */
char *__avl__to_str_postorder(AVLNode *curr, char *str)
{
    // if root is null then exit immediately
    if (curr == NULL)
    {
        return str;
    }
    // go to the left node
    str = __avl__to_str_postorder(curr->left, str); // recursively print the left subtree

    // go to the right node
    str = __avl__to_str_postorder(curr->right, str); // recursively print the right subtree

    // print root node
    str = __avl__update_str(curr->movie, str);

    return str;
}

/**
 * Pre order traversal helper function for converting a AVL to a string.
 * Similar to printing from the team activity, but instead of printf, you will be calling __avl__update_str
 *
 * if (curr == NULL)  - just return the str, don't add NULL to the string
 *
 * @param curr the current node
 * @param str the string to append to
 * @return the string that was appended to
 *
 */
char *__avl__to_str_preorder(AVLNode *curr, char *str)
{
    // if root is null then exit immediately
    if (curr == NULL)
    {
        return str;
    }
    // print root node
    str = __avl__update_str(curr->movie, str);

    // check if left is not null
    str = __avl__to_str_preorder(curr->left, str); // recursively print the left subtree

    // check if right child is not null
    str = __avl__to_str_preorder(curr->right, str); // recursively print the right subtree

    // STUDENT TODO: implement this function
    return str;
}

/**
 * In order traversal helper function for converting a AVL to a string.
 *
 * Similar to printing from the team activity, but instead of printf, you will be calling __avl__update_str
 *
 * if (curr == NULL)  - just return the str, don't add NULL to the string
 *
 * @param curr the current node
 * @param str the string to append to
 * @return the string that was appended to
 */
char *__avl__to_str_inorder(AVLNode *curr, char *str)
{
    // if root is null then exit immediately
    if (curr == NULL)
    {
        return str;
    }
    // check if left is not null
    str = __avl__to_str_inorder(curr->left, str); // recursively print the left subtree

    // print root node
    str = __avl__update_str(curr->movie, str);
    // check if right child is not null
    str = __avl__to_str_inorder(curr->right, str); // recursively print the right subtree

    // STUDENT TODO: implement this function
    return str;
}

/**
 * Helper function for converting a AVL to a string using breadth first traversal.
 *
 * Unlike post/pre/in order traversal, this is not recursive. It also does print NULL
 * nodes, as we want to print the structure of the tree to help us with debugging.
 *
 * @param tree the AVL to convert
 * @param str the string to append to
 * @return the string that was appended to
 */
char *__avl__to_str_breadth_first(AVL *tree, char *str)
{
    if (tree->root == NULL)
    {
        return str;
    }
    AVLNode **queue = malloc(sizeof(AVLNode) * tree->size + 1);
    queue[0] = tree->root;
    int front = 0;
    int back = 1;
    while (front < back)
    {
        AVLNode *node = queue[front++];
        if (node == NULL)
        { // as we still want to print the null nodes
            str = __avl__update_str(NULL, str);
            continue;
        }
        str = __avl__update_str(node->movie, str);
        queue[back++] = node->left;
        queue[back++] = node->right;
    }
    free(queue);
    return str;
}

/**
 * Converts the given AVL to a string using the given traversal method.
 *
 * @param tree the AVL to convert
 * @param traversal the traversal method to use
 * @return the string that was appended to
 */
char *avl_to_str(AVL *tree, int traversal)
{
    char *str = malloc(sizeof(char));
    str[0] = '\0';
    switch (traversal)
    {
    case PRE_ORDER:
        return __avl__to_str_preorder(tree->root, str);
    case IN_ORDER:
        return __avl__to_str_inorder(tree->root, str);
    case POST_ORDER:
        return __avl__to_str_postorder(tree->root, str);
    case BREADTH_FIRST:
        return __avl__to_str_breadth_first(tree, str);
    default:
        return str;
    }
}

/**
 * Helper function for converting a AVL to a sorted array.
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
void __avl__to_sorted_array(AVLNode *curr, Movie **array, int *index)
{
    if (curr == NULL)
    {
        return;
    }

    // Insert the left node.
    __avl__to_sorted_array(curr->left, array, index);

    // Insert the root.
    array[*index] = curr->movie;
    (*index)++;

    // Insert the right node
    __avl__to_sorted_array(curr->right, array, index);
}

/**
 * Converts the given AVL to a sorted array.
 *
 * @param tree the AVL to convert
 * @return the array that was created
 */
Movie **avl_to_sorted_array(AVL *tree)
{
    Movie **array = malloc(sizeof(Movie *) * tree->size);
    int index = 0;
    __avl__to_sorted_array(tree->root, array, &index);
    return array;
}
