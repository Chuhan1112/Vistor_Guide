#include<stdio.h>
#include<stdlib.h>
#include"Grah_func.h"
#include"Structure.h"

#define INF 99999

double road_length[MAXV][MAXV]={{0,INF,5,10,INF},{INF,0,INF,INF,6},{5,INF,0,3,8},{10,INF,3,0,INF},{INF,6,8,INF,0}};
//存储道路长度的邻接矩阵

char spot_name[MAXV][MAX]={“一教学楼”,“二教学楼”,“三教学楼”,“四教学楼”,“五教学楼”};
//存储节点名称




int main (void){
    printf("hello!");
    return 0;
}