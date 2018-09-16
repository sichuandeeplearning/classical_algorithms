#include <iostream>
#include <cstdlib>
#include <vector>

using namespace std;

class Stack {
public:
	bool empty() const;
	void PUSH(const int& x);
	int POP();
private:
	vector<int> S;
};

bool Stack::empty() const
{
	return S.empty() ? true : false;
}

void Stack::PUSH(const int& x)
{
	S.push_back(x);
}

int Stack::POP()
{
	if (empty())
	{
		cerr << "underflow" << endl;
		abort();
	}
	int x = S[S.size() - 1];
	S.pop_back();
	return x;
}

int main()
{
	Stack s;
	cout << s.empty() << endl;
	s.PUSH(2);
	s.PUSH(3);
	s.PUSH(7);
	cout << s.POP() << endl;


	system("pause");
	return 0;
}