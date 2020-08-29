#include<stdio.h>
#include<stdlib.h>

typedef struct HNode* Heap;
//����ѵ���������
struct HNode {
	int* Data;//�������ݵ�����
	int size;//���е�ǰԪ�صĸ���
	int Capacity;//�ѵ��������
};

Heap CreateHeap(Heap MInHeap, int Num);
//��������ΪNUM+1����С��
void ReadData(Heap MinHeap, int NUm, int *Pos, int M);
//������е�����
void PacUp(Heap MinHeap, int p);
//���ˣ���MinHeap����MinHeap->Data[p]Ϊ�����Ӷѵ���Ϊ��С��
void BuildHeap(Heap MinHeap);
//������С��
void Print(Heap MinHeap, int* Pos, int num);
//�������
int main()
{
	int N, M;//NԪ�ظ�����M·������
	Heap MinHeap;//������С��
	int* Pos;//����·������±������

	scanf_s("%d %d", &N, &M);
	Pos = (int*)malloc(sizeof(int) * M);
	MinHeap = (Heap)malloc(sizeof(struct HNode));
	if (!MinHeap) {
		//���
		printf("ERROR");
		return -1;
	}
	MinHeap = CreateHeap(MinHeap, N);
	ReadData(MinHeap, N, Pos, M);
	BuildHeap(MinHeap);
	Print(MinHeap, Pos, M);//��Ҫ�����
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
	//�����ڱ�Ϊ �����������ݵ�һ��ֵ
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
	//���¹��ˣ���MinHeap����MinHeap->Data[p]Ϊ�����Ӷѵ���Ϊ��С��
	int Parent, child;
	int x;
	x = MinHeap->Data[p];//ȡ�����ڵ������
	for (Parent = p; Parent * 2 <= MinHeap->size; Parent = child) {
		child = Parent * 2;
		if ((child != MinHeap->size) && (MinHeap->Data[child] > MinHeap->Data[child + 1]))
			child++;//ָ���ֽڵ��н�С��һ��
		if (x <= MinHeap->Data[child]) break;
		else {
			//���¹���
			MinHeap->Data[Parent] = MinHeap->Data[child];
		}
		MinHeap->Data[Parent] = x;
	}
}

void BuildHeap(Heap MinHeap)
{
	//����MinHeap->Data[]�е�Ԫ�أ�ʹ��������С�ѵ�Ҫ��
	int i;
	//�����һ�����ĸ��ڵ�����������ڵ����
	for (i = MinHeap->size / 2; i > 0; i--) {
		PacUp(MinHeap, i);
	}
}
void Print(Heap MinHeap, int* Pos, int Num)
{//�Ӹ��Ľ���������������������ݣ�ֱ�������
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