#include <iostream>
#include <stdlib.h>
#include <time.h>
#define N 100

using namespace std;

struct Vertex
{
	int data;
	int number;
	Vertex* left;
	Vertex* right;
};

void FillInc (int* Arr, int n){
    int i;
    for (i=0; i<n; i++){
        Arr[i]=i+1;
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


void PrintTree_Left_Right(Vertex* p) {
	if (p != NULL) {
		PrintTree_Left_Right(p->left);
		cout << p->number << '(' << p->data << ") ";
		PrintTree_Left_Right(p->right);
	}
}

int TreeSize(Vertex* p){
	if (p==NULL) return 0;
	else return 1 + TreeSize(p->left) + TreeSize(p->right);
}

int Maximum(int x, int y){
	return x < y ? y : x;
}

int TreeHeight(Vertex* p){
	if(p==NULL) return 0;
	else return 1 + Maximum(TreeHeight(p->left), TreeHeight(p->right));
}

int SumOfPathLengths(Vertex* p, int L){
	if (p==NULL) return 0;
	else return L + SumOfPathLengths(p->left, L+1) + SumOfPathLengths(p->right, L+1);
}

int CheckSum(int Arr[], int n) {
	int i;
	int sum = 0;
	for (i = 0; i < n; i++) {
		sum += Arr[i];
	}
	return sum;
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

int main() {
	srand(time(NULL));
	Vertex* root = NULL, *p;
	int* Arr = new int[N];
	int num = 1;
	FillInc(Arr, N);
	root = ISDP(Arr, 0, N - 1, num);
	PrintTree_Left_Right(root);
	cout << "\n\n\nSums: \t" << CheckSum(Arr, N) << "\t" << CheckSumTree(root) << "\n\n\n";
	cout << "Size: \t" << TreeSize(root) << "\n\n\n";
	cout << "Height:\t" << TreeHeight(root) << "\n\n\n";
	cout << "SrHeight: " << ((float)SumOfPathLengths(root, 1))/TreeSize(root) << endl;
	delete[] Arr;
	FreeTree(root);
	system("pause");
	return 0;
}