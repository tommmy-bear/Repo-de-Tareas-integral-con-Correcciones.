#ifndef LIST_H
#define LIST_H

#include <iostream>
#include <sstream>

// Definición de la clase Link, que representa un nodo en la lista enlazada.
template <class T>
class Link {
public:
    T value;          // El valor almacenado en el nodo.
    Link<T>* next;    // Puntero al siguiente nodo en la lista.

    // Constructor para inicializar un nodo con un valor dado.
    Link(T val) : value(val), next(nullptr) {}
};

// Definición de la clase List, que representa una lista enlazada.
template <class T>
class List {
private:
    Link<T>* head;    // Puntero al primer nodo de la lista.

public:
    // Constructor para inicializar una lista vacía.
    List() : head(nullptr) {}

    // Método para insertar un elemento al final de la lista.
    void insertion(T val) {
        Link<T>* newVal = new Link<T>(val);  // Crear un nuevo nodo con el valor dado.

        if (head == nullptr) {
            head = newVal;  // Si la lista está vacía, el nuevo nodo se convierte en el primer nodo.
        } else {
            Link<T>* current = head;
            while (current->next != nullptr) {
                current = current->next;
            }
            current->next = newVal;  // Agregar el nuevo nodo al final de la lista.
        }
    }

    // Método para buscar un elemento y devolver su índice.
    int search(T val) {
        Link<T>* current = head;
        int index = 0;
        while (current) {
            if (current->value == val) {
                return index;  // Devolver el índice si se encuentra el valor.
            }
            current = current->next;
            index++;
        }
        return -1;  // Devolver -1 si el elemento no se encuentra en la lista.
    }

    // Método para actualizar el valor de un elemento en un índice dado.
    void update(int index, T val) {
        Link<T>* current = head;
        int currentIndex = 0;
        while (current) {
            if (currentIndex == index) {
                current->value = val;  // Actualizar el valor si se encuentra el índice.
                return;
            }
            current = current->next;
            currentIndex++;
        }
    }

    // Método para eliminar un elemento en un índice dado.
    void deleteAt(int index) {
        if (index == 0) {
            Link<T>* temp = head;
            head = head->next;
            delete temp;  // Eliminar el primer nodo si el índice es 0.
        } else {
            Link<T>* current = head;
            int currentIndex = 0;
            while (current) {
                if (currentIndex == index - 1) {
                    Link<T>* temp = current->next;
                    current->next = temp->next;
                    delete temp;  // Eliminar el nodo en el índice dado.
                    return;
                }
                current = current->next;
                currentIndex++;
            }
        }
    }

    // Método para convertir la lista en una cadena de caracteres.
    std::string toString() const {
        std::stringstream aux;
        Link<T>* p = head;
        aux << "[";
        while (p != nullptr) {
            aux << p->value;
            if (p->next != nullptr) {
                aux << ", ";
            }
            p = p->next;
        }
        aux << "]";
        return aux.str();
    }
};

#endif /* LIST_H */
