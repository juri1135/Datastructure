#include <stdio.h>
#include <stdlib.h>
struct CircularQueueStruct{
  int *key;
  int first;
  int rear;
  int qsize;
  int max_queue_size;
};
typedef struct CircularQueueStruct* CircularQueue;
CircularQueue MakeEmpty(int max);
int IsEmpty(CircularQueue Q);
int IsFull(CircularQueue Q);
void Dequeue(CircularQueue Q);
void Enqueue(CircularQueue Q,int X);
void PrintFirst(CircularQueue Q);
void PrintRear(CircularQueue Q);
void DeleteQueue(CircularQueue Q);
CircularQueue MakeEmpty(int max){
  CircularQueue Q;
  Q=malloc(sizeof(struct CircularQueueStruct));
  if(Q==NULL){
    printf("Out of space!\n");
    exit(1);
  }
  Q->key=malloc(sizeof(int)*max);
  if(Q->key==NULL){
    printf("Out of space!\n");
    exit(1);
  }
  Q->first=0;
  Q->rear=-1;
  Q->max_queue_size=max;
  Q->qsize=0;//현재 queue size
}
int IsEmpty(CircularQueue Q){
  return (Q->qsize==0);
}
int IsFull(CircularQueue Q){
  return (Q->qsize==Q->max_queue_size);
}
void Dequeue(CircularQueue Q){
  if(IsEmpty(Q)){
    printf("Dequeue failed: Queue is Empty!\n");
  }
  else{
    printf("Dequeue %d\n",Q->key[Q->first]);
    Q->first=(Q->first+1)%(Q->max_queue_size);
    Q->qsize--;
  }
}
void Enqueue(CircularQueue Q, int X){
  if(IsFull(Q)){
    printf("Enqueue failed: Queue is Full!\n");
  }
  else{
    printf("Enqueue %d\n",X);
    Q->qsize++;
    Q->rear=(Q->rear+1)%(Q->max_queue_size);
    Q->key[Q->rear]=X;
  }
}
void PrintFirst(CircularQueue Q){
  if(IsEmpty(Q)) printf("Queue is Empty!\n");
  else printf("First : %d\n",Q->key[Q->first]);
}
void PrintRear(CircularQueue Q){
  if(IsEmpty(Q)) printf("Queue is Empty!\n");
  else printf("Rear : %d\n",Q->key[Q->rear]);
}
void DeleteQueue(CircularQueue Q){
  while(Q->first<=Q->rear){
    Q->first++;
  }
  free(Q->key);
  free(Q);
}
void main(int argc, char* argv[]){
  char command;
  FILE *input;
  CircularQueue queue;
  int queuesize;
  int tmpNum;

  input=fopen(argv[1],"r");
  while(1){
    command=fgetc(input);
    if(feof(input)) break;
    switch(command){
      case 'n':
        fscanf(input, "%d\n",&queuesize);
        queue=MakeEmpty(queuesize);
        break;
      case 'e':
        fscanf(input, "%d\n", &tmpNum);
        Enqueue(queue, tmpNum);
        break;
      case 'd':
        Dequeue(queue);
        break;
      case 'f':
        PrintFirst(queue);
        break;
      case 'r':
        PrintRear(queue);
        break;
      default:
        break;
    }
  }
  DeleteQueue(queue);
}
