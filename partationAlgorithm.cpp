#include "common.h"
#include <algorithm>
#include <vector>

#if 0
//二分搜索
bool binarySearch(vector<int>& vec, int l, int r, int val)
{
	if (l > r)
	{
		return false;
	}
	int mid = l + (r - l) / 2;
	if (vec[mid] == val)
	{
		return true;
	}
	else if (vec[mid] > val)
	{
		binarySearch(vec, l, mid - 1, val);
	}
	else
	{
		binarySearch(vec, mid + 1, r, val);
	}
}
int main()
{
	vector<int> vec;
	for (int i = 0; i <= 10; ++i)
	{
		vec.push_back(rand() % 100);
	}

	sort(vec.begin(), vec.end());
	for (int v : vec)
	{
		cout << v << " ";
	}
	cout << endl;

	cout << binarySearch(vec, 0, vec.size()-1, 66) << endl;
}
#endif

#if 0
//快速排序
int partation1(vector<int>& vec, int l, int r)
{
	int val = vec[l];
	while (l < r)
	{
		while (l < r && vec[r] >= val)
		{
			r--;
		}
		if (l < r)
		{
			vec[l++] = vec[r];
		
		}
		while (l < r && vec[l] < val)
		{
			l++;
		}

		if (l < r)
		{
			vec[r--] = vec[l];
		}

	}

	vec[l] = val;
	return l;
}
void quickSort1(vector<int>& vec, int l, int r)
{
	if (l >= r)
	{
		return;
	}
	int pos = partation1(vec, l, r);
	quickSort1(vec, l, pos - 1);
	quickSort1(vec, pos + 1, r);
}
int main()
{
	vector<int> vec;
	for (int i = 0; i <= 10; ++i)
	{
		vec.push_back(rand() % 100);
	}

	quickSort1(vec, 0, vec.size()-1);
	for (int v : vec)
	{
		cout << v << " ";
	}
	cout << endl;
	return 0;
}

#endif 


#if 0
//求topK 
//大根堆/小根堆
//快排划分函数
int partation(vector<int>& vec, int l, int r)
{
	int val = vec[l];
	while (l < r)
	{
		while (l < r && vec[r] >= val)
		{
			r--;
		}

		if (l < r)
		{
			vec[l++] = vec[r];
		}
		while (l < r && vec[l] < val)
		{
			l++;
		}

		if (l < r)
		{
			vec[r--] = vec[l];
		}
	}
	vec[l] = val;
	return l;
}

//找前topk大的
int max_select_topK(vector<int>& vec, int l, int r, int k)
{
	int pos = partation(vec, l, r);
	if (pos == vec.size() - k)
	{
		return pos;
	}
	else if (pos < vec.size() - k)
	{
		max_select_topK(vec, pos + 1, r, k);
	}
	else
	{
		max_select_topK(vec, l, pos - 1, k);
	}
}

//找前topk小的
int min_select_topK(vector<int>& vec, int l, int r, int k)
{
	int pos = partation(vec, l, r);
	if (pos == k - 1)
	{
		return pos;
	}
	else if (pos < k - 1)
	{
		min_select_topK(vec, pos + 1, r, k);
	}
	else
	{
		min_select_topK(vec, l, pos - 1, k);
	}
}
int main()
{
	vector<int> vec;

	for (int i = 0; i < 30; ++i)
	{
		vec.push_back(rand() % 100);
	}
	//求topk大的
	int pos = max_select_topK(vec, 0, vec.size() - 1, 4);
	cout << "第topK大的val:" << vec[pos] << endl;
	cout << "前topK大的：";
	for (int i = pos; i < vec.size(); ++i)
	{
		cout << vec[i] << " ";
	}
	cout << endl;
	//求第topK 小的元素
	pos = min_select_topK(vec, 0, vec.size() - 1, 4);
	cout << "第topK小的val:" << vec[pos] << endl;
	cout << "前topK小的：";
	for (int i = 0; i <= pos; ++i)
	{
		cout << vec[i] << " ";
	}
	cout << endl;
	sort(vec.begin(), vec.end());
	for (int v : vec)
	{
		cout << v << " ";
	}
	cout << endl;
	return 0;
}

#endif

#if 0

//分治算法的应用  --- 归并排序
void merge(vector<int>& vec, int low, int high, int mid)
{
	vector<int> tmp;
	tmp.reserve(high - low + 1);
	int i = low;
	int j = mid + 1;

	while (i <= mid && j <= high)
	{
		if (vec[i] < vec[j])
		{
			tmp.push_back(vec[i++]);
		}
		else
		{
			tmp.push_back(vec[j++]);
		}
	}

	while (i <= mid)
	{
		tmp.push_back(vec[i++]);
	}

	while (j <= high)
	{
		tmp.push_back(vec[j++]);
	}

	for (int k = low; k <= high; ++k)
	{
		vec[k] = tmp[k - low];
	}
}

void mergeSort(vector<int>& vec, int l, int r)
{
	if (l >= r)
	{
		return;
	}
	int mid = l + (r - l) / 2;
	mergeSort(vec, l, mid);
	mergeSort(vec, mid + 1, r);

	merge(vec, l, r, mid);
}

int main()
{
	vector<int> vec;
	for (int i = 0; i < 11; ++i)
	{
		vec.push_back(rand() % 100);
	}

	for (int v : vec)
	{
		cout << v << " ";
	}
	cout << endl;

	mergeSort(vec, 0, vec.size() - 1);

	for (int v : vec)
	{
		cout << v << " ";
	}
	cout << endl;
	return 0;
}


#endif

#if 0
//归并的应用  合并k个有序链表
struct ListNode
{
	int val;
	ListNode* next;
	ListNode(int data = 0) :val(data), next(nullptr) {}
};

ListNode* mergeTwoLink(ListNode* p1, ListNode* p2)
{
	ListNode* head = nullptr;
	if (p1 == nullptr)
	{
		return p2;
	}
	if (p2 == nullptr)
	{
		return p1;
	}

	if (p1->val > p2->val)
	{
		head = p2;
		p2 = p2->next;
	}
	else
	{
		head = p1;
		p1 = p1->next;
	}

	ListNode* p = head;
	while (p1 != nullptr && p2 != nullptr)
	{
		if (p1->val > p2->val)
		{
			p->next = p2;
			p = p2;
			p2 = p2->next;
		}
		else
		{
			p->next = p1;
			p = p1;
			p1 = p1->next;
		}

		if (p1 != nullptr)
		{
			p->next = p1;
		}
		if (p2 != nullptr)
		{
			p->next = p2;
		}
		
	}
	return head;
}

ListNode* mergeKLink(vector<ListNode*>& vlink, int i, int j)
{
	if (i >= j)
		return vlink[i];
	
	int mid = (i + j) / 2;

	ListNode* left = mergeKLink(vlink, i, mid);
	ListNode* right = mergeKLink(vlink, mid + 1, j);
	return mergeTwoLink(left, right);
}


ListNode* init_link(initializer_list<int>list)
{
	ListNode* head = nullptr;
	ListNode* p = nullptr;
	for (int v : list)
	{
		if (head == nullptr)
		{
			head = new ListNode(v);
			p = head;
		}
		else
		{
			p->next = new ListNode(v);
			p = p->next;
		}
	}
	return head;
}


int main()
{
	ListNode* p1 = init_link({ 3, 6, 8 });
	ListNode* p2 = init_link({ 2, 4 });
	ListNode* p3 = init_link({ 1, 5, 9});
	ListNode* p4 = init_link({ 0,7 });
	ListNode* p5 = init_link({ 10 });

	vector<ListNode*> vlink;
	vlink.push_back(p1);
	vlink.push_back(p2);
	vlink.push_back(p3);
	vlink.push_back(p4);
	vlink.push_back(p5);

	ListNode* p = mergeKLink(vlink, 0, vlink.size() - 1);

	ListNode* q = p;
	while (q != nullptr)
	{
		cout << q->val << " ";
		q = q->next;
	}
	cout << endl;

	return 0;
}

#endif

#if 0

//对数时间求解中位数
double middleValue(vector<int>& nums1, int len1, vector<int>nums2, int len2)
{
	if (len1 > len2)
	{
		return middleValue(nums2, len2, nums1, len1);
	}	

	if (len1 == 0)
	{
		int k = (len2 - 1) / 2;
		if (len2 % 2 == 0)
		{
			return (nums2[k] + nums2[k + 1]) * 1.0 / 2;
		}
		else
		{
			return nums2[k];
		}
	}
	int i = 0;
	int j = 0;
	int begin = 0;
	int end = len1;

	int k = (len1 + len2 + 1) / 2;

	while (begin <= end)
	{
		i = (begin + end) / 2;
		j = k - i;
		if (i > 0 && j < len2 && nums1[i - 1] > nums2[j])
		{
			end = i - 1;
		}
		else if (j > 0 && i < len1 && nums2[j - 1] > nums1[i])
		{
			begin = i + 1;
		}
		else
		{
			break;
		}
	}
	int left = 0; 
	if (i == 0)
	{
		left = nums2[j - 1];
	}
	else if (j == 0)
	{
		left = nums1[i - 1];
	}
	else
	{
		left = max(nums1[i - 1], nums2[j - 1]);
	}
	int right = 0;
	if (i == len1)
	{
		right = nums2[j];
	}
	else if (j == len2)
	{
		right = nums1[i];
	}
	else
	{
		right = min(nums1[i], nums2[j]);
	}
	

	//找到了合适的i和j的值
	if ((len1 + len2) % 2 == 0)  //偶数长度
	{
		return (left + right) * 1.0 / 2;
	}
	else              //奇数长度
	{
		return left;
	}

}

int main()
{
	vector<int> vec1;
	vector<int> vec2;

	for (int i = 0; i < 10; ++i)
	{
		vec1.push_back(rand() % 100);
	}

	for (int i = 0; i < 5; ++i)
	{
		vec2.push_back(rand() % 100);
	}
	vector<int> vec= vec1;
	for (int v : vec2)
	{
		vec.push_back(v);
	}

	sort(vec.begin(), vec.end());
	for (int v : vec)
	{
		cout << v << " ";
	}
	cout << endl;
	sort(vec1.begin(), vec1.end());
	sort(vec2.begin(), vec2.end());

	double mid = middleValue(vec1, vec1.size(), vec2, vec2.size());

	cout << "middleValue:" << mid << endl;
}

#endif 
