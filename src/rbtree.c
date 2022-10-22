#include "rbtree.h"

#include <stdlib.h>

// RB tree 구조체 생성
// 여러 개의 tree를 생성할 수 있어야 하며 각각 다른 내용들을 저장할 수 있어야 합니다.
rbtree *new_rbtree(void) {
  rbtree *p = (rbtree *)calloc(1, sizeof(rbtree));
  // TODO: initialize struct if needed
  return p;
}

// RB tree 구조체가 차지했던 메모리 반환
// 해당 tree가 사용했던 메모리를 전부 반환해야 합니다. (valgrind로 나타나지 않아야 함)
void delete_rbtree(rbtree *t) {
  // TODO: reclaim the tree nodes's memory
  free(t);
}

// key 추가
// 구현하는 ADT가 multiset이므로 이미 같은 key의 값이 존재해도 하나 더 추가 합니다.
node_t *rbtree_insert(rbtree *t, const key_t key) {
  // TODO: implement insert
  return t->root;
}

// RB tree내에 해당 key가 있는지 탐색하여 있으면 해당 node pointer 반환
// 해당하는 node가 없으면 NULL 반환
node_t *rbtree_find(const rbtree *t, const key_t key) {
  // TODO: implement find
  return t->root;
}

// RB tree 중 최소 값을 가진 node pointer 반환
node_t *rbtree_min(const rbtree *t) {
  // TODO: implement find
  return t->root;
}

// 최대값을 가진 node pointer 반환
node_t *rbtree_max(const rbtree *t) {
  // TODO: implement find
  return t->root;
}

// RB tree 내부의 ptr로 지정된 node를 삭제하고 메모리 반환
int rbtree_erase(rbtree *t, node_t *p) {
  // TODO: implement erase
  return 0;
}

// RB tree의 내용을 key 순서대로 주어진 array로 변환
// array의 크기는 n으로 주어지며 tree의 크기가 n 보다 큰 경우에는 순서대로 n개 까지만 변환
// array의 메모리 공간은 이 함수를 부르는 쪽에서 준비하고 그 크기를 n으로 알려줍니다.
int rbtree_to_array(const rbtree *t, key_t *arr, const size_t n) {
  // TODO: implement to_array
  return 0;
}

