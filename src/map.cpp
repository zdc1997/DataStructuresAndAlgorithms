#include <iostream>
#include <queue>
using namespace std;

/*
ADT 图（Graph)
Data
    顶点的有穷非空集合和边的集合

Operation
    CreateGraph(*G,V,VR):                       //按照顶点集V和边弧集VR的定义构造图G。
    DestroyGraph(*G):                           //图G存在则销毁
    LocateVex(G,u):                             //若图G中存在顶点u，则返回图中的位置
    GetVex(G,v):                                //返回图G中顶点v的值
    PutVex(G,v,value):                          //将图G中顶点v赋值value
    FirstAdjVex(G,*v):                          //返回顶点v的一个邻接顶点，若顶点在G中无邻接顶点返回空
    NextAdjVex(G,v,*w):                         //返回顶点v相对于顶点w的下一个邻接顶点，若w是v的最后一个邻接点则返回‘空’
    InsertVex(*G,v):                            //在图G中新增顶点v
    DeleteVex(*G,v):                            //删除图G中顶点v及其相关的弧
    InsertArc(*G,v,w):                          //在图G中新增弧<v,w>,若G是无向图，还需要新增对称弧<w,v>
    DeleteArc(*G,v,w):                          //在图G中删除弧<v,w>,若G是无向图，还需要删除对称弧<w,v>
    DFSTraverse(G):                             //对图G进行深度优先遍历，在遍历过程对每个顶点调用
    HFSTraverse(G):                             //对图G进行广度优先遍历，在遍历过程对每个顶点调用

endADT
*/


#ifndef 邻接矩阵代码块
//邻接矩阵存储结构
typedef char VertexType;                        //顶点类型应由用户定义
typedef int EdgeType;                           //边上的权值类型应由用户定义
constexpr auto MAXVEX = 100;                    //最大顶点数，应由用户定义
constexpr auto DINFINITY = 65535;               //用65535来代表∞;(INFINITY已有定义)
typedef struct
{
	VertexType vexs[MAXVEX];                    //顶点表
	EdgeType arc[MAXVEX][MAXVEX];               //邻接矩阵，可看成边表
	int numVertexes;                            //图中当前的顶点数
	int numEdges;                               //图中当前的边数
} MGraph;




//建立无向网图的邻接矩阵表示
void CreateMGraph(MGraph *G)
{
	int i, j, k, w;
	printf("输入顶点数和边数:\n");
	scanf("%d,%d", &G->numVertexes, &G->numEdges);  //输入顶点数和边数

	for(i = 0; i < G->numVertexes; i++)
	{
		scanf(&G->vexs[i]);                     //读入顶点信息，建立顶点表
	}

	for(i = 0; i < G->numVertexes; i++)
	{
		for(j = 0; j < G->numVertexes; j++)
		{
			G->arc[i][j] = DINFINITY;           //邻接矩阵初始化
		}
	}

	for(k = 0; k < G->numEdges; k++)            //读入numEdges条边，建立邻接矩阵
	{
		printf("输入边（Vi，Vj）上的下标1，下标j和权w:\n");
		scanf("%d,%d,%d", &i, &j, &w);          //输入边（Vi，Vj）上的权w
		G->arc[i][j] = w;
		G->arc[j][i] = G->arc[i][j];            //因为是无向图，矩阵对称
	}

}
#endif

#ifndef 邻接表代码块
typedef char VertexType;                    //顶点类型应由用户定义
typedef int EdgeType;                       //边上的权值了理想应由用户定义

typedef struct EdgeNode                     //边表结点
{
	int adjvex;                             //邻接点域，存储该顶点对应的下标
	EdgeType weight;                        //用于存储权值，对于非网图可以不需要
	struct EdgeNode *next;                  //链域，指向下一个邻接点
} EdgeNode;

typedef struct VertexNode                   //顶点表结点
{
	VertexType data;                        //顶点域，存储顶点信息
	EdgeNode *firstedge;                    //边表头指针

	//拓扑排序扩充
	int in;                                 //入度信息
	//int data;
} VertexNode,AdjList[MAXVEX];

typedef struct
{
	AdjList adjList;
	int numVertexes;                        //当前顶点数
	int numEdges;                           //当前边数
} GraphAdjList;



//建立图的邻接表结构
//无向图的邻接表创建代码
void CreateALGraph(GraphAdjList *G)
{
	int i, j, k;
	EdgeNode *e;
	printf("输入顶点数和边数:\n");
	scanf("%d,%d", &G->numVertexes, &G->numEdges);  //输入顶点数和边数

	for(i = 0; i < G->numVertexes; i++)     //读入顶点信息，建立顶点表
	{
		scanf(&G->adjList[i].data);         //输入顶点信息
		G->adjList[i].firstedge = NULL;     //将边表置为空表
	}

	for(k = 0; k < G->numEdges; k++)         //建立边表
	{
		printf("输入边(Vi,Vj)上的顶点序号:\n");
		scanf("%d,%d", &i, &j);              //输入边(Vi,Vj)上的顶点序号

		e = (EdgeNode*)malloc(sizeof(EdgeNode));    //向内存申请空间，生成边表结点
		e->adjvex = j;                       //邻接序号为j
		e->next = G->adjList[i].firstedge;   //将e指针指向当前顶点指向的结点
		G->adjList[i].firstedge = e;         //将当前顶点的指针指向e

		e = (EdgeNode*)malloc(sizeof(EdgeNode));    //向内存申请空间，生成边表结点
		e->adjvex = i;                        //邻接序号为i
		e->next = G->adjList[j].firstedge;    //将e指针指向当前顶点指向的结点
		G->adjList[j].firstedge = e;          //将当前顶点的指针指向e
	}
}
#endif

//图的遍历
#pragma region DFS
bool visited[MAXVEX];                         //访问标志的数组：需要遍历的长度

#pragma region 邻接矩阵
//邻接矩阵的深度优先递归算法
void DFS(MGraph G, int i)
{
	int j;
	visited[i] = true;
	printf("%c", G.vexs[i]);                  //打印顶点，也可以其他操作

	for(j = 0; j < G.numVertexes; j++)
	{
		if(G.arc[i][j] = true && !visited[j])
		{
			DFS(G, j);                        //对未访问的邻接顶点调用递归
		}
	}
}

//邻接矩阵的深度遍历操作
void DFSTraverse(MGraph G)
{
	int i;

	for(i = 0; i < G.numVertexes; i++)         //初始所有顶点状态都是未访问过状态
	{
		visited[i] = false;
	}

	for(i = 0; i < G.numVertexes; i++)
	{
		if(!visited[i])                         //对未访问过的顶点调用DFS，若是连通图，只会执行一次
		{
			DFS(G, i);
		}
	}
}
#pragma endregion

#pragma region 邻接表
//邻接表的深度优先递归算法
void DFS(GraphAdjList GL, int i)
{
	EdgeNode *p;
	visited[i] = true;
	printf("%c", GL.adjList[i].data);           //打印顶点，也可以是其他操作
	p = GL.adjList[i].firstedge;

	while(p)
	{
		if(!visited[p->adjvex])
		{
			DFS(GL, p->adjvex);                 //对未访问的邻接顶点递归调用
		}

		p = p->next;
	}
}

//邻接表的深度遍历操作
void DSFTraverse(GraphAdjList GL)
{
	int i;

	for(i = 0; i < GL.numVertexes; i++)
	{
		visited[i] = false;                     //初始化所有顶点状态都是未访问的状态
	}

	for(i = 0; i < GL.numVertexes; i++)
	{
		if(!visited[i])                          //对未访问过的顶点调用DFS，若是连通图，只会执行一次
		{
			DFS(GL, i);
		}
	}
}
#pragma endregion
#pragma endregion

#pragma region BFS
#pragma region 邻接矩阵
//邻接矩阵的广度遍历算法
void BFSTraverse(MGraph G)
{
	int i, j;

	//使用queue 时注意两点：
	//①包含头文件后，再加上命名空间
	//②注意要添加参数类型
	queue<int> Q;

	for(i = 0; i < G.numVertexes; i++)
	{
		visited[i] = false;
	}

	//InitQueue(&Q);                                //初始化列表

	for(i = 0; i < G.numVertexes; i++)                //对每一个顶点做循环
	{
		if(!visited[i])                               //若是未访问过就处理
		{
			visited[i] = true;                      //设置当前顶点访问过
			printf("%c", G.vexs[i]);                //打印顶点，也可以其他操作
			Q.push(i);                              //将此顶点入列

			while(!Q.empty())                         //若当前列队不为空
			{
				i = Q.front();                      //将队中元素出队列，赋值给i
				Q.pop();

				for(j = 0; j < G.numVertexes; j++)
				{
					//判断其他顶点若与当前顶点存在边且未访问过
					if(G.arc[i][j] = true && !visited[j])
					{
						visited[j] = true;          //将找到的顶点标记为已访问
						printf("%c", G.vexs[j]);    //打印顶点
						Q.push(j);                  //将找到的此顶点入队列
					}
				}
			}
		}
	}
}
#pragma endregion

#pragma region 邻接表
//邻接表的广度遍历算法
void BFSTraverse(GraphAdjList GL)
{
	int i;
	EdgeNode *p;
	queue<int> Q;

	for(i = 0; i < GL.numVertexes; i++)
	{
		visited[i] = true;
	}

	//IniteQueue(&Q);

	for(i = 0; i < GL.numVertexes; i++)
	{
		if(!visited[i])
		{
			visited[i] = true;
			printf("%c", GL.adjList[i].data);       //打印顶点，也可以其他操作
			Q.push(i);

			while(!Q.empty())
			{
				i = Q.front();
				Q.pop();
				p = GL.adjList[i].firstedge;        //找到当前点点边表链表头指针

				while(p)
				{
					if(!visited[p->adjvex])           //若此顶点未被访问
					{
						visited[p->adjvex] = true;
						printf("%c", GL.adjList[p->adjvex].data);
						Q.push(p->adjvex);          //将此顶点入列队
					}

					p = p->next;                    //指针指向下一个临界点
				}
			}
		}
	}
}
#pragma endregion
#pragma endregion

//生成最小树：
#pragma region Prim算法
//Prim算法生成最小生成树
void MiniSpanTree_Prim(MGraph G)
{
	int min, i, j, k;
	//两个数组的长度都应为顶点个数
	const int vexNum = 9;
	int adjvex[vexNum];                 //保存相关顶点下标
	int lowcost[vexNum];                //保存相关顶点间边的权值

	//初始化第一个权值为0，即v0加入生成树
	lowcost[0] = 0;                     //lowcost 的值为0，在这里就是此下标的顶点已经加入生成树
	adjvex[0] = 0;                      //初始化第一个顶点下标为0

	for(i = 1; i < G.numVertexes; i++)   //循环除下标为0外的全部顶点
	{
		lowcost[i] = G.arc[0][i];       //将v0顶点与之有边的权值存入数组
		adjvex[i] = 0;                  //初始化都为v0的下标
	}

	for(i = 1; i < G.numVertexes; i++)
	{
		//初始化最小权值为∞
		min = DINFINITY;                //通常设置为不可能的大数字如32767、65535等。

		j = 1;
		k = 0;

		while(j < G.numVertexes)         //循环全部顶点
		{
			//如果权值不为0 且 权值小于min
			if(lowcost[j] != 0 && lowcost[j] < min)
			{
				min = lowcost[j];       //则让当前权值成为最小值
				k = j;                  //将当前最小值的下标存入k
			}

			j++;
		}

		printf("(%d,%d)", adjvex[k], k);    //打印当前顶点边中权值最小边
		lowcost[k] = 0;                  //将当前顶点的权值设置为0，表示此顶点已经完成任务

		for(j = 0; j < G.numVertexes; j++)
		{
			//若下标为k顶点各权值小于此前这些顶点未被加入生成树权值
			if(lowcost[j] != 0 && G.arc[k][j] < lowcost[j])
			{
				lowcost[j] = G.arc[k][j]; //将较小权值存入lowcost
				adjvex[j] = k;            //将下标为k 的顶点存入adjvex
			}
		}
	}
}
#pragma endregion

//c++ 中不把数组形参设置到函数中

#pragma region Kruskal算法
//对边集数组Edge 结构的定义
typedef struct
{
	int begin;
	int end;
	int weight;
} Edge;

//*parent 就是parent[] 数组
//查找连线顶点的尾部下标
int Find(int *parent, int f)
{
	while(parent[f] > 0)
	{
		f = parent[f];
	}

	return f;
}

//Kruskal算法生成最小生成树
void MiniSpanTree_Kruskal(MGraph G)
{
	int i, n, m;
	const int MAXEDGE = 15;
	const int MAXVEX = 9;
	Edge edges[MAXEDGE];                    //定义边集数组
	int parent[MAXVEX];                     //定义一数组用来判断边与边是否形成环路

	/*此处省略将邻接矩阵G 转换为边集数组edges 并按权值由小到大排序的代码*/

	for(i = 0; i < G.numEdges; i++)
	{
		parent[i] = 0;                      //初始化数组值为0
	}

	//循环每一条边
	for(i = 0; i < G.numEdges; i++)
	{
		n = Find(parent, edges[i].begin);
		m = Find(parent, edges[i].end);

		//如果n与m不等，说明此边没有与现有生成树形成环路
		if(n != m)
		{
			//表示此顶点已经在生成树集合中
			parent[n] = m;                  //将此边的结尾顶点放入下标为起点的parent
			printf("( %d, %d) %d", edges[i].begin, edges[i].end, edges[i].weight);
		}
	}













}
#pragma endregion

//最短路径
#pragma region Dijksrta算法
constexpr int SHORTESTPATHINDEX = 9;
typedef int Pathmatirx[SHORTESTPATHINDEX];              //用于存储最短路径下标的数组
typedef int ShortPathTable[SHORTESTPATHINDEX];          //用于存储到各点最短路径的权值和
//Dijkstra 算法，求有向网G 的v0 顶点到其余顶点v 最短路径P[v] 及带权长度D[v]
//P[v] 的值为前驱顶点下标，D[v] 表示v0 到v 的最短路径长度和
void ShortestPath_Dijkstra(MGraph G, int v0, Pathmatirx *P, ShortPathTable *D)
{
	int v, w, k, min;
	int final[SHORTESTPATHINDEX];                       //final[w] = 1 表示求得顶点v0 到vw 的最短路径

	//初始化数据
	for(v = 0; v < G.numVertexes; v++)
	{
		final[v] = 0;                                   //全部顶点初始化为未知最短路径状态
		(*D)[v] = G.arc[v0][v];                         //将与v0 点又连线的顶点加上权值
		(*P)[v] = 0;                                    //初始化路径数组P 为0
	}

	//v0 至v0 的路径为0
	(*D)[v0] = 0;
	//v0 至v0 不需要求路径
	final[v0] = 1;

	//开始主循环，每次求得v0 到某个v 顶点的最短路径
	for(v = 1; v < G.numVertexes; v++)
	{
		min = INT_MAX;                                  //当前所知离v0 顶点最近的距离

		//寻找离v0 最近的顶点
		for(w = 0; w < G.numVertexes; w++)
		{
			//非空且权值更小
			if(!final[w] && (*D)[w] < min)
			{
				k = w;
				min = (*D)[w];                          //w 顶点离v0 顶点更近
			}

		}

		final[k] = 1;                                   //将目前找到最近的顶点置为1

		//修正当前最短路径及距离
		for(w = 0; w < G.numVertexes; w++)
		{
			//非空
			//且经过v 顶点的路径比现在这条路径的长度短
			//则找到了更短路径，修改D[w]、P[w]
			if(!final[w] && (min + G.arc[k][w] < (*D)[w]))
			{
				(*D)[w] = min + G.arc[k][w];            //修改当前路径长度
				(*P)[w] = k;
			}
		}
	}
}

#pragma endregion

#pragma region Floyd算法
//Floyd算法，求网图G 中各顶点
void ShortestPath_Floyd(MGraph G, Pathmatirx *P, ShortPathTable *D)
{
	int v, w, k;

	//初始化D、P
	for(v = 0; v < G.numVertexes; v++)
	{
		for(w = 0; w < G.numVertexes; w++)
		{
			//D[v][w] 值即为对应点间的权值
			D[v][w] = G.arc[v][w];
			//初始化P
			P[v][w] = w;
		}
	}

	for(k = 0; k < G.numVertexes; k++)
	{
		for(v = 0; v < G.numVertexes; v++)
		{
			for(w = 0; w < G.numVertexes; w++)
			{
				//如果经过下标为k 顶点路径比原两点间路径更短
				if(D[v][w] > D[v][k] + D[k][w])
				{
					D[v][w] = D[v][k] + D[k][w];            //将当前两点间权值设为更小的一个
					P[v][w] = P[v][k];                      //路劲设置经过下标为k 的顶点
				}
			}
		}
	}

	//显示代码
	for(v = 0; v < G.numVertexes; v++)
	{
		for(w = v + 1; w < G.numVertexes; w++)
		{
			printf("v%d-v%d weight: %d ", v, w, D[v][w]);
			k = P[v][w];                             //获得第一个路径顶点下标
			printf("path: %d", w);                   //打印源点

			//如果路径顶点下标不是终点
			while(k != w)
			{
				printf(" -> %d", k);                 //打印路径顶点
				k = P[v][w];                         //获得下一个路径顶点下标
			}

			printf(" -> %d\n", w);                   //打印终点
		}

		printf("\n");
	}

}

#pragma endregion

//拓扑排序
#pragma region 拓扑排序
//若GL 无回路，则输出拓扑排序序列并返回ok；否则返回error
bool TopologicalSort(GraphAdjList GL)
{
	EdgeNode *e;
	int i, k, gettop;
	int top = 0;                                    //用于栈指针下标
	int count = 0;                                  //用于统计输出顶点的个数
	int *stack;                                     //建栈存储入度为0 的顶点
	stack = (int *)malloc(GL.numVertexes * sizeof(int));

	for(i = 0; i < GL.numVertexes; i++)
	{
		if(GL.adjList[i].in == 0)
		{
			//①先将入度为0 的顶点入栈
			stack[++top] = i;
		}
	}

	while(top != 0)
	{
		gettop = stack[top--];                      //出栈
		printf("%d -> ", GL.adjList[gettop].data); //打印此顶点
		count++;                                    //统计输出顶点数

		//对入度为0 的顶点的弧表进行遍历
		for(e = GL.adjList[gettop].firstedge; e; e = e->next)
		{
			//将k 号顶点邻接点的入度-1
			k = e->adjvex;

			if(!(--GL.adjList[k].in))
			{
				//②当入度再次为0 时入栈，用于不断遍历循环输出
				stack[++top] = k;
			}
		}

	}

	if(count < GL.numVertexes)
	{
		//如果count 小于顶点数，说明存在环
		return false;
	}
	else
	{
		return true;
	}


};
#pragma endregion

//关键路径
#pragma region 关键路径
//改进的拓扑排序：
//先声明几个全局变量
int *etv, *ltv;                             //时间最早发生时间喝最迟发生时间数组
int *stack2;                                //用于存储拓扑序列的栈
int top2;                                   //用于stack2 的指针

//拓扑排序，用于关键路径计算
bool TopologicalSort_improvement(GraphAdjList GL)
{
	EdgeNode *e;
	int i, k, gettop;
	int top = 0;                            //用于栈指针下标
	int count = 0;                          //用于统计输出顶点的个数
	int *stack;                             //建栈将入度为0 的顶点入栈
	stack = (int *)malloc(GL.numVertexes * sizeof(int));

	for(i = 0; i < GL.numVertexes; i++)
	{
		if(GL.adjList[i].in == 0)
		{
			stack[++top] = i;
		}
	}

	top2 = 0;                                //初始化为0
	//事件最早发生时间
	etv = (int *)malloc(GL.numVertexes * sizeof(int));

	for(i = 0; i < GL.numVertexes; i++)
	{
		//初始化为0
		etv[i] = 0;
	}

	stack2 = (int *)malloc(GL.numVertexes * sizeof(int));

	while(top != 0)
	{
		gettop = stack[top--];
		count++;
		stack2[++top2] = gettop;             //将弹出的顶点序号压入拓扑序列的栈

		for(e = GL.adjList[gettop].firstedge; e; e = e->next)
		{
			k = e->adjvex;

			//入度为0 的压栈
			if(!(--GL.adjList[k].in))
			{
				stack[++top] = k;
			}

			//求各顶点事件最早发生时间值
			if((etv[gettop] + e->weight > etv[k]))
			{
				etv[k] = etv[gettop] + e->weight;
			}

		}

	}

	if(count < GL.numVertexes)
	{
		return false;
	}
	else
	{
		return true;
	}
}

//求关键路径，GL 为有向网，输出GL 的各项关键活动
void CriticalPath(GraphAdjList GL)
{
	EdgeNode *e;
	int i, gettop, k, j;
	int ete, lte;                                       //声明活动最早发生时间喝最迟发生时间变量
	TopologicalSort_improvement(GL);                    //求拓扑序列，计算数组etv 和stack2 的值
	//事件最晚发生时间
	ltv = (int *)malloc(GL.numVertexes * sizeof(int));

	//初始化ltv
	for(i = 0; i < GL.numVertexes; i++)
	{
		ltv[i] = etv[GL.numVertexes - 1];
	}

	//计算ltv
	while(top2 != 0)
	{
		//将拓扑序列出栈，后进先出
		gettop = stack2[top2--];

		//求各顶点事件的最迟发生时间ltv 的值
		for(e = GL.adjList[gettop].firstedge; e; e = e->next)
		{
			k = e->adjvex;

			if(ltv[k] - e->weight < ltv[gettop])
			{
				ltv[gettop] = ltv[k] - e->weight;
			}
		}
	}

	//求ete，lte 和关键活动
	for(j = 0; j < GL.numVertexes; j++)
	{
		for(e = GL.adjList[j].firstedge; e; e = e->next)
		{
			k = e->adjvex;
			//活动最早发生时间
			ete = etv[j];
			//活动最迟发生时间
			lte = ltv[k] - e->weight;

			//两者相等即在关键路径上
			if(ete == lte)
			{
				printf("<v%d,v%d> length:%d , ",
					   GL.adjList[j].data, GL.adjList[k].data, e->weight);
			}

		}
	}

}
#pragma endregion






































