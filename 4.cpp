#include <iostream>
#include <ctime>
#include <iomanip>

using namespace std;

struct Vertex {
    int number;
    int Data;
    int Bal;
    Vertex* Left;
    Vertex* Right;
};
Vertex* RootS;
Vertex* RootA;
bool rost;

void LL(Vertex *&p)
{
    Vertex *q = p->Left;
    p->Bal = 0;
    q->Bal = 0;
    p->Left = q->Right;
    q->Right = p;
    p = q;
}

void RR(Vertex *&p)
{
    Vertex *q = p->Right;
    p->Bal = 0;
    q->Bal = 0;
    p->Right = q->Left;
    q->Left = p;
    p = q;
}

void LR(Vertex *&p)
{
    Vertex *q = p->Left;
    Vertex *r = q->Right;
    if(r->Bal < 0) p->Bal = 1;
    else p->Bal = 0;
    if(r->Bal > 0) q->Bal = -1;
    else q->Bal = 0;
    r->Bal = 0;
    q->Right = r->Left;
    p->Left = r->Right;
    r->Left = q;
    r->Right = p;
    p = r;
}

void RL(Vertex *&p)
{
    Vertex *q = p->Right;
    Vertex *r = q->Left;
    if(r->Bal > 0) p->Bal = -1;
    else p->Bal = 0;
    if(r->Bal < 0) q->Bal = 1;
    else q->Bal = 0;
    r->Bal = 0;
    q->Left = r->Right;
    p->Right = r->Left;
    r->Left = p;
    r->Right = q;
    p = r;
}

void addAVL(int D, Vertex *&p, int n)
{
    if(p == NULL){
        p = new Vertex;
        p->Data = D;
        p->number = n;
        p->Left = NULL;
        p->Right = NULL;
        p->Bal = 0;
        rost = true;
    } else if(p->Data > D){
        addAVL(D, p->Left, n);
        if (rost == true){
            if (p->Bal > 0){
                p->Bal = 0;
                rost = false;
            }else if(p->Bal == 0){
                p->Bal = -1;
                rost = true;
            }else {
                if (p->Left->Bal < 0){
                    LL(p);
                    rost = false;
                }else {
                    LR(p);
                    rost = false;
                }
            }
        }
    } else if (p->Data < D){
        addAVL(D, p->Right, n);
        if (rost == true){
            if(p->Bal < 0){
                p->Bal = 0;
                rost = false;
            } else if (p->Bal == 0){
                p->Bal = 1;
                rost = true;
            } else {
                if(p->Right->Bal > 0){
                    RR(p);
                    rost = false;
                }else{
                    RL(p);
                    rost = false;
                }
            }
        }
    } else cout << "Vertex already in tree!";
}

int MakeSDP(Vertex *&root, int D, int n) {
    if (root == NULL) {
        root = new Vertex;
        root->number = n;
        root->Data = D;
        root->Left = NULL;
        root->Right = NULL;
    } else if (root->Data < D) {
        MakeSDP(root->Right, D, n);
    } else if (root->Data > D) {
        MakeSDP(root->Left, D, n);
    } else return 1;
    return 0;
}

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
        obhod(p->Left);
        if (cnt % 5 == 0){
            cout <<p->number <<":" << p->Data << "  ";
            cnt++;
        } else{
            cout <<p->number <<":" << p->Data << "   ";
            cnt++;
        }
        
        obhod(p->Right);
    }
}


int treeSize(Vertex* p)
{
    int n = 0;
    if (p == NULL) n = 0;
    else {
        n = 1 + treeSize(p->Left) + treeSize(p->Right);
    }
    return n;
}

int checkSum(Vertex* p)
{
    int s = 0;
    if (p == NULL) s = 0;
    else {
        s = p->Data + checkSum(p->Left) + checkSum(p->Right);
    }
    return s;
}

int treeHeight(Vertex* p)
{
    int h = 0;
    if (p == NULL) h = 0;
    else {
        h = 1 + max(treeHeight(p->Left), treeHeight(p->Right));
    }
    return h;
}

int sumWays(Vertex* p, int L)
{
    int s = 0;
    if (p == NULL) s = 0;
    else {
        s = L + sumWays(p->Left, L + 1) + sumWays(p->Right, L + 1);
    }
    return s;
}

void cpy(int a[], int b[])
{
    for (int i = 0; i < 100; i++){
        b[i] = a[i];
    }
}

int main()
{
    srand(time(NULL));
    int size_of_treeS;
    int check_sumS;
    int height_of_treeS;
    float average_heightS;

    int size_of_treeA;
    int check_sumA;
    int height_of_treeA;
    float average_heightA;

    
    int *AS = new int[100];
    int *AA = new int [100];
    GenMas(AS);
    cpy(AS, AA);

    RootS = NULL;    
    for (int i = 0; i < 100; i++) {
        MakeSDP(RootS, AS[i], i+1);
    }

    RootA = NULL;    
    for (int i = 0; i < 100; i++) {
        addAVL(AA[i], RootA, i+1);
    }

    obhod(RootA);
    
    cout << endl;

    size_of_treeS = treeSize(RootS);
    check_sumS = checkSum(RootS);
    height_of_treeS = treeHeight(RootS);
    average_heightS = (float)sumWays(RootS, 1) / (float)size_of_treeS;

    size_of_treeA = treeSize(RootA);
    check_sumA = checkSum(RootA);
    height_of_treeA = treeHeight(RootA);
    average_heightA = (float)sumWays(RootA, 1) / (float)size_of_treeA;

    cout << "n = 100|   " << "size|     " << "checksum|       " << "height| " << "average_height|   " << endl;
    cout << "AVL    |" << setw(7)  << size_of_treeA << "|" << setw(13) << check_sumA <<  "|" << setw(13) << height_of_treeA <<  "|" << setw(15) << average_heightA <<  "|"  << endl;
    cout << "SDP    |" << setw(7)  << size_of_treeS << "|" << setw(13)  << check_sumS << "|" << setw(13) << height_of_treeS <<  "|" << setw(15) << average_heightS <<  "|"  << endl;

    getchar();getchar();
}