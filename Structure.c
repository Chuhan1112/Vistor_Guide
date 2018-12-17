#define MAX 500             //存储文字
#define MAXV 20             //节点个数

typedef struct Anode        //边节点
{  
    int mark;               //景点代号  
    struct Anode *nextarc;  //指向下一景点的指针
    char road_name[MAX];    //道路名称
    char point[MAX];        //道路起止地点
    float length;           //道路长度
}ArcNode;

typedef struct Vnode        //头节点
{
    char name[MAX];         //景点名称
    char introduce[MAX];    //景点介绍内容
    ArcNode *firstarc;      //指向第一个边节点
}VNode;

typedef struct
{
    VNode adjlist[MAXV]
}