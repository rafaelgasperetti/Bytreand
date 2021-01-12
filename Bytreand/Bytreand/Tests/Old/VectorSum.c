int main(){
	
	//Algoritmo
	int a[3] = {3, 4, 1}, b[3] = {5, 2, 7}, c[3], tamanho = 3, i;
	
	for(i = 0; i < tamanho; i++){
		c[i] = a[i] + b[i];
	}
	
	//Teste
	if(c[0] == 8 && c[1] == 6 && c[2] == 8){
		return 1;
	}else{
		return 0;
	}
}
