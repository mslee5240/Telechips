//// �����佺�׳׽��� ü Ȱ��, �����ٱ����� ��� Ȱ��
//
//#include <stdio.h>
//#include <math.h>
//
//int is_prime(int n) {
//	if (n < 2) {
//		return 0;	// 0, 1�� �Ҽ��� �ƴ�
//	}
//	if (n == 2 || n == 3) {
//		return 1;	// 2�� 3�� �Ҽ�
//	}
//	if (n % 2 == 0 || n % 3 == 0) {
//		return 0;	// 2 �Ǵ� 3�� ����� �Ҽ��� �ƴ�
//	}
//
//	for (int i = 5; i * i <= n; i += 6) {	// 6k +- 1 ���� ���
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