//#include <stdio.h>
//
//int main(void) {
//	char ch;
//	int in;
//	double db;
//
//	char* pch = &ch;
//	int* pin = &in;
//	double* pdb = &db;
//
//	printf("char형 변수의 주소 크기: %d\n", sizeof(&ch));
//	printf("int형 변수의 주소 크기: %d\n", sizeof(&ch));
//	printf("double형 변수의 주소 크기: %d\n\n", sizeof(&ch));
//
//	printf("char 포인터 변수의 크기: %d\n", sizeof(pch));
//	printf("int 포인터 변수의 크기: %d\n", sizeof(pin));
//	printf("double 포인터 변수의 크기: %d\n\n", sizeof(pdb));
//
//	printf("char 포인터가 가르키는 변수의 크기: %d\n", sizeof(*pch));
//	printf("int 포인터가 가르키는 포인터 변수의 크기: %d\n", sizeof(*pin));
//	printf("double 포인터가 가르키는 포인터 변수의 크기: %d\n\n", sizeof(*pdb));
//
//	return 0;
//}