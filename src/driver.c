#include "rbtree.h"
#include <stdio.h>


int main(int argc, char *argv[]) {
    rbtree *T = new_rbtree();
    rbtree_insert(T, 1000);
    rbtree_insert(T, 2000);
    rbtree_insert(T, 3000);
    printf("%d\n", T->root->key);
    printf("%d\n", T->root->left->key);
    printf("%d\n", T->root->right->key);
    // printf("%d\n", rbtree_min(T)->key);
    // printf("%d\n", rbtree_max(T)->key);
    // printf("%d\n", rbtree_find(T, 3000)->key);
    // printf("%c\n", rbtree_find(T, 100000));
}

