int main(){
 	
 	//Algoritmo
 	double a[5] = {2, 3, 1, 5, 4}, b[5] = {0, 3, 2, 1, 4};
	int length = 5, index;
	double runningSum = 0;
	
	for (index = 0; index < length; index++){
		runningSum += a[index] * b[index];
	}
	
	//Teste;
	if(runningSum == 32){
		return 1;
	}else{
		return 0;
	}
 }
