//
//  main.c
//  guide_test
//
//  Created by 赵楚涵 on 2018/12/24.
//  Copyright © 2018 赵楚涵. All rights reserved.
//

#include <stdio.h>
//#include "Structure.h"
//#include "Grah_func.h"

#define MAX 500             //存储文字
#define MAXV 5             //节点个数
#define INF 32767.0

double road_length[MAXV][MAXV]={{0,INF,5,10,INF},{INF,0,INF,INF,6},{5,INF,0,3,8},{10,INF,3,0,INF},{INF,6,8,INF,0}};//存储道路长度的邻接矩阵
int edge[MAXV][MAXV]={{0,INF,1,1,INF},{INF,0,INF,INF,1},{1,INF,0,1,1},{1,INF,1,0,INF},{INF,1,1,INF,0}};
char spot_name[MAXV][MAX]={"一教学楼","二教学楼","三教学楼","四教学楼","五教学楼"};
//存储节点名称
char spot_introduce[MAXV][MAX]={"zheshi一教学楼","zheshi二教学楼","zheshi三教学楼","zheshi四教学楼","zheshi五教学楼"};
//景点介绍

typedef struct ANode        //边节点
{
    int adjvex;               //该边邻接点编号
    struct ANode *nextarc;  //指向下一路线的指针
    char road_name[MAX];    //道路名称
    int point[2];        //道路起止地点
    double length;           //道路长度 单位为米
    int  weigh;
}ArcNode;

typedef struct Vnode
{
    int num;
    char name[MAX];         //景点名称
    char introduce[MAX];        //景点介绍内容
    ArcNode *firstarc;      //指向第一个边节点
}VNode;                     //顶点节点（景区）

typedef struct
{
    VNode adjlist[MAXV];
    int v,e;                //v：顶点数；e：边数
}AdjGraph;


void CreateGraph(AdjGraph *G, int A[MAXV][MAXV], int v, int e);
//void DispAdj(AdjGraph *G);
void Find_attractions(AdjGraph* G,int num);
void Find_road(AdjGraph* G,int v1, int v2);
void Recommend(int num);//输入景点
int LocateVex(AdjGraph* G,int u);   //输入景点编号
void Floyd(int g[MAXV][MAXV],int v1, int v2);
void Dispath(int g[][MAXV], int A[][MAXV], int path[][MAXV], int i, int j);

void CreateGraph(AdjGraph *G, int A[MAXV][MAXV], int v, int e){
    int i,j; ArcNode *p;
  //  G=(AdjGraph*)malloc(sizeof(AdjGraph));
    for(i=0;i<v;i++){
        for(j=v-1;j>=0;j--){
            if(A[i][j]!=0 && A[i][j]!=INF){
                G->adjlist[i].num=i;//景点编号赋值
                strcpy(G->adjlist[i].name,spot_name[i]);//景点名称赋值
                strcpy(G->adjlist[i].introduce,spot_introduce[i]);//景点介绍
                
                
                p=(ArcNode*)malloc(sizeof(ArcNode));
                p->adjvex=j;
                p->weigh=A[i][j];
                //头插法
                p->nextarc=G->adjlist[i].firstarc;
                G->adjlist[i].firstarc=p;
                /*printf("请输入道路名称:\n");
                 scanf("%s", p->road_name);
                 printf("请输入道路起止地点:\n");
                 scanf("%s", p->point);
                 printf("请输入道路长度:\n");
                 scanf("%f", p->length);*/
                strcpy(p->road_name,"qqq");//道路名称赋值
                p->length=road_length[i][j];//道路长度
                p->point[0]=i;p->point[1]=p->adjvex;//道路起止地点 用节点代号储存
            }
        }
    }
    G->v=v;G->e=e;
}


void Find_attractions(AdjGraph* G,int num){ //输出景点介绍信息、直接相邻景点列表和距离
    printf("该景点介绍信息：%s\n",G->adjlist[num-1].introduce);
    
    
    ArcNode *p=G->adjlist[num-1].firstarc;
    int count=1;
    printf("与该景点直接相连的景点及距离为：\n");
    while(p->nextarc!=NULL)
    {
        printf("%d.%s %f米\n",count,G->adjlist[p->adjvex].name,p->length);
        p=p->nextarc;
        count++;
    }
    
}

void Find_road(AdjGraph* G,int v1, int v2){
    /* 初始条件：图G存在，v和w是G中两个顶点 */
    /* 操作结果：在G中删除弧<v,w>，若G是无向的，则还删除对称弧<w,v> */
    int i,j;
   // ArcNode e;           //弧e
    i=LocateVex(G,v1); /* i是顶点v(弧尾)的序号 */
    j=LocateVex(G,v2); /* j是顶点w(弧头)的序号 */
    if(i<0||j<0||i==j)   //判断有无输入景点
        printf("输入景点有误\n");
    Floyd(edge,v1,v2);
    
    
}

int LocateVex(AdjGraph* G,int u)   //输入景点编号
{ /* 初始条件：图G存在，u和G中顶点有相同特征 */
    /* 操作结果：若G中存在顶点u，则返回该顶点在图中位置；否则返回-1 */
    int i;
    for(i=0;i<MAXV;++i)
        if(u ==G->adjlist[i].num)
            return i;
    return -1;
}

void Floyd(int g[MAXV][MAXV],int v1, int v2){
    int A[MAXV][MAXV], path[MAXV][MAXV];
    int i,j,k;
    for(i=0;i<MAXV;i++){
        for(j=0;j<MAXV;j++){
            A[i][j]=g[i][j];
            if(i!=j && g[i][j]<INF)
                path[i][j]=i;
            else
                path[i][j]=-1;
        }
    }
    
    for(k=0;k<MAXV;k++){
        for(i=0;i<MAXV;i++){
            for(j=0;j<MAXV;j++)
                if(A[i][j]>A[i][k]+A[k][j]){
                    A[i][j]=A[i][k]+A[k][j];
                    path[i][j]=path[k][j];
                }
        }
    }
    Dispath(g,A,path,v1,v2);
}

void Dispath(int g[][MAXV], int A[][MAXV], int path[][MAXV], int i, int j){
    int apath[MAXV], k,d;       //存放最短路径顶点（反向）及顶点个数
    int i1,j1;
    i1=i-1;j1=j-1;
    if(A[i1][j1]!=INF && i1!=j1){   //i,j存在路径
        printf("从%d到%d的路径为：",i,j);
        k=path[i1][j1]; d=0; apath[d]=j1;
        while(k!=-1 && k!=i1){      //中间点
            d++; apath[d]=k;
            k=path[i1][k];
        }
        d++;apath[d]=i1;         //起点
        printf("%d ",apath[d]+1);  //打印起点
        for(int s=d-1;s>=0;s--)
            printf("%d ",apath[s]+1);
    }
    printf("\n");
}

int main (void){
    AdjGraph* Campus = (AdjGraph*)malloc(sizeof(AdjGraph));
    CreateGraph(Campus, edge, 5, 5);
    int a=0;
    int b1,b2,b3;
    printf("***********************\n");
    printf("\t\t欢迎来到whu\t\t\n");
    printf("1.景点查询\n");
    printf("2.线路查询\n");
    printf("3.浏览路径推荐\n");
    printf("***********************\n");
    while(1){
        scanf("%d",&a);
        switch(a){
            case 1:{
                printf("请输入您想要查询的景点的编号!\n");
                scanf("%d",&b1);
                Find_attractions(Campus,b1);
                break;
            }
            case 2:{
                printf("请依次输入您想要查询的两个景点的编号!\n");
                scanf("%d%d",&b2,&b3);
                Find_road(Campus,b2,b3);
                break;
                
            case 3:{
                printf("请输入您的起点对应的编号!\n");
                
                break;
            }
            default: printf("数据有误,请重新输入!\n");
            }
        }
    }
    return 0;
}
