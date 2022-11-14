#include "btree.h"

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

struct tree_node *Insert(int x, struct tree_node *t) {
  // Insert item x into the tree t
  //allocates memory to the nodes, to be able to slot in data/values
  if (t == NULL)
  {
    t = malloc(sizeof(struct tree_node));
    t->item = x;
    t->left = NULL;
    t->right = NULL;
  }
  else if (t->item <= x)
  {
    t->right = Insert(x, t->right);
  }
  else if(t->item > x)
  {
    t->left = Insert(x, t->left);
  }
}

bool is_leaf(struct tree_node* n) {
  return n->left == NULL && n->right == NULL;
}

struct tree_node *Remove(int x, struct tree_node *t) {
  // Remove one item from the tree t
  //If t is NULL it means that there isnt any values on the tree, so the tree doesnt exist
  if (t == NULL)
  {
    return NULL;
  }

  if (t->item == x)
  {
    //if the node doesnt have any children, we simply remove it
    if (t->right == NULL && t->left == NULL)
    {
      free(t);
      return NULL;
    }
    //if the node has a right child we replace the node with the right child memory
    else if (t->left == NULL && t->right != NULL)
    {
      struct tree_node* tmp = t->right;
      free(t);
      return tmp;
    }
    //if the node has a left childe we replace the node with the left child and free the memory
    else if(t->left != NULL && t->right == NULL)
    {
      struct tree_node *tmp = t->left;
      free(t);
      return tmp;
    }
    else 
    {
      //Find smallest element of subtree of T
      struct tree_node* tmp = t->right;
      while (tmp->left != NULL)
      {
        tmp = tmp->left;
      }
      // now tmp is the smallest element in t->right
      if (is_leaf(tmp))
      {
        // swap values and then free
        t->item = tmp->item;
        free(tmp);
        return t;
      }
    
        // tmp has a right child
        tmp = t->right->item;
        free (t);
        return tmp;
    }
  }
}

int Contains(int x, struct tree_node *t) {

  // Return true if the tree t contains item x. Return false otherwise.
  if (Empty(t)) 
    return 0;
  else if (x == t->item)
    return 1;
  else if (x != t->item && x >= t->item)
    return Contains(x, t->right);
  else if (x != t->item && x < t->item)
    return (Contains(x, t->left));
  else
    return 0;
}

struct tree_node *Initialize(struct tree_node *t) {
  // Create an empty tree
  t = NULL;
  return t;
}

int Empty(struct tree_node *t) {
  // Test if empty
  if (t->item == NULL)
  return 1;
  else
  return 0;
}

int Full(struct tree_node *t) {
  // Test if full
  return 0;
}
