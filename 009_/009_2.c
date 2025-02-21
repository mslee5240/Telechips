//#include <stdio.h>
//
//void fruit(int cnt) {
//	printf("Apple\n");
//	if (cnt == 3) {
//		return 0;
//	}
//	fruit(cnt + 1);
//	printf("Jam\n");
//}
//
//int main(void) {
//	fruit(1);
//
//	return 0;
//}
//
//// jam이 두 번 출력되는 이유: 재귀호출 함수의 경우 최초 호출한 곳이 아니라 이전에 호출했던 곳으로 돌아가기 때문.