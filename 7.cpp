#include <iostream>
#include <ctime>

#include <cstdlib>

using namespace std;

int id = 1;

struct tree {
  int data;
  int weight;
  int iD;
  tree *left = NULL;
  tree *right = NULL;
};

/* swap */

void swap(int* a, int* b)
{
    int temp;
    temp = *a;
    *a = *b;
    *b = temp;
}

/* ��������� ������ */

void checkLine(tree *T, int l, int flag) {
	if (T==NULL) {}
	else if(l == 0) {
		if (flag == 1) T->iD = id++;
		else cout << "("<< T->iD << ")" << T->data << " ";
	} else {
		checkLine(T->left, l-1, flag);
		checkLine(T->right, l-1, flag);
	}
}

void addNums(tree *tree, int height) {
	for(int i = 0; i < height; i++) {
		checkLine(tree, i, 1);
	}
}



/* ������ ������ */
int sizeTree(tree *p, bool root) {
//   if (root) {}
//     // std::cout << std::endl << "The size of the tree: ";
  if (p == NULL)
    return 0;
  else
    return (1 + sizeTree(p->left, 0) + sizeTree(p->right, 0));
}

/* ����������� ����� ������ */
int checkSumTree(tree *p, bool root) {
//   if (root)
//     std::cout << std::endl << "The checksum tree: ";
  if (p == NULL)
    return 0;
  else
    return (p->data + checkSumTree(p->left, 0) + checkSumTree(p->right, 0));
}

/* ����� ���� ��������� ������ */
int sumOfPathLengths(tree *p, int depth, bool root) {
//   if (root)
//     std::cout << std::endl
//               << "The sum of the lengths of the paths of the tree: ";
  if (p == NULL)
    return 0;
  else
    return (depth + sumOfPathLengths(p->left, depth + 1, 0) +
            sumOfPathLengths(p->right, depth + 1, 0));
}

int maxHeight(int a, int b) {
  if (a < b)
    return b;
  else
    return a;
}

/* ������ ������ */

int height(tree * p) {
    if (p==NULL) return 0;
    return 1 + max(height(p->left), height(p->right));
}

/* ������ ������ */
int heightTree(tree *p, bool root) {
  if (root)
    std::cout << std::endl << "The height tree: ";
  if (p == NULL)
    return 0;
  else
    return (1 + maxHeight(heightTree(p->left, 0), heightTree(p->right, 0)));
}

/* ������� ������ ������ */
float averageHeightTree(tree *p, bool root) {
  if (root)
    std::cout << std::endl << "The average height tree: ";
  return (float(sumOfPathLengths(p, 1, 0)) / sizeTree(p, 0));
}

/* ���������������� ������ ������ */
int weightTree(tree* root){
	int n;
	if(root == NULL){
		n=0;
	}else{
		n = root->weight + weightTree(root->left) + weightTree(root->right);
	}
	return n;
}

int sumLengthWaysTreeDOP(tree* root,int L){
	int S;
	if(root == NULL){
		S = 0;
	}else{
		S=root->weight * L + sumLengthWaysTreeDOP(root->left, L + 1) + sumLengthWaysTreeDOP(root->right, L + 1);
	}
	return S;
}

float weightedAverageHeightTree(tree* p, bool root){
	float h;
//   if (root)
//     std::cout << std::endl << "The weighted average height tree: ";
	h = (float)sumLengthWaysTreeDOP(p,1) / weightTree(p);
	return h;
	
}

/* ���������� ������� ����� (AW) */
void calculation_AW(int **AW, int **VW,int size){
	for(int i = 0; i < size; i++){
		for(int j = (i + 1); j < size; j++){
			AW[i][j] = AW[i][j-1] + VW[1][j];
		}
	}
}

/* ���������� ������� ���������� ����� (AP) � ������� �������� (AR) */
void calculation_APandAR(int **AP, int **AR, int **AW, int size){
	for(int i = 0; i < size - 1; i++){
		int j = i + 1;
		AP[i][j] = AW[i][j];
		AR[i][j] = j;
	}
	for(int h = 2; h < size; h++){
		for(int i = 0; i < size - h; i++){
			int j = i + h;
			int m = AR[i][j - 1];
			int min = AP[i][m - 1] + AP[m][j];
			for(int k = m + 1; k <= AR[i + 1][j]; k++){
				int x = AP[i][k - 1] + AP[k][j];
				if(x < min){
					m = k;
					min = x;
				}
			}
			AP[i][j] = min + AW[i][j];
			AR[i][j] = m;
		}
	}
}

/* ���������� �������� � ��������� ������ ������ (�������� (recursive)) */
void addRST_R(tree *&p, int data, int weight) {
  if (p == NULL) {
    p = new tree;
    p -> data = data;
    p -> weight = weight;
  } else if (data < p->data)
    addRST_R(p -> left, data, weight);
  else if (data > p -> data)
    addRST_R(p -> right, data, weight);
}

/* �������� ������ */
void createTree(tree*& root, int lBorder, int rBorder, int **AR, int **VW){
	if(lBorder < rBorder){
		int k = AR[lBorder][rBorder];
    	addRST_R(root, VW[0][k], VW[1][k]);
		createTree(root, lBorder, k - 1, AR, VW);
		createTree(root, k, rBorder, AR, VW);
	}
}



void QuickSortV2(int** A, int R, int L)
{
    while (L < R) {
        int x = A[1][L];
        int i = L;
        int j = R;
        while (i <= j) {
            while (A[1][i] > x)
                i++;
            while (A[1][j] < x)
                j--;
            if (i <= j) {
				swap(&A[0][i], &A[0][j]);
                swap(&A[1][i], &A[1][j]);
                i++;
                j--;
            }
        }
        if (j - L > R - i) {
            QuickSortV2(A, R, i);
            R = j;
        }
        else {
            QuickSortV2(A, j, L);
            L=i; 
        } 
    } 
}

void A1(tree *&p, int size, int **VW)
{
	QuickSortV2(VW,size-1, 0);
	// ���������� �� �����
	// for (int i = 1; i < size; i++) {
	// 	for (int j = size - 1; j > i; j--) {
	// 		if (VW[1][j] > VW[1][j - 1]) {
	// 			swap(&VW[0][j], &VW[0][j - 1]);
	// 			swap(&VW[1][j], &VW[1][j - 1]);
	// 		}
	// 	}
	// }
	// ����� ��������� ������ � �����
	
	short int tmp = 0;
	for (int i = 1; i < size; i++){ 
		std::cout.width(3);
		std::cout << VW[0][i];
		std::cout << "[";
		std::cout.width(2);
		std::cout << VW[1][i]; 
		std::cout << "]" <<"  ";
		tmp++;
		if(tmp == 10){
			std::cout << std::endl;
			tmp = 0;
		}
	}
	for(int i = 1; i < size; i++)
	{
		addRST_R(p, VW[0][i], VW[1][i]);
	}
}

void A2(tree *&p, int L, int R, int **VW)
{
	int wes = 0, sum = 0;
	if(L <= R)
	{
		int i = 0;
		for(i = L; i < R; i++)
			wes = wes + VW[1][i];
		

		for(i = L; i < R; i++)
		{
			if((sum <= wes / 2) && (sum + VW[1][i] > wes / 2))
				break;
			sum = sum + VW[1][i];
		}
		
		addRST_R(p, VW[0][i], VW[1][i]);
		A2(p, L, i - 1, VW);
		A2(p, i + 1, R, VW);
	}
}

void printSquareMatrix (int **arr, int size){
  for(int i = 0; i < size; i++){
    for(int j = 0; j < size; j++){
      std::cout.width(5);
      std::cout << arr[i][j] << " ";
    }
    std::cout << std::endl;
  }
}

void outTree_LefttoRight(tree *p, bool root) {
  if (root)
    std::cout << std::endl << "> : ";
  if (p != NULL) {
    outTree_LefttoRight(p->left, 0);
    std::cout << "(" << p->iD << ")" << p->data << "; ";
    outTree_LefttoRight(p->right, 0);
  }
}

int main () {
    
    
	const int size = 100;
	const int seed = time(NULL);
  	srand(seed);
  	
  	int **VandW = new int*[2]; // ������ � �� ����
  	
  	for (int i = 0; i < 2; i++){
		VandW[i] = new int[size + 1];
	    VandW[i][0] = 0;
	}
	
	bool table[2 * size] = {false};
	int x;
	for (int i = 1; i < size + 1; i++){
		while (table[x = rand() % (2 * size)])
		  ;
		table[x] = true;
		VandW[0][i] = x;
	}

	for (int i = 1; i < size + 1; i++) {
	  for (int j = size - 1 + 1; j > i; j--) {
	      if (VandW[0][j] < VandW[0][j - 1]) {
	          swap(&VandW[0][j], &VandW[0][j - 1]);
	      }
	  }
	}
	for (int i = 1; i < size + 1; i++){
		VandW[1][i] = rand() % size + 1;
	}
	
	std::cout << std::endl;

	int **AW = new int*[size + 1]; 
	int **AP = new int*[size + 1]; 
	int **AR = new int*[size + 1]; 
	
	for (int i = 0; i < size + 1; i++){
		AW[i] = new int[size + 1];
		AP[i] = new int[size + 1];
		AR[i] = new int[size + 1];
		for (int j = 0; j < size + 1; j++)
		  AW[i][j] = AP[i][j] = AR[i][j] = 0;
	}
	calculation_AW(AW, VandW, size + 1);
	calculation_APandAR(AP, AR, AW, size + 1);

	
	tree* OST = NULL;
	createTree(OST, 0, size, AR, VandW);
	std::cout << std::endl << "Optimal search tree" << std::endl;
	
	addNums(OST, height(OST));
	
	outTree_LefttoRight(OST, 1);
	std::cout << std::endl << "_____________________";
	std::cout << "__________________________________________________________________" << endl;
	std::cout << "| n = 100 |   SIZE   |     checkSum      | weightedAverageHeight |" << endl;
	std::cout << "__________________________________________________________________" << endl;
	std::cout << "| DOP     |   " << sizeTree(OST, 1) << "    |       " << checkSumTree(OST, 1) << "        |        " << weightedAverageHeightTree(OST, 1) << "       |" << endl;
	std::cout << "__________________________________________________________________" << endl;
	std::cout << std::endl << std::endl;
	

	return 0;
}
