#include <stdio.h>
#include <stdlib.h>
typedef struct _Queue{
    int size;
    int *key;
    int front;
    int rear;
}Queue;
//typedef struct Queue* Queue;
//queue 초기화
Queue *CreateQueue(int X){
    Queue *q=(Queue*)malloc(sizeof(struct _Queue));
    q->key=malloc(sizeof(int)*X);
    q->size=X;//max size
    q->front=0;//제일 앞 index;
    q->rear=-1;
}
//enqueue
void Enqueue(Queue *Q, int item){
    if(Q->rear==Q->size-1){
        printf("Enqueue failed: Queue is Full!\n");
    }
    else{
        Q->key[++Q->rear]=item;
    }
}
//Dequeue
int Dequeue(Queue *Q){
    if(Q->rear==-1){
        printf("Dequeue failed: Queue is Empty!\n");
    }
    else{
        int x=Q->key[Q->front++];
        return x;
    }
}
//Adjacenecy matrix
typedef struct _Graph{
    int size;
    int *vertex;
    int **edge;
}Graph;
//initialize aj mtx
Graph *CreateGraph(int  X){
    Graph* G=(Graph*)malloc(sizeof(struct _Graph));
    G->size=X;
    G->vertex=malloc(sizeof(int)*X);
    G->edge=malloc(sizeof(int*)*X);
    for(int i=0; i<X; i++){
        G->edge[i]=malloc(sizeof(int)*X);
        for(int k=0; k<X; k++){
            G->edge[i][k]=0;
        }
    }
    return G;
}
//edge 추가
void InsertEdge(Graph *G, int u, int v){
    int r,c;
    for(int i=0; i<G->size; i++){
        if(G->vertex[i]==u) r=i;
        if(G->vertex[i]==v) c=i;
    }
    G->edge[r][c]=1;
}
//sort
void TopSort(Graph *G){
    Queue* q=CreateQueue(G->size);
    int arr[G->size];
    for(int i=0; i<G->size; i++){
        int x=0;
        for(int k=0; k<G->size; k++){
            if(G->edge[k][i]==1) x++;
        }
        arr[i]=x;
    }
    //arr[i]==0이면 다 queue에 집어넣기
    //dequeue하기
    //dequeue한 애랑 연결된 정점으로 가서 걔네 0 아니면 -1씩 하기
    for(int i=0; i<G->size; i++){
        if(arr[i]==0){
            Enqueue(q,G->vertex[i]);
        }
    }
    while(q->front!=q->size){
        int v=Dequeue(q);
        int idx;
        for(int i=0; i<G->size; i++){
            if(G->vertex[i]==v) idx=i;
        }
        printf("%d ",v);
        for(int k=0; k<G->size; k++){
            if(G->edge[idx][k]==1&&arr[k]!=0){
                arr[k]--;
                if(arr[k]==0){
                    Enqueue(q,G->vertex[k]);
                }
            }
        }
    }
    printf("\n");
}

int main(int argc, char *argv[]){
    FILE *fi=fopen(argv[1], "r");
    int X,u,v;
    fscanf(fi, "%d",&X);
    Graph *G=CreateGraph(X);
    for(int i=0; i<X; i++){
        fscanf(fi, "%d",&G->vertex[i]);
    }
    while(fscanf(fi, "%d %d",&u,&v)!=EOF){
        InsertEdge(G,u,v);
    }
    TopSort(G);
    return 0;
}
