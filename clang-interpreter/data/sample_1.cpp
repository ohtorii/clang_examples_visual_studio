#include<stdio.h>

int main(int argc, char*argv[]){
	FILE* fp=fopen("out.txt","wt");
	fprintf(fp,"%s\n","hallo clang");
	fprintf(fp,"%s\n","����ɂ���Aclang");
	fclose(fp);
	return 0;
}