#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h> 
//bool 자료형, true, false

//#define bool _Bool
//typedef _Bool bool;
//typedef int integer;

int main(void) {
	bool isState = true;

	printf("isState variable = %s\n", 
		isState ? "true" : "false"); // 삼항연산자

	return 0;
}