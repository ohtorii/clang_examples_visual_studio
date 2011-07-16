#include<stdio.h>

class foo{
public:
	foo(){
		printf("ctor\n");
	}
	~foo(){
		printf("dtor\n");
	}
};

foo g;	//  <------- Global ctor/dtor.

int main(int argc, char*argv[]){
	printf("Enter main.\n");
	return 0;
}
