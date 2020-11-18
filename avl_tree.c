//2016116317_��ǻ���к�_��â��
//visual studio 2019���� �ۼ��߽��ϴ�.
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

	if (argc != 3) {					// ���ڰ� 3���� �ƴҰ�� �����޽����� ����մϴ�
		printf("�Է� ���� �̸��� �Է����ּ���.\n");
		exit(1);
	}
	else if (argc > 3) {				// ���ڰ� 3���� �ʰ����� ��� �����޽����� ����Ϻ��
		printf("�Է� ���ڰ� �ʹ� �����ϴ�. (�Է����� �������) ������ �Է����ּ���.\n");
		exit(1);
	}
	else fr = fopen(argv[1], "r");
	if (!fr) {							// argv[1]�� ���� �̸��� ������ �ִٸ� ������ ������ �ʰ� �����޽����� ����մϴ�
		printf("�Է� ���� �̸��� ������ �ֽ��ϴ�.\n");
		exit(1);
	}
	fw = fopen(argv[2], "w");
	if (!fw) {						// argv[2]�� ���� �̸��� ������ �ִٸ� ������ ������ �ʰ� �����޽����� ����մϴ�
		printf("��� ���� �̸��� ������ �ֽ��ϴ�.\n");
		exit(1);
	}

	tree = avl_create();

	while (fscanf(fr, "%d", &input) != EOF) {			// �Է������� ������ fscanf()��  �̿��� �н��ϴ�.
		//while (avl_find(tree, input));
		avl_insert(tree, input);
		if (z == 0) firstval = input;
		fprintf(fw, "%d��° Ʈ�� : ", ++cnt);
		printTree(tree, fw);
		z = 1;
	}
	fclose(fr);

	delete(tree->root, firstval);
	fprintf(fw, "%d��° Ʈ�� : ", ++cnt);
	printTree(tree, fw);

	fclose(fw);
	return 0;
}


avl_tree_* avl_create() {		// ���ʷ� avl Ʈ���� malloc�� ���� ����ϴ�.
	avl_tree_* tree = NULL;
	if ((tree = malloc(sizeof(avl_tree_))) == NULL)
		return NULL;
	tree->root = NULL;
	return tree;
}

Avl_node* avl_create_node() {	// ���� �ڽĳ��� ������ �ڽĳ�尡 NULL�� avl ��带 �ϳ� ����ϴ�
	Avl_node* node = NULL;
	if ((node = malloc(sizeof(Avl_node))) == NULL) {
		return NULL;
	}
	node->left = NULL;
	node->right = NULL;
	node->key = 0;
	return node;
}

int avl_node_height(Avl_node* node) { // AVL ����� height�� recursive�ϰ� ã���ϴ�.
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
int find_balance_factor(Avl_node* node) {	// AVL ����� ���� ���� ������ ����� balance_factor�� ����մϴ�
	int balancefactor = 0;

	if (node->left) balancefactor += avl_node_height(node->left);
	if (node->right) balancefactor -= avl_node_height(node->right);

	return balancefactor;
}

Avl_node* avl_LL(Avl_node* node) {		// avl tree�� LeftLeft ȸ���մϴ�
	Avl_node* center = node;
	Avl_node* target = center->left;

	center->left = target->right;
	target->right = center;

	return(target);
}

Avl_node* avl_LR(Avl_node* node) {		// avl tree�� LeftRight ȸ���մϴ�
	Avl_node* center = node;
	Avl_node* target = center->left;
	Avl_node* source = target->right;

	center->left = source->right;
	target->right = source->left;
	source->left = target;
	source->right = center;

	return(source);
}

Avl_node* avl_RL(Avl_node* node) {		// avl tree�� RightLeft ȸ���մϴ�
	Avl_node* center = node;
	Avl_node* target = center->right;
	Avl_node* source = target->left;

	center->right = source->left;
	target->left = source->right;
	source->right = target;
	source->left = center;

	return(source);
}

Avl_node* avl_RR(Avl_node* node) {		// avl tree�� RightRight ȸ���մϴ�
	Avl_node* center = node;
	Avl_node* target = center->right;

	center->right = target->left;
	target->left = center;

	return(target);
}

Avl_node* get_balance(Avl_node* node) {		// node�� ������ ����ϴ�
	Avl_node* temp = NULL;

	if (node->left)							// .���� ���� �ڽ��� �ִٸ� ���� �ڽ��� ������ ���
		node->left = get_balance(node->left);
	if (node->right)						// ���� ������ �ڽ��� �ִٸ� ������ �ڽ��� ������ ����ϴ�.
		node->right = get_balance(node->right);

	int balance_F = find_balance_factor(node);

	if (balance_F >= 2) {					// ���� �����ڽİ� ������ �ڽ��� ���� ���̰� 2�̻��̶�� LR �Ǵ� LL�� �ǽ��մϴ�.
		if (find_balance_factor(node->left) <= -1)
			temp = avl_LR(node);
		else
			temp = avl_LL(node);
	}
	else if (balance_F <= -2) {				// ���� �����ڽİ� ������ �ڽ��� ���� ���̰� -2���϶�� RL �Ǵ� RR�� �ǽ��մϴ�.
		if (find_balance_factor(node->right) >= 1)
			temp = avl_RL(node);
		else
			temp = avl_RR(node);
	}
	else {									// �̹� ������ �����ִٸ�, �״�� node�� ��ȯ�մϴ�.
		temp = node;
	}

	return(temp);
}

void avl_balance(avl_tree_* tree) {			// Ʈ���� ������ ����ϴ�.
	Avl_node* temp = NULL;

	temp = get_balance(tree->root);
	if (temp != tree->root)
		tree->root = temp;
}

void avl_insert(avl_tree_* tree, int val) {		// Ʈ���� ���ο� ��带 �����մϴ�.
	Avl_node* node = NULL;
	Avl_node* new = NULL;
	Avl_node* on = NULL;

	if (tree->root == NULL) {						// root��忡 ���� ���ٸ� ��, NULL �̶�� ���ο� ��带 ���� Ʈ���� �־��ݴϴ�.
		node = avl_create_node();
		node->key = val;
		tree->root = node;
	}
	else {											// root ��尡 �ִٸ� Ʈ���� ��� �־������ �����մϴ�.
		new = tree->root;
		while (new != NULL) {
			on = new;

			if (val < new->key) {
				new = new->left;
			}
			else if (val > new->key) {				// val���� node�� key������ ũ�ٸ� ���ο� ����� ������ �ڽ����� ���ϴ�.
				new = new->right;
			}
		}
		node = avl_create_node();					// ���ο� ��带 ����ϴ�.
		node->key = val;							// ��忡 key������ val���� �ֽ��ϴ�.
		if (val < on->key) on->left = node;			// val���� node�� key������ �۴ٸ� ���ο� ����� ���� �ڽ����� ���ϴ�.
		if (val > on->key) on->right = node;		// val���� node�� key������ ũ�ٸ� ���ο� ����� ������ �ڽ����� ���ϴ�.

	}

	avl_balance(tree);
}

Avl_node* avl_find(avl_tree_* tree, int val) {		//  val���� ��ġ�ϴ� key�� ������ ��带 ã�Ƽ� ��ȯ�մϴ�.
	Avl_node* current = tree->root;

	while (current && current->key != val) {
		if (val > current->key)
			current = current->right;
		else
			current = current->left;
	}

	return current;
}

void avl_traverse_inorder(Avl_node* node, FILE* f) {	// Ʈ���� inorder traversal�ϸ鼭 Ʈ���� ��� key���� ����մϴ�.
	if (node) {
		avl_traverse_inorder(node->left,f);
		fprintf(f, "%d ", node->key);
		avl_traverse_inorder(node->right,f);
	}
}

void avl_traverse_preorder(Avl_node* node, FILE* f) {// Ʈ���� preorder traversal�ϸ鼭 Ʈ���� ��� key���� ����մϴ�.
	if (node) {
		fprintf(f, "%d ", node->key);
		avl_traverse_preorder(node->left, f);
		avl_traverse_preorder(node->right, f);
	}
}

void successor(Avl_node* node) {					// ������ ����Ʈ������ ���� ���� key�� minval�� �����մϴ�.
	if (node) {
		if (minval < node->key) minval = node->key;
		successor(node->left, NULL);
		successor(node->right, NULL);
	}
};

Avl_node* delete(Avl_node* root, int val)			// val�� ��ġ�ϴ� key�� ������ ��带 �����մϴ�.
{
	Avl_node* remove_node;
	minval = 0;
	if (root == NULL) {
		return root;
	}

	if (val < root->key) {							// ���� val���� node�� key�� �۴ٸ� ���� �ڽ����� �������ϴ�.
		root->left = delete(root->left, val);

	}
	else if (val > root->key) {						// ���� val���� node�� key�� �۴ٸ� ������ �ڽ����� �������ϴ�.
		root->right = delete(root->right, val);

	}
	else {
		if ((root->left == NULL) && (root->right != NULL)) {	// ���� �ڽ��� ����, ������ �ڽ��� �����Ұ��
			remove_node = root->right;
			*root = *remove_node;
		}
		else if ((root->right == NULL) && (root->left != NULL)) {	// ������ �ڽ��� ����, ���� �ڽ��� �����Ұ��
			remove_node = root->left;
			*root = *remove_node;

		}
		else if ((root->right == NULL) && (root->left == NULL)) {		// ������ �ڽ��� ����, ���� �ڽ��� �������
			remove_node = root;
			root = NULL;
		}
		else {													// �� �̿��� ���
			minval = root->right->key;
			successor(root->right);
			root->key = minval;
			root->right = delete(root->right, minval);
		}
	}

	if (root == NULL) {
		return root;

		find_balance_factor(root);

		if (find_balance_factor(root) >= 2) {	// ���� �����ڽİ� ������ �ڽ��� ���� ���̰� 2�̻��̶�� LR �Ǵ� LL�� �ǽ��մϴ�.
			if (find_balance_factor(root->left) <= -1) {
				return avl_LR(root);
			}
			else
				return avl_LL(root);
		}
		else if (find_balance_factor(root) <= -2) {	// ���� �����ڽİ� ������ �ڽ��� ���� ���̰� -2���϶�� RL �Ǵ� RR�� �ǽ��մϴ�.
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

void printTree(avl_tree_* tree, FILE* f) {			// inorder, preorder ��ȸ�� �ϸ鼭 �ش��ϴ� ����� ������Ͽ� �����մϴ�.
	fprintf(f, "\n");
	fprintf(f, "inorder  : ");
	avl_traverse_inorder(tree->root, f);
	fprintf(f, "\n");
	fprintf(f, "preorder : ");
	avl_traverse_preorder(tree->root, f);
	fprintf(f, "\n");
}

