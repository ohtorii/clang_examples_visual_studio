#include<stdio.h>

template<class T>
class add{
public:
	add(T v) : m_base(v){
	}
	T operator()(T v)const{
		return v + m_base;
	};
private:
	T	m_base;
};

int main(int argc, char*argv[]){
	add<int>	obj(10);
	printf("value=%d\n", obj(20));
	return 0;
}