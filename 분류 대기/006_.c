#include <stdio.h>

double average(double a, double b) {
	double temp = 0;
	temp = (a + b) / 2.0;
	printf("%lf", temp);
}

int main() {
	double res = 0;

	res = average(1.5, 3.4);

	return 0;
}