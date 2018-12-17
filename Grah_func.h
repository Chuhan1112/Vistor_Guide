#include "Structure.h"

void CreateGraph(AdjGraph *G, int A[MAXV][MAXV], int v, int e);
//void DispAdj(AdjGraph *G);
void DestoryAd(AdjGraph* G);
void Find_attractions(int num);
void Find_road(int v1, int v2);
void Recommend(int num);//输入景点