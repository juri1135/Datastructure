#include  <stdio.h>
#include <stdlib.h>
typedef struct HeapStruct* Heap;
struct HeapStruct{
	int Capacity;
	int Size;
	int *Element;
};
Heap CreateHeap(int heapSize);
void Insert(Heap heap, int value);
int Find(Heap heap, int value);
void DeleteMax(Heap heap);
void PrintHeap(Heap heap);
void FreeHeap(Heap heap);

Heap CreateHeap(int heapSize){
	Heap heap;
	heap=malloc(sizeof(struct HeapStruct));
	if(heap==NULL)
		exit(1);
	heap->Element=malloc(sizeof(int)*heapSize);
	if(heap->Element==NULL)
		exit(1);
	heap->Capacity=heapSize;
	heap->Size=0;
	return heap;
}

void Insert(Heap heap,int value){
	if(heap->Size==heap->Capacity){
		printf("Insertion Error: Max Heap is full.\n");
		return;
	}
	if(Find(heap,value)){
		printf("%d is already in the heap.\n", value);
		return;
	}
	if(heap->Size==0){
		heap->Size++;
		heap->Element[1]=value;
		printf("Insert %d\n", value);
		return;
	}
	int i;
	heap->Element[++heap->Size]=value;
	for(i=heap->Size; i>1; i/=2){
		if(heap->Element[i]>heap->Element[i/2]){
			int x=heap->Element[i];
			heap->Element[i]=heap->Element[i/2];
			heap->Element[i/2]=x;
		}
		else{
			break;
		}
	}
	
	printf("Insert %d\n",value);
}
void DeleteMax(Heap heap){
	if(heap->Size==0){
		printf("Deletion Error: Max Heap is empty!\n");
		return;
	}
	int lastelement=heap->Element[heap->Size], maxelement=heap->Element[1];
	int child,i;
	heap->Size--;
	for(i=1; i*2<=heap->Size; i=child){//왼쪽으로 갈지 오른쪽으로 갈지 모르니까 i=child여야 한다
	       	child=i*2;
       		if(child!=heap->Size&&heap->Element[child]<heap->Element[child+1])
	 		child++;
		if(lastelement<heap->Element[child])
			heap->Element[i]=heap->Element[child];
		else
			break;		
	}
	
	heap->Element[i]=lastelement;//다 빠져나오면 비어 있는 자리니까 lastelement 넣어줘야 함
	printf("Max element(%d) deleted\n",maxelement);
	//heap->Size--;
}
	
int Find(Heap heap, int value){
	for(int i=1; i<=heap->Size; i++){
		if(heap->Element[i]==value)
			return 1;
	}//complete tree라서 array로 표현할 수 있음!
	return 0;
}
void PrintHeap(Heap heap){
	if(heap->Size==0){
		printf("Max Heap is empty!\n");
		return;
	}
	for(int i=1; i<=heap->Size; i++){
		printf("%d ",heap->Element[i]);
	}
	printf("\n");
}
void FreeHeap(Heap heap){
	free(heap->Element);
	free(heap);
}
void main(int argc, char* argv[]){
	FILE *fi=fopen(argv[1],"r");
	char cv;
	Heap maxHeap;
	int value, maxValue;
	while(!feof(fi)){
		fscanf(fi, "%c", &cv);
		switch(cv){
			case 'n':
				fscanf(fi, "%d\n", &value);
				maxHeap=CreateHeap(value);
				break;
			case 'i':
				fscanf(fi, "%d\n", &value);
				Insert(maxHeap, value);
				break;
			case 'd':
				DeleteMax(maxHeap);
				break;
			case 'f':
				fscanf(fi, "%d\n", &value);
				if(Find(maxHeap, value))
					printf("%d is in the heap.\n",value);
				else
					printf("%d is not in the heap.\n",value);
				break;
			case 'p':
				PrintHeap(maxHeap);
		}
	}
	FreeHeap(maxHeap);
}

