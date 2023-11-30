#ifndef SORTS_H_
#define SORTS_H_
#include <vector>
#include <list>

template <class T>
class Sorts {
private:
	void swap(std::vector<T>&, int, int);
	void copyArray(std::vector<T>&, std::vector<T>&, int, int);
	void mergeArray(std::vector<T>&, std::vector<T>&, int, int, int);
	void mergeSplit(std::vector<T>&, std::vector<T>&, int, int);
    int  bs_aux(std::vector<T> &v, int min, int max, int val);
public:
	void ordenaBurbuja(std::vector<T>&);
	void ordenaSeleccion(std::vector<T>&);
	void ordenaMerge(std::vector<T>&);
    T busqSecuencial(const std::vector<T>&, int valor);
    T busqBinaria(const std::vector<T>&, int valor);
};

template <class T>
void Sorts<T>::swap(std::vector<T> &v, int i, int j) {
	T aux = v[i];
	v[i] = v[j];
	v[j] = aux;
}

template <class T>
void Sorts <T>::ordenaBurbuja(std::vector<T> &source) {
	//std::vector<T> v(source);

	for (int i = source.size() - 1; i > 0; i--) {
		for (int j = 0; j < i; j++) {
			if (source[j] > source[j + 1]) {
				swap(source, j, j + 1);
	
		}
	}
}
}

template <class T>
void Sorts<T>::ordenaSeleccion(std::vector<T> &source) {
	//std::vector<T> v(source);

	int pos;

	// Recorre todo el arreglo
	for (int i = source.size() - 1; i > 0; i--) {
		pos = 0; // Variable para checar el índice 
		// Se encarga de comparar valores 
		for (int j = 1; j <= i; j++) {
			if (source[j] > source[pos]) {
				// Sobreescribir la variable 
				pos = j;
			}
		}

		// Hace el swaping pero una vez teniendo una cmsbio previo
		if (pos != i) {
			swap(source, i, pos);
		}
	}
}

template <class T>
void Sorts<T>::copyArray(std::vector<T> &A, std::vector<T> &B, int low, int high) {
	for (int i = low; i <= high; i++) {
		A[i] = B[i];
	}
}

template <class T>
void Sorts<T>::mergeArray(std::vector<T> &A, std::vector<T> &B, int low, int mid, int high) {
	int i, j, k;

	i = low;
	j = mid + 1;
	k = low;

	while (i <= mid &&j <= high) {
		if (A[i] < A[j]) {
			B[k] = A[i];
			i++;
		} else {
			B[k] = A[j];
			j++;
		}
		k++;
	}
	if (i > mid) {
		for (; j <= high; j++) {
			B[k++] = A[j];
		}
	} else {
		for (; i <= mid; i++) {
			B[k++] = A[i];
		}
	}
}

template <class T>
void Sorts<T>::mergeSplit(std::vector<T> &A, std::vector<T> &B, int low, int high) {
	int mid;

	if ( (high - low) < 1 ) {
		return;
	}
	mid = (high + low) / 2;
	mergeSplit(A, B, low, mid);
	mergeSplit(A, B, mid + 1, high);
	mergeArray(A, B, low, mid, high);
	copyArray(A, B, low, high);
}

template <class T>
void Sorts<T>::ordenaMerge(std::vector<T> &source) {
	 //std::vector<T> v(source);
	 std::vector<T> tmp(source.size());

	mergeSplit(source, tmp, 0, source.size() - 1);
}

template <class T>
T Sorts<T>:: busqSecuencial(const std::vector<T>&source, int valor){
    int mid;
	int low = 0;
	int high = source.size()-1;

	while (low < high) {
		mid = (high + low) / 2;
		if (valor == source[mid]) {
			return mid;
		} else if (valor < source[mid]) {
			high = mid - 1;
		} else if (valor > source[mid]) {
			low = mid + 1;
		}
    }
    if (source[low]==valor){return low;}
	else return -1;
}

template <class T>
int Sorts<T>:: bs_aux(std::vector<T> &v, int min, int max, int valor) {
	int mid;
	if (min <= max) {
		mid = (min + max) / 2;
		if (valor == v[mid]) {
			return mid;
		} else if (valor < v[mid]) {
			return bs_aux(v, min, mid - 1, valor);
		} else if (valor > v[mid]) {
			return bs_aux(v, mid + 1, max, valor);
		}
	}
	if (v[min]==valor){return min;}
	else return -1;
}

template <class T>
T Sorts<T>::busqBinaria(const std::vector<T> &source, int valor) {
	std::vector<T> v(source);
	return bs_aux(v, 0, v.size() - 1, valor);
}



#endif /* SORTS_H_ */