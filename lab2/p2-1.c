#include<stdio.h>
#include <stdlib.h>
int main(int argv, char* argc[]){
   int n=atoi(argc[1]);
   char** arr=(char**)malloc(n*sizeof(char*));
   printf("enter %d names:\n",n);
   for(int i=0; i<n; i++){
      arr[i]=(char*)malloc(30*sizeof(char));
      scanf("%s", arr[i]);
   }   
   printf("the names you entered:\n");
   for(int i=0; i<n; i++){
      printf("%s\n",arr[i]);
   }
   for(int i=0; i<n; i++){
      free(arr[i]);
   }
   free(arr);
}
