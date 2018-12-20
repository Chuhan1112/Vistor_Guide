#include "Structure.h"

void CreateGraph(AdjGraph *G, int A[MAXV][MAXV], int v, int e);
//void DispAdj(AdjGraph *G);
void DestoryAd(AdjGraph* G);
void Find_attractions(AdjGraph* G,int num);
void Find_road(AdjGraph* G,int v1, int v2);
void Recommend(int num);//输入景点