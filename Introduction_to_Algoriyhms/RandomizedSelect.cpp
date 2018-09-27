#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <algorithm>

using namespace std; 

int Partition(vector<int>& num, int begin, int end)
{
	int x = num[end];
	int i = begin - 1;
	int j = begin;
	for (; j < end; ++j)
	{
		if (num[j] <= x)
		{
			++i;
			swap(num[i], num[j]);
		}
	}
	swap(num[i + 1], num[end]);
	return i + 1;
}

int Randomized_Partition(vector<int>& num, int begin, int end)
{
	int i = rand() % (end - begin + 1) + begin;
	swap(num[i], num[end]);
	return Partition(num, begin, end);
}

int Randomized_Select(vector<int>& num, int begin, int end, int i)
{
	srand((unsigned)time(NULL));
	if (begin == end)
		return num[begin];
	int q = Randomized_Partition(num, begin, end);
	int k = q - begin + 1;
	if (k == i)
		return num[q];
	else if (i < k)
		return Randomized_Select(num, begin, q - 1, i);
	else
		return Randomized_Select(num, q + 1, end, i - k);
}

int main()
{
	vector<int> A = { 3, 2, 9, 0, 7, 5, 4, 8, 6, 1 };
	int pos = 5;
	int ans = 0;
	ans = Randomized_Select(A, 0, A.size() - 1, pos);
	cout << ans << endl;

	system("pause");
	return 0;
}

