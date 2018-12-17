#include "Structure.h"
#include "Grah_func.h"
#include "stdlib.h"
#include "stdio.h"

void CreateGraph(AdjGraph *G, int A[MAXV][MAXV], int v, int e){
    int i,j; ArcNode *p;
    G=(AdjGraph*)malloc(sizeof(AdjGraph));
    for(i=0;i<v;i++){
        for(j=v-1;j>=0;j--){
            if(A[i][j]!=0){
                G->adjlist[i].num=i;//景点编号赋值
                
                p=(ArcNode*)malloc(sizeof(ArcNode));
                p->adjvex=j;
                p->weigh=A[i][j];
                //头插法
                p->nextarc=G->adjlist[i].firstarc;
                G->adjlist[i].firstarc=p;
                printf("请输入道路名称:\n");
                scanf("%s", p->road_name);
                printf("请输入道路起止地点:\n");
                scanf("%s", p->point);
                printf("请输入道路长度:\n");
                scanf("%f", p->length);
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