//only use opencv to show the output
#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <map>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;
using namespace cv;

template<typename T>
vector<vector<T>> Convex_Hull(vector<vector<T>> nums)
{
	int point_nums = nums.size();
	vector<vector<T>> order;
	//�����µ�˳��
	vector<vector<T>> order_n;
	T minum = INT_MAX;
	T row_start = 0;	//͹����ʼ���x����
	T col_start = 0;	//͹����ʼ���x����
	T pos = 0;
	double k1 = 0;
	double k2 = 0;


	//��map���Գ�����ʼ������е��������ʼ���б�ʽ�������
	//��б�ʷ�Ϊ������,��б��С��0ʱ,��б��ԽСԽ����ǰ��
	//��б�ʴ�����ʱ,б��ԽСԽ����ǰ��
	map<double, vector<int>> m_negtive;
	map<double, vector<int>> m_positive;



	/*�ų��������С��3�����*/
	if (point_nums <= 3)
	{
		cout << "�������Ŀ̫��!!!" << endl;
		abort();
	}
	if (point_nums == 3)
	{
		if (nums[0][0] == nums[1][0] && nums[0][0] == nums[2][0])	//3������һ��ֱ����,�������������б��Ϊ����
		{
			cout << "��������һ��ֱ���ϣ����ܹ��ɰ���" << endl;
			abort();
		}
		//�������������б��
		k1 = ((double)(nums[1][1] - nums[0][1])) / (nums[1][0] - nums[0][0]);
		k2 = ((double)(nums[2][1] - nums[0][1])) / (nums[2][0] - nums[0][0]);
		if (k1 == k2)	//3����һ��ֱ����
		{
			cout << "��������һ��ֱ���ϣ����ܹ��ɰ���" << endl;
			abort();
		}
		else
		{
			return nums;	//3�㲻��һ��ֱ����,�����뱾�����һ��͹��,����ԭ����
		}
	}

	//Ѱ��y������С�ĵ�,����С�㲻ֹ��һ��,������y������С��ѹ��order������
	for (int i = 0; i < point_nums; ++i)
	{
		if (nums[i][1] < minum)
		{
			minum = nums[i][1];
			order.clear();
			order.push_back(nums[i]);
		}
		else if (nums[i][1] == minum)
		{
			order.push_back(nums[i]);
		}
	}
	//minum������Ѱ��x�������ĵ�
	minum = INT_MIN;
	//��y��С�㲻ֹ��һ��,��Ѱ��x�������ĵ���Ϊ��ʼ��
	//��pos�������x����ʱ��λ��
	if (order.size() >= 2)
	{
		for (int i = 0; i < order.size(); ++i)
		{
			if (order[i][0] > minum)
			{
				minum = order[i][0];
				pos = i;
			}
		}
		row_start = order[pos][0];
		col_start = order[pos][1];
	}
	else
	{
		row_start = order[0][0];
		col_start = order[0][1];
	}
	//order���������б��Ϊ����ĵ�
	order.clear();

	//����k1����ʾб��
	k1 = 0;
	//k1Ϊ��,����m_negtive
	//����,����m_negtive
	for (int i = 0; i < point_nums; ++i)
	{
		if (nums[i][0] == row_start && nums[i][1] == col_start)
		{
			continue;
		}

		if (nums[i][0] == row_start && nums[i][1] != col_start)
		{
			order.push_back(nums[i]);
			continue;
		}

		k1 = ((double)(nums[i][1] - col_start)) / (nums[i][0] - row_start);
		if (k1 < 0)
		{
			m_negtive[k1] = nums[i];
		}
		else
		{
			m_positive[k1] = nums[i];
		}
	}

	//order_nΪ�µķ���˳��
	for (auto i = m_positive.begin(); i != m_positive.end(); ++i)
	{
		order_n.push_back(i->second);
	}

	for (auto i = order.begin(); i != order.end(); ++i)
	{
		order_n.push_back(*i);
	}

	for (auto i = m_negtive.begin(); i != m_negtive.end(); ++i)
	{
		order_n.push_back(i->second);
	}

	//����order��������Ľ��,������ջ������
	order.clear();
	//����oeder_n�ĵ�һ����һ���ķ���������
	order.push_back(vector<T>{row_start, col_start});
	order.push_back(order_n[0]);

	//�ж��Ƿ�����ʱ��
	//��area��ֵ���ж�a,b,c 3�����Ƿ�����ʱ��
	//area = (b.x - a.x)*(c.y - a.y) - (b.y - a.y)*(c.x - a.x)
	//area > 0;	a,b,c��ʱ��
	//area == 0; ��ͬһ��ֱ����
	//area < 0; a,b,c˳ʱ��
	double area = 0;
	//ʵʱ����order_n��size;
	int sz = order.size();
	for (int i = 1; i < order_n.size(); ++i)
	{
		area = (order[sz - 1][0] - order[sz - 2][0]) * (order_n[i][1] - order[sz - 2][1]) - (order[sz - 1][1] - order[sz - 2][1]) * (order_n[i][0] - order[sz - 2][0]);
		if (area > 0)
		{
			order.push_back(order_n[i]);
		}
		else
		{
			order.pop_back();
			sz = order.size();
			area = (order[sz - 1][0] - order[sz - 2][0]) * (order_n[i][1] - order[sz - 2][1]) - (order[sz - 1][1] - order[sz - 2][1]) * (order_n[i][0] - order[sz - 2][0]);
			while (area <= 0)
			{
				order.pop_back();
				sz = order.size();
				area = (order[sz - 1][0] - order[sz - 2][0]) * (order_n[i][1] - order[sz - 2][1]) - (order[sz - 1][1] - order[sz - 2][1]) * (order_n[i][0] - order[sz - 2][0]);
			}
			order.push_back(order_n[i]);
		}
		sz = order.size();
	}

	area = (order[sz - 1][0] - order[sz - 2][0]) * (col_start - order[sz - 2][1]) - (order[sz - 1][1] - order[sz - 2][1]) * (row_start - order[sz - 2][0]);

	while (area <= 0)
	{
		order.pop_back();
		sz = order.size();
		area = (order[sz - 1][0] - order[sz - 2][0]) * (col_start - order[sz - 2][1]) - (order[sz - 1][1] - order[sz - 2][1]) * (row_start - order[sz - 2][0]);

	}
	order.push_back(order[0]);

	return order;
}


int main()
{
	RNG& rng = theRNG();
	Mat image(600, 600, CV_8UC3);
	namedWindow("image", CV_WINDOW_AUTOSIZE);
	Point point;
	Point point1;
	int count = 100;	//�������
	vector<vector<int>> num;
	for (int i = 0; i < count; ++i)
	{
		point.x = rng.uniform(image.cols / 4, image.cols * 3 / 4);
		point.y = rng.uniform(image.rows / 4, image.rows * 3 / 4);
		num.push_back({ point.x, point.y });
	}

	vector<vector<int>> ans;
	ans = Convex_Hull(num);

	cout << "����������Ϊ:" << endl;

	for (int i = 0; i < ans.size(); ++i)
	{
		cout << ans[i][0] << " " << ans[i][1] << endl;
	}


	for (int i = 0; i < num.size(); ++i)
	{
		circle(image, Point(num[i][0], num[i][1]), 3, Scalar(rng.uniform(0, 254), rng.uniform(0, 254), rng.uniform(0, 254)), FILLED, LINE_AA);
	}
	point = { ans[0][0], ans[0][1] };
	for (int i = 1; i < ans.size(); ++i)
	{
		point1 = { ans[i][0], ans[i][1] };
		line(image, point, point1, Scalar(255, 255, 255), 2, LINE_AA);
		circle(image, point, 3, Scalar(0, 0, 255), FILLED, LINE_AA);
		point = point1;
	}

	
	imshow("image", image);

	waitKey(0);

	return 0;
}

