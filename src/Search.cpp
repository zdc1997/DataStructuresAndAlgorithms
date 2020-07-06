#include <iostream>
#include<stdio.h>
#include "E:\源码\DataStructuresAndAlgorithms\DataStructuresAndAlgorithms\src\tree.cpp"
using namespace std;

#pragma region 查找
//顺序查找，a 为数组，n 为要查找的数组个数，key 为要查找的关键字
int Sequential_Search(int *a, int n, int key)  //传指针速度会快些
{
	int i;

	for(i = 1; i <= n; i++)
	{
		if(a[i] == key)
		{
			return i;
		}
	}

	return 0;
}

//顺序查找优化（放置哨兵）
int Sequential_Search_sentry(int *a, int n, int key)
{
	int i;
	a[0] = key;                         //设置a[0] 为关键字值，称为‘哨兵’
	i = n;                              //循环从数组尾部开始

	while(a[i] != key)
	{
		i--;
	}

	return i;                           //返回0 则说明查找失败
}


//折半查找
int Binary_Search(int *a, int n, int key)
{
	int low, high, mid;
	low = 1;                            //定义最低下标为记录首位
	high = n;                           //定义最高下标位记录末位

	while(low <= high)
	{
		mid = (low + high) / 2;         //折半

		//若查找值比中值小
		if(key < a[mid])
		{
			//最高下标调整到中位下标小一位
			high = mid - 1;
		}
		//若查找值比中值大
		else if(key > a[mid])
		{
			//最低下标调整到中位下标大一位
			low = mid + 1;
		}
		//若相等
		else
		{
			//则表示找到结果
			return mid;
		}
	}

	return 0;
}

//插值查找
int Binary_Search_interpolation(int *a, int n, int key)
{
	int low, high, mid;
	low = 1;                            //定义最低下标为记录首位
	high = n;                           //定义最高下标位记录末位

	while(low <= high)
	{
		//插值改进的核心改造
		mid = low + (high - low)*(key - a[low]) / (a[high] - a[low]);

		//若查找值比中值小
		if(key < a[mid])
		{
			//最高下标调整到中位下标小一位
			high = mid - 1;
		}
		//若查找值比中值大
		else if(key > a[mid])
		{
			//最低下标调整到中位下标大一位
			low = mid + 1;
		}
		//若相等
		else
		{
			//则表示找到结果
			return mid;
		}
	}

	return 0;
}

//斐波那契数列：即这个数列从第二项开始，每一项都等于前两项之和
//0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144, ...
int Fibonacci_sequence(int n)      //n代表第几项。特别指出：0是第0项，不是第1项。
{
	if(n <= 1)
	{
		return n;
	}
	else
	{
		return Fibonacci_sequence(n - 1) + Fibonacci_sequence(n - 2);
	}

}

int Fibonacci_Search(int *a, int n, int key)
{
	int low, high, mid, i, k;
	low = 1;                            //定义最低下标为记录首位
	high = n;                           //定义最高下标为记录末位
	//k 为斐波那契数列的下标
	k = 0;
	int F[100];

	//此为求斐波那契数列
	for(i = 0; i < 100; i++)
	{
		F[i] = Fibonacci_sequence(i);
	}

	while(n > F[k] - 1)
	{
		//计算n 位于斐波那契数列的位置
		k++;
	}

	for(i = n; i < F[k] - 1; i++)
	{
		//将不满的数值补全
		a[i] = a[n];
	}

	while(low <= high)
	{
		mid = low + F[k - 1] - 1;       //计算当前分隔的下标

		//若查找记录小于当前分隔记录
		if(key < a[mid])
		{
			high = mid - 1;             //最高下标调整到分隔下标mid - 1处
			k = k - 1;                  //斐波那契数列下标减一位
		}
		//若查找记录大于当前分隔记录
		else if(key > a[mid])
		{
			//最低下标调整到分隔下标mid + 1处
			low = mid + 1;
			k = k - 2;                  //斐波那契数列下标减两位
		}
		else
		{
			if(mid <= n)
			{
				return mid;             //若相等则说明mid 即为查找到的位置
			}
			else
			{
				return n;               //若mid > n 则说明是补全数值，返回n
			}
		}
	}

	return 0;
}
#pragma endregion


#pragma region 二叉排序树
//递归查找二叉排序树T 中是否存在key
//指针f 指向T 的双亲，其初始调用值为null
//若查找成功，则指针p 指向该数据元素结点，并返回true
//否则指针p 指向查找路径上访问的最后一个结点并返回false
bool SearchBST(BiTree T, int key, BiTree f, BiTree *p)
{
	//查找不成功
	if(!T)
	{
		*p = f;
		return false;
	}
	//查找成功
	else if(key == T->data)
	{
		*p = T;
		return true;
	}
	else if(key < T->data)
	{
		//在左子树继续查找
		return SearchBST(T->lchild, key, T, p);
	}
	else
	{
		//在右子树继续查找
		return SearchBST(T->rchild, key, T, p);
	}

}

//当二叉排序树T 中不存在关键字等于key 的数据元素时
//插入key 并返回true ，否则返回false
bool InserBSF(BiTree *T, int key)
{
	BiTree p, s;

	//查找不成功
	//指针p 指向查找路径上访问的最后一个结点并返回false
	if(!SearchBST(*T, key, NULL, &p))
	{
		s = (BiTree)malloc(sizeof(BiTree));
		s->data = key;
		s->lchild = s->rchild = NULL;

		if(!p)
		{
			//插入s 为新的根结点
			*T = s;
		}
		else if(key < p->data)
		{
			//插入s 为左孩子
			p->lchild = s;

		}
		else
		{
			//插入s 为右孩子
			p->rchild = s;
		}

		return true;
	}
	else
	{
		//树中已有关键字相同的结点，不再插入
		return false;
	}
}

//二叉顺序树的构建
BiTree CreateBFS()
{
	int i;
	int a[10] = { 62,88,85,47,35,73,51,99,37,93 };
	BiTree T = NULL;

	for(i = 0; i < 10; i++)
	{
		InserBSF(&T, a[i]);
	}

	return T;
}

//从二叉排序树中删除结点p，并重接它的左或右子树
bool Delete(BiTree *p)
{
	BiTree q, s;

	//右子树空则只需要重接它的左子树
	//即直接把当前结点删除，再把左子树接上
	if((*p)->rchild == NULL)
	{
		q = *p;
		*p = (*p)->lchild;
		free(q);
	}
	//左子树空则只需要重接它的右子树
	//即直接把当前结点删除，再把右子树接上
	else if((*p)->lchild == NULL)
	{
		q = *p;
		*p = (*p)->rchild;
		free(q);
	}
	//左右子树均不空
	else
	{
		q = *p;
		s = (*p)->lchild;

		//转左，然后向右到尽头（找待删结点的前驱）
		while(s->rchild)
		{
			q = s;
			s = s->rchild;                  //找到直接前驱，转左后最右的
		}

		(*p)->data = s->data;               //s 指向被删结点的直接前驱

		if(q != *p)
		{
			q->rchild = s->lchild;          //重接q 的右子树
		}
		else
		{
			q->lchild = s->lchild;          //重接q 的左子树
		}

		free(s);
	}

	return true;
}


//若二叉排序树T 中存在关键字等于key 的数据元素时，则删除该数据元素结点
//并返回true ；否则返回false
bool DeleteBSF(BiTree *T, int key)
{
	//不存在关键字等于key 的数据元素
	if(!T)
	{
		return false;
	}
	else
	{
		//找到关键字等于key 的数据元素
		if(key == (*T)->data)
		{
			return Delete(T);
		}

		else if(key < (*T)->data)
		{
			return DeleteBSF(&(*T)->lchild, key);
		}
		else
		{
			return DeleteBSF(&(*T)->rchild, key);
		}
	}
}
#pragma endregion


#pragma region 平衡二叉树
//对以p 为根的二叉排序树作右旋操作
//处理之后p 指向新的树根结点，即选择处理之前的左子树的根结点
void R_Rotate(BiTree *p)
{
	BiTree L;                                  //新建一个结点L
	L = (*p)->lchild;                          //L 为结点p 的左孩子

	//这步重点理解
	//此选择结点，比L 大且比p 小
	L->rchild = (*p)->lchild;                  //①将原本结点p 的左孩子L 的右结点，旋转到结点p 的左结点

	L->rchild = (*p);                          //②将结点p 选择为左孩子L 的右结点。
	*p = L;                                    //最后p 指向新的根结点
}

//对以p 为根的二叉排序树作左旋处理
//处理之后p 指向新的树根结点，即旋转处理之前的右子树的根结点o
void L_Rotate(BiTree *p)
{
	BiTree R;
	R = (*p)->rchild;                          //R 指向p 的右子树根结点
	R->lchild = (*p)->rchild;                  //R 的左子树挂接为p 的右子树
	R->lchild = (*p);
	*p = R;                                    //p 指向新的根结点
}

//左平衡选择处理的函数代码
constexpr auto LH = +1;                        //左高
constexpr auto EH = 0;                         //等高
constexpr auto RH = -1;                        //右高

//对以指针T 所指结点为根的二叉树作左平衡旋转处理
//本算法结束时，指针T 指向新的根结点
void LeftBalance(BiTree *T)
{
	BiTree L, Lr;
	L = (*T)->lchild;                          //L 指向T 的左子树根结点

	//检查T 的左子树的平衡度，并作相应平衡处理
	switch(L->bf)
	{
	//新结点插入在T 的左孩子的左子树上，要作单右旋处理
	case LH:
		(*T)->bf = L->bf = EH;
		R_Rotate(T);
		break;

	//新结点插入在T 的左孩子的右子树上，要作双旋处理
	case RH:
		Lr = L->rchild;                          //Lr 指向T 的左孩子的右子树根

		//修改T 及其左孩子的平衡因子
		switch(Lr->bf)
		{
		case LH:
			(*T)->bf = RH;
			L->bf = EH;
			break;

		case EH:
			(*T)->bf = L->bf = EH;
			break;

		case RH:
			(*T)->bf = EH;
			L->bf = LH;
			break;
		}

		Lr->bf = EH;
		L_Rotate(&(*T)->lchild);                   //对T 的左子树作左旋平衡处理
		R_Rotate(T);                               //对T 作右旋平衡处理
	}
}

//未验证！（慎用）
void RightBalance(BiTree *T)
{
	BiTree L, Lr;
	L = (*T)->rchild;                          //L 指向T 的右子树根结点

	//检查T 的右子树的平衡度，并作相应平衡处理
	switch(L->bf)
	{
	//新结点插入在T 的右孩子的右子树上，要作单左旋处理
	case RH:
		(*T)->bf = L->bf = EH;
		L_Rotate(T);
		break;

	//新结点插入在T 的右孩子的左子树上，要作双旋处理
	case LH:
		Lr = L->lchild;                          //Lr 指向T 的右孩子的左子树根

		//修改T 及其右孩子的平衡因子
		switch(Lr->bf)
		{
		case RH:
			(*T)->bf = LH;
			L->bf = EH;
			break;

		case EH:
			(*T)->bf = L->bf = EH;
			break;

		case LH:
			(*T)->bf = EH;
			L->bf = RH;
			break;
		}

		Lr->bf = EH;
		R_Rotate(&(*T)->rchild);                   //对T 的右子树作右旋平衡处理
		L_Rotate(T);                               //对T 作左旋平衡处理
	}
}

//若在平衡的二叉排序树T 中不存在和e 有相同关键字的结点，则插入一个
//数据元素为e 的新结点并返回1，否则返回0。若因插入而使二叉排序树
//失去平衡，则作平衡旋转处理，bool 变量taller 反映T长高
bool InsertAVL(BiTree *T, int e, bool *taller)
{
	//插入新结点，树‘长高’，置taller 为TRUE
	if(!*T)
	{
		*T = (BiTree)malloc(sizeof(BiTree));
		(*T)->data = e;
		(*T)->lchild = (*T)->rchild = NULL;
		(*T)->bf = EH;
		*taller = true;
	}
	else
	{
		//树中已存在和e 有相同关键字的结点则不再插入
		if((*T)->data == e)
		{
			*taller = false;
			return false;
		}

		if(e < (*T)->data)
		{
			//应继续在T 的左子树中进行搜索
			if(!InsertAVL(&(*T)->lchild, e, taller))
			{
				//未插入
				return false;
			}

			//已插入到T 的左子树中且左子树‘长高’
			if(taller)
			{
				//检查T 的平衡度
				switch((*T)->bf)
				{
				//原本左子树比右子树高，需要作左平衡处理
				case LH:
					LeftBalance(T);
					*taller = false;
					break;

				//原本左右子树等高，现因左子树增高而树增高
				case EH:
					(*T)->bf = LH;
					*taller = true;
					break;

				//原本右子树比左子树高，现左右子树等高
				case RH:
					(*T)->bf = EH;
					*taller = false;
					break;
				}
			}
		}
		else
		{
			//应继续在T 的右子树中进行搜索
			if(!InsertAVL(&(*T)->rchild, e, taller))
			{
				//未插入
				return false;
			}

			//已插入到T 的右子树且右子树‘长高’
			if(taller)
			{
				//检查T 的平衡度
				switch((*T)->bf)
				{
				//原本左子树比右子树高，现左、右子树等高
				case LH:
					(*T)->bf = EH;
					*taller = false;
					break;

				//原本左右子树等高，现因右子树增高而树增高
				case EH:
					(*T)->bf = RH;
					*taller = true;
					break;

				//原本右子树比左子树高，需要作右平衡处理
				case RH:
					RightBalance(T);
					*taller = false;
					break;
				}
			}
		}
	}

	return true;
}

bool CreateAVL()
{
	int i;
	int a[10] = { 3,2,1,4,5,6,7,10,9,8 };
	BiTree T = NULL;
	bool taller;

	for(i = 0; i < 10; i++)
	{
		if(!InsertAVL(&T, a[i], &taller))            //形参为指针，实参传递地址
		{
			return false;
		}
	}

	return true;
}
#pragma endregion

