#include <stdio.h>
#include <stdlib.h>

typedef struct Stack{
   int* key;//array
   int top;//원소 갯수
   int max_stack_size;//최대 크기
}Stack;

Stack* CreateStack(int max){
    Stack* s;

    s=(Stack*)malloc(sizeof(Stack));
    if(s==NULL){
        printf("out of space!\n");
        exit(1);
    }
   
    s->key=(int*)malloc(max*sizeof(int));
    if(s->key==NULL){
        printf("out of space!\n");
        exit(1);
    }
    s->max_stack_size=max;
    s->top=-1;
    return s;
}

int IsEmpty(Stack* s){//비어 있으면 1 반환 아니면 0 반환
    return (s->top==-1);
}

int IsFull(Stack* s){//비어 있으면 1 반환 아니면 0 반환
	return (s->top==s->max_stack_size-1);
}

void Push(Stack* s,int x){
    if(IsFull(s)){
        printf("\nStack is full!\n");
	exit(1);
    }
    else{
        s->key[++s->top]=x;
    }
}

int Pop(Stack* s){//top 원소 반환하고 pop
    if(IsEmpty(s)){
        printf("\nStack does not have any element!\n");
       	exit(1);
    }
    else{
        int in=s->key[s->top];
        s->top--;//원소 갯수 하나 줄이기 
        return in;//top==0일 때가 원소 하나 있는 거라 top--해야 함
    }
}

int Top(Stack* s){//top의 원소 반환
    if(IsEmpty(s)){
        printf("\nStack dose not have element!\n");
	exit(1);
    }
    else{
        return s->key[s->top];//array[top--]
    }
}

void DeleteStack(Stack* s){
    if(s==NULL){
	    printf("\nNo stack exists!\n");
	    exit(1);
    }
    else{
        while(!IsEmpty(s)){
            Pop(s);
        }
    }
    free(s->key);
    free(s);
}


void Postfix(Stack* s, char input_str){//여기만 짜면 될듯
    int x;
    if(input_str>=49&&input_str<=57){
        x=input_str-'0';
        Push(s,x);
    }
    else{
        int a,b;
        b=Pop(s);
        a=Pop(s);
        if(input_str=='+'){
            x=a+b;
            Push(s,x);
        }
        else if(input_str=='-'){
            x=a-b;
            Push(s,x);
        }
        else if(input_str=='*'){
            x=a*b;
            Push(s,x);
        }
        else if(input_str=='/'){
            x=a/b;
            Push(s,x);
        }
        else if(input_str=='%'){
            x=a%b;
            Push(s,x);
        }
    }
}

void main(int argc, char* argv[]){
   FILE* fi=fopen(argv[1],"r");
   Stack* stack=CreateStack(10);
   printf("Top numbers: ");
   int count=0;
   while(1){
      char c;
      fscanf(fi, "%c", &c);
      count++;
      if(count>100){
	      printf("no more than 100 characters!\n");
	      exit(1);
      }
      if(c=='#') break;
      Postfix(stack,c);
      printf("%d ",Top(stack));
   }
   printf("\n");
   printf("evaluation result: %d\n",Pop(stack));

   fclose(fi);
   DeleteStack(stack);
}
