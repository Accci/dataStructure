#include "common.h"

//非递归
#if 0
int BinarySearch(int arr[], int size, int val)
{
	int first = 0;
	int last = size - 1;
	while (first <= last)
	{
		int mid = (first + last) >> 1;
		if (arr[mid] == val)
		{
			return mid;
		}
		else if (arr[mid] > val)
		{
			last = mid - 1;
		}
		else
		{
			first = mid + 1;
		}
	}
	return -1;
}
#endif

#if 0
//递归
int BinarySearchHelper(int arr[], int i, int j, int val)
{
	if (i > j)
		return -1;
	int mid = (i + j) / 2;
	if (arr[mid] == val)
		return mid;
	else if (arr[mid] > val)
		return BinarySearchHelper(arr, i, mid - 1, val);
	else
		return BinarySearchHelper(arr, mid + 1, j, val);
}

int BinarySearch(int arr[], int size, int val)
{
	return BinarySearchHelper(arr, 0, size - 1, val);
}

int main()
{
	int arr[] = { 12, 25, 34, 39, 45, 57, 63, 78, 82, 96, 100 };
	cout << BinarySearch(arr, 11, 45) << endl;
	cout << BinarySearch(arr, 11, 12) << endl;
	cout << BinarySearch(arr, 11, 64) << endl;
	return 0;
}
#endif