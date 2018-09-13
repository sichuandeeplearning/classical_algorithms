//������ȶ���
#include <iostream>
#include <cstdlib>
#include <vector>
#include <algorithm>

using namespace std;

/***********�������*****************/
int Parent(const int& x);
int Left(const int& x);
int Right(const int& x);
//ά��Max��,����һ�����鼰�����,��֤����������������
void Max_Heapify(vector<int>& A, int i);
//��Max��, ��������һ��vector����
void Build_Max_Heap(vector<int>& A);
//Max������, ����һ������
vector<int> HeapSort(vector<int>& A);
/***********�������*****************/

//�������ֵ
int Heap_Maximum(const vector<int>& A);
//��ȡ���ֵ
int Heap_Extract_Max(vector<int>& A);
//Max��ָ��Ԫ��ֵ����
void Heap_Increase_key(vector<int>& A, int i, int key);
//��Max���в���һ��Ԫ��
void Max_Heap_Insert(vector<int>& A, int key);

int main()
{
	vector<int> num = { 4, 1, 3, 2, 16, 9, 10, 14, 8, 7 };
	for (auto i : num)
		cout << i << " ";
	cout << endl;

	Build_Max_Heap(num);

	for (auto i : num)
		cout << i << " ";
	cout << endl;
	

	Max_Heap_Insert(num, 18);
	for (auto i : num)
		cout << i << " ";
	cout << endl;


	system("pause");
	return 0;
}


int Parent(const int& x)
{
	return (x - 1) / 2;
}

int Left(const int& x)
{
	return 2 * x + 1;
}

int Right(const int& x)
{
	return 2 * (x + 1);
}

void Max_Heapify(vector<int>& A, int i)
{
	int l = Left(i);
	int r = Right(i);
	int largest = 0;
	if (l < A.size() && A[i] < A[l])
	{
		largest = l;
	}
	else
		largest = i;
	if (r < A.size() && A[r] > A[largest])
		largest = r;
	if (largest != i)
	{
		swap(A[i], A[largest]);
		Max_Heapify(A, largest);
	}
}

void Build_Max_Heap(vector<int>& A)
{
	int it = A.size() / 2 - 1;
	for (; it >= 0; --it)
	{
		Max_Heapify(A, it);
	}
}

vector<int> HeapSort(vector<int>& A)
{
	vector<int> heapsorted;
	for (int i = A.size() - 1; i >= 0; --i)
	{
		heapsorted.push_back(A[0]);
		swap(A[0], A[A.size() - 1]);
		A.pop_back();
		Max_Heapify(A, 0);
	}
	return heapsorted;
}


int Heap_Maximum(const vector<int>& A)
{
	return A[0];
}

int Heap_Extract_Max(vector<int>& A)
{
	if (A.empty())
	{
		cerr << "heap underflow" << endl;
		abort();
	}
	int Max = A[0];
	A[0] = A[A.size() - 1];
	A.pop_back();
	Max_Heapify(A, 0);
	return Max;
}

void Heap_Increase_key(vector<int>& A, int i, int key)
{
	if (A[i] > key)
	{
		cerr << "new key is smaller than current key";
		abort();
	}
	A[i] = key;
	int parent = Parent(i);
	while (i > 0 && A[parent] < A[i])
	{
		swap(A[i], A[parent]);
		i = parent;
		parent = Parent(i);
	}
}

void Max_Heap_Insert(vector<int>& A, int key)
{
	int val = INT_MIN;
	A.push_back(val);
	Heap_Increase_key(A, A.size() - 1, key);
}