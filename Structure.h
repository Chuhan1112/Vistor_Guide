#define MAX 500             //存储文字
#define MAXV 15             //节点个数

typedef struct ANode        //边节点
{  
    int adjvex;               //该边邻接点编号 
    struct ANode *nextarc;  //指向下一路线的指针
    char road_name[MAX];    //道路名称
    char point[MAX];        //道路起止地点
    double length;           //道路长度
    int  weigh;          
}ArcNode;

typedef struct Vnode        
{
    int num;
    char name[MAX];         //景点名称
    char *introduce;        //景点介绍内容
    ArcNode *firstarc;      //指向第一个边节点
}VNode;                     //顶点节点（景区）

typedef struct
{
    VNode adjlist[MAXV];
    int v,e;                //v：顶点数；e：边数
}AdjGraph;