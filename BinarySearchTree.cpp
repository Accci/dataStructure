#include "common.h"
#include <stack>
#include <queue>
#include <functional>
template<typename T, typename Compare =less<T>>
class BST
{
public:
	BST(Compare comp = Compare()) :root_(nullptr), comp_(comp) {}
	//层序遍历的思想
	~BST() {
		if (root_ == nullptr)
			return;
		queue<Node*> que;
		que.push(root_);
		while (!que.empty())
		{
			Node* front = que.front();
			que.pop();
			if (front->leftChild_ != nullptr)
			{
				que.push(front->leftChild_);
			}

			if (front->rightChild_ != nullptr)
			{
				que.push(front->rightChild_);
			}

			delete front;
		}
	}
public:
	//非递归插入
	void n_insert(const T& val)
	{
		//树空插入根节点
		if (root_ == nullptr)
		{
			root_ = new Node(val);
			return;
		}
		Node* parent = nullptr;
		Node* cur = root_;
		while (cur != nullptr)
		{
			if (cur->data_ == val)
			{
				//不插入元素相同的值
				return;
			}
			else if (comp_(cur->data_, val))  //less  小于
			{
				parent = cur;
				cur = cur->rightChild_;
			}
			else
			{
				parent = cur;
				cur = cur->leftChild_;

			}
		}
		if (comp_(parent->data_, val))
		{
			parent->rightChild_ = new Node(val);
		}
		else
		{
			parent->leftChild_ = new Node(val);

		}

	}

	//递归插入 
	void insert(const T& val)
	{
		root_ = insert(root_, val);
	}

	//非递归删除
	//情况1 ： 删除的节点是叶子节点，左右孩子为空
	//情况2 ： 删除的节点只有一个孩子
	//情况3 ： 删除的节点同时有两个孩子
	void n_remove(const T& val)
	{
		//树空直接返回
		if (root_ == nullptr)
			return;

		Node* parent = nullptr;
		Node* cur = root_;
		while (cur != nullptr)
		{
			if (cur->data_ == val)
			{
				break;
			}
			else if (comp_(cur->data_, val))
			{
				parent = cur;
				cur = cur->rightChild_;
			}
			else
			{
				parent = cur;
				cur = cur->leftChild_;

			}
		}
		//没有找到删除的节点
		if (cur == nullptr)
		{
			return;
		}

		//情况3 ： ====》删除前驱节点， 左子树最大的一个节点（归结成情况1,2）
		if (cur->leftChild_ != nullptr && cur->rightChild_ != nullptr)
		{
			parent = cur;
			Node* pre = cur->leftChild_;
			while (pre->rightChild_ != nullptr)
			{
				parent = pre;
				pre = pre->rightChild_;
			}
			cur->data_ = pre->data_;
			cur = pre;   //让cur指向前驱节点
		}

		Node* child = cur->leftChild_;
		if (child == nullptr)
		{
			child = cur->rightChild_;
		}

		if (parent == nullptr)		//特殊情况，删除的是根节点
		{
			root_ = child;
		}
		else
		{
			if (parent->leftChild_ == cur)
			{
				parent->leftChild_ = child;
			}
			else
			{
				parent->rightChild_ = child;
			}
		}
		delete cur;  // 删除当前节点
	}
	//递归删除
	void remove(const T& val)
	{
		root_ = remove(root_, val);
	}

	//非递归查询
	bool n_query(int val)
	{
		Node* cur = root_;
		while (cur != nullptr)
		{
			if (cur->data_ == val)
			{
				return true;
			}
			else if (comp_(cur->data_, val))
			{
				cur = cur->rightChild_;
			}
			else
			{
				cur = cur->leftChild_;
			}
		}
		return false;
	}
	//递归查询
	bool query(int val)
	{
		return nullptr != query(root_, val);
	}

	//递归前序
	void preOrder()
	{
		cout << "[递归] 前序遍历:";
		preOrder(root_);
		cout << endl;
	}

	//非递归
	void n_preOrder()
	{
		cout << "[非递归] 前序遍历:";
		if (root_ == nullptr)
		{
			return;
		}

		stack<Node*>s1;
		s1.push(root_);
		while (!s1.empty())
		{
			Node* top = s1.top();
			s1.pop();

			cout << top->data_ << " ";
			if (top->rightChild_ != nullptr)
			{
				s1.push(top->rightChild_);
			}

			if (top->leftChild_ != nullptr)
			{
				s1.push(top->leftChild_);
			}
		}

		cout << endl;

	}
	//递归中序
	void inOrder()
	{
		cout << "[递归] 中序遍历:";
		inOrder(root_);
		cout << endl;
	}

	//非递归中序

	void n_inorder()
	{
		cout << "[非递归] 中序遍历:";
		if (root_ == nullptr)
		{
			return;
		}
		stack<Node*>s1;
		Node* cur = root_;
		while (!s1.empty() || cur != nullptr)
		{
			if (cur != nullptr)
			{
				s1.push(cur);
				cur = cur->leftChild_;

			}
			else
			{
				Node* top = s1.top();
				s1.pop();
				cout << top->data_ << " ";

				cur = top->rightChild_;
			}
		}

		cout << endl;
	}

	//递归后序
	void postOrder()
	{
		cout << "[递归] 后序遍历:";
		postOrder(root_);
		cout << endl;
	}

	void n_postOrder()
	{
		cout << "[非递归] 后序遍历:";
		if (root_ == nullptr)
		{
			return;
		}
		stack<Node*>s1;
		stack<Node*>s2;
		s1.push(root_);
		while (!s1.empty())
		{
			Node* top = s1.top();
			s1.pop();

			s2.push(top);

			if (top->leftChild_ != nullptr)
			{
				s1.push(top->leftChild_);
			}

			if (top->rightChild_ != nullptr)
			{
				s1.push(top->rightChild_);
			}
		}

		while (!s2.empty())
		{
			cout << s2.top()->data_ << " ";
			s2.pop();
		}
		cout << endl;
	}

	//递归层序遍历
	void  levelOrder()
	{
		cout << "[递归] 层序遍历:";
		int h = high();

		for (int i = 0; i < h; ++i)
		{
			levelOrder(root_, i);
		}
		cout << endl;
	}

	//非递归层序遍历
	void n_levelOrder()
	{
		cout << "[非递归] 层序遍历:";
		if (root_ == nullptr)
		{
			return;
		}

		queue<Node*>que;
		que.push(root_);
		while (!que.empty())
		{
			Node* front = que.front();
			que.pop();

			cout << front->data_ << " ";

			if (front->leftChild_ != nullptr)
			{
				que.push(front->leftChild_);
			}

			if (front->rightChild_ != nullptr)
			{
				que.push(front->rightChild_);
			}
		}
		cout << endl;
	}

	//递归求二叉树的层数

	int high()
	{
		return high(root_);
	}

	//递归求二叉树的节点个数
	int number()
	{
		return number(root_);
	}

	//区间元素查找， 用中序遍历
	void searchElement(vector<T>& vec, int i, int j)
	{
		searchElement(root_, vec, i, j);
	}

	//判断一颗树是否是BST树
	bool isBSTree()
	{
		Node* pre = nullptr;  //前驱结点
		return isBSTree(root_, pre);
	}

	//判断二叉树子树问题
	bool isSubtree(BST<T, Compare>& child)
	{
		if (child.root_ == nullptr)
		{
			return true;
		}
		Node* cur = root_;
		while (cur != nullptr)
		{
			if (cur->data_ == child.root_->data_)
			{
				break;
			}
			else if (comp_(cur->data_, child.root_->data_))
			{
				cur = cur->rightChild_;
			}
			else
			{
				cur = cur->leftChild_;
			}
		}
		if (cur == nullptr)
		{
			return false;
		}

		return isSubtree(cur, child.root_);
	}

	//求最近公共祖先
	int getLCA(T val1, T val2)
	{
		Node* node = getLCA(root_, val1, val2);
		if (node == nullptr)
		{
			throw " no! LCA";
		}
		else
		{
			return node->data_;
		}
	}

	//镜像反转问题
	void  mirror01()
	{
		mirror01(root_);
	}

	//二叉树对称问题

	bool mirror02()
	{
		if (root_ == nullptr)
		{
			return true;
		}
		return mirror02(root_->leftChild_, root_->rightChild_);
	}

	//根据前序和中序重建二叉树
	void buildTree(int pre[], int i, int j, int in[], int m, int n)
	{
		root_ = _buildTree(pre, i, j, in, m, n);
	}

	//判断二叉树是否为平衡树
	bool isBalance()
	{
		int l = 0;
		bool flag = true;
		isBalance(root_, l, flag);
		return flag;
	}

	//求中序倒数第K个节点
	int getVal(int k)
	{
		Node* node = getVal(root_, k);
		if (node == nullptr)
		{
			throw "no NO.k";
		}
		return node->data_;
	}

public:
	//private:
	struct Node
	{
		Node(T data = T()) :data_(data), leftChild_(nullptr), rightChild_(nullptr) {}
		T data_;
		Node* leftChild_;
		Node* rightChild_;
	};



	void preOrder(Node* node)
	{
		if (node != nullptr)
		{
			cout << node->data_ << " ";
			preOrder(node->leftChild_);
			preOrder(node->rightChild_);
		}
	}

	void inOrder(Node* node)
	{
		if (node != nullptr)
		{

			inOrder(node->leftChild_);
			cout << node->data_ << " ";
			inOrder(node->rightChild_);
		}
	}

	void postOrder(Node* node)
	{
		if (node != nullptr)
		{

			postOrder(node->leftChild_);
			postOrder(node->rightChild_);
			cout << node->data_ << " ";
		}
	}

	int high(Node* node)
	{
		if (node == nullptr)
		{
			return 0;
		}

		int left = high(node->leftChild_);
		int right = high(node->rightChild_);
		return left > right ? left + 1 : right + 1;
	}

	int number(Node* node)
	{
		if (node == nullptr)
			return 0;
		return number(node->leftChild_) + number(node->rightChild_) + 1;
	}

	void levelOrder(Node* node, int i)
	{
		if (node == nullptr)
		{
			return;
		}
		if (i == 0)
		{
			cout << node->data_ << " ";
		}
		levelOrder(node->leftChild_, i - 1);
		levelOrder(node->rightChild_, i - 1);
	}

	Node* insert(Node* node, const T& val)
	{
		if (node == nullptr)
		{
			return new Node(val);
		}
		if (node->data_ == val)
		{
			return node;
		}
		else if (comp_(node->data_, val))
		{
			node->rightChild_ = insert(node->rightChild_, val);

		}
		else
		{
			node->leftChild_ = insert(node->leftChild_, val);
		}
		return node;
	}

	Node* query(Node* node, const T& val)
	{
		if (node == nullptr)
			return nullptr;
		if (node->data_ == val)
		{
			return node;
		}
		else if (comp_(node->data_, val))
		{
			return query(node->rightChild_, val);
		}
		else
		{
			return query(node->leftChild_, val);
		}
	}

	Node* remove(Node* node, const T& val)
	{
		if (node == nullptr)
		{
			return nullptr;
		}

		if (node->data_ == val)
		{
			if (node->leftChild_ != nullptr && node->rightChild_ != nullptr)
			{
				Node* pre = node->leftChild_;
				while (pre->rightChild_ != nullptr)
				{
					pre = pre->rightChild_;
				}
				node->data_ = pre->data_;
				node->leftChild_ = remove(node->leftChild_, pre->data_);
			}
			else
			{
				if (node->leftChild_ != nullptr)   //有左孩子没有右孩子
				{
					Node* left = node->leftChild_;
					delete node;
					return left;
				}
				else if (node->rightChild_ != nullptr) //有右孩子没有左孩子
				{
					Node* right = node->rightChild_;
					delete node;
					return right;
				}
				else  //删除叶子节点
				{
					delete node;
					return nullptr;
				}

			}

		}
		else if (comp_(node->data_, val))
		{
			node->rightChild_ = remove(node->rightChild_, val);
		}
		else
		{
			node->leftChild_ = remove(node->leftChild_, val);
		}

		return node;   // 更新父节点
	}





	void searchElement(Node* node, vector<T>& vec, int i, int j)
	{
		if (node == nullptr)
			return;
		if (node->data_ > i)
		{
			searchElement(node->leftChild_, vec, i, j);
		}
		if (node->data_ >= i && node->data_ <= j)
		{
			vec.push_back(node->data_);
		}

		if (node->data_ < j)
		{
			searchElement(node->rightChild_, vec, i, j);
		}
	}

	bool isBSTree(Node* node, Node*& pre)
	{
		if (node == nullptr)
		{
			return true;
		}
		if (!isBSTree(node->leftChild_, pre))
		{
			return false;
		}
		if (pre != nullptr)
		{
			if (comp_(node->data_, pre->data_))
			{
				return false;
			}
		}
		pre = node;
		return isBSTree(node->rightChild_, pre);
	}

	bool isSubtree(Node* father, Node* child)
	{
		if (father == nullptr && child == nullptr)
		{
			return true;
		}

		if (child == nullptr)
		{
			return true;
		}

		if (father == nullptr)
		{
			return false;
		}

		//判断不相同
		if (father->data_ != child->data_)
		{
			return false;
		}
		return isSubtree(father->leftChild_, child->leftChild_) && isSubtree(father->rightChild_, child->rightChild_);

	}

	Node* getLCA(Node* node, T val1, T val2)
	{
		if (node == nullptr)
			return node;
		if (comp_(node->data_, val1) && comp_(node->data_, val2))
		{
			return getLCA(node->rightChild_, val1, val2);
		}
		else if (comp_(val1, node->data_) && comp_(val2, node->data_))
		{
			return getLCA(node->leftChild_, val1, val2);
		}
		else
		{
			return node;
		}
	}

	void mirror01(Node* node)
	{
		if (node == nullptr)
			return;
		Node* tmp = node->leftChild_;
		node->leftChild_ = node->rightChild_;
		node->rightChild_ = tmp;


		mirror01(node->leftChild_);
		mirror01(node->rightChild_);
	}
	bool mirror02(Node* node1, Node* node2)
	{
		if (node1 == nullptr && node2 == nullptr)
		{
			return true;
		}
		if (node1 == nullptr || node2 == nullptr)
		{
			return false;
		}

		if (node1->data_ != node2->data_)
			return false;
		return mirror02(node1->leftChild_, node2->rightChild_) && mirror02(node1->rightChild_, node2->leftChild_);
	}

	Node* _buildTree(int pre[], int i, int j, int in[], int m, int n)
	{
		if (i > j || m > n)
			return nullptr;
		Node* node = new Node(pre[i]);
		for (int k = m; k <= n; ++k)
		{
			if (in[k] == pre[i])
			{
				node->leftChild_ = _buildTree(pre, i + 1, i + (k - m), in, m, k - 1);
				node->rightChild_ = _buildTree(pre, i + (k - m) + 1, j, in, k + 1, n);
				return node;
			}
		}
		return node;
	}

	int isBalance(Node* node, int l, bool &flag)
	{
		if (node == nullptr)
			return l;
		
		int left = isBalance(node->leftChild_, l + 1, flag);
		if (!flag)
			return left;
		int right = isBalance(node->rightChild_, l + 1, flag);
		if (!flag)
			return right;
		if (abs(left - right) > 1)
		{
			flag = false;
		}
		return max(left, right);
		
	}

	int i = 1;
	Node* getVal(Node* node, int k)
	{
		if (node == nullptr)
		{
			return nullptr;
		}

		Node* right = getVal(node->rightChild_, k);  //
		if (right != nullptr)
			return right;
		if (i++ == k)
		{
			return node;
		} 
		return getVal(node->leftChild_, k);
	}

	Node* root_;
	Compare comp_;
};

//测试判断是否为BST树
void test01()
{
	using Node = BST<int>::Node;
	BST<int> bst;
	bst.root_ = new Node(40);
	Node* node1 = new Node(20);
	Node* node2 = new Node(60);
	//Node* node3 = new Node(30);
	Node* node3 = new Node(50);
	Node* node4 = new Node(80);
	
	bst.root_->leftChild_ = node1;
	bst.root_->rightChild_ = node2;
	node2->leftChild_ = node3;
	node2->rightChild_ = node4;

	cout << bst.isBSTree() << endl;
}
//测试子树问题
void test02()
{
	int arr[] = { 58, 24, 67, 0, 34, 62, 69, 5, 41, 64, 78 };
	BST<int>bst1;
	for (int v : arr)
	{
		bst1.insert(v);
	}
	using Node = BST<int>::Node;
	BST<int> bst;
	bst.root_ = new Node(67);
	Node* node1 = new Node(62);
	Node* node2 = new Node(69);
	Node* node3 = new Node(60);

	bst.root_->leftChild_ = node1;
	bst.root_->rightChild_ = node2;
	//node2->leftChild_ = node3;

	cout << bst1.isSubtree(bst) << endl;
	
}

//测试最近公共祖先
void test03()
{
	int arr[] = { 58, 24, 67, 0, 34, 62, 69, 5, 41, 64, 78 };
	BST<int>bst;
	for (int v : arr)
	{
		bst.insert(v);
	}

	cout << bst.getLCA(34, 62)<< endl;
}


//树对称
void test04()
{
	using Node = BST<int>::Node;
	BST<int> bst;
	bst.root_ = new Node(40);
	Node* node1 = new Node(20);
	Node* node2 = new Node(20);
	Node* node3 = new Node(10);
	Node* node4 = new Node(15);
	Node* node5 = new Node(15);
	Node* node6 = new Node(12);

	bst.root_->leftChild_ = node1;
	bst.root_->rightChild_ = node2;
	node1->leftChild_ = node3;
	node1->rightChild_ = node4;
	node2->leftChild_ = node5;
	node2->rightChild_ = node6;

	cout << bst.mirror02() << endl;
}

//根据前序和中序重建
void test05()
{
	BST<int> bst;
	int pre[] = { 58,24,0,5,34,41,67,62,64,69,78 };
	int in[] = { 0,5,24,34,41,58,62,64,67,69,78 };
	bst.buildTree(pre, 0, 10, in, 0, 10);
	bst.preOrder();
	bst.inOrder();

}

#if 0
int main()
{
	//test05();
#if 0
	using elm = pair<int, string>;
	using functor = function<bool(pair<int, string>, pair<int, string>)>;
	BST<elm, functor> bstree([](elm e1, elm e2)->bool {
		return e1.first > e2.first;
		});
#endif
#if 0
	int arr[] = { 58,24,0,5,34,41,67,62,64,69,78 };
	BST<int> bst;
	for (int v : arr)
	{
		bst.insert(v);
	}
	cout << bst.getVal(4) << endl;
	bst.inOrder();
	//cout << bst.isBalance() << endl;
	//bst.insert(12);
	//cout << bst.isBalance() << endl;
	//bst.inOrder();
	//bst.mirror01();
	//bst.inOrder();
	//vector<int> vec;
	//bst.searchElement(vec, 10, 70);
	//for (int v : vec)
	//{
	//	cout << v << " ";
	//}
	//cout << endl;
#endif
#if 0
	bst.preOrder();
	bst.n_preOrder();
	bst.inOrder();
	bst.n_inorder();
	bst.postOrder();
	bst.n_postOrder();
	bst.levelOrder();
	bst.n_levelOrder();
	bst.n_insert(12);
	cout << bst.query(12) << endl;
	bst.remove(12);
	cout << bst.query(12) << endl;
	bst.remove(34);
	bst.remove(58);
	bst.preOrder();
	cout << bst.query(24) << endl;

#endif
	return 0;
}
#endif
/*
	二叉树遍历
	前序遍历   VLR
	中序遍历   LVR
	后序遍历   LRV

*/

