#include <iostream>

using namespace std;

struct Vertex
{
	int iD;
	int data;
	Vertex* left;
	Vertex* right;
};

struct Vertex* addtree(int datatree, int iD){
	struct Vertex *p;
  	p=new Vertex;
  	p->iD= iD;
  	p->data=datatree;
  	p->left=NULL;
  	p->right=NULL;
  	return p;
	
}

Vertex* tree(){
	Vertex *p=addtree(5,1);
	p->left=addtree(4,2);
	p->right=addtree(8,3);
	p->left->left=addtree(3,4);
    p->right->left=addtree(7,5);
	p->right->right=addtree(9,6);
    return p;
}

void PrintTree_Left_Right(Vertex* p) {
	if (p != NULL) {
		PrintTree_Left_Right(p->left);
		cout << "(" << p->iD << ")" << p->data << " ";
		PrintTree_Left_Right(p->right);
	}
}

void PrintTree_Up_Down(Vertex* p) {
	if (p != NULL) {
		cout << "(" << p->iD << ")" << p->data << " ";
		PrintTree_Up_Down(p->left);
		PrintTree_Up_Down(p->right);
	}
}

void PrintTree_Down_Up(Vertex* p) {
	if (p != NULL) {
		PrintTree_Down_Up(p->left);
		PrintTree_Down_Up(p->right);
		cout << "(" << p->iD << ")" << p->data << " ";
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
	Vertex* root = tree();
	cout << "Obhod Left-Right:" << endl;
	PrintTree_Left_Right(root);
	cout << "\n\nObhod Up-Down:" << endl;
	PrintTree_Up_Down(root);
	cout << "\n\nObhod Down-Up:" << endl;
	PrintTree_Down_Up(root);
	cout << "\n\n\nSums: \t" << CheckSumTree(root) << "\n\n\n";
	cout << "Size: \t" << TreeSize(root) << "\n\n\n";
	cout << "Height:\t" << TreeHeight(root) << "\n\n\n";
	cout << "SrHeight: " << ((float)SumOfPathLengths(root, 1))/TreeSize(root) << endl;
	FreeTree(root);
	cout << endl;
}