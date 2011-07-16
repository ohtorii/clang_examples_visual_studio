#include<stdio.h>

#define RETTYPE	int
#define VAL_1	1
#define VAL_2	(VAL_1+1)
#define VAL_3	(VAL_2+1)

template<class T>
T add(T l, T r){
	return l+r;
}

RETTYPE main(int argc, char*argv[]){
	int a=VAL_1;
	int b=VAL_2;
	int c=add(a,b);
	printf("%d\n",c);
	return 0;
}