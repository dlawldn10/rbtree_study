
## RB tree 삽입과 삭제 과정 시각적 정리 figma

https://www.figma.com/file/AUi98y03ruuTRpvJMDZtoT/RB-tree?node-id=0%3A1


---


## RB tree 삽입, 삭제와 관련된 함수만 추가 설명.
```C
// 새로운 트리를 생성한다.
rbtree *new_rbtree(void) {
  // rbtree *p 와 node_t *NIL 를 선언, 메모리를 할당한다.
  // *NIL 의 색을 black으로 설정하고
  // 새로 만든 트리의 nil 노드와 root 노드를 *NIL 로 설정해준다.
  // rbtree *p를 리턴한다.
}

// pivot 노드를 중심으로 오른쪽으로 회전한다.
// = pivot과 pivot의 왼쪽 자녀를 오른쪽으로 회전시킬 것이다.
void right_rotate(rbtree *tree, node_t *pivot){
  // 오른쪽으로 회전할 것이므로 
  // pivot노드의 왼쪽 자녀를 찾아서 node_t *tmp 로 선언한다.

  // if(*tmp가 트리의 리프노드가 아니라면) {
  //   tmp의 오른쪽 자녀의 parent 주소를 pivot의 주소로 변경한다.}

  // tmp의 parent 주소를 pivot의 parenet의 주소로 변경한다.

  // if (pivot의 parent가 트리의 nil노드라면){ 
  //   pivot이 root노드라는 뜻이므로
  //   트리의 root노드의 주소를 tmp의 주소로 변경한다.}
  // else if (pivot이 부모의 왼쪽 자녀였다면) {
  //   pivot의 부모의 왼쪽 자녀의 주소를 tmp의 주소로 설정해준다.}
  // else{ (pivot이 부모의 오른쪽 자녀였다면)
  //   pivot의 부모의 오른쪽 자녀의 주소를 tmp의 주소로 설정해준다.}
  
  // tmp의 오른쪽 자녀의 주소를 pivot의 주소로 설정해준다.
  // pivot parent의 주소를 tmp의 주소로 설정해준다.

}

// pivot 노드를 중심으로 왼쪽으로 회전한다.
// = pivot과 pivot의 오른쪽 자녀를 왼쪽으로 회전시킬 것이다.
void left_rotate(rbtree *tree, node_t *pivot){
  // 왼쪽으로 회전할 것이므로 
  // pivot노드의 오른쪽 자녀를 찾아서 node_t *tmp 로 선언한다.

  // if(*tmp가 트리의 리프노드가 아니라면) {
  //   tmp의 왼쪽 자녀의 parent 주소를 pivot의 주소로 변경한다.}

  // tmp의 parent 주소를 pivot의 parenet의 주소로 변경한다.

  // if (pivot의 parent가 트리의 nil노드라면){ 
  //   pivot이 root노드라는 뜻이므로
  //   트리의 root노드의 주소를 tmp의 주소로 변경한다.}
  // else if (pivot이 부모의 왼쪽 자녀였다면) {
  //   pivot의 부모의 왼쪽 자녀의 주소를 tmp의 주소로 설정해준다.}
  // else{ (pivot이 부모의 오른쪽 자녀였다면)
  //   pivot의 부모의 오른쪽 자녀의 주소를 tmp의 주소로 설정해준다.}
  
  // tmp의 왼쪽 자녀의 주소를 pivot의 주소로 설정해준다.
  // pivot parent의 주소를 tmp의 주소로 설정해준다.
}


node_t *rbtree_insert(rbtree *tree, const key_t x) {
  //트리의 루트노드(추후 새로운 노드의 자리를 뜻하게 됨.) node_t *temp_child 선언
  //트리의 리프 노드(추후 새로운 노드의 parent가 됨.) node_t *temp_parent 선언
  //새로 넣어줄 노드 node_t *new_node 선언, calloc으로 메모리 할당.


  // x를 넣을 자리를 탐색하는 과정을 진행한다.
  // 이 과정에서 temp_child는 결국 말단을 가리키게 된다. 우리는 temp_parent를 잘 찾는 것이 목적.
  // while (temp_child 가 트리의 말단까지 도달할 때까지){
  //   temp_parenet 주소를 temp_child주소로 저장해 놓는다.

  //   if (넣고자 하는 값이 현재 노드보다 작을때){
  //      temp_child의 주소를 temp_child의 왼쪽 자녀의 주소로 설정한다.
  //      =  왼쪽 자녀로 내려간다.}
  //   else { (넣고자 하는 값이 현재 노드보다 크거나 같을 때)
  //      temp_child의 주소를 temp_child의 오른쪽 자녀의 주소로 설정한다.
  //      =  오른쪽 자녀로 내려간다.}      
  // }

  // while문을 빠져나오면 new_node의 parent의 주소인 temp_parent를 찾은 상태이다.
  // temp_parent의 값을 대소비교하여 new_node가 temp_parent의 왼쪽자녀로 들어갈지, 오른쪽 자녀로 들어갈지를 결정해준다.
  // if (temp_parent의 주소가 트리의 nil노드의 주소라면){
  //   new_node가 트리의 첫번째 노드라는 뜻이므로
  //   트리의 root노드의 주소를 new_node으로 설정해준다.}
  // else if (새로 삽입하고 싶은 값 x가 temp_parent의 key값보다 작으면){
  //   부모의 왼쪽으로 넣어준다.}
  // else (새로 삽입하고 싶은 값 x가 temp_parent의 key값보다 크면){
  //   부모의 오른쪽으로 넣어준다.}

  // new_node의 자리도 다 찾았으니 node의 남은 포인터들을 설정해준다.
  // new_node의 parent의 주소는 temp_parenet의 주소.
  // new_node의 key는 x.
  // new_node의 왼쪽 자녀의 주소는 트리의 nil노드의 주소.
  // new_node의 오른쪽 자녀의 주소는 트리의 nil노드의 주소.
  // new_node의 색은 RED.

  // new_node를 삽입한 후 RB tree의 특성에 위배되는 것이 있다면 재정렬한다.
  // = insert_fixup(tree, new_node); 호출

  //새로 삽입한 노드 주소 반환.
}

// rbtree_insert 함수 내부에서 호출된다.
// new_node를 삽입한 후 RB tree의 특성에 위배되는 것이 있다면 재정렬한다.
void insert_fixup(rbtree *tree, node_t *new_node) {
  // 재정렬 과정에서 색을 바꿔주기 위해 미리 삼촌노드를 선언해준다.

  // while (new_node의 parent의 색이 RED라면){
  // new_node의 색은 RED이므로 4번 규칙 위배한 경우이다.
  //   if (왼쪽 서브트리에 일자로 나열된 형태인 경우: case3) {
  //     색을 바꿔주기 위해 삼촌노드의 주소를 찾아 정의해준다.
  //
  //       if(삼촌노드도 부모노드와 같이 빨간색 인 경우){
  //         할아버지 노드의 색과, 부모&삼촌 노드의 색을 서로 반전 시킨다.
  //         반전시켜서 4번 규칙을 올바르게 바꿔준 후
  //         new_node의 주소를 할아버지 노드의 주소로 갱신하여 위로 올린다.
  //        }
  //        else {(삼촌노드는 검정인 경우.)
  //  
  //          if (꺾여있는 경우: case2){
  //            new_node->parent를 기준으로 왼쪽으로 회전시킬 것이므로
  //            new_node에 new_node->parent를 할당.
  //            new_node를 기준으로 왼쪽으로 회전.
  //            = left_rotate(tree, new_node);
  //           }
           
  //        case2를 회전시키면 case3과 형태가 같아짐.
  //        회전했으므로 new_node는 다시 리프노드임.
  //        여기서는 삼촌의 색은 변경할 필요가 없으므로 부모의 색깔과 할아버지의 색깔만 반전시켜줌.
  //        할아버지를 기준으로 오른쪽으로 회전
  //        = right_rotate(tree, new_node->parent->parent);
  //        레드를 기준으로 그 아래의 블랙노드와 함께 회전시키므로 위쪽이 블랙, 아래쪽이 레드가 된다.
  //       따라서 위의 경우와 같이 new_node를 갱신시켜줄 필요는 없다.
  //       }
  //   }else{ 
  //     위의 경우와 반전되는 경우... (생략)
  //   }  

  // }

  // while문이 모두 끝난 후 마지막으로 트리의 루트의 색을 BLACK으로 설정해준다.
}


// u의 연결을 끊고 u의 parent와 v를 연결해준다.
void transplant(rbtree *tree, node_t* u, node_t *v){

  // if (u의 parent가 트리의 nil노드인 경우 즉 u가 root일때){
  //   트리의 root노드의 주소를 v의 주소로 설정한다.}
  // else if (u가 left child 일때){
  //   u의 parent의 왼쪽자녀의 주소를 v의 주소로 설정한다.}
  // else { (u가 right child 일때)
  //   u의 parent의 오른쪽자녀의 주소를 v의 주소로 설정한다.}
  
  // u의 parent의 주소를 v의 parent의 주소로 바꿔준다.
}


// RB tree 내부의 ptr로 지정된 node z 를 삭제하고 메모리를 free한다.
int rbtree_erase(rbtree *tree, node_t *z) {
  // 삭제되는 노드의 색을 알기 위해 node_t *z 를 복사하여 node_t *y를 만든다.
  // 노드 y의 원래 색을 저장해준다.
  // 삭제된 노드와 이어주는 노드인 node_t *x 도 선언해준다.

  // if (삭제하려는 노드z가 오른쪽 자녀만 가지고 있을 때){
  //   x를 z의 오른쪽 자녀로 설정해준뒤,
  //   z를 삭제하고 z의 부모와 z->right 노드를 연결한다.
  //   = transplant(tree, z, z->right);}
  // else if (삭제하려는 노드z가 왼쪽 자녀만 가지고 있을 때){
  //   x를 z의 왼쪽 자녀로 설정해준뒤,
  //   z를 삭제하고 z의 부모와 z->left 노드를 연결한다.
  //   = transplant(tree, z, z->left);}  
  // else { (삭제하려는 노드가 자녀를 양쪽 다 가지고 있을 때)
  //   오른쪽 서브트리에서의 최솟값을 찾는다.
  //   노드 y의 원래색을 지금 저장해준다.
  //   if (y의 parent가 z인 경우){
  //     x의 parent를 y의 주소로 설정한다.}
  //   else{
  //     transplant(tree,y, y->right);를 수행하고
  //     y의 오른쪽 자녀의 주소를 z의 오른쪽 자녀의 주소로 설정하고,
  //     y의 오른쪽 자녀의 parent의 주소를 y로 설정해준다.
  //     y를 삭제되는 z대신에 넣고 이어주는 과정이다. }

  //   transplant(tree, z, y); 를 수행하고
  //   분리된 오른쪽, 왼쪽 서브트리를 서로 이어준다.
  //
  // }

  // if (y의 원래 색이 BLACK이었다면){
  //    erase_fixup(tree, x); 을 호출하여 재정렬한다.
  // }
  
  // 마지막으로 삭제되는 z 노드의 메모리까지 free 해주면 완료.
  // free(z);

  // return 0;
}




// 최종적으로 red-and-black으로 만들어서 extra black을 간단하게 없애주는 과정:
// rotate와 부모-자녀들 색변경 과정을 통해서.
void erase_fixup(rbtree *tree, node_t*x){

  // 우리는 최종적으로 case4를 해결하여 루프를 탈출할 것이다.
  // while (x가 root가 아니며 색이 BLACK인 동안 수행한다.){
  //  
  //   if(x가 왼쪽 자녀인 경우){
  //     부모의 오른쪽 자녀인 node_t *w 를 선언한다.
  //
  //     case 1:
  //     if(w가 빨간색일때.){ 
  //       w의 색을 검정으로 바꾸고
  //       부모의 색을 빨강으로 바꾼다.
  //       부모를 기준으로 왼쪽으로 회전한다. = left_rotate(tree, x->parent);
  //       바뀐 x의 형제노드 w를 새롭게 정의해준다.(갱신)
  //     }

  //     douly-black의 형제가 black && 그 형제의 자녀들 모두 black일때.
  //     w가 black && w의 자녀들 모두 black.
  //     이 case의 경우 자녀들 선에서 정리할 수 없으므로 
  //     extra black을 부모에게 전해서 다른 case의 경우로 변경하여 해결한다.
  //     case2:
  //     if (w->left->color == RBTREE_BLACK && w->right->color == RBTREE_BLACK){
  //       부모와 자녀들의 색으로 서로 바꾸는 과정. 
  //       extra blcak을 이용하여 바꿔주므로, 
  //       부모노드의 색에 구애 받지 않고 자녀들의 색이 반전된다.

  //       w의 색을 빨강으로 바꾼다.
  //       x가 한칸 위로 올라간다.
  //       }
  //     doubly-black의 형제가 black && 그 형제의 오른쪽 자녀만 black일때.
  //     w가 black && w의 오른쪽 자녀만 black.
  //     case4의 형태로 만드는 과정.
  //     case3:
  //     else{
  //     
  //       if(w->right->color == RBTREE_BLACK){
  //         w와 w의 왼쪽 자녀의 색을 교환한다.
  //         w를 기준으로 오른쪽으로 회전한다. = right_rotate(tree, w);
  //         w를 다시 설정해준다.
  //         (추후 아래에 있는 case 4의 해결방법이나 while 루프를 통한 방법으로 해결한다.)
  //        }

  //       douly-black의 형제가 black && 그 형제의 오른쪽 자녀가 red.
  //       w가 black && w의 오른쪽 자녀가 red.
  //       case4:
  //       w와 그 자녀들의 색을 서로 바꾸고
  //       w, x와 그 부모의 색을 바꾸고
  //       부모를 기준으로 왼쪽으로 회전한다. = left_rotate(tree, x->parent);

  //       case4 처리 완료하였으므로 이 위에 노드들은 확인할 필요가 없다.
  //       따라서 while 루프를 끝내기 위해 x를 root으로 설정한다. 
  //     }
  //  }
  //  else{
        // 위의 if에서와 좌우 반대의 경우 ... (생략)
  //  }
  
  // 마지막으로 x의 색을 BLACK으로 바꿔준다.
  
}
