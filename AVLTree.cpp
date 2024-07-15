#include "common.h"
#if 0
/*
	平衡二叉搜索树：

	节点失衡的原因：
	1.左孩子的左子树太高
	右旋								//右旋
	 A node								child = node->left;
	/									node->left = child->right;
   B child   ====>    B					child->right = node;
  / \				 / \
C    X				C	A
					   /
					  X
	2.右孩子的右子树太高
 A										//左旋
  \										child = node->right;
   B     ====>       B					node->right = child->left;
  / \				/ \					child->left = node;
 X	 C			   A   C	
					\
					 X	

	3.左孩子的右子树太高   左右旋转  左平衡操作
		A            A
	   /			/
      B    ===》   C  ==>    C
	   \		  /			/  \
		C        B		   B    A
	4. 右孩子的左子树太高   右左   右平衡操作
 */

template<typename T>
class AVLTree
{
public:
	AVLTree() :root_(nullptr)
	{}
	//插入操作
	void insert(const T& val)
	{
		root_ = insert(root_, val);

	}

	void remove(const T& val)
	{
		root_ = remove(root_, val);
	}
private:
	struct Node
	{
		Node(T data = T()) :data_(data), left_(nullptr), right_(nullptr), height_(1) {}
		T data_;
		Node* left_;
		Node* right_;
		int height_;
	};

	//返回节点的高度值
	int  height(Node *node)
	{
		return node == nullptr ? 0 : node->height_;
	}

	//右旋转操作,以参数Node为轴做右旋转操作，并把新的根节点返回
	Node* rightRotate(Node* node)
	{
		Node* child = node->left_;
		node->left_ = child->right_;
		child->right_ = node;

		//高度更新
		node->height_ = max(height(node->left_), height(node->right_)) + 1;
		child->height_ = max(height(child->left_), height(child->right_)) + 1;

		//返回旋转后的子树新的根节点
		return child;
	}

	//左旋
	Node* leftRotate(Node* node)
	{
		Node* child = node->right_;
		node->right_ = child->left_;
		child->left_ = node;

		node->height_ = max(height(node->left_), height(node->right_)) + 1;
		child->height_ = max(height(child->left_), height(child->right_)) + 1;
		return child;
	}

	//左平衡
	Node* leftBalance(Node* node)
	{
		node->left_ = leftRotate(node->left_);
		return rightRotate(node);
	}
	//右平衡
	Node* rightBalance(Node* node)
	{
		node->right_ = rightRotate(node->right_);
		return leftRotate(node);
	}

	Node* insert(Node* node, const T& val)
	{
		if (node == nullptr)
		{
			return new Node(val);
		}

		if (node->data_ > val)
		{
			node->left_ = insert(node->left_, val);
			if (height(node->left_) - height(node->right_) > 1)
			{
				//左孩子的左子树
				if (height(node->left_->left_) >= height(node->left_->right_))
				{
					node = rightRotate(node);
				}
				else
				{
					//左平衡
					node = leftBalance(node);
				}
			}
		}
		else if (node->data_ < val)
		{
			node->right_ = insert(node->right_, val);

			if (height(node->right_) - height(node->left_) > 1)
			{
				//右孩子右子树
				if (height(node->right_->right_) >= height(node->right_->left_))
				{
					node = leftRotate(node);
				}
				else
				{
					//右孩子左子树
					node = rightBalance(node);
				}
			}
		}
		else
		{
			;//找到相同的节点了 
		}

		node->height_ = max(height(node->left_), height(node->right_)) + 1;
		return node;
	}

	Node* remove(Node* node, const T& val)
	{
		if (node == nullptr)
			return nullptr;
		if (node->data_ > val)
		{
			node->left_ = remove(node->left_, val);
			if (height(node->right_) - height(node->left_) > 1)
			{
				// 右孩子的右子树高
				if (height(node->right_->right_) >= height(node->right_->left_))
				{
					node = leftRotate(node);
				}
				else
				{
					//右孩子的左子树高
					node = rightBalance(node);
				}

			}
		}
		else if (node->data_ < val)
		{
			node->right_ = remove(node->right_, val);
			
			if (height(node->left_) - height(node->right_) > 1)
			{
				//左孩子的左子树高
				if (height(node->left_->left_) >= height(node->left_->right_))
				{
					node = rightRotate(node);
				}
				else
				{
					//左孩子的右子树高
					node = leftBalance(node);
				}

			}
		}
		else
		{
			//找到了先处理右两个孩子的节点删除情况
			if (node->left_ != nullptr && node->right_ != nullptr)
			{
				//为了避免删除前驱或后继节点造成节点的失衡，谁高删谁
				if (height(node->left_) >= height(node->right_))
				{
					//删前驱
					Node* pre = node->left_;
					while (pre->right_ != nullptr)
					{
						pre = pre->right_;
					}
					node->data_ = pre->data_;
					node->left_ = remove(node->left_, pre->data_);  //删除前驱节点
				}
				else
				{
					//删除后继
					Node* post = node->right_;
					while (post->left_ != nullptr)
					{
						post = post->left_;
					}
					node->data_ = post->data_;
					node->right_ = remove(node->right_, post->data_); //删除后继节点
				}

			}
			else  //删除节点， 最多右一个孩子
			{
				if (node->left_ != nullptr)
				{
					Node* left = node->left_;
					delete node;
					return left;
				}else if (node->right_ != nullptr)
				{
					Node* right = node->right_;
					delete node;
					return right;
				}
				else
				{
					return nullptr;
				}
			}
		}
		node->height_ = max(height(node->left_), height(node->right_)) + 1;
		return node;
	}

	//
	Node* root_;
};


int main()
{
	AVLTree<int> avl;

	for (int i = 1; i <= 10; ++i)
	{
		avl.insert(i);
	}

	avl.remove(9);
	avl.remove(10);
	avl.remove(6);
	avl.remove(1);
	avl.remove(2);
	avl.remove(3);

	return 0;
}

#endif