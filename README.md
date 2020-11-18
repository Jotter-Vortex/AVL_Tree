# AVL_Tree


### avl_tree.c
* AVL tree is a binary tree balanced with respect to the heights of subtrees
 1. introduced by Adelson-Velskii and Landis, in 1962
 2. use rebalancing using 4 kinds of rotations 
 3. search, insert, delete: O(log n)

      -Definitions:
        -An empty tree is height-balanced. If T is a nonempty binary tree with TL and TR
          as its left and right subtrees respectively, then T is height-balanced iff
               1) TL and TR are height-balanced and
               2) | hL- hR| ≤ 1 where hL and hR are the heights of TL and TR respectively.

 
 
 + BST를 만들때, height를 고려하지않고 만든다면,
 + 노드의 개수가 n개라면 최악의 경우 log2(n)만큼의 비용이 발생합니다.
 + 노드를 추가,삭제 할때마다 균형잡힌 트리를 만듭니다.
 + 노드의 key값을 변경할때 역시 균형잡힌 트리로 만들어줍니다.
