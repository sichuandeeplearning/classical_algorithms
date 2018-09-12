#include <iostream>
#include <cstdlib>
#include <vector>

using namespace std;

void InsertSort(vector<int>& num)
{
	int k = 0;
	int j = 0;
	int mid = 0;
	for (size_t i = 1; i < num.size(); ++i)
	{
		k = num[i];
		j = i - 1;
		while ((j >= 0) && (num[j] > k))
		{
			num[j + 1] = num[j];
			j--;
		}
		num[j + 1] = k;
	}
}

int main()
{
	vector<int> nums = {5, 2, 4, 6, 1, 3, 3, 4, 5, 6, 23, 54};

	cout << "ÅÅÐòÇ°:" << endl;
	for (size_t i = 0; i < nums.size(); ++i)
		cout << nums[i] << " ";
	cout << endl;

	InsertSort(nums);

	cout << "ÅÅÐòºó:" << endl;
	for (size_t i = 0; i < nums.size(); ++i)
		cout << nums[i] << " ";
	cout << endl;

	system("pause");
	return 0;
}