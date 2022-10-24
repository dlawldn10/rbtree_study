#ifndef _RBTREE_H_
#define _RBTREE_H_

#include <stddef.h>

// 색 선언
typedef enum { RBTREE_RED, RBTREE_BLACK } color_t;

// 트리에 들어갈 값의 데이터타입
typedef int key_t;

// node 구조체
typedef struct node_t {
  color_t color;
  key_t key;
  struct node_t *parent, *left, *right;
} node_t;

// rbtree 구조체
typedef struct {
  node_t *root;
  node_t *nil;  // for sentinel
} rbtree;

// rbtree 생성자
rbtree *new_rbtree(void);
void delete_rbtree(rbtree *);

node_t *rbtree_insert(rbtree *, const key_t);
node_t *rbtree_find(const rbtree *, const key_t);
node_t *rbtree_min(const rbtree *);
node_t *rbtree_max(const rbtree *);
int rbtree_erase(rbtree *, node_t *);

int rbtree_to_array(const rbtree *, key_t *, const size_t);

void right_rotate(rbtree *, node_t *);
void left_rotate(rbtree *, node_t *);
void insert_fixup(rbtree *, node_t *);
node_t *rbtree_insert(rbtree *, const key_t);

#endif  // _RBTREE_H_
