#include <stdio.h>
#include <stdlib.h>

const int INF=(int)2e9;

typedef struct Node{
    int vertex;
    int dist;
    int prev;
}Node;

typedef struct Graph{
    int size;
    Node* nodes;
    int** matrix;
}Graph;

typedef struct Heap{
    int capacity;
    int size;
    Node* elements;
}Heap;
Graph* createGraph(int X);
Heap* createMinHeap(int X);
Graph* findShortestPath(Graph* G, int s);
void printShortestPath(Graph* G);
void insert(Heap* H, Node N);
Node deleteMin(Heap* H);
void decreaseKey(Heap* H, Node N);


Graph* createGraph(int X){
    Graph* G=malloc(sizeof(struct Graph));
    G->size=X;
    G->nodes=malloc(sizeof(struct Node)*(X+1));//1번 인덱스부터 값 넣을 거니까!
    for(int i=1; i<=X; i++){
        G->nodes[i].vertex=i;//i번째 노드는 i
        G->nodes[i].dist=INF;
        G->nodes[i].prev=0;//1번 노드부터 있으니까 일단 0으로 초기화
    }
    G->matrix=malloc(sizeof(int*)*(X+1));
    for(int i=1; i<=X ;i++){
        G->matrix[i]=calloc(X+1, sizeof(int));//바로 0으로 다 초기화
    }
    return G;
}

Heap* createMinHeap(int X){
    Heap* H=malloc(sizeof(struct Heap));
    H->capacity=X;
    H->size=0;
    H->elements=malloc((sizeof(struct Node))*X);
}

Graph* findShortestPath(Graph* G, int s){
    //1번 노드부터 시작
    Heap* H=createMinHeap(G->size);
    G->nodes[s].dist=0;//첫 번째 노드 거리 0으로 설정
    for(int i=1; i<=G->size; i++){
        if(G->matrix[s][i]!=0&&i!=s){//사이클 아니고, 인접한 경우
            G->nodes[i].dist=G->matrix[s][i];//거리는 가중치
            G->nodes[i].prev=s;//이전노드는 첫 번째 노드로 설정
        }
        if(i!=s) insert(H,G->nodes[i]);//첫 번째 노드 빼고 모든 노드 heap에 넣기
    }
    while(H->size>0){//Heap에 원소 남아 있으면 계속 돌려
        Node N=deleteMin(H);//dist 최소인 애 잡고
        for(int i=1; i<=G->size; i++){
            if(G->matrix[N.vertex][i]!=0&&i!=s){//본인 아니고, 인접한 노드들 검색
                if((N.dist)+(G->matrix[N.vertex][i])< G->nodes[i].dist){//만약 새로운 경로가 원래 경로보다 효율적이면
                    G->nodes[i].dist=N.dist+G->matrix[N.vertex][i];//바꿔주기
                    G->nodes[i].prev=N.vertex;//해당 노드는 최소 경로인 노드랑 연결
                    decreaseKey(H,G->nodes[i]);//하나는 tem에서 per로 바꼈으니까 decreasekey해주기
                }
            }
        }
    }
    return G;
}

void printShortestPath(Graph* G){
    for(int i=2; i<=G->size; i++){//1번째 노드가 시작노드니까 2번부터 돌려야 함
        Node N=G->nodes[i];//시작 노드
        int d=N.dist;
        printf("%d",N.vertex);//node 하나 출력
        while(1){
            if(N.prev==0){//도달하지 못 했거나 시작 노드
                if(d==INF){//도달하지 못 한 경우
                    printf(" can not be reached.\n"); 
                }
                else{//도달해서 시작 노드까지 간 경우, 시작 노드까지의 dist 출력
                    printf(" cost: %d\n",d);
                }
                break;
                //도달하지 못 했거나 시작 노드라면 더 이상 출력할 값 없으므로 break;
            }
            else{//중간 노드면 화살표 + 노드
                N=G->nodes[N.prev];//전 노드로 넘어가기
                printf("<-%d",N.vertex);
            }
        }
    }
}




void insert(Heap* H, Node N){
    if(H->size==H->capacity){
        printf("Insertion Error: Min Heap is full.\n");
    }
    else{
        int i;
	    for(i=++H->size; i>=1&&H->elements[i/2].dist>N.dist; i/=2){//하나 넣을 거니까 size 하나 증가시켜두고 제일 위 노드까지 올라갈 건데, 위에 있는 노드의 거리가 지금 넣으려는 노드의 가중치보다 커야 함(minheap이니까)
            H->elements[i]=H->elements[i/2];//만약 조건을 만족한다면 그 자리에 위에 값 넣기
        }
	    H->elements[i]=N;//그리고 비어 있는 값에 넣으려는 노드 추가
    }
}

Node deleteMin(Heap* H){
    if(H->size==0){
        printf("Deletion Error: Max Heap is empty!\n");
    }
    else{
        Node lastelement=H->elements[H->size--], minelement=H->elements[1];
	    int child,i;
	    for(i=1; i*2<=H->size; i=child){//왼쪽으로 갈지 오른쪽으로 갈지 모르니까 i=child여야 한다
	       	child=i*2;
       		if(child!=H->size&&H->elements[child].dist>H->elements[child+1].dist);
	 		    child++;
		    if(lastelement.dist>H->elements[child].dist)
			    H->elements[i]=H->elements[child];
		    else
			    break;		
	    }
	
	    H->elements[i]=lastelement;//다 빠져나오면 비어 있는 자리니까 lastelement 넣어줘야 함
	    return minelement;
    }
	
}
void decreaseKey(Heap* H, Node N){
    int i;
    for(int i=1; i<=H->size; i++){
        if(H->elements[i].vertex==N.vertex) break;
    }
    for(i=H->size; i>1&&H->elements[i/2].dist>N.dist; i/=2){
        H->elements[i]=H->elements[i/2];
    }
    H->elements[i]=N;
}

int main(int argc, char* argv[]){
    FILE *fi=fopen(argv[1],"r");
    int size;
    fscanf(fi, "%d", &size);

    Graph* G=createGraph(size);

    int node_s, node_d, weight;
    while(fscanf(fi, "%d %d %d",&node_s,&node_d,&weight)!=EOF){
        G->matrix[node_s][node_d]=weight;
    }
   
    G=findShortestPath(G,1);
    printShortestPath(G);
    free(G);
    return 0;
}