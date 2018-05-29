#include <iostream>
#include <cstdlib>
#include <map>
#include <string>

using namespace std;

int partial_match_table(int count, const char* str2)
{
	if (count == 0)
		return 0;
	int plen = strlen(str2);
	const char* s1 = str2;
	int i = 0;
	int be = 0;
	int af = 0;
	int num = 0;
	char *aa = new char[count - 1];
	char *bb = new char[count - 1];

	for (; i < count - 1; i++)
	{
		aa[i] = str2[i];
		bb[i] = str2[count - i - 1];
		for (int j = 0; j <= i; ++j)
		{
			if (aa[j] == bb[i - j])
			{
				if(j == i)
					num = j +1;
			}
			else
				break;
		}
	}
	delete[]aa;
	delete[]bb;
	return num == 0 ? 0 : num - 1;
}

bool K_M_P(const char* str1, const char* str2)
{
	
	int slen = strlen(str1);
	int plen = strlen(str2);
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
			i = i - partial_match_table(j,str2) + 1;
			j = 0;
		}
	}
	if (j == plen)
		return true;
	return false;
}


int main()
{
	char str1[] = "BBC ABCDAB ABCDABCDABGJEOIGNLJSJFGOEWJGNVBFWUIHFOEKMGDSNGWOIHGPIEWJGWGOGNDSNOIWSDE";
	char str2[] = "ABCDABCD";
	char str3[] = "JEOIGNLJSJFGOEWJGNVBFWUIHFOEKMGDSNGW";

	cout << K_M_P(str1, str3) << endl;
	




	system("pause");
	return 0;
}