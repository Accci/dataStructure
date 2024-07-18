#include "common.h"

/*
红黑树
不是一颗平衡树， 节点的左右子树高度差，长的不超过短的2倍

查询较多选 AVL

红黑树的定义：
1.每个节点都是有颜色，不是黑就是红
2.nullptr是黑色
3.root必须是黑色
4.每个红色节点必须右两个黑色的子节点，不能有连续的红色节点
5.从根节点开始，到任意一个叶子节点的路径上，黑色节点的数量必须是一致的


红黑树的插入操作：
1.空树   ---》插入节点：黑色

2.非空  ---》插入节点----叶子节点：红色！！！
	检查父节点的颜色
		黑色  ---》 插入完成
		红色  ---》 插入调整
插入调整 

	情况1 ：父亲跟爷爷的颜色交换，继续向上调整
		A(b)	 A.color = RED 			A(r)      x = A  继续向上调整
	  /    \     B.color = BLACK	   /    \     root.color = BLACK
	B(r)    D(r) D.color = BLACK	B(b)    D(b)   
	/			    ----》	         /
   x(r)新插						x(r)新插


   情况2: 叔叔的颜色也是黑
	   A(b)						 A(r)					  B(b)
	  /    \					/    \					 /	  \
    B(r)    D(b)    ----》	 B(b)    D(b)    ---》	x(r)新插   A(r)
	/						 /									\
x(r)新插					x(r)新插							D(b)

	先交换A B 的颜色， 但是AD分支会少一个黑节点， 在以A右旋 rightRate(A)

	情况3：
	   A(b)						 A(b)					 
	  /    \					/    \					
	B(r)    D(b)    ----》	 x(r)   D(b)   情况2 
	 \						 /									
	x(r)新插				B(r)

	先以B节点左旋 leftRotate(B)   ---> 得到情况2


	删除操作
	删除的节点右两个孩子   ==>前驱结点删除
	删除的节点右一个孩子  ==> 用孩子替换到删除的位置

	1.如果删除的是一个红色的节点,不做任何删除调整,正常删
	2.如果删除的是一个黑色的节点,分两种情况
		1.补上来的孩子是红色,则变黑
		2.补上来的孩子是黑色,往兄弟借一个黑色节点
			1.如果兄弟为黑, 且右孩子是红, 
					A(b/r)											C(b/r)
					/  \			C.color = A.color				/  \
				B(b)    C(b)   -->	A.color = BLACK       -->	   A(b) D(b)
				(delete) \			C.right.color = BLACK				 \
						  D(r)		leftRotate(A)						  E(b)
							\
							 E(b)
			2. 兄弟为黑，但左孩子 为红，右孩子黑
					A(b/r)											A(b/r)
					/   \											/   \
				B(b)    C(b)   -->	D.color = BLACK       -->	   B(b) D(b)  -->情况1
			(delete)	/  \		C.color = RED						  \
					   D(r)	 E(b)	rightRotate(C)						  C(r)
																		    \
																			E(b)

		  3. 兄弟的子节点全黑， 就把兄弟变红，向上回溯（1）发现指向红色节点，直接变黑 （2）还是黑还是属于这4种情况
					A(b/r)										A(b)	 
					/   \										/   \	 
				B(b)    C(b)   -->	C.color = RED    -->	 B(b)    C(r)   
			(delete)	/  \		 								/  \	  
					   D(b)	 E(b)								   D(b)  E(b)

		  4. 兄弟节点是红，其父节点，子节点都是黑

					 A(b)										C(b)
					/   \			A.color = RED 			   /   \
				B(b)    C(r)   -->	C.color = BLACK    -->	 A(r)    E(b)   ===》 转到上面三种情况
			(delete)	/  \		leftRotate(A)			 /  \	
					   D(b)	 E(b)						  B(b)  D(b)	
														(delete)
*/
#if 0
template<typename T>
class RBTree
{
public:
	RBTree() :root_(nullptr) {}


	//插入操作
	void insert(const T &val)
	{
		if (root_ == nullptr)
		{
			root_ = new Node(val);
			return;
		}
		Node* parent = nullptr;
		Node* cur = root_;
		while (cur != nullptr)
		{
			if (cur->data_ > val)
			{
				parent = cur;
				cur = cur->left_;
			}
			else if (cur->data_ < val)
			{
				parent = cur;
				cur = cur->right_;
			}
			else
			{
				return;
			}
		}

		//设置当前节点的parent和颜色
		Node* node = new Node(val, parent, nullptr, nullptr, RED);
		if (parent->data_ > val)
		{
			parent->left_ = node;
		}
		else
		{
			parent->right_ = node;
		}

		//如果新插入的红色节点,父节点也是红色,不满足红黑树的性质
		if (RED == color(parent))
		{
			fixAfterInsert(node);
		}
	}

	void remove(const T& val)
	{
		if (root_ == nullptr)
		{
			return;
		}

		Node* cur = root_;
		while (cur != nullptr)
		{
			if (cur->data_ > val)
			{
				cur = cur->left_;
			}
			else if (cur->data_ < val)
			{
				cur = cur->right_;
			}
			else
			{
				break;
			}

			if (cur == nullptr)  // 没有找到val节点
			{
				return;
			}
		}
		//删除前驱节点 
		if (cur->left_ != nullptr && cur->right_ != nullptr)
		{
			Node* pre = cur->left_;
			while (pre->right_ != nullptr)
			{
				pre = pre->right_;
			}
			cur->data_ = pre->data_;
			cur = pre;   //cur指向前驱节点
		}

		//删除cur指向的节点
		Node* child = cur->left_;
		if (child == nullptr)
		{
			child = cur->right_;
		}

		if (child != nullptr)
		{
			child->parent_ = cur->parent_;
			if (cur->parent_ == nullptr)
			{
				root_ = child;
			}
			else
			{

				if (cur->parent_->left_ == cur)
				{
					cur->parent_->left_ = child;
				}
				else
				{
					cur->parent_->right_ = child;
				}
			}

			Color c = color(cur);
			delete cur;
			if (c == BLACK)
			{
				fixAfterRemove(child);
			}
		}
		else  //child == nullptr
		{
			if (cur->parent_ == nullptr)
			{
				delete cur;
				root_ = nullptr;
				return;
			}
			else
			{
				if (color(cur) == BLACK)
				{
					fixAfterRemove(cur);
				}

				if (cur->parent_->left_ == cur)
				{
					cur->parent_->left_ = nullptr;
				}
				else
				{
					cur->parent_->right_ = nullptr;
				}
				delete cur;
			}
		}
	}
private:

	enum Color
	{
		BLACK,
		RED
	};
	struct Node
	{
		Node(T data = T(), Node* parent = nullptr, Node* left = nullptr, Node* right = nullptr, Color color = BLACK)
			:data_(data)
			, left_(left)
			, right_(right)
			, parent_(parent)
			, color_(color)
		{}
		T data_;
		Node* left_;
		Node* right_;
		Node* parent_;
		Color color_;
	};

	Node* root_;

	Color color(Node * node)
	{
		return node == nullptr ? BLACK : node->color_;
	}

	void setColor(Node * node, Color color)
	{
		node->color_ = color;
	}

	Node* left(Node * node)
	{
		return node->left_;
	}

	Node* right(Node * node)
	{
		return node->right_;
	}

	Node* parent(Node * node)
	{
		return node->parent_;
	}

	//左旋转
	void leftRotate(Node * node)
	{
		Node* child = node->right_;
		child->parent_ = node->parent_;
		if (node->parent_ == nullptr)
		{
			root_ = child;
		}
		else
		{
			if (node->parent_->left_ == node)
			{
				node->parent_->left_ = child;
			}
			else
			{
				node->parent_->right_ = child;
			}
		}

		node->right_ = child->left_;
		if (child->left_ != nullptr)
		{
			child->left_->parent_ = node;
		}

		child->left_ = node;
		node->parent_ = child;
	}

	//右旋转
	void rightRotate(Node * node)
	{
		Node* child = node->left_;
		child->parent_ = node->parent_;
		if (node->parent_ == nullptr)   //node原来是root
		{
			root_ = child;
		}
		else
		{
			//node原来在父节点的左边
			if (node->parent_->left_ == node)
			{
				node->parent_->left_ = child;
			}
			else
			{
				//node原来在父节点的右边
				node->parent_->right_ = child;
			}
		}
		node->left_ = child->right_;
		if (child->right_ != nullptr)
		{
			child->right_->parent_ = node;
		}
		child->right_ = node;
		node->parent_ = child;
	}

	void fixAfterInsert(Node * node)
	{
		while (color(parent(node)) == RED)
		{
			//插入的节点在左子树当中
			if (left(parent(parent(node))) == parent(node))
			{
				Node* uncle = right(parent(parent(node)));
				if (RED == color(uncle))  //情况一
				{
					setColor(parent(node), BLACK);		//父节点设为黑
					setColor(uncle, BLACK);				//叔叔节点设为黑
					setColor(parent(parent(node)), RED); //yeye节点设为红
					node = parent(parent(node));
				}
				else //uncle节点位黑
				{
					   //先处理情况三
					if (right(parent(node)) == node)
					{
						node = parent(node);
						leftRotate(node);
					}
					//统一处理情况二
					setColor(parent(node), BLACK);
					setColor(parent(parent(node)), RED);
					rightRotate(parent(parent(node)));
					break;
				}
			}
			else
			{
				Node* uncle = left(parent(parent(node)));
				if (RED == color(uncle))  //情况一
				{
					setColor(parent(node), BLACK);		//父节点设为黑
					setColor(uncle, BLACK);				//叔叔节点设为黑
					setColor(parent(parent(node)), RED); //爷爷节点设为红
					node = parent(parent(node));
				}
				else //uncle节点位黑
				{
					//先处理情况三
					if (left(parent(node)) == node)
					{
						node = parent(node);
						rightRotate(node);
					}
					//统一处理情况二
					setColor(parent(node), BLACK);
					setColor(parent(parent(node)), RED);
					leftRotate(parent(parent(node)));
					break;
				}
			}
		}
		//此处强制root为黑色节点
		setColor(root_, BLACK);
	}

	void fixAfterRemove(Node* node)
	{
		while (node != root_ && color(node) == BLACK)
		{
			if (left(parent(node)) == node)
			{
				//删除的黑色节点在左子树
				Node* brother = right(parent(node));
				if (color(brother) == RED)
				{
					setColor(parent(node), RED);
					setColor(brother, BLACK);
					leftRotate(parent(node));
					brother = right(parent(node));
				}

				if (color(left(brother)) == BLACK && color(right(brother)) == BLACK)  //情况三
				{
					setColor(brother, RED);
					node = parent(node);
				}
				else
				{
					if (color(right(brother)) != RED)   //情况二
					{
						setColor(brother, RED);
						setColor(left(brother), BLACK);
						rightRotate(brother);
						brother = right(parent(node));
					}

					//归结到情况一
					setColor(brother, color(parent(node)));
					setColor(parent(node), BLACK);
					setColor(right(brother), BLACK);
					leftRotate(parent(node));
					break;
				}
			}
			else
			{
				//删除的在右子树
				Node* brother = left(parent(node));
				if (color(brother) == RED)
				{
					setColor(parent(node), RED);
					setColor(brother, BLACK);
					rightRotate(parent(node));
					brother = left(parent(node));
				}

				if (color(left(brother)) == BLACK && color(right(brother)) == BLACK)  //情况三
				{
					setColor(brother, RED);
					node = parent(node);
				}
				else
				{
					if (color(left(brother)) != RED)   //情况二
					{
						setColor(brother, RED);
						setColor(right(brother), BLACK);
						leftRotate(brother);
						brother = left(parent(node));
					}

					//归结到情况一
					setColor(brother, color(parent(node)));
					setColor(parent(node), BLACK);
					setColor(left(brother), BLACK);
					rightRotate(parent(node));
					break;
				}
			}
		}
		// 补上来的孩子是红色，直接涂成黑色
		setColor(node, BLACK);  
	}
};

int main()
{
	RBTree<int> rb;

	for (int i = 1; i <= 10; ++i)
	{
		rb.insert(i);
	}
	rb.remove(9);
	rb.remove(10);
	rb.remove(5);
	rb.remove(3);
	return 0;
}

#endif