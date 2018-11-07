#include <iostream>
#include <vector>
#include <cstdlib>

using namespace std;

void LUP(vector<vector<double>> A, vector<vector<double>>& P,
	vector<vector<double>>& L, vector<vector<double>>& U);
vector<double> Linear_Equations_LUP(const vector<vector<double>>& A, const vector<double>& b);
template<typename T>
void exchangerow(vector<T>& first, vector<T>& last)
{
	vector<T> tmp(first);
	int length = first.size();
	for (int i = 0; i < length; ++i)
	{
		first[i] = last[i];
		last[i] = tmp[i];
	}
}
template<typename T>
void exchangerow(T& first, T& second)
{
	T tmp = first;
	first = second;
	second = tmp;
}

int main()
{
	vector<vector<double>> A = { { 1,0,0 },{ 0,1,0 },{ 0,0,1}};
	vector<double> b = {12, 9, 5};
	vector<vector<double>> c;
	vector<double> x;
 	x = Linear_Equations_LUP(A, b);

	for (auto i : x)
	{
		cout << i << " ";
	}
	cout << endl;

	system("pause");
	return 0;
}

void LUP(vector<vector<double>> A, vector<vector<double>>& P,
	vector<vector<double>>& L, vector<vector<double>>& U)
{
	int row = A.size();
	if (row == 0)
	{
		cerr << "非法矩阵" << endl;
		abort();
	}
	if (row != A[0].size())
	{
		cerr << "系数矩阵不是 N * N !!!" << endl;
		abort();
	}

	vector<int> pos(row, 0);
	double maxnum = 0;
	double mul = 0;

	for (int i = 0; i < row; ++i)
	{
		pos[i] = i;
	}

	for (int i = 0; i < row - 1; ++i)
	{
		maxnum = abs(A[i][i]);
		mul = i;
		for (int k = i + 1; k < row; ++k)
		{
			if (abs(A[k][i]) > maxnum)
			{
				maxnum = abs(A[k][i]);
				mul = k;
			}
		}
		exchangerow(pos[i], pos[mul]);
		exchangerow(A[i], A[mul]);

		for (int k = i + 1; k < row; ++k)
		{
			mul = A[k][i] / A[i][i];
			A[k][i] = mul;
			for (int j = i + 1 ; j < row; ++j)
			{
				A[k][j] = A[k][j] - A[i][j] * mul;
			}
		}
		
	}
	for (int i = 0; i < pos.size(); ++i)
	{
		P[i][pos[i]] = 1;
	}

	for (int i = 0; i < row; ++i)
	{
		for (int j = 0; j < row; ++j)
		{
			if (j < i)
			{
				L[i][j] = A[i][j];
			}
			else if(i == j)
			{
				L[i][j] = 1;
				U[i][j] = A[i][j];
			}
			else
			{
				U[i][j] = A[i][j];
			}
		}
	}

	if (abs(U[row - 1][row - 1]) < 0.000001)
	{
		cerr << "输入矩阵必须是非奇异矩阵!" << endl;
		abort();
	}
}

vector<double> Linear_Equations_LUP(const vector<vector<double>>& A, const vector<double>& b)
{
	int row = A.size();
	if (row != b.size())
	{
		cerr << "矩阵维度不同" << endl;
		abort();
	}
	vector<vector<double>> P(row, vector<double>(row, 0));
	vector<vector<double>> L(row, vector<double>(row, 0));
	vector<vector<double>> U(row, vector<double>(row, 0));
	LUP(A, P, L, U);

	vector<double> n_b(row, 0);
	vector<double> y(row, 0);
	vector<double> x(row, 0);
	for (int i = 0; i < row; ++i)
	{
		for (int j = 0; j < row; ++j)
		{
			if (P[i][j] != 0)
			{
				n_b[i] = b[j];
				break;
			}
		}
	}

	for (int i = 0; i < row; ++i)
	{
		for (int j = 0; j < i; ++j)
		{
			y[i] += L[i][j] * y[j];
		}
		y[i] = n_b[i] - y[i];
	}
	
	for (int i = row - 1; i >= 0; --i)
	{
		for (int j = i + 1; j < row; ++j)
		{
			x[i] += U[i][j] * x[j];
		}
		x[i] = (y[i] - x[i]) / U[i][i];
	}
	return x;
}
