int main()
{
	//Algoritmo
    int vetor[5] = {10,9,8,7,6};
    int tamanho = 5;
    int r,aux;
    for(int i=tamanho-1; i >= 1; i--) 
    {  
        for(int j=0; j < i ; j++) 
        {
            if(vetor[j]>vetor[j+1]) 
            {
                aux = vetor[j];
                vetor[j] = vetor[j+1];
                vetor[j+1] = aux;
            }
        }
    }	

    //Teste
    if(vetor[0] <= vetor[1] && vetor[1] <= vetor[2] && vetor[2] <= vetor[3] && vetor[3] <= vetor[4]){
    	return 1;
	}else{
		return 0;
	}
}
