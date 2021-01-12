//Algoritmo
int max(int a, int b){
	if(a >= b){
		return a;
	}else{
		return b;
	}
}

int main(){
	int x = 2, y = 5;
	
	//Teste
	if(max(x,y) == 5){
		return 1;
	}else{
		return 0;
	}
}
