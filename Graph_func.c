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

