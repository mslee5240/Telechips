#include <stdio.h>

double centi_to_meter(int cm) {
	double result;
	result = (double)cm / 100.0;
	return result;
}

int main() {
	double res;
	res = centi_to_meter(187);
	printf("%.2lfm\n", res);

	return 0;
}