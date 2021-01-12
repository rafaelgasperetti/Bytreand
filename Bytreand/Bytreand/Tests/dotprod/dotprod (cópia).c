//#define N 2048

int main() {
	int n = 2048, o, p = 3;
	int a[n], b[n];
	int sum = 0;
	for (int i=0; i<n; i++)
		sum += a[i] * b[i];

	return sum;
}
