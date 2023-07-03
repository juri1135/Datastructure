#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct student{
	char *name;
	int student_id;
	char *major;
}student;
int main(int argc, char** args){
	char *input_path, *output_path;
	FILE *fi, *fo;
	int num;
	int i;
	student* students;
	input_path=args[1];
	output_path=args[2];
	fi=fopen(input_path,"r");
	if(fi==NULL){
		return 0;
	}
        fscanf(fi,"%d\n", &num);	
	students=(student*)malloc(num*sizeof(student));
	for(i=0; i<num; i++){
		students[i].name=(char*)malloc(30*sizeof(char));
		students[i].major=(char*)malloc(30*sizeof(char));
		fscanf(fi,"%s %d %s\n",students[i].name,&students[i].student_id,students[i].major);
	}
	fo=fopen(output_path, "w");
	if(fo==NULL){
		return 0;
	}
	for(i=0; i<num; i++){
		fprintf(fo,"%s %d %s\n",students[i].name,students[i].student_id,students[i].major);
		free(students[i].name);
		free(students[i].major);
	}
	free(students);
	fclose(fi);
	fclose(fo);

}
