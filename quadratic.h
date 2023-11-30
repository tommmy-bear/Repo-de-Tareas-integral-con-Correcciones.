#ifndef QUADRATIC_H_
#define QUADRATIC_H_

#include <iostream>
#include <string>
#include <sstream>

// Definición de la plantilla de clase para una tabla hash con exploración cuadrática.
template <class Key, class Value>
class Quadratic {
private:
    // Estructura interna para almacenar las claves, valores y un indicador de ocupación.
    struct Node {
        Key key;
        Value value;
        bool filled;

        Node() : filled(false) {} // Constructor que inicializa 'filled' como falso.
    };

    Node* table; // Puntero al arreglo de nodos (tabla hash).
    unsigned int size; // Tamaño de la tabla hash.
    Key initialValue; // Valor inicial para la clave.

    unsigned int (*hashFunction)(const Key); // Puntero a la función de hash.

public:
    // Constructor: inicializa la tabla hash y la función de hash.
    Quadratic(unsigned int tableSize, Key initial, unsigned int (*func)(const Key))
        : size(tableSize), initialValue(initial), hashFunction(func) {
        table = new Node[size]; // Asignación dinámica de memoria para la tabla.
    }

    // Destructor: libera la memoria asignada a la tabla.
    ~Quadratic() {
        delete[] table;
    }

    // Función para insertar un par clave-valor en la tabla hash.
    void put(const Key& key, const Value& value) {
        unsigned int index = hashFunction(key) % size; // Calcula el índice inicial.
        unsigned int originalIndex = index;
        int i = 1;

        // Bucle para encontrar una posición libre usando exploración cuadrática.
        while (table[index].filled) {
            index = (originalIndex + i * i) % size; // Cálculo del nuevo índice.
            i++;
        }

        // Almacenamiento del par clave-valor en la posición encontrada.
        table[index].key = key;
        table[index].value = value;
        table[index].filled = true;
    }

    // Función para obtener el valor asociado a una clave.
    Value get(const Key& key) {
        unsigned int index = hashFunction(key) % size; // Calcula el índice inicial.
        unsigned int originalIndex = index;
        int i = 1;

        // Bucle para buscar la clave en la tabla.
        while (table[index].filled) {
            if (table[index].key == key) {
                return table[index].value; // Retorna el valor si la clave coincide.
            }
            index = (originalIndex + i * i) % size; // Cálculo del nuevo índice.
            i++;
        }

        throw std::runtime_error("Key not found"); // Lanza excepción si no se encuentra la clave.
    }

    // Función para convertir la tabla hash a un string (para propósitos de depuración).
    std::string toString() const {
        std::stringstream aux;
        for (int i = 0; i < size; i++) {
            if (table[i].filled) {
                aux << "(" << i << " " << table[i].key << " : " << table[i].value << ") ";
            }
        }
        return aux.str();
    }
};

#endif /* QUADRATIC_H_ */
