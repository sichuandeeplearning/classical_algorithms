//Counting Sort
#include <iostream>
#include <cstdlib>
#include <vector>

using namespace std;

vector<int> CountingSort(vector<int>& A);

int main()
{
	vector<int> num = { 2,5,3,0,2,3,0,3 };
	vector<int> ans = CountingSort(num);
	for (auto i : ans)
		cout << i << " ";
	cout << endl;

	system("pause");
	return 0;
}

vector<int> CountingSort(vector<int>& A)
{
	vector<int> B(A.size(), 1);
	int Max(0);
	for (auto i: A)
	{
		if (i > Max)
			Max = i;
	}
	vector<int> C(Max + 1, 0);
	for (int i = 0; i < A.size(); ++i)
	{
		C[A[i]]++;
	}
	for (int i = 1; i < C.size(); ++i)
	{
		C[i] += C[i - 1];
	}
	for (int j = A.size() - 1; j >= 0; --j)
	{
		B[C[A[j]] - 1] = A[j];
		C[A[j]]--;
	}
	return B;
}