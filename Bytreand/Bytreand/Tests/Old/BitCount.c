unsigned int bitCount (unsigned int value) {
    unsigned int count = 0;
    while (value > 0) {           // until all bits are zero
        if ((value & 1) == 1)     // check lower bit
            count++;
        value >>= 1;              // shift bits, removing lower bit
    }
    return count;
}

int main(){
	
	//Teste
	if(bitCount(9) == 2){
		return 1;
	}else{
		return 0;
	}
}
