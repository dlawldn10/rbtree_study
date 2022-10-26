#include "rbtree.h"

#include <stdlib.h>
#include <stdio.h>

rbtree *new_rbtree(void) {
  rbtree *p = (rbtree *)calloc(1, sizeof(rbtree));
  node_t *NIL = (node_t *)calloc(1, sizeof(node_t));
  NIL->color = RBTREE_BLACK;
  p->nil = NIL;
  p->root = NIL;
  return p;
}

void right_rotate(rbtree *tree, node_t *pivot){
  node_t *tmp = pivot->left;
  pivot->left = tmp->right;

  if (tmp->right != tree->nil){
    tmp->right->parent = pivot;
  }

  tmp->parent = pivot->parent;

  if(pivot->parent == tree->nil){
    tree->root = tmp;
  }
  else if(pivot == pivot->parent->left){
    pivot->parent->left = tmp;
  }
  else{
    pivot->parent->right = tmp;
  }

  tmp->right = pivot;
  pivot->parent = tmp;

}

void left_rotate(rbtree *tree, node_t *pivot){
  node_t *tmp = pivot->right;
  pivot->right = tmp->left;

  if (tmp->left != tree->nil){
    tmp->left->parent = pivot;
  }

  tmp->parent = pivot->parent;

  if(pivot->parent == tree->nil){
    tree->root = tmp;
  }
  else if(pivot == pivot->parent->left){
    pivot->parent->left = tmp;
  }
  else{
    pivot->parent->right = tmp;
  }

  tmp->left = pivot;
  pivot->parent = tmp;

}



void delete_node(rbtree* t, node_t* n)
{
  if (n == t->nil){
    return;
  }
  delete_node(t, n->left);
  delete_node(t, n->right);
  free(n);
}


void delete_rbtree(rbtree *t)
{
  delete_node(t, t->root);
  free(t->nil);
  free(t);
}



node_t *rbtree_insert(rbtree *tree, const key_t x) {
  node_t *temp_child = tree->root;
  node_t *temp_parent = tree->nil;
  node_t *new_node = (node_t *)calloc(1, sizeof(node_t));


  while(temp_child != tree->nil){
    temp_parent = temp_child;
    if(x < temp_child->key){
      temp_child = temp_child->left;
    }
    else {
      temp_child = temp_child->right;
    }

  }

  
  if (temp_parent == tree->nil){
    tree->root = new_node;
  }
  else if(x < temp_parent->key){
    temp_parent->left = new_node;
  }
  else{
    temp_parent->right = new_node;
  }

  new_node->parent = temp_parent;
  new_node->key = x;
  new_node->left = tree->nil;
  new_node->right = tree->nil;
  new_node->color = RBTREE_RED;
  
  insert_fixup(tree, new_node);

  return new_node;
}


void insert_fixup(rbtree *tree, node_t *new_node) {
  node_t *uncle;

  while (new_node->parent->color == RBTREE_RED){
    if (new_node->parent == new_node->parent->parent->left){
      uncle = new_node->parent->parent->right;
      if (uncle->color == RBTREE_RED){
        new_node->parent->color = RBTREE_BLACK;
        uncle->color = RBTREE_BLACK;
        new_node->parent->parent->color = RBTREE_RED;
        new_node = new_node->parent->parent;
      }
      else{ 
        if(new_node == new_node->parent->right){
          new_node = new_node->parent;
          left_rotate(tree, new_node);
        }
        new_node->parent->color = RBTREE_BLACK;
        new_node->parent->parent->color = RBTREE_RED;
        right_rotate(tree, new_node->parent->parent);
      }
    }else{
      uncle = new_node->parent->parent->left;
      if (uncle->color == RBTREE_RED){
        new_node->parent->color = RBTREE_BLACK;
        uncle->color = RBTREE_BLACK;
        new_node->parent->parent->color = RBTREE_RED;
        new_node = new_node->parent->parent;
      }
      
      else{ 
        
        if(new_node == new_node->parent->left){
          new_node = new_node->parent;
          right_rotate(tree, new_node);
        }
        
        new_node->parent->color = RBTREE_BLACK;
        new_node->parent->parent->color = RBTREE_RED;
        
        left_rotate(tree, new_node->parent->parent);
      }

    }
  
  }

tree->root->color = RBTREE_BLACK;

}



node_t *rbtree_find(const rbtree *t, const key_t key) {
  node_t* temp = t->root;
  while (temp != t->nil)
  {
    if (temp->key == key)
      return temp;

    if (temp->key < key) 
      temp = temp->right;
    else
      temp = temp->left;
  }
  return NULL;
}

node_t *rbtree_min(const rbtree *tree) {
  node_t *p = tree->root;
  node_t *n = tree->nil;
  
  while(p != tree->nil){
    n = p;
    p = p->left;
  }

  return n;
}

node_t *rbtree_max(const rbtree *tree) {
  node_t *p = tree->root;
  node_t *n;
  
  while(p != tree->nil){
    n = p;
    p = p->right;
  }

  return n;
}


void transplant(rbtree *tree, node_t* u, node_t *v){
  if(u->parent == tree->nil){
    tree->root = v;
  }
  else if(u == u->parent->left){
    u->parent->left = v;
  }
  else
  {
    u->parent->right = v;
  }

  v->parent = u->parent;
  
}


int rbtree_erase(rbtree *tree, node_t *z) {
  node_t *y = z;
  key_t y_original_color = y->color;
  node_t *x;

  if(z->left == tree->nil){
    x = z->right;
    transplant(tree, z, z->right);
  }
  else if (z->right == tree->nil)
  {
    x = z->left;
    transplant(tree, z, z->left);
  }
  else{
    y = subtree_minimum(tree, z->right);
    y_original_color = y->color;
    x = y->right;
    if (y->parent == z){
      x->parent = y;
    }else{
      transplant(tree,y, y->right);
      y->right = z->right;
      y->right->parent = y;
    }

    transplant(tree, z, y);
    y->left = z->left;
    y->left->parent = y;
    y->color = z->color;

  }

  if (y_original_color == RBTREE_BLACK){
    erase_fixup(tree, x);
  }

  free(z);

  return 0;
}


void erase_fixup(rbtree *tree, node_t*x){
  while (x != tree->root && x->color == RBTREE_BLACK){
    if(x == x->parent->left){

      node_t *w = x->parent->right;
      if(w->color == RBTREE_RED){ 
        w->color = RBTREE_BLACK;
        x->parent->color = RBTREE_RED;
        left_rotate(tree, x->parent);
        w = x->parent->right;
      }

      if (w->left->color == RBTREE_BLACK && w->right->color == RBTREE_BLACK){
        w->color = RBTREE_RED;
        x = x->parent;
      }
      else{
      
        if(w->right->color == RBTREE_BLACK){
          w->left->color = RBTREE_BLACK;
          w->color = RBTREE_RED;
          right_rotate(tree, w);
          w = x->parent->right;
        }

        
        w->color = x->parent->color;
        x->parent->color = RBTREE_BLACK;
        w->right->color = RBTREE_BLACK;
        left_rotate(tree, x->parent);

        x = tree->root;
      }
    }
    else{
      node_t *w = x->parent->left;
      if(w->color == RBTREE_RED){
        w->color = RBTREE_BLACK;
        x->parent->color = RBTREE_RED;
        right_rotate(tree, x->parent);
        w = x->parent->left;
      }

      if (w->right->color == RBTREE_BLACK && w->left->color == RBTREE_BLACK){
        w->color = RBTREE_RED;
        x = x->parent;
      }
      else{
        if(w->left->color == RBTREE_BLACK){
          w->right->color = RBTREE_BLACK;
          w->color = RBTREE_RED;
          left_rotate(tree, w);
          w = x->parent->left;
        }

        w->color = x->parent->color;
        x->parent->color = RBTREE_BLACK;
        w->left->color = RBTREE_BLACK;
        right_rotate(tree, x->parent);
        x = tree->root;
      }
    }
  }
  x->color = RBTREE_BLACK;
}

int node_to_array(const rbtree* t, node_t *n, key_t *arr, int i){
  if (n == t->nil)
    return i; 

  i = node_to_array(t, n->left, arr, i);
  arr[i++] = n->key;
  i = node_to_array(t, n->right, arr, i);
  return i;
}

int rbtree_to_array(const rbtree *t, key_t *arr, const size_t n)
{
  node_to_array(t, t->root, arr, 0);
  return 0;
}


node_t* subtree_minimum(rbtree* t, node_t* z)
{
  node_t* temp_parent;
  node_t* temp_child = z;

  while (temp_child != t->nil)
  {
    temp_parent = temp_child;
    temp_child = temp_child->left;
  }
  return temp_parent;
}