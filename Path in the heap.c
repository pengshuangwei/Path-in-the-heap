#include <stdio.h>
#define MAXN 1005
#define MINDATA -10005

int Data[MAXN], size;

void Insert(int x) {
    int i = ++size;
    for (; x < Data[i / 2]; i /= 2)
        Data[i] = Data[i / 2];
    Data[i] = x;
}

int main() {
    int N, M;
    int x;
    scanf_s("%d%d", &N, &M);
    Data[0] = MINDATA;
    size = 0;
    while (N--) {
        scanf_s("%d", &x);
        Insert(x);
    }
    while (M--) {
        scanf_s("%d", &x);
        printf("%d", Data[x]);
        x /= 2;
        while (x) {
            printf(" %d", Data[x]);
            x /= 2;
        }
        printf("\n");
    }
    return 0;
}