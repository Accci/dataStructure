#include "common.h"
#include <vector>

//硬币选择问题， 1, 3, 5分，给定面值11，问组成所需的最少硬币数量？
#if 0
//分治
int func(int n)
{
	if (n == 1 || n == 3 || n == 5)
	{
		return 1;
	}
	else if (n == 2 || n == 4)
	{
		return 2;
	}
	else
	{
		int n1 = func(n - 1) + 1;  //选择1分
		int n2 = func(n - 3) + 1;  //选择3分
		int n3 = func(n - 5) + 1;  //选择5分

		return min(min(n1, n2), n3);
	}
}
int main()
{
	int n = 18;
	int num = func(n);
	cout << "num:" << num << endl;
	return 0;
}

#endif


//动态规划递归
#if 0 
int n = 18;
vector<int>dp(n+1, 0);
int func(int n)
{
	if (dp[n] > 0)
	{
		return dp[n];
	}
	if (n == 1 || n == 3 || n == 5)
	{
		dp[n] = 1;
		return 1;
	}
	else if (n == 2 || n == 4)
	{
		dp[n] = 2;
		return 2;
	}
	else
	{
		int n1 = func(n - 1) + 1;
		int n2 = func(n - 3) + 1;
		int n3 = func(n - 5) + 1;
		dp[n] = min(min(n1, n2), n3);
		return dp[n];
	}
}

int main()
{
	int num = func(n);
	cout << "num:" << num << endl;
} 

#endif

//非递归的动态规划求硬币数量
#if 0
int main()
{
	int n = 18;
	int arr[] = {1, 3, 5};
	int len = sizeof(arr) / sizeof(arr[0]);
	int* dp = new int[n + 1]();   // ()在这里会初始化dp中的元素为0
	for (int i = 0; i <= n; ++i)
	{
		dp[i] = i;   //表示初始全由1分硬币组成
		for (int j = 0; j < len; ++j)
		{
			if (i >= arr[j] && (1 + dp[i - arr[j]]) < dp[i])
			{
				dp[i] = 1 + dp[i - arr[j]];
			}
		}
	}
	cout << "num:" << dp[n] << endl;
	delete[]dp;
	return 0;
}
#endif 

#if 0
//斐波那契数列
int fabnacci(int n)
{
	if (n == 1 || n == 2)
		return 1;
	return fabnacci(n - 1) + fabnacci(n - 2);
} 


int main()
{
	int num = fabnacci(8);
	cout << num << endl;
}
#endif

#if 0
int main()
{
	int n = 6;
	vector<int>dp(n, 0);
	dp[0] = 1;
	dp[1] = 1;
	for (int i = 2; i < n; ++i)
	{
		dp[i] = dp[i - 1] + dp[i - 2];
	}
	cout << dp[n - 1] << endl;
}
#endif 

#if 0
/* 动态规划求子段和 */
int main()
{
	vector<int> vec = { -2, 11, - 4, -13, -5, - 2 };
	int n = vec.size();
	vector<int>dp(n, 0);
	dp[0] = vec[0] > 0 ? vec[0] : 0;
	int maxVal = dp[0];

	for (int i = 1; i < n; ++i)
	{
		dp[i] = vec[i] + dp[i - 1];  // 状态转移方程
		if (dp[i] < 0)
		{
			dp[i] = 0;
		}
		if (dp[i] > maxVal)
		{
			maxVal = dp[i];
		}
	}

	cout << "maxVal:" << maxVal << endl;
}
#endif 

#if 0

/*
LIS问题：求序列的最长非降（升序）子序列的长度
5 3 4 1 8 7 9 
====》 3 4 7 9 

d[i]  表示第i个元素的最长子序列长度
dp[0] = 1;
dp[1] = 1 or  1 +dp[0] (当满足 arr[1] >=arr[0]时)
dp[2] = 1 or   1 + dp[0]      or 1 + dp[1] 
			arr[2] >= arr[0]     arr[2] >= arr[1]
*/

int main()
{
	vector<int> vec = { 5, 3, 4, 1, 8, 6, 7, 10};
	int n = vec.size();
	vector<int> dp(n, 0);
	int maxVal = 0;
	
	for (int i = 1; i < n; ++i)
	{
		dp[i] = 1;
		for (int j = 0; j < i; ++j)
		{
			if (vec[j] <= vec[i] && (1 + dp[j]) > dp[i])
			{
				dp[i] = 1 + dp[j];
			}
		}

		if (maxVal < dp[i])
		{
			maxVal = dp[i];
		}
		
	}
	cout << maxVal << endl;
	return 0;
}
#endif 

#include <string>
/*
LCS: 求两个序列的最长公共子序列的长度 子串
X:helloworld
Y:hlweord

X: X1 ,X2...Xn
Y: Y1, Y2...Ym

if  Ym == Xn
LCS(X[1..n], Y[1...m]) = LCS(X[1..n-1], LCS[1...m-1]) + 1;

else
LCS(X[1..n], Y[1...m]) = max(LCS(X[1..n], LCS[1...m-1]), LCS(X[1..n-1], LCS[1...m]))
*/

#if 0
//分治
int LCS01(string X, int n, string Y, int m)
{
	if (n < 0 || m < 0)
	{
		return 0;
	}
	if (X[n] == Y[m])
	{
		return LCS01(X, n - 1, Y, m - 1) + 1;
	}
	else
	{
		return max(LCS01(X, n - 1, Y, m), LCS01(X, n, Y, m - 1));
	}
}


int main()
{
	string str1 = "helloworld";
	string str2 = "hlweord";

	int size = LCS01(str1, str1.size() - 1, str2, str2.size() - 1);

	cout << "LCS length:" << size << endl;
}
#endif


#if 0
//动态规划 递归二维dp

string str1 = "helloworld";
string str2 = "hlweord";

int n = str1.size();
int m = str2.size();
vector<vector<int>>dp(n, vector<int>(m, -1));

int LCS02(string& X, int n, string& Y, int m)
{
	if (n < 0 || m < 0)
		return 0;
	if (dp[n][m] > 0)
	{
		return dp[n][m];
	}
	if (X[n] == Y[m])
	{
		dp[n][m] = LCS02(X, n - 1, Y, m - 1) + 1;
	}
	else
	{
		dp[n][m] = max(LCS02(X, n, Y, m - 1), LCS02(X, n - 1, Y, m));
	}

	return dp[n][m];
	
}
int main()
{
	int size = LCS02(str1, n - 1, str2, m - 1);

	cout << "LCS length:" << size << endl;
}
#endif 

#if 0

//二维dp非递归
int main()
{
	string str1 = "helloworld";
	string str2 = "hlweod";
	int n = str1.size();
	int m = str2.size();
	vector<vector<int>>dp(n+1, vector<int>(m+1, 0));

	for (int i = 1; i <= n; ++i)
	{
		for (int j = 1; j <= m; ++j)
		{
			if (str1[i-1] == str2[j-1])
			{
				dp[i][j] = dp[i - 1][j - 1] + 1;
			}
			else
			{
				dp[i][j] = max(dp[i][j - 1], dp[i - 1][j]);
			}
		}
	}

	cout << dp[n][m] << endl;
	return 0;
}

#endif 

#if 0
 // 0-1背包
void backtrace(vector<int>& w, vector<int>& v, int c, vector<vector<int>>dp)
{
	int bestv = 0;
	for (int i = 0; i < w.size()-1; ++i)
	{
		if (dp[i][c] != dp[i + 1][c])
		{
			cout << w[i] << " ";
			bestv += v[i];
			c -= w[i];
		}
	}
	if (dp[w.size() - 1][c] > 0)
	{
		cout << w[w.size() - 1] << " ";
		bestv += v[w.size() - 1];
	}
	cout << endl;
	cout << "bestv:" << bestv<<endl;
}

int main()
{
	vector<int> w = { 8, 6, 4, 2, 5 };
	vector<int> v = { 6, 4, 7, 8, 6 };
	
	int c = 12;
	int n = w.size();

	vector<vector<int>> dp(n, vector<int>(c+1));
	for (int j = 1; j <= c; ++j)
	{
		if (w[n-1] > j)
		{
			dp[n-1][j] = 0;
		}
		else
		{
			dp[n-1][j] = v[n-1];
		}
	}
	
	for (int i = n-2; i >= 0; --i)
	{
		for (int j = 1; j <= c; ++j)
		{
			if (w[i] > j)
			{
				dp[i][j] = dp[i + 1][j];
			}
			else
			{
				dp[i][j] = max(dp[i + 1][j], v[i] + dp[i + 1][j - w[i]]);
			}
		}
	}

	//打印dp数组
	for (auto v : dp)
	{
		for (int val : v)
		{
			cout << val << " ";
		}
		cout << endl;
	}
	backtrace(w, v, c, dp);
	//cout << dp[0][c] << endl;
	return 0;
}

#endif

#if 0
//三角数组求和
int main()
{
	vector<int> v1 = { 2 };
	vector<int> v2 = { 3,4};
	vector<int> v3 = { 6,5,7};
	vector<int> v4 = { 4,1,8,3};

	vector<vector<int>> v = { v1, v2, v3, v4 };

	int n = v.size();
	int m = v4.size();
	vector<vector<int>>dp(n, vector<int>(m));

	for (int i = 0; i < m; ++i)
	{
		dp[n-1][i] = v[n-1][i];
	}

	for (int i = n - 2; i >= 0; --i)
	{
		for (int j = 0; j < v[i].size(); ++j)
		{
			dp[i][j] = min(dp[i + 1][j], dp[i + 1][j + 1]) + v[i][j];
		}
	}

	/*for (auto v : dp)
	{
		for (int val : v)
			cout << val << " ";
		cout << endl;
	}*/
	cout << dp[0][0] << endl;


}

#endif 
