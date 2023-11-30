
#include <iostream>

class Funciones{
	public:
	long sumaIterativa(int n) {
	int sum = 0; 

	for(int i = 0; i <= n; i++){
		sum += i;
	}

	return sum;
}


long sumaRecursiva(int n) {
	if(n == 0)
		return 0; 
	return n + sumaRecursiva(n-1);
}

long sumaDirecta(int n) { 
	// Gauss :)
	return n*(n+1) / 2;
}
};

