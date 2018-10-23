#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <algorithm>
using namespace std;

void Select_sort(vector<int>& num)
{
	int minum = 0;
	int pos = 0;
	for (int i = 0; i < num.size() - 1; ++i)
	{
		minum = num[i];
		pos = i;
		for (int j = i + 1; j < num.size(); ++j)
		{
			if (num[j] < minum)
			{
				minum = num[j];
				pos = j;
			}
		}
		swap(num[i], num[pos]);
	}
}

int main()
{
	vector<int> A = { 2, 4, 1,5,6,3 };
	cout << "before sort" << endl;
	for (auto i : A)
		cout << i << " ";
	cout << endl;

	Select_sort(A);

	cout << "after sort" << endl;
	for (auto i : A)
		cout << i << " ";
	cout << endl;

	system("pause");
	return 0;
}

