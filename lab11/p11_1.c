#include <stdio.h>
#include <stdlib.h>
struct MergeSort{
	int Capacity;
	int Size;
	int *array;
	int *Tmparray;
};

typedef struct MergeSort* MergeSort;

MergeSort make_list(int size);
void Insert(MergeSort m, int a);
void printArray(MergeSort A, int l, int r);
void RmergeSort(MergeSort A, int l, int r);
void ImergeSort(MergeSort A, int n);
void merge(MergeSort A, int l, int m, int r);

MergeSort make_list(int size){
	MergeSort arr=malloc(sizeof (struct MergeSort));
	arr->array=malloc(sizeof(int)*size);
	arr->Tmparray=malloc(sizeof(int)*size);
	arr->Capacity=size;
	arr->Size=0;
	return arr;
}

void Insert(MergeSort m, int a){
	m->array[m->Size++]=a;
}

void printArray(MergeSort A, int l, int r){
	for(int i=l; i<=r; i++){
		printf("%d ",A->array[i]);
	}
	printf("\n");
}

void RmergeSort(MergeSort A, int l, int r){
	int m=(r+l)/2;
	if(l<r){
		RmergeSort(A,l,m);
		RmergeSort(A,m+1,r);
		merge(A,l,m+1,r);
		printArray(A,l,r);
	}
}

void ImergeSort(MergeSort A, int n)
{
    int size, left;
    for(size = 1; size <= n; size *= 2)
    {
        for(left = 0; left <= n; left += 2 * size)
        {
            int mid = left + size - 1;
            if(mid >= n) mid = n;
            int right = left + 2 * size - 1;
            if(right >= n) right = n;
            merge(A, left, mid+1, right);
            printArray(A, left, right);
        }
    }
    
}


void merge(MergeSort A, int l, int m, int r){
	int LeftEnd=m-1, num=r-l+1, pos=l;
	int lf=l,rf=r;
	while(l<=LeftEnd&&m<=r){
        
		if(A->array[l]<A->array[m]){
			A->Tmparray[pos++]=A->array[l++];
		}
		else if(A->array[l]>=A->array[m]){
			A->Tmparray[pos++]=A->array[m++];
		}
	}
	while(l<=LeftEnd){
		A->Tmparray[pos++]=A->array[l++];
	}
	while(m<=r){
		A->Tmparray[pos++]=A->array[m++];
	}
	for(int i=0; i<num; i++){
		A->array[i+lf]=A->Tmparray[i+lf];
	}

}
		

void main(int argc, char* argv[1]){
	int size;
      int key;
	int *iter_tmp, *rec_tmp;
	FILE *fi=fopen(argv[1], "r");
	MergeSort iter_m, rec_m;
	
	fscanf(fi, "%d", &size);

	iter_m=make_list(size);
	rec_m=make_list(size);

	for(int i=0; i<size; i++){
		fscanf(fi, "%d", &key);
		Insert(iter_m, key);
		Insert(rec_m, key);
	}

	printf("input: \n");
	printArray(iter_m, 0, iter_m->Size-1);
	printf("\n");

	printf("iterative : \n");
	ImergeSort(iter_m, iter_m->Size-1);
	printf("\n");

	printf("recursive : \n");
	RmergeSort(rec_m, 0, rec_m->Size-1);
	printf("\n");
	free(iter_m->array);
	free(iter_m->Tmparray);
	free(rec_m->array);
	free(rec_m->Tmparray);
	free(iter_m);
	free(rec_m);
}
