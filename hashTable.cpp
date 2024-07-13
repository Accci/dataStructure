#include "common.h"

//线性探测哈希表

//桶的状态

enum State
{
	STATE_UNUSE,
	STATE_USING,
	STATE_DEL,
};

//桶的类型

struct Bucket
{
	Bucket(int key = 0, State state = STATE_UNUSE)
		:key_(key)
		, state_(state) {}
	int key_;
	State state_;
};


//线性探测哈希表类型
class HashTable
{
public:
	HashTable(int size = primes_[0], double loadFactor = 0.75) 
	:useBucketNum_(0)
	,loadFactor_(loadFactor)
	,primeIdx_(0)
	{
		if (size != primes_[0])
		{
			for (; primeIdx_ < PRIME_SIZE; primeIdx_)
			{
				if (primes_[primeIdx_] > size)
				{
					break;
				}
			}

			if (primeIdx_ == PRIME_SIZE)  //用户传入的参数值太大，已经超过最后一个素数
			{
				primeIdx_--;
			}
		}

		tableSize_ = primes_[primeIdx_];
		table_ = new Bucket[tableSize_];

	}
	~HashTable()
	{
		delete[] table_;
		table_ = nullptr;
	}
public:
	bool insert(int key)
	{
		//考虑扩容
		double factor = useBucketNum_ * 1.0 / tableSize_;
		cout << " factor:" << factor << endl;
		if (factor > loadFactor_)
		{
			//哈希表开始扩容
			expand();
		}

		int idx = key % tableSize_;

		int i = idx;
		do
		{
			if (table_[i].state_ != STATE_USING)
			{
				table_[i].state_ = STATE_USING;
				table_[i].key_ = key;
				useBucketNum_++;
				return true;
			}

			i = (i + 1) % tableSize_;

		} while ( i != idx );
		
		

		return false;
	}

	//删除元素
	bool erase(int key)
	{
		int idx = key % tableSize_;

		int i = idx;
		do
		{
			if (table_[i].state_ == STATE_USING && table_[i].key_ == key)
			{
				table_[i].state_ = STATE_DEL;
				useBucketNum_--;
			}
			i = (i + 1) % tableSize_;

		} while (table_[i].state_ != STATE_UNUSE && i != idx);

		return true;
	}

	bool find(int key)
	{
		int idx = key % tableSize_;

		int i = idx;
		do
		{
			if (table_[i].state_ == STATE_USING && table_[i].key_ == key)
			{
				return true;	
			}
			i = (i + 1) % tableSize_;

		} while (table_[i].state_ != STATE_UNUSE && i != idx);

		return false;
	}

private:
	Bucket* table_;			//指向动态开辟的哈希表
	int tableSize_;			//哈希表当前的长度
	int useBucketNum_;		//已经使用的桶的个数

	double loadFactor_;		//转载因子

	static const int PRIME_SIZE = 10;		//素数表的大小
	static int primes_[PRIME_SIZE];			//素数表
	int primeIdx_;			//当前使用的素数下标

	void expand()
	{
		++primeIdx_;
		if (primeIdx_ == PRIME_SIZE)
			throw "HashTable is too large, can not expand anymore!";

		Bucket* newTable = new Bucket[primes_[primeIdx_]];

		for (int i = 0; i < tableSize_; ++i)
		{
			if (table_[i].state_ == STATE_USING) // 旧表有效数据，重新哈希后放到扩容后的新表
			{
				int idx = table_[i].key_ % primes_[primeIdx_];

				int k = idx;

				do
				{
					if (newTable[k].state_ == STATE_UNUSE)
					{
						newTable[k].state_ = STATE_USING;
						newTable[k].key_ = table_[i].key_;
						break;
					}

					k = (k + 1) % primes_[primeIdx_];

				} while (k != idx);
			}
		}

		delete[] table_;
		table_ = newTable;
		tableSize_ = primes_[primeIdx_];
	}
};

int HashTable::primes_[PRIME_SIZE] = { 3, 7, 23, 47, 97, 251, 443, 911, 1471, 42773 };

/*
线性探测哈希表的缺陷
	1.发生哈希冲突时  =》越来越靠近O(n)的时间复杂度， 存储变慢了
	2.多线程环境中, 线性探测所用到的基于数组实现的哈希表只能给全局的表用互斥锁来保证哈希表的原子操作
	保证线程安全。

	链式哈希表， 可以用分段的锁，既保证的线程安全，又有一定的并发量，提高了效率

	每个桶的链表比较长，链表搜索花费的时间长
		优化一：当链表长度大于8（10），把桶里面的这个链表转化成红黑树
	优化二：链式哈希表每个桶都可以创建自己的互斥锁，不同桶中链表操作，可以并发起来
*/

#if 0
//链式哈希表
#include <vector>
#include <list>
#include <algorithm>

class LinkHashTable
{
public:
	LinkHashTable(int size = primes_[0], double loadFactor = 0.75)
		:useBucketNum_(0)
		, loadFactor_(loadFactor)
	{
		if (size != primes_[0])
		{
			for (; primeIdx_ < PRIME_SIZE; primeIdx_++)
			{
				if (primes_[primeIdx_] > size)
				{
					break;
				}
			}
			if (primeIdx_ == PRIME_SIZE)
			{
				primeIdx_--;
			}
		}

		table_.resize(primes_[primeIdx_]);
	}

public:
	//增加元素 不能重复插入
	void insert(int key)
	{
		double factor = useBucketNum_ * 1.0 / table_.size();
		cout << "factor: " << factor << endl;
		if (factor > loadFactor_)
		{
			expand();
		}

		int idx = key % table_.size();

		if (table_[idx].empty())
		{
			useBucketNum_++;
			table_[idx].emplace_front(key);
		}
		else
		{
			auto it = ::find(table_[idx].begin(), table_[idx].end(), key);
			if (it == table_[idx].end())
			{
				//key不存在
				table_[idx].emplace_front(key);
			}
		}
	}

	void erase(int key)
	{
		int idx = key % table_.size();
		auto it = ::find(table_[idx].begin(), table_[idx].end(), key);
		if (it != table_[idx].end())
		{
			table_[idx].erase(it);

			if (table_[idx].empty())
			{
				useBucketNum_--;
			}
		}
	}

	bool find(int key)
	{
		int idx = key % table_.size();
		auto it = ::find(table_[idx].begin(), table_[idx].end(), key);
		return it != table_[idx].end();
	}

private:
	void expand()
	{
		if (primeIdx_ + 1 == PRIME_SIZE)
		{
			throw "LinkHashTable can not expand anymore!";
		}

		primeIdx_++;
		useBucketNum_ = 0;
		vector<list<int>> oldtable;
		table_.swap(oldtable);

		table_.resize(primes_[primeIdx_]);
		for (auto list : oldtable)
		{
			for (auto key : list)
			{
				int idx = key % table_.size();

				if (table_[idx].empty())
				{
					useBucketNum_++;
				}
				table_[idx].emplace_front(key);
	
			}
		}
	}
private:
	vector<list<int>> table_;  //哈希的数据结构
	int useBucketNum_;	
	double loadFactor_;

	static const int PRIME_SIZE = 10;
	static int primes_[PRIME_SIZE];
	int primeIdx_;

};

int LinkHashTable::primes_[PRIME_SIZE] = { 3, 7, 23, 47, 97, 251, 443, 911, 1471, 42773 };

int main()
{
	LinkHashTable hTable;

	hTable.insert(21);
	hTable.insert(32);
	hTable.insert(14);
	hTable.insert(15);
	hTable.insert(22);
	hTable.insert(34);

	cout << hTable.find(34) << endl;
	hTable.erase(34);
	cout << hTable.find(34) << endl;
}

#endif 
/*
大数据查重：
哈希表
位图

*/


//哈希表

#include <vector>
#include <unordered_set>
#include <unordered_map>

#if 0
int main()
{
	vector<int> vec;
	srand(time(0));

	for (int i = 0; i < 10000; ++i)
	{
		vec.push_back(rand() % 10000);
	}
#if 0

	//找到第一个出现重复的数字
	unordered_set<int> s1;
	for (auto v : vec)
	{
		auto it = s1.find(v);
		if (it == s1.end())
		{
			s1.insert(v);
		}
		else
		{
			cout << *it << " ";
			break;
		}	
	}


	//找到所有重复出现的数字
	unordered_set<int> s1;
	for (auto v : vec)
	{
		auto it = s1.find(v);
		if (it == s1.end())
		{
			s1.insert(v);
		}
		else
		{
			cout << *it << " ";
		}
	}

#endif

#if 0
	//统计重复数字出现的次数

	unordered_map<int, int> m1;
	for (int key : vec)
	{
		/*auto it = m1.find(key);
		if (it == m1.end())
		{
			m1.emplace(key,1);
		}
		else
		{
			it->second += 1;
		}*/
		m1[key]++;
	}

	for (auto pair : m1)
	{
		if (pair.second > 1)
		{
			cout << "key : " << pair.first << " count: " << pair.second << endl;
		}
	}
#endif


	//一组数据有些是重复的，把重复的数字过滤掉，每个数字出现一次

	unordered_set<int>s1;
	for (auto key : vec)
	{
		s1.emplace(key);
	}
}
#endif

#if 0
//在一串字符串中找到第一个出现的不重复的字符

int main()
{
	string str = "hahhahahhahajljhdfgsfgafd";

	unordered_map<int, int>m1;
	
	for (auto ch : str)
	{
		m1[ch]++;
	}

	for (auto ch : str)
	{
		if (m1[ch] == 1)
		{
			cout << "第一个出现的非重复的字符是：" << ch << endl;
			return 0;
		}
	}
	cout << "没有不重复的字符！" << endl;
	return 0;
}
#endif

/*
有两个文件分别是a和b，里面有很多IP地址（url地址，email地址），让你找出两个文件重复的ip，输出出来


没有内存限制的话

先把a文件的所有ip存到一个哈希表，再依次遍历文件b的ip，每次遍历一个ip就i在哈希表中搜索一下，能搜到的即是重复的IP


如果a和 b 各有1亿条数据 (1亿 大概 100M) ， 内存限制100M 怎么解决上面的问题?
分治法-----》用除留余数法将 a中的ip映射到 11个小文件中， b中的ip采用同样的散列函数进行映射同样个小文件
每个小文件一一做对比，从而实现

位数组， 以数位下标，出现了就把那个位标记为1


*/

#if 0

//位图
#include <memory>
int main()
{
	vector<int> vec{ 12, 34, 12, 90, 8, 90, 34 };

	//定义位图数组
	int max = vec[0];
	for (int i = 1; i < vec.size(); ++i)
	{
		if (max < vec[i])
		{
			max = vec[i];
		}
	}

	int* bitmap = new int[max / 32 + 1]();
	unique_ptr<int[]> ptr(bitmap);

	//找到第一个重复出现的数字
	for (auto key : vec)
	{
		int index = key / 32;
		int offset = key % 32;

		//取key对应位的值
		if (0 == (bitmap[index] & (1 << offset)))
		{
			bitmap[index] |= (1 << offset);
		}
		else
		{
			/*cout << key << "是第一个重复出现的数字" << endl;
			return 0;*/
			//求所有重复的数字
			cout << key << " 是重复出现的数字" << endl;
		}
	}

	return 0;
}
#endif
/*
布隆过滤器 Bloom fliter 布隆过滤器， 位数组+ k个哈希函数

增加一个元素：
	1.经过K个哈希函数计算，得到bitmap位数组里面的一组位的序号
	2.把相应的位置位1
搜索一个元素:
	1.经过K个哈希函数计算，得到bitmap位数组里面的一组位的序号
	2.判断上面几个位置的值如果全是1，证明相应的key存在，如果有一个是0，则证明key不在bloom fliter中

bloom fliter 能提供删除操作吗？ 不能，不同的key，经过K个哈希函数计算后，可能共用一些位

bloom fliter 查询一个key是否存在？ 如果查出来key经过k个哈希函数处理后对应的位都是1， 能说明这个key是存在的吗？

	bloom fliter说数据在，其实数据不一定存在			会误判
	bloom fliter说数据不在， 那么数据肯定不存在！！！！   这是肯定的


应用
场景一： 提示过滤一些非法的网站，或者钓鱼网站
把所有可能怀疑有问题的网站的URL （黑名单网址）添加到bloom fliter中。
如果存在 （实际不一定在） ，会进行提示
如果不存在， 那么一定在白名单中，可直接访问


场景二： redis缓存的应用
查找key， getBit(key) =>key不存在=》直接找DB中=》放入redis进行缓存=》返回
		  getBit(key) =>key存在 =》redis中查找（虽然有误判，但是概率其实较低）
	 
*/

#if 0
#include "stringhash.h"
#include <string>
class BloomFliter
{
public:
	BloomFliter(int bitsize = 1471)
		:bitsize_(bitsize)
	{
		bitmap_.resize(bitsize_ / 32 + 1);
	}
public:
	void setBit(const char* str)
	{
		int idx1 = BKDRHash(str) % bitsize_;
		int idx2 = RSHash(str) % bitsize_;
		int idx3 = APHash(str) % bitsize_;

		int index = 0;
		int offset = 0;

		index = idx1 / 32;
		offset = idx1 % 32;
		bitmap_[index] |= (1 << offset);

		index = idx2 / 32;
		offset = idx2 % 32;
		bitmap_[index] |= (1 << offset);

		index = idx3 / 32;
		offset = idx3 % 32;
		bitmap_[index] |= (1 << offset);
	}

	bool getBit(const char* str)
	{
		int idx1 = BKDRHash(str) % bitsize_;
		int idx2 = RSHash(str) % bitsize_;
		int idx3 = APHash(str) % bitsize_;

		int index = 0;
		int offset = 0;

		index = idx1 / 32;
		offset = idx1 % 32;
		if (0 == (bitmap_[index] & (1 << offset)))
		{
			return false;
		}

		index = idx2 / 32;
		offset = idx2 % 32;
		if (0 == (bitmap_[index] & (1 << offset)))
		{
			return false;
		}

		index = idx3 / 32;
		offset = idx3 % 32;
		if (0 == (bitmap_[index] & (1 << offset)))
		{
			return false;
		}
		return true;
	}
private:
	int bitsize_;
	vector<int> bitmap_;

};

class BalckUrl
{
public:
	void add(string str)
	{
		bloomFliter.setBit(str.c_str());
	}

	bool query(string str)
	{
		return bloomFliter.getBit(str.c_str());
	}

private:
	BloomFliter bloomFliter;
};



int main()
{
	BalckUrl list;
	list.add("http://www.baidu.com");
	list.add("http://www.360buy.com");
	list.add("http://www.tmall.com");
	list.add("http://www.tencent.com");

	string url = "http://www.tencent.com";
	cout << list.query(url) << endl;
	
	return 0;
}
#endif


/*
* 求topK问题
* 1.大根堆，小根堆
	求一串数据中最小的K个数， 用大根堆
	求一串数据中最大的K个数，用小根堆

2.快排分割
*/


#include <queue>

#if 0
int main()
{
	srand(time(0));
	vector<int> vec;
	for (int i = 0; i < 1000; ++i)
	{
		vec.push_back(rand() % 10000);
	}

	priority_queue<int> maxHeap;  //默认是 less<int>  大根堆
	//求前5个最小的数
	for (int i = 0; i < 5; ++i)
	{
		maxHeap.push(vec[i]);
	}

	for (int i = 5; i < vec.size(); ++i)
	{
		if (maxHeap.top() > vec[i])
		{
			maxHeap.pop();
			maxHeap.push(vec[i]);
		}
	}

	while (!maxHeap.empty())
	{
		cout << maxHeap.top() << " ";
		maxHeap.pop();
	}
	cout << endl;


	//求最大的5个数， 用小根堆
	priority_queue<int, vector<int>, greater<int>> minHeap;

	for (int i = 0; i < 5; ++i)
	{
		minHeap.push(vec[i]);
	}

	for (int i = 5; i < vec.size(); ++i)
	{
		if (minHeap.top() < vec[i])
		{
			minHeap.pop();
			minHeap.push(vec[i]);
		}
	}

	while (!minHeap.empty())
	{
		cout << minHeap.top() << " ";
		minHeap.pop();
	}
	cout << endl;

	return 0;
}

#endif

#if 0
// 查重和topK问题结合起来
#include <functional>
int main()
{
	vector<int> vec;
	srand(time(0));

	for (int i = 0; i < 10000; ++i)
	{
		vec.push_back(rand() % 1000);
	}

#if 0
	//求重复次数最小的前3个数
	//先用哈希表存储重复的次数
	unordered_map<int, int> m1;
	int k = 3;
	for (auto key : vec)
	{
		m1[key]++;
	}

	using type = pair<int, int>;
	using Comp = function<bool(type&, type&)>;
	priority_queue<type, vector<type>, Comp> maxHeap([](type& a, type& b)->bool {
		return a.second < b.second;
		});

	
	auto it = m1.begin();
	for (int i = 0; i < k; ++i, ++it)
	{
		maxHeap.push(*it);
	}

	while (it != m1.end())
	{
		if (maxHeap.top().second > it->second)
		{
			maxHeap.pop();
			maxHeap.push(*it);
		}
		++it;
	}

	while (!maxHeap.empty())
	{
		cout << "key:" << maxHeap.top().first << " "
			<< "cnt:" << maxHeap.top().second << endl;
		maxHeap.pop();
	}

#endif 

	//统计重复次数最大的前3个数字

	unordered_map<int, int>m1;
	for (int key : vec)
	{
		m1[key]++;
	}

	using type = pair<int, int>;
	using Comp = function<bool(type&, type&)>;
	priority_queue<type, vector<type>, Comp>minHeap([](type& a, type& b)->bool {
		return a.second > b.second;
		});

	auto it = m1.begin();

	for (int i = 0; i < 3; ++i, ++it)
	{
		minHeap.push(*it);
	}

	while (it != m1.end())
	{
		if (minHeap.top().second < it->second)
		{
			minHeap.pop();
			minHeap.push(*it);
		}
		++it;
	}

	while (!minHeap.empty())
	{
		cout << "key: " << minHeap.top().first << " "
			<< "cnt: " << minHeap.top().second << endl;
		minHeap.pop();
	}
	return 0;
}

#endif

#if 0
//快排分割的方法 
int Partation(int arr[], int begin, int end)
{
	int i = begin;
	int j = end;
	int val = arr[begin];
	while (i < j)
	{
		while (i < j && arr[j] < val) { j--; }   
		if (i < j)
		{
			arr[i] = arr[j];
			i++;
		}

		while (i < j && arr[i] > val) { i++; }
		if (i < j)
		{
			arr[j] = arr[i];
			j--;
		}
	}
	arr[i] = val;
	return i;
}
void selectMinKNum(int arr[], int begin, int end, int k)
{
	int pos = Partation(arr, begin, end);
	if (pos == k - 1)
	{
		return;
	}
	else if (k > pos)
	{
		selectMinKNum(arr, pos + 1, end, k);
	}
	else
	{
		selectMinKNum(arr, begin, pos - 1, k);
	}
}
int main()
{
	int arr[] = { 23, 45, 67, 12, 4, 9, 7, 10, 78 };
	int size = sizeof arr / sizeof arr[0];

	//求前3个最小的数 ,分割的时候左边是小于基准的数， 右边是大于基准的数
	//求3个最大的数， 分割的时候左边是大于基准的数， 右边是小于基准的数
	int k = 3;
	selectMinKNum(arr, 0, size-1, k);

	for (int i = 0; i < k; ++i)
	{
		cout << arr[i] << " ";
	}
	cout << endl;
}

#endif 