#include "common.h"
#include <vector>

#if 0
vector<int> x;
void func(vector<int>& vec, int i, int length)
{
	if (i == length)
	{
		for (auto v : x)
		{
			cout << v << " ";
		}
		cout << endl;
	}
	else
	{
		x.push_back(vec[i]);
		func(vec, i + 1, length);
		x.pop_back();
		func(vec, i + 1, length);
	}
}



int main()
{
	vector<int> vec = { 1, 2, 3 };
	int size = vec.size();
	func(vec, 0, size);
	return 0;
}

#endif

#if 0

/*
给定一组整数，从里面挑选出一组整数，让选择的整数的和，和剩下的整数的和的差最小
*/

vector<int> vec = { 12, 6, 7 , 11, 16, 3,8 };
vector<int> x;
vector<int> result;
int r;
int sum = 0;
unsigned int minval = 0xFFFFFFFF;

void func(vector<int>&vec, int i, int len)
{
	if (i == len)
	{
		int res = abs(r - sum); 
		if (minval > res)
		{
			minval = res;
			result = x;
		}
	}
	else
	{
		r -= vec[i];
		sum += vec[i];
		x.push_back(vec[i]);
		func(vec, i + 1, len);
		x.pop_back();
		sum -= vec[i];
		r += vec[i];
		func(vec, i + 1, len);
	}
}

int main()
{
	for (int v : vec)
	{
		r += v;
	}
	func(vec, 0, vec.size());

	for (int v : result)
	{
		cout << v << " ";
	}
	cout << endl;
	cout << "min :" << minval;
}

#endif

#if 0
/*
整数选择问题： 给定2N个整数，从里面挑选出n个整数，让选则的整数的和，与剩下的整数的和差最小
*/

vector<int> vec = { 12, 6, 7 , 11, 16, 3, 8 , 9};
vector<int> x;   //记录子集中选择的元素
vector<int>bestx;
int sum = 0;	//记录选择的子集的数字之和
int r = 0;		//记录为选择的数字之和
unsigned int minVal = 0xFFFFFFFF;
int lecnt = vec.size();
int cnt = 0;  //用于测试次数

void func(vector<int>& vec, int i, int len)
{
	if (i == len)
	{
		cnt++;
		if (x.size() > len / 2)
		{
			return;
		}
		int res = abs(r - sum);
		if (minVal > res)
		{
			minVal = res;
			bestx = x;
		}
	}
	else
	{
		lecnt--;
		if (x.size() < len / 2)   //剪左树枝
		{
			x.push_back(vec[i]);
			sum += vec[i];
			r -= vec[i];
			func(vec, i + 1, vec.size());
			x.pop_back();
			sum -= vec[i];
			r -= vec[i];
			
		}

		//lecnt表示未来可能选择的个数
		if ((x.size() + lecnt) >= len / 2) //剪右树枝
		{
			func(vec, i + 1, vec.size());
		}
		lecnt++;
		
	}
}

int main()
{
	for (int v : vec)
	{
		r += v;
	}

	func(vec, 0, vec.size());

	for (int v : bestx)
	{
		cout << v << " ";
	}
	cout << endl;
	cout << "min:" << minVal << endl;
	cout << "cnt:" << cnt<<endl;
}

#endif

#if 0
//01背包， 一组物品，重量为w1,w2...价值 v1,v2 ... 背包容量C
//问如何选择物品使得价值最大
vector<int> w = {12, 5, 8, 9, 6};
vector<int> v = {9, 2, 4, 7, 8};
const int len = v.size();
vector<int>x;
vector<int>bestx;
int c = 20;	//背包容量
int cw = 0; //已选择的物品重量
int cv = 0; //已选择的物品的价值
int bestv = 0;
int r = 0;


void func(int i)
{
	if (i == len)
	{
		if (bestv < cv)
		{
			bestv = cv;
			bestx = x;
			
		}
		
	}
	else
	{
		r -= v[i];
		if (cw + w[i] <= c)
		{
			x.push_back(w[i]);
			cw += w[i];
			cv += v[i];
			func(i + 1);
			cw -= w[i];
			cv -= v[i];
			x.pop_back();
		}
		if (cv + r > bestv)
		{
			func(i + 1);
		}
		r += v[i];
	}
}

int main()
{
	for (int val : v)
	{
		r += val;
	}
	func(0);
	for (int val : bestx)
	{
		cout << val << " ";
	}
	cout << endl;

	cout << "bestv:" << bestv << endl;
}

#endif 

#if 0
/* 
挑选数字: 有一组整数，请挑选一组数字，让他们的和等于指定的值，存在解打印，不存在不打印

*/
vector<int> vec = { 4, 8, 12, 16, 7, 9, 3 };
int number = 18;
vector<int> x;
int sum = 0;
int r = 0;

void func(int i, int len)
{
	if (i == len)
	{
		if (sum == number)
		{
			for (int v : x)
			{
				cout << v << " ";
			}
			cout << endl;
		}

	}
	else
	{
		r -= vec[i];
		if (sum + vec[i] <= number)   //剪左树枝
		{
			sum += vec[i];
			x.push_back(vec[i]);
			func(i + 1, len);
			sum -= vec[i];
			x.pop_back();
		}

		if ((sum + r) >= number)  //剪右树枝
		{
			func(i + 1, len);
		}	
		r += vec[i];
	}

}





int main()
{

	for (int val : vec)
	{
		r += val;
	}
	func(0, vec.size());
	return 0;
}

#endif

#if 0
//穷举法实现

vector<int> vec = { 4, 8, 12, 16, 7, 9, 3 };
int number = 18;
int len = vec.size();
vector<int> x;

void func(int i, int number)
{
	if (number == 0)
	{

		for (int v : x)
		{
			cout << v << " ";
		}
		cout << endl;
	}
	else
	{
		for (int k = i; k < len; ++k)
		{
			if (number >= vec[k])
			{
				x.push_back(vec[k]);
				func(k + 1, number - vec[k]);   // 
				x.pop_back();
			}
		}
	}
}

int main()
{
	func(0, number);
}
#endif 

#if 0
//全排列

void func(vector<int>& vec, int i, int len)
{
	if (i == len)
	{
		for (int j = 0; j < len; ++j)
		{
			cout << vec[j] << " ";
		}
		cout << endl;
	}
	else
	{
		for (int k = i; k < len; ++k)
		{
			swap(vec[i], vec[k]);
			func(vec, i + 1, len);
			swap(vec[i], vec[k]);
		}
	}
	
}
int main()
{
	vector<int> vec = { 1,2 ,3, 4 };
	func(vec, 0, vec.size());
	return 0;
}

#endif 
#if 0

//全排列穷举法
vector<int> vec = { 1, 2, 3 };
vector<int> x;
int n = vec.size();
vector<bool> state(n, false);

void func(vector<int>& vec, int i, int len)
{
	if (i == len)
	{
		for (int v : x)
		{
			cout << v << " ";
		}
		cout << endl;
	}
	else
	{
		for (int k = 0; k < len; ++k)
		{
			if (!state[k])
			{
				state[k] = true;
				x.push_back(vec[k]);
				func(vec, i + 1, len);
				x.pop_back();
				state[k] = false;
			}
		}
	}
}

int main()
{
	func(vec, 0, n);
	return 0;
}
#endif

#if 0

bool judge(vector<int>& vec, int i)
{
	for (int j = 0; j < i; ++j)
	{
		if (i == j || vec[i] == vec[j] || abs(i - j) == abs(vec[i] - vec[j]))
			return false;
		
	}
	return true;
}

//n皇后
void func(vector<int>& vec, int i, int len)
{
	if (i == len)
	{
		for (int j = 0; j < len; ++j)
		{
			cout << vec[j] << " ";
		}
		cout << endl;
	}
	else
	{
		for (int k = i; k < len; ++k)
		{
			swap(vec[i], vec[k]);
			if (judge(vec, i))
			{
				func(vec, i + 1, len);
			}
			swap(vec[i], vec[k]);
		}
	}
}

int main()
{
	vector<int> matrix = { 1, 2, 3, 4, 5, 6, 7, 8};
	int len = matrix.size();
	func(matrix, 0, len);
}

#endif 