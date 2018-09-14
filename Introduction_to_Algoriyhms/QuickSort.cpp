//Quick Sort
#include <iostream>
#include <cstdlib>
#include <vector>
#include <algorithm>

using namespace std;

int Partition(vector<int>& A, int begin, int end);
void QuickSort(vector<int>& A, int begin, int end);

int main()
{
	vector<int> num = { 2,8,7,1,3,5,6,4 };
	
	cout << "ÅÅÐòÇ°:" << endl;
	for (int i = 0; i < num.size(); ++i)
		cout << num[i] << " ";
	cout << endl;
	
	QuickSort(num, 0, num.size() - 1);

	cout << "ÅÅÐòºó:" << endl;
	for (int i = 0; i < num.size(); ++i)
		cout << num[i] << " ";
	cout << endl;

	system("pause");
	return 0;
}

int Partition(vector<int>& A, int begin, int end)
{
	int x = A[end];
	int i = begin - 1;
	int count = 0;
	for (int j = begin; j < end; ++j)
	{
		if (A[j] == x)
			count++;
		if (A[j] < x)
		{
			++i;
			swap(A[i], A[j]);
		}
	}
	swap(A[i + 1], A[end]);
	return i + 1 - count / 2;
}

void QuickSort(vector<int>& A, int begin, int end)
{
	if (begin < end)
	{
		int q = Partition(A, begin, end);
		QuickSort(A, begin, q - 1);
		QuickSort(A, q + 1, end);
	}
}