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
	//保存新的顺序
	vector<vector<T>> order_n;
	T minum = INT_MAX;
	T row_start = 0;	//凸包开始点的x坐标
	T col_start = 0;	//凸包开始点的x坐标
	T pos = 0;
	double k1 = 0;
	double k2 = 0;


	//用map来对除开起始点后所有点相对于起始点的斜率进行排序
	//将斜率分为两部分,当斜率小于0时,则斜率越小越排在前面
	//当斜率大于零时,斜率越小越排在前面
	map<double, vector<int>> m_negtive;
	map<double, vector<int>> m_positive;



	/*排除坐标点数小于3的情况*/
	if (point_nums <= 3)
	{
		cout << "坐标点数目太少!!!" << endl;
		abort();
	}
	if (point_nums == 3)
	{
		if (nums[0][0] == nums[1][0] && nums[0][0] == nums[2][0])	//3个点在一条直线上,且任意两个点的斜率为无穷
		{
			cout << "三个点在一条直线上，不能构成包络" << endl;
			abort();
		}
		//计算任意两点的斜率
		k1 = ((double)(nums[1][1] - nums[0][1])) / (nums[1][0] - nums[0][0]);
		k2 = ((double)(nums[2][1] - nums[0][1])) / (nums[2][0] - nums[0][0]);
		if (k1 == k2)	//3点在一条直线上
		{
			cout << "三个点在一条直线上，不能构成包络" << endl;
			abort();
		}
		else
		{
			return nums;	//3点不在一条直线上,则输入本身就是一个凸包,返回原数组
		}
	}

	//寻找y坐标最小的点,若最小点不止有一个,则将所有y坐标最小点压入order数组中
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
	//minum将用来寻找x坐标最大的点
	minum = INT_MIN;
	//若y最小点不止有一个,则寻找x坐标最大的点作为起始点
	//用pos保存最大x坐标时的位置
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
	//order将用来存放斜率为无穷的点
	order.clear();

	//将用k1来表示斜率
	k1 = 0;
	//k1为负,放入m_negtive
	//否则,放入m_negtive
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

	//order_n为新的访问顺序
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

	//将用order保存输出的结果,可以起到栈的作用
	order.clear();
	//起点和oeder_n的第一个点一定的符合条件的
	order.push_back(vector<T>{row_start, col_start});
	order.push_back(order_n[0]);

	//判断是否是逆时针
	//用area的值来判断a,b,c 3个点是否是逆时针
	//area = (b.x - a.x)*(c.y - a.y) - (b.y - a.y)*(c.x - a.x)
	//area > 0;	a,b,c逆时针
	//area == 0; 在同一条直线上
	//area < 0; a,b,c顺时针
	double area = 0;
	//实时更新order_n的size;
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
	int count = 100;	//随机点数
	vector<vector<int>> num;
	for (int i = 0; i < count; ++i)
	{
		point.x = rng.uniform(image.cols / 4, image.cols * 3 / 4);
		point.y = rng.uniform(image.rows / 4, image.rows * 3 / 4);
		num.push_back({ point.x, point.y });
	}

	vector<vector<int>> ans;
	ans = Convex_Hull(num);

	cout << "包络线依次为:" << endl;

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

