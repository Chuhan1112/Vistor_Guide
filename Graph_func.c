#include "Structure.h"
#include "Grah_func.h"
#include "stdlib.h"
#include "stdio.h"
#include<string.h>

double road_length[MAXV][MAXV]={{0,INF,5,10,INF},{INF,0,INF,INF,6},{5,INF,0,3,8},{10,INF,3,0,INF},{INF,6,8,INF,0}};
//存储道路长度的邻接矩阵
char spot_name[MAXV][MAX]={“一教学楼”,“二教学楼”,“三教学楼”,“四教学楼”,“五教学楼”};
//存储节点名称
char spot_introduce[MAXV][MAX]={“zheshi一教学楼”,“zheshi二教学楼”,“zheshi三教学楼”,“zheshi四教学楼”,“zheshi五教学楼”};
//景点介绍

void CreateGraph(AdjGraph *G, int A[MAXV][MAXV], int v, int e){
    int i,j; ArcNode *p;
    G=(AdjGraph*)malloc(sizeof(AdjGraph));
    for(i=0;i<v;i++){
        for(j=v-1;j>=0;j--){
            if(A[i][j]!=0){
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
                p->point[0]=i,p->point[1]=p->adjvex;//道路起止地点 用节点代号储存
            }
        }
    }
    G->v=v;G->e=e;
}


void DestoryAd(AdjGraph* G){
    ArcNode *pre,*p;
    for(int i=0;i<G->v;i++){
        pre=G->adjlist[i].firstarc;
        if(pre!=NULL){
        p=pre->nextarc;
        //释放第i个单链表的所有边结点
        while(p!=NULL){
            free(pre);
            pre=p;
            p=pre->nextarc;
            }
        free(pre);
        }
    }
    free(G);
}

void Find_attractions(AdjGraph* G,int num){ //输出景点介绍信息、直接相邻景点列表和距离
    printf("该景点介绍信息：%s\n",G->adjlist[num].introduce);


    ArcNode *p=G->adjlist[num].firstarc;
    int count=1;
    printf("与该景点直接相连的景点及距离为：\n");
    while(p->nextarc!=NULL)
    {
        printf("%d.%c\t%f米\n",count,G->adjlist[p->adjvex].name,p->length);
        p=p->nextarc;

    }

}

