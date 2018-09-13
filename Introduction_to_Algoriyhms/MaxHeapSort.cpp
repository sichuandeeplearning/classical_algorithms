#include <iostream>
#include <cstdlib>
#include <vector>
#include <algorithm>

using namespace std;

int Parent(const int& x);
int Left(const int& x);
int Right(const int& x);
//维护Max堆,输入一个数组及坐标点,保证此坐标点的最大堆性质
void Max_Heapify(vector<int>& A, int i);
//建Max堆, 任意输入一个vector数组
void Build_Max_Heap(vector<int>& A);
//Max堆排序, 输入一个最大堆
vector<int> HeapSort(vector<int>& A);

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
	vector<int> ans = HeapSort(num);
	for (auto i : ans)
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