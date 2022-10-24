#include "rbtree.h"

#include <stdlib.h>

// RB tree 구조체 생성
// 여러 개의 tree를 생성할 수 있어야 하며 각각 다른 내용들을 저장할 수 있어야 합니다.
rbtree *new_rbtree(void) {
  //트리와 루트노드를 선언, 할당한다.
  rbtree *p = (rbtree *)calloc(1, sizeof(rbtree));
  node_t *NIL = (node_t *)calloc(1, sizeof(node_t));
  NIL->color = RBTREE_BLACK;
  p->nil = NIL;
  p->root = NIL;
  return p;
}


// RB tree 구조체가 차지했던 메모리 반환
// 해당 tree가 사용했던 메모리를 전부 반환해야 합니다. (valgrind로 나타나지 않아야 함)
void delete_rbtree(rbtree *t) {
  free(t);
}


node_t *rbtree_insert(rbtree *tree, const key_t x) {
  //트리의 루트노드(추후 새로운 노드의 자리를 뜻하게 됨.)
  node_t *p = tree->root;
  //트리의 리프 노드(추후 새로운 노드의 parent가 됨.)
  node_t *n = tree->nil;
  //새로 넣어줄 노드 메모리 할당.
  node_t *new_node = (node_t *)calloc(1, sizeof(node_t));

  // x를 넣을 자리를 탐색하는 과정.
  // p는 결국 말단을 가리키게 된다. 우리는 n을 잘 찾는 것이 목적.
  while(p != tree->nil){
    n = p;
    // 넣고자 하는 값이 현재 노드보다 작을때
    if(x < p->key){
      // 왼쪽 자녀로 내려간다.
      p = p->left;
    }
    // 넣고자 하는 값이 현재 노드보다 크거나 같을 때
    else {
      // 오른쪽 자녀로 내려간다.
      p = p->right;
    }

  }

  // x노드를 이어주는 과정
  // 키값 넣어주기.
  new_node->key = x;
  // 부모 설정해주기.
  new_node->parent = n;

  // x노드의 위치 결정하기.
  // n이 nil 이라면, 트리가 비어있었다는 뜻이므로
  if (n == tree->nil){
    // root으로 설정해준다.
    tree->root = new_node;
  }
  // 부모의 키값보다 작으면 부모의 왼쪽으로 넣어준다.
  else if(x < n->key){
    n->left = new_node;
  }
  // 부모의 키값보다 크면 부모의 오른쪽으로 넣어준다.
  else{
    n->right = new_node;
  }

  new_node->left = tree->nil;
  new_node->right = tree->nil;
  new_node->color = RBTREE_RED;
  
  // 재정렬
  insert_fixup(tree, new_node);

  return new_node;
}

void insert_fixup(rbtree *tree, node_t *new_node) {

  // new_node의 색은 RED이므로 4번 규칙 위배
  while (new_node->parent->color == RBTREE_RED){
    // 왼쪽 서브트리에 일자로 나열된 형태인 경우: case3
    if (new_node->parent == new_node->parent->parent->left){
      // 색을 바꿔주기 위해 삼촌노드를 찾아준다.
      node_t *uncle = new_node->parent->parent->right;
      // 삼촌노드도 부모노드와 같이 빨간색 인 경우
      if (uncle->color == RBTREE_RED){
        // 할아버지 노드의 색과 부모, 산촌 노드의 색을 서로 반전 시킨다.
        new_node->parent->color = RBTREE_BLACK;
        uncle->color = RBTREE_BLACK;
        new_node->parent->parent->color = RBTREE_RED;
        // 반전시켜서 4번 규칙을 올바르게 바꿔준 후 위로 이동.
        new_node = new_node->parent->parent;
      }
      // 삼촌노드는 검정인 경우.
      else{ 
        // 그런데 꺾여있는 경우: case2
        if(new_node == new_node->parent->right){
          // new_node->parent를 기준으로 왼쪽으로 회전시킬 것이므로
          // new_node에 new_node->parent를 할당.
          new_node = new_node->parent;
          // new_node를 기준으로 왼쪽으로 회전.
          left_rotate(tree, new_node);
        }
        // 회전시키면 case3과 형태가 같아짐.
        // 회전했으므로 new_node는 다시 리프노드임.
        // 여기서는 삼촌의 색은 변경할 필요가 없으므로 부모의 색깔과 할아버지의 색깔만 반전시켜줌.
        new_node->parent->color = RBTREE_BLACK;
        new_node->parent->parent->color = RBTREE_RED;
        // 할아버지를 기준으로 오른쪽으로 회전
        right_rotate(tree, new_node->parent->parent);
        // 레드를 기준으로 그 아래의 블랙노드와 함께 회전시키므로 위쪽이 블랙, 아래쪽이 레드가 된다.
        // 따라서 위의 경우와 같이 new_node를 갱신시켜줄 필요는 없다.
      }
    }else{
      // 위의 경우와 반전되는 경우.
      // 오른쪽 서브트리에 일자로 나열된 형태인 경우: case3
      node_t *uncle = new_node->parent->parent->left;
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

void left_rotate(rbtree *tree, node_t *pivot){
  // pivot과 pivot의 오른쪽 자녀를 왼쪽으로 회전시킬 것이다.
  // pivot의 오른쪽 자녀를 찾아 정의해준다.
  node_t *tmp = pivot->right;
  pivot->right = tmp->left;

  // tmp의 왼쪽자녀가 nil이 아닌 내부 노드라면
  if (tmp->left != tree->nil){
    // 그 노드와 pivot을 연결해준다.
    tmp->left->parent = pivot;
  }

  // tmp를 pivot의 부모와 이어준다.
  tmp->parent = pivot->parent;

  // pivot노드가 루트노드였다는 뜻이므로
  if(pivot->parent == tree->nil){
    // tmp를 루트노드로 만들어 준다.
    tree->root = tmp;
  }
  // pivot이 왼쪽 자녀였을 경우
  else if(pivot == pivot->parent->left){
    // pivot의 부모의 왼쪽 자녀를 tmp로 고쳐준다.
    pivot->parent->left = tmp;
  }
  // pivot이 오른쪽 자녀였을 경우
  else{
    // pivot의 부모의 오른쪽 자녀를 tmp로 고쳐준다.
    pivot->parent->right = tmp;
  }

  // tmp의 왼쪽 자녀로 pivot을 지정해준다.
  tmp->left = pivot;
  // pivot의 부모로 tmp를 지정해준다.
  pivot->parent = tmp;

}

// left의 반전과 같다.
void right_rotate(rbtree *tree, node_t *pivot){
  node_t *tmp = pivot->left;
  pivot->left = tmp->right;
  if (tmp->right != tree->nil){
    tmp->right->parent = pivot;
  }
  tmp->parent = pivot->parent;
  if(pivot->parent == tree->nil){
    tree->root = tmp;
  }else if(pivot == pivot->parent->right){
    pivot->parent->right = tmp;
  }else{
    pivot->parent->left = tmp;
  }

  tmp->right = pivot;
  pivot->parent = tmp;

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

