#include "rbtree.h"

#include <stdlib.h>
#include <stdio.h>

rbtree *new_rbtree(void) {
  //트리와 루트노드를 선언, 할당한다.
  rbtree *p = (rbtree *)calloc(1, sizeof(rbtree));
  node_t *NIL = (node_t *)calloc(1, sizeof(node_t));
  NIL->color = RBTREE_BLACK;
  p->nil = NIL;
  p->root = NIL;
  return p;
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



void delete_rbtree(rbtree *t) {
  free(t);
}

void insert_fixup(rbtree *tree, node_t *new_node) {
  node_t *uncle;

  // new_node의 색은 RED이므로 4번 규칙 위배
  while (new_node->parent->color == RBTREE_RED){
    // 왼쪽 서브트리에 일자로 나열된 형태인 경우: case3
    if (new_node->parent == new_node->parent->parent->left){
      // 색을 바꿔주기 위해 삼촌노드를 찾아준다.
      uncle = new_node->parent->parent->right;
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


node_t *rbtree_insert(rbtree *tree, const key_t x) {
  //트리의 루트노드(추후 새로운 노드의 자리를 뜻하게 됨.)
  node_t *p = tree->root;
  //트리의 리프 노드(추후 새로운 노드의 parent가 됨.)
  node_t *n = tree->nil;
  //새로 넣어줄 노드 메모리 할당.
  node_t *new_node = (node_t *)calloc(1, sizeof(node_t));

  // 키값 넣어주기.
  new_node->key = x;

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

// RB tree 중 최소 값을 가진 node pointer 반환
node_t *rbtree_min(const rbtree *tree) {
  //트리의 루트노드(추후 새로운 노드의 자리를 뜻하게 됨.)
  node_t *p = tree->root;
  //트리의 리프 노드(추후 새로운 노드의 parent가 됨.)
  node_t *n = tree->nil;
  
  while(p != tree->nil){
    n = p;
    p = p->left;
  }

  return n;
}

// 최대값을 가진 node pointer 반환
node_t *rbtree_max(const rbtree *tree) {
  //트리의 루트노드(추후 새로운 노드의 자리를 뜻하게 됨.)
  node_t *p = tree->root;
  //트리의 리프 노드(추후 새로운 노드의 parent가 됨.)
  node_t *n;
  
  while(p != tree->nil){
    n = p;
    p = p->right;
  }

  return n;
}

// RB tree 내부의 ptr로 지정된 node를 삭제하고 메모리 반환
int rbtree_erase(rbtree *tree, node_t *z) {
  // 우리는 z를 삭제하고 싶다.
  node_t *y = z;
  key_t y_original_color = y->color;
  node_t *x;

  // 삭제하려는 노드z가 오른쪽 자녀만 가지고 있을 때
  if(z->left == tree->nil){
    x = z->right;
    transplant(tree, z, z->right);
  }
  // 삭제하려는 노드z가 왼쪽 자녀만 가지고 있을 때
  else if (z->right == tree->nil)
  {
    x = z->left;
    transplant(tree, z, z->left);
  }
  // 삭제하려는 노드가 자녀를 양쪽 다 가지고 있을 때
  else{
    // 오른쪽 서브트리에서의 최솟값을 찾는다.
    y = subtree_minimum(tree, z->right);
    y_original_color = y->color;
    x = y->right;
    if (y->parent == z){
      x->parent = y;
    }else{
      transplant(tree,y, y->right);
      // 찾은 y를 삭제되는 z대신에 붙여주는 것.
      y->right = z->right;
      y->right->parent = y;
    }

    // 분리된 오른쪽, 왼쪽 서브트리를 서로 이어준다.
    transplant(tree, z, y);
    y->left = z->left;
    y->left->parent = y;
    y->color = z->color;

  }

  if (x != tree->nil && y_original_color == RBTREE_BLACK){
    erase_fixup(tree, x);
  }
  free(z);
  return 0;
}



// u의 연결을 끊고 u의 parent와 v를 연결해준다.
void transplant(rbtree *tree, node_t* u, node_t *v){
  // u가 root일때
  if(u->parent == tree->nil){
    tree->root = v;
  }
  // u가 left child 일때
  else if(u == u->parent->left){
    u->parent->left = v;
  }
  // u가 right child 일때
  else
  {
    u->parent->right = v;
  }

  // u의 parent가 v의 parent가 된다. 
  v->parent = u->parent;
  
}

// 최종적으로 red-and-black으로 만들어서 extra black을 간단하게 없애주는 과정:
// rotate와 부모-자녀들 색변경 과정을 통해서.
void erase_fixup(rbtree *tree, node_t*x){
  // x의 형제노드
  
  // x가 root가 아니며 검정색인 동안 수행한다.
  // 우리는 최종적으로 case4를 해결하여 루프를 탈출할 것이다.
  while (x != tree->root && x->color == RBTREE_BLACK){
    // x가 왼쪽 자녀인 경우
    if(x == x->parent->left){

      // w는 x의 오른쪽에 있는 형제이다. 즉 부모의 오른쪽 자녀.
      node_t *w = x->parent->right;
      // w가 빨간색일때.
      // case 1
      if(w->color == RBTREE_RED){ 
        // w의 색을 검정으로 바꾸고
        w->color = RBTREE_BLACK;
        // 부모의 색을 빨강으로 바꾼다.
        x->parent->color = RBTREE_RED;
        // 부모를 기준으로 왼쪽으로 회전한다.
        left_rotate(tree, x->parent);
        // 바뀐 x의 형제노드 w를 새롭게 정의해준다.(갱신)
        w = x->parent->right;
      }

      // douly-black의 형제가 black && 그 형제의 자녀들 모두 black일때.
      // w가 black && w의 자녀들 모두 black.
      // 이 case의 경우 자녀들 선에서 정리할 수 없으므로 
      // extra black을 부모에게 전해서 다른 case의 경우로 변경하여 해결한다.
      // case2
      if (w->left->color == RBTREE_BLACK && w->right->color == RBTREE_BLACK){
        // 부모와 자녀들의 색으로 서로 바꾸는 과정. 
        // extra blcak을 이용하여 바꿔주므로, 
        // 부모노드의 색에 구애 받지 않고 자녀들의 색이 반전된다.

        // w의 색을 빨강으로 바꾼다.
        w->color = RBTREE_RED;
        // x가 한칸 위로 올라간다.
        x = x->parent;
      }
      // doubly-black의 형제가 black && 그 형제의 오른쪽 자녀만 black일때.
      // w가 black && w의 오른쪽 자녀만 black.
      // case4의 형태로 만드는 과정.
      // case3
      else{
      
        if(w->right->color == RBTREE_BLACK){
           // w와 w의 왼쪽 자녀의 색을 교환한다.
          w->left->color = RBTREE_BLACK;
          w->color = RBTREE_RED;
          // w를 기준으로 오른쪽으로 회전한다.
          right_rotate(tree, w);
          // w를 다시 설정해준다.
          // (추후 아래에 있는 case 4의 해결방법이나 while 루프를 통한 방법으로 해결한다.)
          w = x->parent->right;
        }

        // douly-black의 형제가 black && 그 형제의 오른쪽 자녀가 red.
        // w가 black && w의 오른쪽 자녀가 red.
        // case4
        // w와 그 자녀들의 색을 서로 바꾸고
        // w, x와 그 부모의 색을 바꾸고
        // 부모를 기준으로 왼쪽으로 회전한다.
        w->color = x->parent->color;
        x->parent->color = RBTREE_BLACK;
        w->right->color = RBTREE_BLACK;
        left_rotate(tree, x->parent);

        // case4처리 완료하였으므로 이 위에 노드들은 확인할 필요가 없다.
        // 따라서 while 루프를 끝내기 위해 x를 root으로 설정한다. 
        x = tree->root;
      }
    }
    else{
      // 위의 if에서와 반대의 경우
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

  i = node_to_array(t, n->left, arr, i);   //left recur
  arr[i++] = n->key;   //print
  i = node_to_array(t, n->right, arr, i);  //right recur
  return i;
}

int rbtree_to_array(const rbtree *t, key_t *arr, const size_t n)
{
  node_to_array(t, t->root, arr, 0);
  return 0;
}


//z가 루트인 서브트리의 최소값을 찾는다.
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