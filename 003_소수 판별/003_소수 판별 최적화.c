//// 에라토스테네스의 체 활용, 제곱근까지만 계산 활용
//
//#include <stdio.h>
//#include <math.h>
//
//int is_prime(int n) {
//	if (n < 2) {
//		return 0;	// 0, 1은 소수가 아님
//	}
//	if (n == 2 || n == 3) {
//		return 1;	// 2와 3은 소수
//	}
//	if (n % 2 == 0 || n % 3 == 0) {
//		return 0;	// 2 또는 3의 배수는 소수가 아님
//	}
//
//	for (int i = 5; i * i <= n; i += 6) {	// 6k +- 1 패턴 사용
//		if (n % i == 0 || n % (i + 2) == 0) {
//			return 0;
//		}
//	}
//	return 1;
//}
//
//int main() {
//	int nInput = 0;
//	scanf_s("%d", &nInput);
//
//	for (int i = 0; i < nInput; i++) {
//		if (is_prime(i)) {
//			printf("%5d", i);
//		}
//	}
//	
//	return 0;
//}