#include <stdio.h>
#include <stdlib.h>
typedef struct Node* PtrToNode;
typedef PtrToNode List;
typedef PtrToNode Position;
typedef int ElementType;
struct Node{
	ElementType element;
	Position next;
};
List MakeEmptyList();
int isLast(Position P, List l);
void Delete(ElementType x, List l);
Position FindPrevious(ElementType x, List l);
Position Find(ElementType x, List l);
void Insert(ElementType x, Position p, List l);
void DeleteList(List l);
void PrintList(List l);
int main(int argc, char *argv[]){
	char command;
	int key1,key2;
	FILE *input, *output;
	Position header=NULL, tmp=NULL;
	if(argc<=1){
		printf("Please enter an input file.");
		return 0;
	}
	else{
		input=fopen(argv[1],"r");
	}
	header=MakeEmptyList();
	while(1){
		command=fgetc(input);
		if(feof(input)) break;
		
		switch(command){
		case 'i':
			fscanf(input,"%d %d\n",&key1,&key2);
			tmp=Find(key2,header);//key2값을 가진 node의 위치를 알아낸다
			Insert(key1,tmp,header);//key1값을 가진 node를 tmp 위치에 넣는다 insert함수를 tmp next로 가게 짜야 할듯
			break;
		case 'd':
			fscanf(input,"%d\n", &key1);
			Delete(key1,header);
			break;
		case 'f':
			fscanf(input,"%d\n",&key1);
			tmp=FindPrevious(key1,header);
			if(tmp==NULL){//만약 key값 가진 node가 없어서 tmp가 null이라면 
				printf("Could not find %d in the list.\n",key1);
			}
			else if(tmp->element>0){
				printf("Key of the previous node of %d is %d.\n",key1,tmp->element);
			}
			else{
				printf("Key of the previous node of %d is header.\n",key1);
			}
			break;
		case 'p':
			PrintList(header);
			break;
		defalut:
			printf("Invalid command line.");
		}
	}
	DeleteList(header);
	fclose(input);
	return 0;
}
List MakeEmptyList(){
	List l=(List)malloc(sizeof(struct Node));
	l->element=-999;
	l->next=NULL;
	return l;
}
int isLast(Position p, List l){//마지막 노드(NULL 이전)라면 1 반환
	Position current=l;
	while(current->next!=NULL){
		current=current->next;
	}
	return p==current;
}
Position FindPrevious(ElementType x, List l){
	Position posi=l;
	if(l->next==NULL){
		return NULL;
	}
	while(posi->next->element!=x&&posi->next!=NULL){
		if(posi->next->next==NULL){
			return NULL; //그냥 없으면 임의로 null 반환하기
		}
		posi=posi->next;
	}
	return posi;
}
Position Find(ElementType x, List l){ //여기 다시 짜기
	if(x==-1){
		return l;
	}
	Position posi=l->next;
	while(posi!=NULL&&posi->element!=x){
		if(posi->next==NULL){
			return NULL;
//현 node의 key값이 x는 아닌데 다음 node가 NULL이라면 그냥 NULL 반환 이거 예외 처리 안 해주니까 seg fault 뜨는 거 보니 posi가 NULL에 도달해버리면 안 되는 것 같음
		}
		posi=posi->next;
	}
	return posi;
}
void Insert(ElementType x, Position p, List l){//여기 다시 짜기
	if(p==NULL){//main에서 find했을 때 key2값이 없어서 null 반환한 경우
        printf("Insertion(%d) Failed: cannot find the location to be inserted.\n",x);
        return;
    	}
    	Position tmp;
	tmp=malloc(sizeof(struct Node));
	if(tmp==NULL){//동적 할당이 불가능하면 error 메시지
		printf("Out of space!!'\n");
        	return;
	}
    	tmp->element=x;
    	tmp->next=p->next;
	p->next=tmp;
}
void Delete(ElementType x, List l){//delete(key1,header);
	Position posi=FindPrevious(x,l);
	Position p;
	if(Find(x,l)==NULL){
		printf("Deletion failed. element %d is not in the list.\n",x);
		return;
	}
	if(!isLast(posi,l)){//key값이 x인 노드가 마지막 노드가 아닐 때만 마지막 노드면 p에 NULL이 되면서 접근이 불가능해짐
		p=posi->next;
		posi->next=p->next;
		free(p);
	}
	
}
void PrintList(List l){
	PtrToNode tmp=NULL;
	tmp=l->next;
	if(tmp==NULL){
		printf("list is empty!\n");
		return;
	}
	while(tmp!=NULL){
		printf("key: %d\t", tmp->element);
		tmp=tmp->next;
	}
	printf("\n");
}
void DeleteList(List l){
	Position p=NULL, tmp=NULL;
	p=l->next;
	l->next=NULL;
	while(p!=NULL){
		tmp=p->next;
		free(p);
		p=tmp;
	}
}
