#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstdio>
#define N 100

using namespace std;

struct Vertex
{
	int data;
	int number;
	Vertex* left;
	Vertex* right;
};

void FillRand(int* Arr, int n) {
	int i;
	for (i = 0; i < n; i++) {
		Arr[i] = rand() % 201 - 100;
	}
}

void FillInc(int* Arr, int n) {
	int i;
	for (i = 0; i < n; i++) {
		Arr[i] = i + 1;
	}
}

Vertex* ISDP(int *A, int L, int R, int& num) {
	int m;
	if (L > R) return NULL;
	else {
		m = (L + R + 1) / 2;
		Vertex* p = new Vertex;
		p->data = A[m];
		p->number = num++;
		p->left = ISDP(A, L, m - 1, num);
		p->right = ISDP(A, m + 1, R, num);
		return p;
	}
}

void SDP(int D, Vertex*& root, int& num) {
	Vertex** p = &root;
	while ((*p) != NULL) {
		if (D < (*p)->data) p = &((*p)->left);
		else if (D > (*p)->data) p = &((*p)->right);
		else break;
	}
	if ((*p) == NULL) {
		(*p) = new Vertex;
		(*p)->data = D;
		(*p)->number = num++;
		(*p)->left = (*p)->right = NULL;
	}
}

void SDP2(int D, Vertex*& p, int& num) {
	if (p == NULL) {
		p = new Vertex;
		p->data = D;
		p->number = num++;
		p->right = p->left = NULL;
	}
	else if (D < p->data) SDP2(D, p->left, num);
	else if (D > p->data) SDP2(D, p->right, num);
}

void PrintTree_Left_Right(Vertex* p) {
	if (p != NULL) {
		PrintTree_Left_Right(p->left);
		cout << p->number << '(' << p->data << ") ";
		PrintTree_Left_Right(p->right);
	}
}

int TreeSize(Vertex* p) {
	if (p == NULL) return 0;
	else return 1 + TreeSize(p->left) + TreeSize(p->right);
}

int Maximum(int x, int y) {
	return x < y ? y : x;
}

int TreeHeight(Vertex* p) {
	if (p == NULL) return 0;
	else return 1 + Maximum(TreeHeight(p->left), TreeHeight(p->right));
}

int SumOfPathLengths(Vertex* p, int L) {
	if (p == NULL) return 0;
	else return L + SumOfPathLengths(p->left, L + 1) + SumOfPathLengths(p->right, L + 1);
}

int CheckSumTree(Vertex* p) {
	if (p == NULL) return 0;
	else return p->data + CheckSumTree(p->left) + CheckSumTree(p->right);
}

void FreeTree(Vertex* tree) {
	if (tree->left)   FreeTree(tree->left);
	if (tree->right)  FreeTree(tree->right);
	delete tree;
}

void Table(Vertex* a, Vertex* b) {
	int i;
	cout << "\n\n";
	cout << "\n|------|-----|------|----|------|";
	cout << "\n|      |     |      |    |      |";
	printf("\n|%-6s| %-4d| %-5d| %-3d| %-5.2f|", " ISDP", TreeSize(b), CheckSumTree(b), TreeHeight(b), ((float)SumOfPathLengths(b, 1)) / TreeSize(b));
	cout << "\n|      |     |      |    |      |";
	cout << "\n|------|-----|------|----|------|";
	cout << "\n|      |     |      |    |      |";
	printf("\n|%-6s| %-4d| %-5d| %-3d| %-5.2f|", " SDP", TreeSize(a), CheckSumTree(a), TreeHeight(a), ((float)SumOfPathLengths(a, 1)) / TreeSize(a));
	cout << "\n|      |     |      |    |      |";
	cout << "\n|------|-----|------|----|------|\n\n";
}

int main() {
	srand(time(NULL));
	int* Arr = new int[N];
	int* Arr2 = new int[N];
	FillRand(Arr, N);
	FillInc(Arr2, N);
	int i, num = 1;
	Vertex* root = NULL, *root2 = NULL, *root3 = NULL;
	for (i = 0; i < N; i++) {
		SDP(Arr[i], root, num);
	}
	num = 1;
	FillRand(Arr, N);
	for (i = 0; i < N; i++) {
		SDP2(Arr[i], root2, num);
	}
	cout << "SDP" << endl;
	PrintTree_Left_Right(root);
	cout << "\n\n\nReckSDP:" << endl;
	PrintTree_Left_Right(root2);
	num = 1;
	root3 = ISDP(Arr2, 0, N - 1, num);
	Table(root, root3);
	delete[] Arr;
	delete[] Arr2;
	FreeTree(root);
	FreeTree(root2);
	FreeTree(root3);
	system("pause");
	return 0;
}