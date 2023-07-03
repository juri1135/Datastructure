#include <stdio.h>
#include <stdlib.h>
struct TreeStruct{
	int size;
	int numOfNode;
	int* element;
};

typedef struct TreeStruct* Tree;

void DeleteTree(Tree tree);
Tree CreateTree(int size);
void Insert(Tree tree, int value);
void PrintTree(Tree tree);
void printPreorder(Tree tree, int index);
void printInorder(Tree tree, int index);
void printPostorder(Tree tree, int index);

Tree CreateTree(int size){
	Tree tree;

	tree=malloc(sizeof(struct TreeStruct));
	tree->element=malloc(sizeof(int)*size);

	tree->numOfNode=0;
	tree->size=size;

	return tree;
}

void Insert(Tree tree, int value){
	if(tree->numOfNode==tree->size){
		printf("Error! Tree is full.\n");
	}
	else{
		tree->numOfNode++;
		tree->element[tree->numOfNode]=value;
	}
}
void PrintTree(Tree tree){
	printf("Preorder: ");
	printPreorder(tree,1);
	printf("\nInorder: ");
	printInorder(tree,1);
	printf("\nPostorder: ");
	printPostorder(tree,1);
}
void printPreorder(Tree tree, int index){
	if(index<=tree->numOfNode){
		printf("%d ",tree->element[index]);
		printPreorder(tree,index*2);
		printPreorder(tree,index*2+1);
	}
}
void printInorder(Tree tree, int index){
	if(index<=tree->numOfNode){
		printInorder(tree,index*2);
		printf("%d ",tree->element[index]);
		printInorder(tree,index*2+1);
	}
}
void printPostorder(Tree tree, int index){
	if(index<=tree->numOfNode){
		printPostorder(tree,index*2);
		printPostorder(tree,index*2+1);
		printf("%d ",tree->element[index]);
	}
}
void DeleteTree(Tree tree){
	free(tree->element);
	free(tree);
}
void main(int argc, char* argv[]){
	FILE *fi;
	Tree tree;
	int treeSize;
	int tmpNum;

	fi=fopen(argv[1],"r");
	fscanf(fi, "%d\n", &treeSize);
	tree=CreateTree(treeSize);

	while(fscanf(fi, "%d",&tmpNum)==1){
		Insert(tree,tmpNum);
	}
	PrintTree(tree);
	DeleteTree(tree);
}
