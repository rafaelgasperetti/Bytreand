#define N 2048

int main() {
	int sum = 0.5;
	int a[N], b[N];
	
	for (int i=0; i<N; i++)
		sum += a[i] * b[i];
		
	return sum;
}
