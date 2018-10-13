#include <iostream>
#include <cstdlib>
#include <map>
#include <string>

using namespace std;

int partial_match_table(int count, const string& str2)
{
	if (count == 0)
		return 0;
	int plen = str2.size();
	const string s1 = str2;
	int i = 0;
	int be = 0;
	int af = 0;
	int num = 0;
	
	string aa, bb;
	aa.resize(count - 1);
	bb.resize(count - 1);

	for (; i < count - 1; i++)
	{
		aa[i] = str2[i];
		bb[i] = str2[count - i - 1];
		for (int j = 0; j <= i; ++j)
		{
			if (aa[j] == bb[i - j])
			{
				if (j == i)
					num = j + 1;
			}
			else
				break;
		}
	}
	return num == 0 ? 0 : num - 1;
}

bool K_M_P(const string& str1, const string& str2)
{

	int slen = str1.size();
	int plen = str2.size();
	int i = 0;
	int j = 0;
	while ((i < slen) && (j < plen))
	{
		if (str1[i] == str2[j])
		{
			i++;
			j++;
		}
		else
		{
			i = i - partial_match_table(j, str2) + 1;
			j = 0;
		}
	}
	if (j == plen)
		return true;
	return false;
}


int main()
{
	string str1 = "BBC ABCDAB ABCDABCDABGJEOIGNLJSJFGOEWJGNVBFWUIHFOEKMGDSNGWOIHGPIEWJGWGOGNDSNOIWSDE";
	string str2 = "ABCDABCD";
	string str3 = "JEOIGNLJSJFGOEWJGNVBFWUIHFOEKMGDSNGW";

	cout << K_M_P(str2, str3) << endl;





	system("pause");
	return 0;
}