//2016116317_컴퓨터학부_이창진
//visual studio 2019에서 작성했습니다.
#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct avl_node_ {
	struct avl_node_* left;
	struct avl_node_* right;
	int key;
};
typedef struct avl_node_ Avl_node;

struct avl_tree {
	struct avl_node_*   root;
};
typedef struct avl_tree avl_tree_;
int minval;

avl_tree_* avl_create();
Avl_node* avl_create_node();
int avl_node_height(Avl_node* node);
int find_balance_factor(Avl_node* node);
Avl_node* avl_LL(Avl_node* node);
Avl_node* avl_LR(Avl_node* node);
Avl_node* avl_RL(Avl_node* node);
Avl_node* avl_RR(Avl_node* node);
Avl_node* get_balance(Avl_node* node);
void avl_balance(avl_tree_* tree);
void avl_insert(avl_tree_* tree, int val);
Avl_node* avl_find(avl_tree_* tree, int val);
void avl_traverse_inorder(Avl_node* node, FILE* f);
void avl_traverse_preorder(Avl_node* node, FILE* f);
void successor(Avl_node* node);
Avl_node* delete(Avl_node* root, int val);
void printTree(avl_tree_* tree, FILE* f);

int main(int argc, char* argv[]) {
	FILE* fr;
	FILE* fw;
	avl_tree_* tree = NULL;
	int input;
	int cnt = 0;
	int z = 0;
	int firstval;
	int i = 0;
	int r = 0;

	if (argc != 3) {					// 인자가 3개가 아닐경우 에러메시지를 출력합니다
		printf("입력 파일 이름을 입력해주세요.\n");
		exit(1);
	}
	else if (argc > 3) {				// 인자가 3개를 초과했을 경우 에러메시지를 출력하빈다
		printf("입력 인자가 너무 많습니다. (입력파일 출력파일) 순으로 입력해주세요.\n");
		exit(1);
	}
	else fr = fopen(argv[1], "r");
	if (!fr) {							// argv[1]이 파일 이름에 오류가 있다면 파일이 열리지 않고 에러메시지를 출력합니다
		printf("입력 파일 이름에 오류가 있습니다.\n");
		exit(1);
	}
	fw = fopen(argv[2], "w");
	if (!fw) {						// argv[2]이 파일 이름에 오류가 있다면 파일이 열리지 않고 에러메시지를 출력합니다
		printf("출력 파일 이름에 오류가 있습니다.\n");
		exit(1);
	}

	tree = avl_create();

	while (fscanf(fr, "%d", &input) != EOF) {			// 입력파일의 끝까지 fscanf()를  이용해 읽습니다.
		//while (avl_find(tree, input));
		avl_insert(tree, input);
		if (z == 0) firstval = input;
		fprintf(fw, "%d번째 트리 : ", ++cnt);
		printTree(tree, fw);
		z = 1;
	}
	fclose(fr);

	delete(tree->root, firstval);
	fprintf(fw, "%d번째 트리 : ", ++cnt);
	printTree(tree, fw);

	fclose(fw);
	return 0;
}


avl_tree_* avl_create() {		// 최초로 avl 트리를 malloc을 통해 만듭니다.
	avl_tree_* tree = NULL;
	if ((tree = malloc(sizeof(avl_tree_))) == NULL)
		return NULL;
	tree->root = NULL;
	return tree;
}

Avl_node* avl_create_node() {	// 왼쪽 자식노드와 오른쪽 자식노드가 NULL인 avl 노드를 하나 만듭니다
	Avl_node* node = NULL;
	if ((node = malloc(sizeof(Avl_node))) == NULL) {
		return NULL;
	}
	node->left = NULL;
	node->right = NULL;
	node->key = 0;
	return node;
}

int avl_node_height(Avl_node* node) { // AVL 노드의 height를 recursive하게 찾습니다.
	int left_height = 0;
	int right_height = 0;

	if (node->left) left_height = avl_node_height(node->left);
	if (node->right) right_height = avl_node_height(node->right);
	if (right_height > left_height)
		return ++right_height;
	else 
		return ++left_height;
}

/* Find the balance of an AVL node */
int find_balance_factor(Avl_node* node) {	// AVL 노드의 왼쪽 노드와 오른쪽 노드의 balance_factor를 계산합니다
	int balancefactor = 0;

	if (node->left) balancefactor += avl_node_height(node->left);
	if (node->right) balancefactor -= avl_node_height(node->right);

	return balancefactor;
}

Avl_node* avl_LL(Avl_node* node) {		// avl tree를 LeftLeft 회전합니다
	Avl_node* center = node;
	Avl_node* target = center->left;

	center->left = target->right;
	target->right = center;

	return(target);
}

Avl_node* avl_LR(Avl_node* node) {		// avl tree를 LeftRight 회전합니다
	Avl_node* center = node;
	Avl_node* target = center->left;
	Avl_node* source = target->right;

	center->left = source->right;
	target->right = source->left;
	source->left = target;
	source->right = center;

	return(source);
}

Avl_node* avl_RL(Avl_node* node) {		// avl tree를 RightLeft 회전합니다
	Avl_node* center = node;
	Avl_node* target = center->right;
	Avl_node* source = target->left;

	center->right = source->left;
	target->left = source->right;
	source->right = target;
	source->left = center;

	return(source);
}

Avl_node* avl_RR(Avl_node* node) {		// avl tree를 RightRight 회전합니다
	Avl_node* center = node;
	Avl_node* target = center->right;

	center->right = target->left;
	target->left = center;

	return(target);
}

Avl_node* get_balance(Avl_node* node) {		// node의 균형을 잡습니다
	Avl_node* temp = NULL;

	if (node->left)							// .만약 왼쪽 자식이 있다면 왼쪽 자식의 균형을 잡고
		node->left = get_balance(node->left);
	if (node->right)						// 만약 오른쪽 자식이 있다면 오른쪽 자식의 균형을 잡습니다.
		node->right = get_balance(node->right);

	int balance_F = find_balance_factor(node);

	if (balance_F >= 2) {					// 만약 왼쪽자식과 오른쪽 자식의 균형 차이가 2이상이라면 LR 또는 LL을 실시합니다.
		if (find_balance_factor(node->left) <= -1)
			temp = avl_LR(node);
		else
			temp = avl_LL(node);
	}
	else if (balance_F <= -2) {				// 만약 왼쪽자식과 오른쪽 자식의 균형 차이가 -2이하라면 RL 또는 RR을 실시합니다.
		if (find_balance_factor(node->right) >= 1)
			temp = avl_RL(node);
		else
			temp = avl_RR(node);
	}
	else {									// 이미 균형이 잡혀있다면, 그대로 node를 반환합니다.
		temp = node;
	}

	return(temp);
}

void avl_balance(avl_tree_* tree) {			// 트리의 균형을 잡습니다.
	Avl_node* temp = NULL;

	temp = get_balance(tree->root);
	if (temp != tree->root)
		tree->root = temp;
}

void avl_insert(avl_tree_* tree, int val) {		// 트리에 새로운 노드를 삽입합니다.
	Avl_node* node = NULL;
	Avl_node* new = NULL;
	Avl_node* on = NULL;

	if (tree->root == NULL) {						// root노드에 값이 없다면 즉, NULL 이라면 새로운 노드를 만들어서 트리에 넣어줍니다.
		node = avl_create_node();
		node->key = val;
		tree->root = node;
	}
	else {											// root 노드가 있다면 트리의 어디에 넣어야할지 선택합니다.
		new = tree->root;
		while (new != NULL) {
			on = new;

			if (val < new->key) {
				new = new->left;
			}
			else if (val > new->key) {				// val값이 node의 key값보다 크다면 새로운 노드의 오른쪽 자식으로 들어갑니다.
				new = new->right;
			}
		}
		node = avl_create_node();					// 새로운 노드를 만듭니다.
		node->key = val;							// 노드에 key값으로 val값을 넣습니다.
		if (val < on->key) on->left = node;			// val값이 node의 key값보다 작다면 새로운 노드의 왼쪽 자식으로 들어갑니다.
		if (val > on->key) on->right = node;		// val값이 node의 key값보다 크다면 새로운 노드의 오른쪽 자식으로 들어갑니다.

	}

	avl_balance(tree);
}

Avl_node* avl_find(avl_tree_* tree, int val) {		//  val값과 일치하는 key를 가지는 노드를 찾아서 반환합니다.
	Avl_node* current = tree->root;

	while (current && current->key != val) {
		if (val > current->key)
			current = current->right;
		else
			current = current->left;
	}

	return current;
}

void avl_traverse_inorder(Avl_node* node, FILE* f) {	// 트리를 inorder traversal하면서 트리의 모든 key값을 출력합니다.
	if (node) {
		avl_traverse_inorder(node->left,f);
		fprintf(f, "%d ", node->key);
		avl_traverse_inorder(node->right,f);
	}
}

void avl_traverse_preorder(Avl_node* node, FILE* f) {// 트리를 preorder traversal하면서 트리의 모든 key값을 출력합니다.
	if (node) {
		fprintf(f, "%d ", node->key);
		avl_traverse_preorder(node->left, f);
		avl_traverse_preorder(node->right, f);
	}
}

void successor(Avl_node* node) {					// 오른쪽 서브트리에서 제일 작은 key를 minval에 저장합니다.
	if (node) {
		if (minval < node->key) minval = node->key;
		successor(node->left, NULL);
		successor(node->right, NULL);
	}
};

Avl_node* delete(Avl_node* root, int val)			// val과 일치하는 key를 가지는 노드를 삭제합니다.
{
	Avl_node* remove_node;
	minval = 0;
	if (root == NULL) {
		return root;
	}

	if (val < root->key) {							// 만약 val보다 node의 key가 작다면 왼쪽 자식으로 내려갑니다.
		root->left = delete(root->left, val);

	}
	else if (val > root->key) {						// 만약 val보다 node의 key가 작다면 오른쪽 자식으로 내려갑니다.
		root->right = delete(root->right, val);

	}
	else {
		if ((root->left == NULL) && (root->right != NULL)) {	// 왼쪽 자식이 없고, 오른쪽 자식이 존재할경우
			remove_node = root->right;
			*root = *remove_node;
		}
		else if ((root->right == NULL) && (root->left != NULL)) {	// 오른쪽 자식이 없고, 왼쪽 자식이 존재할경우
			remove_node = root->left;
			*root = *remove_node;

		}
		else if ((root->right == NULL) && (root->left == NULL)) {		// 오른쪽 자식이 없고, 왼쪽 자식이 없을경우
			remove_node = root;
			root = NULL;
		}
		else {													// 그 이외의 경우
			minval = root->right->key;
			successor(root->right);
			root->key = minval;
			root->right = delete(root->right, minval);
		}
	}

	if (root == NULL) {
		return root;

		find_balance_factor(root);

		if (find_balance_factor(root) >= 2) {	// 만약 왼쪽자식과 오른쪽 자식의 균형 차이가 2이상이라면 LR 또는 LL을 실시합니다.
			if (find_balance_factor(root->left) <= -1) {
				return avl_LR(root);
			}
			else
				return avl_LL(root);
		}
		else if (find_balance_factor(root) <= -2) {	// 만약 왼쪽자식과 오른쪽 자식의 균형 차이가 -2이하라면 RL 또는 RR을 실시합니다.
			if (find_balance_factor(root->right) >= -1) {
				return avl_RL(root);
			}
			else
				return avl_RR(root);
		}
		else
			return root;
	}

	return root;
}

void printTree(avl_tree_* tree, FILE* f) {			// inorder, preorder 순회를 하면서 해당하는 출력을 출력파일에 저장합니다.
	fprintf(f, "\n");
	fprintf(f, "inorder  : ");
	avl_traverse_inorder(tree->root, f);
	fprintf(f, "\n");
	fprintf(f, "preorder : ");
	avl_traverse_preorder(tree->root, f);
	fprintf(f, "\n");
}

