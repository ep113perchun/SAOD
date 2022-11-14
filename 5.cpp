#include <iostream>
#include <cmath>
#include <clocale>
#include <ctime>
#include <iomanip>

using namespace std;

struct Vertex {
    int data;
    int number;
    Vertex *left;
    Vertex *right;
    int Balance;
} Root;
bool rost = true;
int ym = 1, VR = 1, HR = 1;
Vertex *q = new Vertex;

void BL(Vertex *&p);
void BR(Vertex *&p);
void LL1(Vertex *&p);
void RR1(Vertex *&p);
void DEL(Vertex *&r);
void DeleteAVL(Vertex *&p, int x);
void LL(Vertex *&p);
void RR(Vertex *&p);
void LR(Vertex *&p);
void RL(Vertex *&p);
void AddAVL(Vertex *&root, int D, int n);

void GenMas(int A[])
{
    int* Rand = new int[1000];
    for (int i = 0; i < 1000; i++) {
            Rand[i] = i;
    }

    for (int j = 0; j < 100; j++) {
        int i = rand() % 1000;
        while (Rand[i] == 0) {
            i = i + 1;
            if (i == 1000) i = 0;
        }
        A[j] = Rand[i];
        Rand[i] = 0;
    }
}

int cnt = 1;
void obhod(Vertex* p)
{
    if (p != NULL) {
        obhod(p->left);
        if (cnt % 5 == 0){
            cout << p->number << "(" << p->data << ")" <<"  ";
            cnt++;
        } else{
            cout << p->number << "(" << p->data << ")" <<"  ";
            cnt++;
        }
      //  cout << p->number << "(" << p->data << ")" <<"  ";
        obhod(p->right);
    }
}

int main()
{
    Vertex* root;
    srand(time(NULL));
    int *A = new int [100];
    GenMas(A);

    root = NULL;    
    for (int i = 0; i < 10; i++) {
        AddAVL(root, A[i], i+1);
    }

    int key;
    obhod(root);
    cout << endl;
    for (int i = 0; i < 10; i++) {
        cout << "[Delete] Input key" << endl;  
        cin >> key;
        DeleteAVL(root, key);
        cout << "Vertex deleted !" << endl;
        obhod(root);
        cout << endl;
    }
}





void BL(Vertex *&p) {
    if (p->Balance == -1) {
        p->Balance = 0;
    } else if (p->Balance == 0) {
        p->Balance = 1;
        ym = 0;
    } else if (p->Balance == 1) {
        if (p->right->Balance >= 0) {
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
        if (p->left->Balance <= 0) {
            LL1(p);
        } else {
            LR(p);
        }
    }
}

void LL1(Vertex *&p) {
    Vertex *q;
    q = p->left;
    if (q->Balance == 0) {
        q->Balance = 1;
        p->Balance = -1;
        ym = 0;
    } else {
        q->Balance = 0;
        p->Balance = 0;
    }
    p->left = q->right;
    q->right = p;
    p = q;
}

void RR1(Vertex *&p) {
    Vertex *q;
    q = p->right;
    if (q->Balance == 0) {
        q->Balance = -1;
        p->Balance = 1;
        ym = 0;
    } else {
        q->Balance = 0;
        p->Balance = 0;
    }
    p->right = q->left;
    q->left = p;
    p = q;
}

void DEL(Vertex *&r) {
    if (r->right != NULL) {
        DEL(r->right);
        if (ym == 1) {
            BR(r);
        }
    } else {
        q->data = r->data;
        q = r;
        r = r->left;
        ym = 1;
    }
}

void DeleteAVL(Vertex *&p, int x) {
    if (p == NULL) {
        cout << "not found";
    } else if (x < p->data) {
        DeleteAVL(p->left, x);
        if (ym == 1) {
            BL(p);
        }
    } else if (x > p->data) {
        DeleteAVL(p->right, x);
        if (ym == 1) {
            BR(p);
        }
    } else {
        q = p;
        if (q->left == NULL) {
            p = q->right;
            ym = 1;
        } else if (q->right == NULL) {
            p = q->left;
            ym = 1;
        } else {
            DEL(q->left);
            if (ym == 1) {
                BL(p);
            }
        }
        free(q);
    }
}

void LL(Vertex *&p) {
    Vertex *q;
    q = p->left;
    p->Balance = 0;
    q->Balance = 0;
    p->left = q->right;
    q->right = p;
    p = q;
}

void RR(Vertex *&p) {
    Vertex *q;
    q = p->right;
    p->Balance = 0;
    q->Balance = 0;
    p->right = q->left;
    q->left = p;
    p = q;
}

void LR(Vertex *&p) {
    Vertex *q = p->left;
    Vertex *r = q->right;
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
    q->right = r->left;
    p->left = r->right;
    r->left = q;
    r->right = p;
    p = r;
}

void RL(Vertex *&p) {
    Vertex *q = p->right;
    Vertex *r = q->left;
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
    q->left = r->right;
    p->right = r->left;
    r->right = q;
    r->left = p;
    p = r;
}

void AddAVL(Vertex *&root, int D, int n) {
    if (root == NULL) {
        root = new Vertex;
        root->data = D;
        root->number = n; 
        root->left = NULL;
        root->right = NULL;
        root->Balance = 0;

        rost = true;
    } else if (root->data > D) {
        AddAVL(root->left, D, n);

        if (rost == true) {
            if (root->Balance > 0) {
                root->Balance = 0;
                rost = false;
            } else if (root->Balance == 0) {
                root->Balance = -1;
                rost = true;
            } else {
                if (root->left->Balance < 0) {
                    LL(root);
                    rost = false;
                } else {
                    LR(root);
                    rost = false;
                }
            }
        }
    } else if (root->data < D) {
        AddAVL(root->right, D, n);

        if (rost == true) {
            if (root->Balance < 0) {
                root->Balance = 0;
                rost = false;
            } else if (root->Balance == 0) {
                root->Balance = 1;
                rost = true;
            } else {
                if (root->right->Balance > 0) {
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