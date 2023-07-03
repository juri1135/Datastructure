#include <stdio.h>
#include <stdlib.h>
#include <time.h>
typedef struct _DisjointSet{
	int size;
	int *ptr_arr; //members
}DisjointSets;

typedef struct _PrintDisjointSet{
	int size;
	int *ptr_arr;  //wall
}PrintDisjointSets;

void init(DisjointSets *sets, PrintDisjointSets* maze, int n);
int find(DisjointSets *sets, int x);
void union_(DisjointSets *sets, int i, int j);
void createMaze(DisjointSets *sets, PrintDisjointSets *maze, int n);
void printMaze(PrintDisjointSets *maze, int n);
void freeMaze(DisjointSets *sets, PrintDisjointSets *maze);

void init(DisjointSets *sets, PrintDisjointSets* maze, int n){
	sets->ptr_arr=malloc(sizeof(int)*(n*n));
	if(sets->ptr_arr==NULL) exit(1);
	sets->size=n*n+1;

	maze->size=2*n*n+2*n;
	maze->ptr_arr=malloc(sizeof(int)*maze->size);
	if(maze->ptr_arr==NULL) exit(1);

	for(int i=1; i<=n*n; i++) sets->ptr_arr[i]=0;
	
	for(int i=0; i<2*n*n+2*n; i++) maze->ptr_arr[i]=1;
	
	maze->ptr_arr[n]=0; //start 벽 뚫기
	maze->ptr_arr[2*n*n+n-1]=0;//end 벽 뚫기
}

int find(DisjointSets *sets, int x){
	if(sets->ptr_arr[x]<=0) return x;
	else return(sets->ptr_arr[x]=find(sets, sets->ptr_arr[x]));
}

void union_(DisjointSets *sets, int i, int j){
	int ih=find(sets,i);
	int jh=find(sets,j);
	if(sets->ptr_arr[jh]<sets->ptr_arr[ih]){//음수니까 j의 height이 더 작은 경우 j를 i로! j의 parent가 i
		sets->ptr_arr[ih]=jh;
	}
	else{
		if(sets->ptr_arr[ih]==sets->ptr_arr[jh]){
            sets->ptr_arr[ih]--;
        }
        sets->ptr_arr[jh]=ih;//height이 같은 경우 임의로 i의 부모를 j로 정했으니까 j의 height은 증가(음수니까 감소)
        
	}
}	

void createMaze(DisjointSets* sets, PrintDisjointSets *maze, int n){
	//벽이면 1, 뚫려 있으면 0
	while(find(sets,1)!=find(sets,n*n)){//start와 end가 same set일 때까지 반복
		srand(time(NULL));
		int r=rand()%((2*n*n)+(2*n));
        if(maze->ptr_arr[r]==0) continue; //이미 뚫렸으면 다시 돌리기
		int c1,c2;
        if(r%(2*n+1)==n||r%(2*n+1)==2*n||r<n||r>=n*(2*n+1)) continue; //테두리면 다시 돌리기
        if(r%(2*n+1)<n){
            c1=r/(2*n+1)*n+r%(2*n+1)-n+1;
            c2=c1+n;
        }
        else{
            c1=(r/(2*n+1)-1)*n+r%(2*n+1);
            c2=c1+1;
        }
        if(find(sets,c1)==find(sets,c2)) continue; //같은 set에 있으면 다시 돌리기
        else{
            union_(sets,c1,c2);
            maze->ptr_arr[r]=0;
        }
	}
}

void printMaze(PrintDisjointSets *maze, int n){
    for(int i=0; i<2*n*n+2*n; i++){
        if(i%(2*n+1)<n){
            if(maze->ptr_arr[i]==0) printf("  ");
            else printf(" -");
        }
        else{
            if(maze->ptr_arr[i]==1) printf("| ");
            else printf("  ");
        }
        if(i%(2*n+1)==(n-1)||i%(2*n+1)==(2*n)) printf("\n");
    }
}

void freeMaze(DisjointSets *sets, PrintDisjointSets *maze){
	free(sets->ptr_arr);
	free(maze->ptr_arr);
	free(sets);
	free(maze);
}

int main(int argc, char* argv[]){
	int num;
	FILE *fi=fopen(argv[1], "r");
	fscanf(fi, "%d", &num);
	fclose(fi);
	DisjointSets *sets;
	PrintDisjointSets *maze;

	sets=(DisjointSets*)malloc(sizeof(DisjointSets));
	maze=(PrintDisjointSets*)malloc(sizeof(PrintDisjointSets));

	init(sets, maze, num);

	createMaze(sets, maze, num);

	printMaze(maze, num);

	freeMaze(sets, maze);

	return 0;
}
