//元素必须是自然数

#include <iostream>
#include <cstdlib>
#include <vector>

using namespace std;
int max_bits(const vector<int>& data)
{
	int  maxnum = 0;
	int length = data.size();
	for (int i = 0; i < length; ++i)
	{
		if (data[i] > maxnum)
			maxnum = data[i];
	}
	int d = 1;
	int p = 10;
	while (maxnum >= p)
	{
		p *= 10;
		d++;
	}
	return d;
}


void radix_sort(vector<int>& data)
{
	int length = data.size();
	if (length == 0)
		return;
	int d = max_bits(data);
	vector<int> tmp(length, 0);
	int count[10];
	int p = 1;
	int k = 0;
	for (int i = 0; i < d; ++i)
	{
		for (int j = 0; j < 10; ++j)
			count[j] = 0;
		for (int j = 0; j < length; ++j)
		{
			tmp[j] = 0;
			k = (data[j] / p) % 10;
			count[k]++;
		}
		for (int j = 1; j < 10; ++j)
		{
			count[j] += count[j - 1];
		}
		for (int j = length - 1; j >= 0; --j)
		{
			k = (data[j] / p) % 10;
			tmp[count[k] - 1] = data[j];
			count[k]--;
		}
		for (int j = 0; j < length; ++j)
			data[j] = tmp[j];
		p *= 10;
	}
}


int main()
{
	vector<int> array = { 73,22,93,43,55,14,28,65,39,81,520,121};

	radix_sort(array);

	for (int i = 0; i < array.size(); ++i)
		cout << array[i] << " ";
	cout << endl;


	system("pause");
	return 0;
}