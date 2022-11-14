#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <sstream>
#include <time.h>

using namespace std;

int N = 100;
int ym = 1;
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

Vertex *q = new Vertex;

// --------------------------------------
//| Get string
// --------------------------------------

string to_str(int a);

// --------------------------------------
//| Parametrs for tree
// --------------------------------------

int controlSumm(Vertex *p);
int size(Vertex * p);
int height(Vertex * p);
int sumOfPathLengths(Vertex *p, int L);
float averageHeight(Vertex *p);

// --------------------------------------
//| ISDP
// --------------------------------------

Vertex* PBST(int *arr, int L, int R);

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
void checkLine(Vertex *T, int l, int flag);
void addNums(Vertex *tree, int height);
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

// --------------------------------------
//| AVL rotates for add
// --------------------------------------

void LL(Vertex *&p);
void RR(Vertex *&p);
void LR(Vertex *&p);
void RL(Vertex *&p);

// --------------------------------------
//| AVL add
// --------------------------------------

void AddAVL(Vertex *&root, int D);
void AVL(Vertex *&Root, int *D, int N);

// --------------------------------------
//| AVL rotates for delete
// --------------------------------------

void LL1(Vertex *&p);
void RR1(Vertex *&p);
void BL(Vertex *&p);
void BR(Vertex *&p);
 
// --------------------------------------
//| AVL delete
// --------------------------------------
 
void DEL(Vertex *&r);
void DeleteAVL(Vertex *&p, int x);

// --------------------------------------
//| DBD delete
// --------------------------------------
 
bool B2INSERT(Vertex *& p, int data , bool &VR,bool &HR){
  if (p == NULL){
    p = new Vertex;
    p->Data = data;
    p->Left = p->Right = NULL;
    p->Balance = false;
    VR = true;
  }
  else if (p->Data > data){
    if(B2INSERT(p->Left, data, VR, HR)){
      if (VR){
        if (!p->Balance){
          Vertex * q = p->Left;
          p->Left = q->Right;
          q->Right = p;
          p = q;
          q->Balance = true;
          VR = false;
          HR = true;
        }
        else{
          p->Balance = false;
          VR = true;
          HR = false;
        }
      }
      else
        HR = false;
    }
    else 
      return false;
  }
  else if (p->Data < data)
  {
    if(B2INSERT(p->Right, data, VR, HR)){
      if (VR){
        p->Balance = true;
        HR = true;
        VR = false;
      }
      else if (HR)
      {
        if (p->Balance){
          Vertex * q = p->Right;
          p->Balance = false;
          q->Balance = false;
          p->Right = q->Left;
          q->Left = p;
          p = q;
          VR = true;
          HR = false;
        }
        else
          HR = false;
      }
    }
    else 
      return false;
  }
  else 
    return false;
  return true;
}

Vertex *createDBD(int *n, bool &VR, bool &HR, bool log) {
  Vertex *root = NULL;
	for( int i = 0; i < N; i++) {
		int data = n[i];
	    if (B2INSERT(root, data, VR, HR)) {
	    	
		}
	    else if (log)
	      std::cout << "\t\t /* ������ � ������ \"" << data
                << "\" ��� ���� � ������ */" << std::endl;
	}
  return root;
}

// --------------------------------------
//| MAIN
// --------------------------------------

int main()
{
	srand(time(NULL));
	
	
	int v;
 	
    int* arr = new int[N];
    
    GenMas(arr);
    
    cout << "--------------------------------------------------------------------------------" <<endl;
	cout << "Arr: ";
    printArr(arr, N);
        
    /* DBD tree */
    
    bool HR= true;
	bool VR= true; 
    
    Vertex* tree = createDBD(arr, VR, HR, 0);
	
	addNums(tree, height(tree));
	id = 1;
    
    cout << "--------------------------------------------------------------------------------" <<endl;
	cout << "DBD: ";
	printTree(tree);
	cout << endl;
    
    /* AVL tree */
    
	Vertex* tree2 = NULL;
	
	AVL(tree2, arr, N); 

	addNums(tree2, height(tree2));
	
	cout << "--------------------------------------------------------------------------------" <<endl;
	cout << "AVL: ";
	printTree(tree2);
    cout << endl;
    
    /* Table */
    
    int cs = controlSumm(tree);
    float ah = averageHeight(tree);
    int h = height(tree);
    int s = size(tree);
    
	int cs2 = controlSumm(tree2);
    float ah2 = averageHeight(tree2);
    int h2 = height(tree2);
    int s2 = size(tree2);
    
 	cout << "\n\n N = " << N <<  "  |  size  |	controlSumm    |  height |  averageHeight" << endl;
    cout << "   AVL   |   " << s2 << "   |      " <<  cs2 << "          |     "  << h2 << "   |    " << ah2 << endl;
    cout << "   DBD   |   " << s  << "   |      " <<  cs  << "          |     "  << h  << "   |    " << ah  << endl;
    
    
	return 0;
}

// --------------------------------------
//| All realization
// --------------------------------------

string to_str(int a) {
	stringstream ss;
	ss << a;
	string str = ss.str();
	return str;
}

Vertex* PBST(int *arr, int L, int R) {
    if (L > R)
        return NULL;
    int m = (L + R) / 2;
    if ((L + R) % 2 != 0)
    	m++;
    Vertex *p = new struct Vertex;
    p->Data = arr[m];
    p->Left = PBST(arr, L, m-1);
    p->Right = PBST(arr, m+1, R);
    return p;
}

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

float averageHeight(Vertex *p) {
    return (float)sumOfPathLengths(p, 1) / (float)size(p);
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

void LL(Vertex *&p) {
    Vertex *q;
    q = p->Left;
    p->Balance = 0;
    q->Balance = 0;
    p->Left = q->Right;
    q->Right = p;
    p = q;
}
 
void RR(Vertex *&p) {
    Vertex *q;
    q = p->Right;
    p->Balance = 0;
    q->Balance = 0;
    p->Right = q->Left;
    q->Left = p;
    p = q;
}
 
void LR(Vertex *&p) {
    Vertex *q = p->Left;
    Vertex *r = q->Right;
    if (r->Balance < 0) {
        p->Balance = 1;
    } else {
        p->Balance = 0;
    }
    if (r->Balance > 0) {
        q->Balance = -1;
    } else {
        q->Balance = 0;
    }
    r->Balance = 0;
    q->Right = r->Left;
    p->Left = r->Right;
    r->Left = q;
    r->Right = p;
    p = r;
}
 
void RL(Vertex *&p) {
    Vertex *q = p->Right;
    Vertex *r = q->Left;
    if (r->Balance > 0) {
        p->Balance = -1;
    } else {
        p->Balance = 0;
    }
    if (r->Balance < 0) {
        q->Balance = 1;
    } else {
        q->Balance = 0;
    }
    r->Balance = 0;
    q->Left = r->Right;
    p->Right = r->Left;
    r->Right = q;
    r->Left = p;
    p = r;
}

void AddAVL(Vertex *&root, int D) {
    
	if (root == NULL) {
        root = new Vertex;
        root->Data = D;
        root->Left = NULL;
        root->Right = NULL;
        root->Balance = 0;
 
        rost = true;
    } else if (root->Data > D) {
        AddAVL(root->Left, D);
 
        if (rost == true) {
            if (root->Balance > 0) {
                root->Balance = 0;
                rost = false;
            } else if (root->Balance == 0) {
                root->Balance = -1;
                rost = true;
            } else {
                if (root->Left->Balance < 0) {
                    LL(root);
                    rost = false;
                } else {
                    LR(root);
                    rost = false;
                }
            }
        }
    } else if (root->Data < D) {
        AddAVL(root->Right, D);
 
        if (rost == true) {
            if (root->Balance < 0) {
                root->Balance = 0;
                rost = false;
            } else if (root->Balance == 0) {
                root->Balance = 1;
                rost = true;
            } else {
                if (root->Right->Balance > 0) {
                    RR(root);
                    rost = false;
                } else {
                    RL(root);
                    rost = false;
                }
            }
        }
    }
}

void AVL(Vertex *&Root, int *D, int N) {
	for (int i = 0; i < N; i++) {
		AddAVL(Root, D[i]);
	}
	cout << endl;
}

void LL1(Vertex *&p) {
    Vertex *q;
    q = p->Left;
    if (q->Balance == 0) {
        q->Balance = 1;
        p->Balance = -1;
        ym = 0;
    } else {
        q->Balance = 0;
        p->Balance = 0;
    }
    p->Left = q->Right;
    q->Right = p;
    p = q;
}
 
void RR1(Vertex *&p) {
    Vertex *q;
    q = p->Right;
    if (q->Balance == 0) {
        q->Balance = -1;
        p->Balance = 1;
        ym = 0;
    } else {
        q->Balance = 0;
        p->Balance = 0;
    }
    p->Right = q->Left;
    q->Left = p;
    p = q;
}

void BL(Vertex *&p) {
    if (p->Balance == -1) {
        p->Balance = 0;
    } else if (p->Balance == 0) {
        p->Balance = 1;
        ym = 0;
    } else if (p->Balance == 1) {
        if (p->Right->Balance >= 0) {
            RR1(p);
        } else {
            RL(p);
        }
    }
}
 
void BR(Vertex *&p) {
    if (p->Balance == 1) {
        p->Balance = 0;
    } else if (p->Balance == 0) {
        p->Balance = -1;
        ym = 0;
    } else if (p->Balance == -1) {
        if (p->Left->Balance <= 0) {
            LL1(p);
        } else {
            LR(p);
        }
    }
}
 
void DEL(Vertex *&r) {
    if (r->Right != NULL) {
        DEL(r->Right);
        if (ym == 1) {
            BR(r);
        }
    } else {
        q->Data = r->Data;
        q = r;
        r = r->Left;
        ym = 1;
    }
}
 
void DeleteAVL(Vertex *&p, int x) {
    if (p == NULL) {
        cout << "-+-+-+-+-   Vertex not found   -+-+-+-+-" << endl;;
    } else if (x < p->Data) {
        DeleteAVL(p->Left, x);
        if (ym == 1) {
            BL(p);
        }
    } else if (x > p->Data) {
        DeleteAVL(p->Right, x);
        if (ym == 1) {
            BR(p);
        }
    } else {
        q = p;
        if (q->Left == NULL) {
            p = q->Right;
            ym = 1;
        } else if (q->Right == NULL) {
            p = q->Left;
            ym = 1;
        } else {
            DEL(q->Left);
            if (ym == 1) {
                BL(p);
            }
        }
        free(q);
    }
}
