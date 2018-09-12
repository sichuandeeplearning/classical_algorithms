#include <iostream>
#include <cstdlib>
#include <vector>

using namespace std;

void Merge(vector<int>& num, int begin, int mid, int end);

void MergeSort(vector<int>& num, int begin, int end)
{
	if (begin < end)
	{
		int mid = (begin + end) / 2;
		MergeSort(num, begin, mid);
		MergeSort(num, mid + 1, end);
		Merge(num, begin, mid, end);
	}
}

void Merge(vector<int>& num, int begin, int mid, int end)
{
	vector<int> L1((num.begin() + begin), (num.begin() + mid + 1));
	vector<int> L2((num.begin() + mid + 1), (num.begin() + end + 1));
	int sz1 = 0;
	int sz2 = 0;
	for (int i = begin; i <= end; ++i)
	{
		if (sz1 >= L1.size())
		{
			num[i] = L2[sz2];
			sz2++;
		}
		else if (sz2 >= L2.size())
		{
			num[i] = L1[sz1];
			sz1++;
		}
		else
		{
			if (L1[sz1] > L2[sz2])
			{
				num[i] = L2[sz2];
				sz2++;
			}
				
			else
			{
				num[i] = L1[sz1];
				sz1++;
			}
		}
	}
}

int main()
{
	vector<int> nums = {5, 2, 4, 6, 1, 3, 3,4,5,63,2,5,2,4};
	cout << "ÅÅĞòÇ°:" << endl;
	for (size_t i = 0; i < nums.size(); ++i)
		cout << nums[i] << " ";
	cout << endl;

	MergeSort(nums, 0, nums.size() - 1);

	cout << "ÅÅĞòºó:" << endl;
	for (size_t i = 0; i < nums.size(); ++i)
		cout << nums[i] << " ";
	cout << endl;



	system("pause");
	return 0;
}