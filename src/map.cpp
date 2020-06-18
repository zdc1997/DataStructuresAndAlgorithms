#include <iostream>


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



//邻接矩阵存储结构
typedef char VertexType;                        //顶点类型应由用户定义
typedef int EdgeType;                           //边上的权值类型应由用户定义
constexpr auto MAXVEX = 100;                    //最大顶点数，应由用户定义
constexpr auto DINFINITY = 65535;               //用65535来代表∞;(INFINITY已有定义)
typedef struct
{
	VertexType vexs[MAXVEX];                    //顶点表
	EdgeType arc[MAXVEX][MAXVEX];               //邻接矩阵，可看成边表
	int numVertexes, numEdges;                  //图中当前的顶点数和边数
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
			G->arc[i][j] = DINFINITY;          //邻接矩阵初始化
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









