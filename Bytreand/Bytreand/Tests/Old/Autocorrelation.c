int main(){
	//Algoritmo
	int x[5] = {5, 3, 2, 4, 1};

	int vet[5];
    int i,j, n = 5, sum, sumTotal = 0;

    for (i=0;i<n;i++) {
        sum=0;
        for (j=0;j<n-i;j++) {
            sum+=x[j]*x[j+i];
        }
        vet[i]=sum;
        sumTotal+=sum;
    }

	return vet[sumTotal%5];//55
}

