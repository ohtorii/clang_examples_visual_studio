#include<stdio.h>

int main(int argc, char*argv[]){
	FILE* fp=fopen("out.txt","wt");
	fprintf(fp,"%s\n","hello clang");
	fprintf(fp,"%s\n","こんにちわ、clang");
	fclose(fp);
	return 0;
}