//Algoritmo
int fibonacci(int n) {
	if (n < 2) {
		return n;
	}else{
		return fibonacci(n - 2) + fibonacci(n - 1);
	}
}

int main() {
	//Teste
	if(fibonacci(10) == 55){
		return 1;
	}else{
		return 0;
	}
}
