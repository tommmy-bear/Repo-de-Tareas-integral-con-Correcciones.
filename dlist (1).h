#ifndef DLIST_H
#define DLIST_H

#include <string>
#include <sstream>

// Declaración adelantada de DList para que DLink pueda ser su amigo
template <class T> class DList;

// Clase que representa un nodo en la lista
template <class T>
class DLink {
private:
    // Constructores privados para que solo DList pueda crear nodos
    DLink(T);
    DLink(T, DLink<T>*, DLink<T>*);

    T value;          // Valor almacenado en el nodo
    DLink<T> *previous; // Puntero al nodo anterior
    DLink<T> *next;     // Puntero al nodo siguiente

    friend class DList<T>; // DList es amigo de DLink
};

// Implementación de los constructores de DLink
template <class T>
DLink<T>::DLink(T val) : value(val), previous(nullptr), next(nullptr) {}

template <class T>
DLink<T>::DLink(T val, DLink *prev, DLink* nxt) : value(val), previous(prev), next(nxt) {}

// Clase que representa la lista doblemente enlazada
template <class T>
class DList {
private:
    DLink<T> *head; // Puntero al primer nodo
    DLink<T> *tail; // Puntero al último nodo
    int size;       // Tamaño de la lista

public:
    DList();                           // Constructor predeterminado
    DList(const DList<T>&);            // Constructor de copia
    ~DList() { clear(); }               // Destructor
    bool empty() const { return (head == 0); }; // Verifica si la lista está vacía
    void clear();                      // Borra todos los elementos de la lista

    void insertion(T);                 // Inserta un elemento al final de la lista
    T search(T);                       // Busca un elemento y devuelve su índice (o -1 si no se encuentra)
    void update(int, T);               // Actualiza un elemento en una posición dada
    void deleteAt(int);                // Elimina un elemento en una posición dada

    std::string toStringForward() const;  // Representación hacia adelante de la lista como cadena
    std::string toStringBackward() const; // Representación hacia atrás de la lista como cadena
};

// Implementación de los métodos de DList

// Constructor predeterminado
template <class T>
DList<T>::DList() : head(nullptr), tail(nullptr) {}

// Constructor de copia
template <class T>
DList<T>::DList(const DList<T> &source) : head(nullptr), tail(nullptr) {
    DLink<T> *p, *q;

    if (source.empty()) {
        size = 0;
        head = 0;
        tail = 0;
    } else {
        p = source.head;
        head = new DLink<T>(p->value);
        q = head;

        p = p->next;
        while (p != 0) {
            q->next = new DLink<T>(p->value, q, 0);
            p = p->next;
            q = q->next;
        }
        size = source.size;
    }
}

// Método para borrar todos los elementos de la lista
template <class T>
void DList<T>::clear() {
    DLink<T> *p, *q;

    p = head;
    while (p != 0) {
        q = p->next;
        delete p;
        p = q;
    }
    head = 0;
    tail = 0;
    size = 0;
}

// Método para insertar un elemento al final de la lista
template <class T>
void DList<T>::insertion(T val) {
    DLink<T> *newLink = new DLink<T>(val);

    if (empty()) {
        head = newLink;
        tail = newLink;
    } else {
        tail->next = newLink;
        newLink->previous = tail;
        tail = newLink;
    }
    size++;
}

// Método para buscar un elemento y devolver su índice (o -1 si no se encuentra)
template <class T>
T DList<T>::search(T val) {
    DLink<T> *current = head;
    int index = 0;

    while (current) {
        if (current->value == val) {
            return index;
        }
        current = current->next;
        index++;
    }
    return -1;
}

// Método para actualizar un elemento en una posición dada
template <class T>
void DList<T>::update(int index, T val) {
    DLink<T> *current = head;
    for (int i = 0; i < index; i++) {
        current = current->next;
    }
    current->value = val;
}

// Método para eliminar un elemento en una posición dada
template <class T>
void DList<T>::deleteAt(int index) {
    int pos;
    DLink<T> *p;
    if (index == 0) {
        p = head;

        if (head == tail) {
            head = nullptr;
            tail = nullptr;
        } else {
            head = p->next;
            p->next->previous = nullptr;
        }
        delete p;
        size--;
        return;
    }
    p = head;
    pos = 0;
    while (pos != index) {
        p = p->next;
        pos++;
    }

    p->previous->next = p->next;
    if (p->next != nullptr) {
        p->next->previous = p->previous;
    }
    size--;
    delete p;
}

// Método para obtener una representación hacia adelante de la lista como cadena
template <class T>
std::string DList<T>::toStringForward() const {
    std::stringstream aux;
    DLink<T> *p;

    p = head;
    aux << "[";
    while (p != 0) {
        aux << p->value;
        if (p->next != 0) {
            aux << ", ";
        }
        p = p->next;
    }
    aux << "]";
    return aux.str();
}

// Método para obtener una representación hacia atrás de la lista como cadena
template <class T>
std::string DList<T>::toStringBackward() const {
    std::stringstream aux;
    DLink<T> *p;

    p = tail;
    aux << "[";
    while (p != 0) {
        aux << p->value;
        if (p->previous != 0) {
            aux << ", ";
        }
        p = p->previous;
    }
    aux << "]";
    return aux.str();
}

#endif
