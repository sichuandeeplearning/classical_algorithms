//#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
using namespace std;

int LCS_Length(const string& X, const string& Y)
{
	int x = X.size();
	int y = Y.size();
	vector<vector<int>> c(x + 1, vector<int>(y + 1, 0));
	for (int i = 0; i < x; ++i)
	{
		for (int j = 0; j < y; ++j)
		{
			if (X[i] == Y[j])
			{
				c[i + 1][j + 1] = c[i][j] + 1;
			}
			else if(c[i][j + 1] >= c[i + 1][j])
			{
				c[i + 1][j + 1] = c[i][j + 1];
			}
			else
			{
				c[i + 1][j + 1] = c[i + 1][j];
			}
		}
	}
	return c[x][y];
}

int main()
{
	string A("ABCBDAB");
	string B("BDCABA");

	cout << LCS_Length(A, B) << endl;

	system("pause");
	return 0;
}

