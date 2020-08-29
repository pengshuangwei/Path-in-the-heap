#include<stdio.h>
#include<stdlib.h>

typedef struct HNode* Heap;
//定义堆得数据类型
struct HNode {
	int* Data;//储存数据的数组
	int size;//堆中当前元素的个数
	int Capacity;//堆得最大容量
};

Heap CreateHeap(Heap MInHeap, int Num);
//创建容量为NUM+1的最小堆
void ReadData(Heap MinHeap, int NUm, int *Pos, int M);
//读入堆中的数据
void PacUp(Heap MinHeap, int p);
//上滤，将MinHeap中以MinHeap->Data[p]为根的子堆调整为最小堆
void BuildHeap(Heap MinHeap);
//建立最小堆
void Print(Heap MinHeap, int* Pos, int num);
//输出函数
int main()
{
	int N, M;//N元素个数，M路径个数
	Heap MinHeap;//定义最小堆
	int* Pos;//储存路径起点下标的数组

	scanf_s("%d %d", &N, &M);
	Pos = (int*)malloc(sizeof(int) * M);
	MinHeap = (Heap)malloc(sizeof(struct HNode));
	if (!MinHeap) {
		//验空
		printf("ERROR");
		return -1;
	}
	MinHeap = CreateHeap(MinHeap, N);
	ReadData(MinHeap, N, Pos, M);
	BuildHeap(MinHeap);
	Print(MinHeap, Pos, M);//按要求输出
	free(MinHeap->Data);
	free(MinHeap);
	free(Pos);

	return 0;
}

Heap CreateHeap(Heap MinHeap, int Num)
{
	MinHeap->Capacity = Num + 1;
	MinHeap->Data = (int*)malloc(sizeof(int) * (Num + 1));
	if (!MinHeap->Data) {
		printf("ERROR");
		return NULL;
	}
	MinHeap->size = 0;
	MinHeap->Data[0] = -10002;
	//定义哨兵为 大于所有数据的一个值
	return MinHeap;
}
void ReadData(Heap MinHeap, int Num, int* Pos, int M)
{
	int i = 0;
	for (i = 1; i <= Num; i++) {
		scanf_s("%d", &MinHeap->Data[i]);
		MinHeap->size++;
	}
	for (i = 0; i < M; i++) {
		scanf_s("%d", &Pos[i]);
	}
}
void PacUp(Heap MinHeap, int p)
{
	//向下过滤，将MinHeap中以MinHeap->Data[p]为根的子堆调整为最小堆
	int Parent, child;
	int x;
	x = MinHeap->Data[p];//取出根节点的数据
	for (Parent = p; Parent * 2 <= MinHeap->size; Parent = child) {
		child = Parent * 2;
		if ((child != MinHeap->size) && (MinHeap->Data[child] > MinHeap->Data[child + 1]))
			child++;//指向字节点中较小的一个
		if (x <= MinHeap->Data[child]) break;
		else {
			//向下过滤
			MinHeap->Data[Parent] = MinHeap->Data[child];
		}
		MinHeap->Data[Parent] = x;
	}
}

void BuildHeap(Heap MinHeap)
{
	//调整MinHeap->Data[]中的元素，使其满足最小堆的要求
	int i;
	//从最后一个结点的父节点出发，到根节点结束
	for (i = MinHeap->size / 2; i > 0; i--) {
		PacUp(MinHeap, i);
	}
}
void Print(Heap MinHeap, int* Pos, int Num)
{//从给的结点出发，输出各个结点的数据，直到根结点
	int i, j;
	int flag = 0;
	for (j = 0; j < Num; j++) {
		flag = 0;
		for (i = Pos[j]; i > 0; i /= 2) {
			if (flag == 0) flag = 1;
			else printf(" ");
			printf("%d", MinHeap->Data[i]);
		}
		printf("\n");
	}
}