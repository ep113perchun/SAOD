#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <sstream>
#include <time.h>

using namespace std;

int N = 10;
int id = 1;
int posOnLine = 1;
bool rost;

// --------------------------------------
//| Vertex
// --------------------------------------

struct Vertex {
    int Data;
    int iD;
    int Balance;
    int x;
    int y;
    Vertex *Left;
    Vertex *Right;
};

// --------------------------------------
//| Parametrs for tree
// --------------------------------------

int controlSumm(Vertex *p);
int size(Vertex * p);
int height(Vertex * p);
int sumOfPathLengths(Vertex *p, int L);
int averageHeight(Vertex *p);

// --------------------------------------
//| SDP
// --------------------------------------

void RST(Vertex *&Root, int *D, int N);
void addRST2(Vertex *&p, int D);
void RST2(Vertex *&Root, int *D, int N);

void Delete_Vertex(int key, Vertex*&Root);

// --------------------------------------
//| 
// --------------------------------------

void printTree(Vertex *p);
void PrintTree_Up_Down(Vertex* p)
void checkLine(Vertex *T, int l, int flag); // ohod dlY numeracii
void addNums(Vertex *tree, int height); // num po shirine
void up(Vertex *tree, int height);

// --------------------------------------
//| Fiill array
// --------------------------------------

int* FillInc(int N);
int* FillDec(int N);
int* FillRand(int N);
void GenMas(int A[]);

// --------------------------------------
//| Print/Sort array
// --------------------------------------

void printArr(int *arr, int N);
int* SortArr(int *arr, int N);

int main()
{
	srand(time(NULL));
	
	
	int v;
 	
    int* arr = new int[N];
    
    GenMas(arr);
    
    printArr(arr, N);
        
    /* AVL tree */
        
	Vertex* tree2 = NULL;

	RST(tree2, arr, N);

	addNums(tree2, height(tree2));
	
	while (true) {
		cout << "SDP: ";
		printTree(tree2);
	    cout << endl;
	    cout << "Enter Vertex:  ";
	    cin >> v;
	    Delete_Vertex(v, tree2);
		addNums(tree2, height(tree2));
	}
    
	return 0;
}

// --------------------------------------
//| All realization
// --------------------------------------

void RST(Vertex *&Root, int *D, int N) {
	for (int i = 0; i < N; i++) {
		Vertex **p = &Root;
		while (*p != NULL) {
			if (D[i] < (*p)->Data) p = &((*p)->Left);
			else if (D[i] > (*p)->Data) p = &((*p)->Right);
			else break;
		}
		if (*p == NULL) {
			*p = new Vertex;
			(*p)->Data = D[i];
			(*p)->Left = NULL;
			(*p)->Right = NULL;
		}
	}
}

void PrintTree_Up_Down(Vertex* p) {
	if (p != NULL) {
		cout << "(" << p->iD << ")" << p->data << " ";
		PrintTree_Up_Down(p->left);
		PrintTree_Up_Down(p->right);
	}

void addRST2(Vertex *&p, int D) {
	if (p == NULL) {
		p = new Vertex;
		p->Data = D;
		p->Left = NULL;
		p->Right = NULL;
	} else if (D < p->Data) addRST2(p->Left, D);
		else if (D > p->Data) addRST2(p->Right, D);
}

void RST2(Vertex *&Root, int *D, int N) {
	for (int i = 0; i < N; i++) {
		addRST2(Root, D[i]);
	}
}

int controlSumm(Vertex *p) {
    if (p==NULL) return 0;
    return p->Data + controlSumm(p->Left) + controlSumm(p->Right);
}

int size(Vertex * p) {
    if (p==NULL) return 0;
    return 1 + size(p->Left) + size(p->Right);
}

int height(Vertex * p) {
    if (p==NULL) return 0;
    return 1 + max(height(p->Left), height(p->Right));
}

int sumOfPathLengths(Vertex *p, int L) {
    if (p==NULL) return 0;
    return L + sumOfPathLengths(p->Left, L+1) + sumOfPathLengths(p->Right, L+1);
}

int averageHeight(Vertex *p) {
    return sumOfPathLengths(p, 1) / size(p);
}

void printTree(Vertex *p) {
    if (p!=NULL) {
        printTree(p->Left);
        cout << "("<< p->iD << ")" << p->Data << " ";
        printTree(p->Right);
    }
}

void checkLine(Vertex *T, int l, int flag) {
	if (T==NULL) {}
	else if(l == 0) {
		if (flag == 1) T->iD = id++;
		else cout << "("<< T->iD << ")" << T->Data << " ";
	} else {
		checkLine(T->Left, l-1, flag);
		checkLine(T->Right, l-1, flag);
	}
}

void addNums(Vertex *tree, int height) {
	for(int i = 0; i < height; i++) {
		checkLine(tree, i, 1);
	}
}

void up(Vertex *tree, int height) {
	for(int i = height - 1; i >= 0; i--) {
		checkLine(tree, i, 0);
	}
}

int* FillInc(int N) {
    int* arr = new int[N];
    for (int i = 0; i < N; i++)
        arr[i] = i + 1;
    return arr;
}

int* FillDec(int N) {
    int* arr = new int[N];
    for (int i = 0; i < N; i++)
    {
    	arr[i] = N - i;
	}
    return arr;
}

int* FillRand(int N) {
    int* arr = new int[N];
    for (int i = 0; i < N; i++)
        {
        	arr[i] = rand() % 100;
		}
    return arr;
}

void printArr(int *arr, int N) {
	for (int i = 0; i < N; i++) {
		cout << arr[i] << "  ";
	}
	cout << endl;
	cout << endl;
}

int* SortArr(int *arr, int N) {
	int *Arr = new int[N];
	for (int i = 0; i < N; i++) {
		Arr[i] = arr[i];
	}
	for (int i = 0; i < N - 1; i++) {
		for (int j = N - 1; j > i; j--) {
			if (Arr[j] < Arr[j - 1]) {
				int buf = Arr[j];
				Arr[j] = Arr[j - 1];
				Arr[j - 1] = buf;
			}
		}
	}
	return Arr;
}

void GenMas(int A[]){
	int* Rand = new int[1000];
	for (int i = 0; i < 1000; i++) {
		Rand[i] = i;
	}
    for (int j = 0; j < N; j++) {
	    int i = rand() % 1000;
	    while (Rand[i] == 0) {
	        i = i + 1;
	        if (i == 1000) i = 0;
	    }
	A[j] = Rand[i];
	Rand[i] = 0;
    }
}

void Delete_Vertex(int key, Vertex*&Root) {
   Vertex** p = &Root;
   while (*p != NULL) {
       if (key < (*p)->Data) p = &((*p)->Left);
       else if (key > (*p)->Data) p = &((*p)->Right);
       else break;
   }
   if (*p != NULL) {
       Vertex* q = *p;
       if (q->Left == NULL) *p = q->Right;
       else if (q->Right == NULL) *p = q->Left;
       else { Vertex* r; Vertex* s; 
       r = q->Left;
       s = q;
       if (r->Right) {
           r->Right = q->Right;
           *p = r;
       }
       else {
           while (r->Right != NULL) {
               s = r;
               r = r->Right;
           }
           s->Right = r->Left;
           r->Left = q->Left;
           r->Right = q->Right;
           *p = r;
       }
       }
       delete(q);
   }else printf("Vertex not found, try again\n\n");
   
}

