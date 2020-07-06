#include <iostream>
/*
ADT 树(tree)

Data
    树是由一个根节点和若干棵子树构成。树中结点具有相同数据类型及层次关系

Operation
    InitTree(*T):                       构造空树T
    DestroyTree(*T):                    销毁树T
    CreateTree(*T,definition):          按Definition 中给出的树的定义来构造树
    ClearTree(*T):                      若树存在，则将树T清空
    TreeEmpty(T):                       若T为空树，返回true，否则返回false
    TreeDepth(T):                       返回T的深度
    Root(T):                            返回T的根节点
    Value(T,cur_e):                     cur_e 是树T的一个结点，返回此结点的值
    Assign(T,cur_e,value):              给树T的结点cur_e 赋值为value
    Parent(T,cur_e):                    若cur_e 是树T的非根根点，则返回它的双亲，否则返回为空
    LeftChild(T,cur_e):                 若cur_e 是树T的非叶结点，则返回它的最左孩子，否则返回空
    RightSibling(T,cur_e):              若cur_e 有右兄弟，则返回它的右兄弟，否则返回空
    InsertChild(*T,*p,i,c):             其中p指向树T的某个结点，i为所指结点p的度加上1，
                                        非空树c与T不相交，操作结果为插入c为树T中p指结点的第i棵子树
    DeleteChild(*T,*p,i):               其中p指向树T的某个结点，i为所指结点p的度
                                        操作结果为删除T中p所指结点的第i棵子树

endADT
*/


/*树的双亲表示法结点结构定义*/
constexpr auto MAX_TREE_SIZE = 100;     //宏转换为constexpr
typedef int TElemType;                  //树结点的数据类型，目前暂定为整型
typedef struct PTNode                   //结点结构
{
	TElemType data;                     //结点数据
	int parent;                         //双亲位置
} PTNode;

typedef struct                          //树结构
{
	PTNode nodes[MAX_TREE_SIZE];        //结点数组
	int r, n;                           //根的位置和结点数
} PTree;



/*树的孩子表示法结构定义*/
typedef struct CTNode                   //孩子结点
{
	int child;
	struct CTNode *next;
} *ChildPtr;

typedef struct                          //表头结构
{
	TElemType data;
	ChildPtr firstchild;
} CTBox;

typedef struct                          //树结构
{
	CTBox nodes[MAX_TREE_SIZE];         //结点数组
	int r, n;                           //根的位置和结点数
} CTree;



/*树的孩子兄弟表示法结构定义*/
typedef struct CSNode
{
	TElemType data;
	struct CSNode *firstchild, *rightsib;
} CSNode,*CSTree;



/*二叉树的二叉链表结点结构定义*/
typedef struct BiTNode                  //结点结构
{
	TElemType data;                     //结点数据
	struct BiTNode *lchild, *rchild;    //左右孩子指针

	//平衡二叉树新增
	int bf;                             //结点的平衡因子
} BiTNode,*BiTree;



/*二叉树的前序遍历递归算法：中左右*/
void PreOrderTraverse(BiTree T)
{
	if(T == NULL)
	{
		return;
	}

	printf("%c", T->data);              //显示结点数据，可以更改为其他对结点的操作
	PreOrderTraverse(T->lchild);        //再先序遍历左子树
	PreOrderTraverse(T->rchild);        //最后先序遍历右子树
}



/*二叉树的中序遍历递归算法：左中右*/
void InOrderTraverse(BiTree T)
{
	if(T == NULL)
	{
		return;
	}

	InOrderTraverse(T->lchild);         //中序遍历左子树
	printf("%c", T->data);              //显示结点数据，可以更改为其他对结点的操作
	InOrderTraverse(T->rchild);         //最后中序遍历右子树
}



/*二叉树的后序遍历递归算法：左右中*/
void PostOrderTraverse(BiTree T)
{
	if(T == NULL)
	{
		return;
	}

	PostOrderTraverse(T->lchild);        //先后序遍历左子树
	PostOrderTraverse(T->rchild);        //再后序遍历右子树
	printf("%c", T->data);               //显示结点数据，可以更改为其他对结点的操作
}



/*按前序输入二叉树中结点的值*/
/*#表示空树，构造二叉链表表示二叉树T*/
//C++ 中使用scanf 会报错，因此在项目->项目名称属性->配置属性-> C / C ++->预处理器->预处理器定义->编辑...添加行_CRT_SECURE_NO_WARNINGS
void CreateBiTree(BiTree *T)
{
	TElemType ch;
	scanf("%c", &ch);

	if(ch == '#')
	{
		*T = NULL;
	}
	else
	{
		*T = (BiTree)malloc(sizeof(BiTNode));

		if(!*T)
		{
			exit(OVERFLOW);
		}

		(*T)->data = ch;                    //生成根结点
		CreateBiTree(&(*T)->lchild);        //构造左子树
		CreateBiTree(&(*T)->rchild);        //构造右子树
	}
}



//二叉树的二叉线索存储结构的定义
enum PointerTag
{
	Linke,                                  //Link == 0     表示指向左右孩子指针
	Thread                                  //Thread == 1   表示指向前驱或后继的线索
};

typedef struct BiThrNode                    //二叉线索存储结点结构
{
	TElemType data;                         //结点数据
	struct BiThrNode *lchild, *rchild;      //左右孩子指针
	PointerTag LTag;
	PointerTag RTag;                        //左右标志
} BiThrNode,*BiThrTree;



BiThrTree pre;                              //全局变量，始终指向刚刚访问过的结点
//中序遍历进行中序线索化
void InThreading(BiThrTree p)
{
	if(p)
	{
		InThreading(p->lchild);             //递归左子树线索化

		if(!p->lchild)                      //没有左孩子
		{
			p->LTag = Thread;               //前驱线索
			p->lchild = pre;                //左孩子指针指向前驱
		}

		if(!pre->rchild)                    //前驱没有右孩子
		{
			pre->RTag = Thread;             //后继线索
			pre->rchild = p;                //前驱右孩子指针指向后继（当前结点p）
		}

		pre = p;                            //保持pre指向p的前驱

		InThreading(p->rchild);             //递归右子树线索化
	}
}



typedef int Status;
constexpr int OK = 1;
//T指向头结点，头结点左键lchild 指向根节点，头结点右键rchild 指向中序遍历的
//最后一个结点。中序遍历线索二叉链表表示的二叉树T。
Status InOrderTraverse_Thr(BiThrTree T)
{
	BiThrTree p;
	p = T->lchild;                          //p指向根结点

	while(p != T)                           //空树或遍历结束时。p == T
	{
		while(p->LTag == Linke)             //当LTag == 0时循环到中序序列第一个结点
		{
			p = p->lchild;
		}

		printf("%c", p->data);

		while(p->RTag == Thread && p->rchild != T)
		{
			p = p->rchild;
			printf("%c", p->data);
		}

		p = p->rchild;                      //p进至其右子树根
	}

	return OK;
}







