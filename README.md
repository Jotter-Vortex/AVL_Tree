# AVL_Tree


### avl_tree.c
###### * AVL tree is a binary tree balanced with respect to the heights of subtrees
    −  1. introduced by Adelson-Velskii and Landis, in 1962
    −  2. use rebalancing using 4 kinds of rotations 
    −  3. search, insert, delete: O(log n)

###### Definitions:
        -An empty tree is height-balanced. If T is a nonempty binary tree with TL and TR
          as its left and right subtrees respectively, then T is height-balanced iff
               1) TL and TR are height-balanced and
               2) | hL- hR| ≤ 1 where hL and hR are the heights of TL and TR respectively.

 
 ###### ◆ 높이 균형 트리 정의
    − 공백 트리 T는 높이 균형 트리
    − T는 공백이 아니고, 왼쪽과 오른쪽 서브트리가 TL과 TR인 이진 트리일 때
           TL과 TR이 높이 균형 트리이고
           | hL – hR | ≤ 1 (hL과 hR은 각각 TL, TR의 높이)
 ###### ◆ 균형인수(balance factor)
    − 왼쪽과 오른쪽 서브트리의 높이 차이
    − BF(N) = hL – hR
    − AVL 트리: 모든 노드 N에 대해 BF(N) = -1, 0, 1
    
 ###### ◆ 삽입된 노드 Y에 가장 가까우면서 균형인수가 ±2인 조상노드 A에 대한 회전 성질
    − 단일회전(Single rotation): LL과 RR 불균형을 바로잡는 변환
    − 이중회전(Double rotation): LR과 RL 불균형을 바로잡는 변환

 ###### ☆Time complexity
     − 원소 k를 탐색 : O(log n)
     − j번째 항목을 탐색 : O(log n)
     − 원소 k를 삭제  : O(log n)
     − j번째 항목을 삭제 : O(log n)
     − 삽입 : O(log n)
     − 순서대로 출력 : O(n)
     + (이중 연결 리스트이며 k의 위치를 알고있음. 삽입할 위치를 아는경우임.)
