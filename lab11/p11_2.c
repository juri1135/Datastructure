#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct QuickSort{
	int Capacity;
	int Size;
	int *array;
};

typedef struct QuickSort* QuickSort;

QuickSort make_list(int size);
void Insert(QuickSort q, int a);
void printArray(QuickSort q);
void swap(int *a, int*b);
int middle_partition(QuickSort q, int low, int high);
int leftmost_partition(QuickSort q, int left, int right);
int rightmost_partition(QuickSort q, int left, int right);
void quicksort(QuickSort q, int left, int right, int type);

QuickSort make_list(int size){
	QuickSort q=malloc(sizeof(struct QuickSort));
	q->array=malloc(sizeof(int)*size);
	q->Size=0;
	q->Capacity=size;
}

void Insert(QuickSort q, int a){
	q->array[q->Size++]=a;
}

void printArray(QuickSort q){
	for(int i=0; i<q->Size; i++){
		printf("%d ", q->array[i]);
	}
	printf("\n");
}

void swap(int *a, int *b){
	int x=*a;
	*a=*b;
	*b=x;
}

int middle_partition(QuickSort q, int low, int high){
	int p=q->array[(low+high)/2];
	int i=low;
	int j=high;
	printf("pivot value: %d\n",p);
	for(;;){
		while(q->array[j]>p) j--;
		while(q->array[i]<p) i++;
		if(i>=j){
			printf("result : ");
			printArray(q);
			return j;
		}
		swap(q->array+i,q->array+j);
	}
}

int leftmost_partition(QuickSort q, int left, int right){
	int p=q->array[left];
	int i=left;
	int j=right+1;
	printf("pivot value: %d\n",p);
	for(;;){
		while(q->array[++i]<p);
		while(q->array[--j]>p);
		if(i<j){
			swap(q->array+i,q->array+j);
		}
		else{
			swap(q->array+left,q->array+j);
			printf("result : ");
			printArray(q);
			return j;
		}
	}
	
}
int rightmost_partition(QuickSort q, int left, int right){
	int p=q->array[right];
	printf("pivot value : %d\n",p);
	int i=left-1;
	int j=right;
	for(;;){
		while(q->array[--j]>p);//오른쪽 애들은 pivot보다 커야함
		while(q->array[++i]<p);//왼쪽 애들은 pivot보다 작게
		if(i<j) swap(q->array+i,q->array+j);//정렬 다 되면 low랑 high 교환 
		else{
			swap(q->array+right,q->array+i);//pivot이랑 low를 교환
			printf("result : ");
			printArray(q);
			return i;
		}
	}
}

void quicksort(QuickSort q, int left, int right, int type){
	if(left<right){
		if(type==0){
			int pidx=leftmost_partition(q,left,right);
			quicksort(q,left,pidx-1,0);
			quicksort(q,pidx+1,right,0);
		}
		else if(type==1){
			int pidx=rightmost_partition(q,left,right);
			quicksort(q,left,pidx-1,1);
			quicksort(q,pidx+1,right,1);
		}
		else if(type==2){
			int pidx=middle_partition(q,left,right);
			quicksort(q,left,pidx-1,2);
			quicksort(q,pidx+1,right,2);
		}
	}
}
void main(int argc, char* argv[]){
	char type_s[10];
	int list_size,type_i,key;
	QuickSort q;
	FILE *fi=fopen(argv[1],"r");

	fscanf(fi, "%s", type_s);
	if(!(strcmp(type_s, "leftmost"))) type_i=0;
	else if(!(strcmp(type_s, "rightmost"))) type_i=1;
	else if(!(strcmp(type_s, "middle"))) type_i=2;
	fscanf(fi, "%d", &list_size);
	q=make_list(list_size);
	for(int i=0; i<list_size; i++){
		fscanf(fi, "%d", &key);
		Insert(q,key);
	}
	quicksort(q,0,list_size-1,type_i);

	free(q->array);
	free(q);
}
