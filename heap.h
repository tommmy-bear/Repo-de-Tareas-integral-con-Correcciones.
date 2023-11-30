#ifndef HEAP_H_
#define HEAP_H_

#include <string>
#include <sstream>
#include <iostream>

template <class T>
class Heap {
private:
	T *data;
	unsigned int heapsize;
	unsigned int count;

	unsigned int parent(unsigned int) const;
	unsigned int left(unsigned int) const;
	unsigned int right(unsigned int) const;
	void heapify(unsigned int);
	void swap(unsigned int, unsigned int);

public:
	Heap(unsigned int) ;
	~Heap();
	bool empty() const;
	bool full() const;
	void push(T) ;
	T pop();
	void clear();
	std::string toString() const;
	unsigned int size(); 
	T top();
};

template <class T>
Heap<T>::Heap(unsigned int sze) {
	heapsize = sze + 1;
	data = new T [heapsize]; 
	if (data == 0){
		std::cerr << "OutOfMemory()" << std::endl;
	}
	count = 1; 
}

template <class T>
Heap<T>::~Heap() {
	delete [] data; 
	data = 0; 
	heapsize = 0; 
	count = 0; 
}

template <class T>
bool Heap<T>::empty() const {
	return (count == 1);
}

template <class T>
bool Heap<T>::full() const {
	return (count == heapsize);
}

template <class T>
unsigned int Heap<T>::parent(unsigned int pos) const {
	return pos / 2;
}

template <class T>
unsigned int Heap<T>::left(unsigned int pos) const {
	return 2 * pos;
}

template <class T>
unsigned int Heap<T>::right(unsigned int pos) const {
	return 2 * pos + 1;
}

template <class T>
void Heap<T>::swap(unsigned int i, unsigned int j) {
	T aux = data[i];
	data[i] = data[j];
	data[j] = aux;
}

template <class T>
void Heap<T>::heapify(unsigned int pos) {
	unsigned int le = left (pos);
	unsigned int ri = right (pos);
	unsigned int min = pos;
	if(le <= count && data[le] < data[min]){
		min = le; 
	}
	if (ri <= count && data[ri] < data[min]){
		min = ri;
	}
	if (min != pos){
		swap(pos, min); 
		heapify(min);
	}
}

template <class T>
void Heap<T>::push(T val)  {
	unsigned int pos; 

	if (full()){
		std::cerr << "Overflow()" << std::endl;
	}

	pos = count; 
	count++; 

	while (pos > 0 && val < data[parent(pos)]){
		data[pos] = data[parent(pos)]; 
		pos = parent (pos); 
	}

	if(pos == 0){
		data[1]	= val;
	}
	
	data[pos] = val;
}

template <class T>
T Heap<T>::pop()  {
	if(empty()){
		std::cerr << "NoSuchElement()" << std::endl;
	}
	T aux = data[1];

	data[1] = data[--count];
	heapify(1); 
	return aux; 
}

template <class T>
void Heap<T>::clear() {
	count = 1;
}


template <class T>
std::string Heap<T>::toString() const {
	std::stringstream aux;

	aux << "[";
	for (unsigned int i = 1; i < count; i++) {
		if (i != 1) {
			aux << " ";
		}
		aux << data[i];
	}
	aux << "]";
	return aux.str();
}

template <class T>
unsigned int Heap <T> :: size(){
	unsigned int count2 = count-1;
	return count2;
}

template <class T>
T Heap <T> :: top(){
	T aux = data[1];
	return aux;
}

#endif /* HASH_H_ */