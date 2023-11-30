#ifndef BST_H
#define BST_H

#include <string>
#include <sstream>

// Declaración previa de las clases para que puedan referenciarse mutuamente
template <class T> class BST;

template <class T>
class TreeNode {
private:
	T value;
	TreeNode *left, *right;

public:
	// Constructores de nodo
	TreeNode(T);
	TreeNode(T, TreeNode<T>*, TreeNode<T>*);

	// Métodos para agregar, buscar, eliminar descendientes, encontrar ancestros
	void add(T);
	bool find(T);
	void removeChilds();
	void ancestors(std::stringstream&, T) const;
	void inorder(std::stringstream&) const;
	void preorder(std::stringstream&) const;
	void postorder(std::stringstream&) const;
	void levelbylevel(std::stringstream&, const TreeNode<T>*, int) const;

	friend class BST<T>;
};

// Implementación de los constructores de nodo
template <class T>
TreeNode<T>::TreeNode(T val) : value(val), left(0), right(0){}

template <class T>
TreeNode<T>::TreeNode(T val, TreeNode<T> *le, TreeNode<T> *ri) : value(val), left(le), right(ri) {}

// Método para agregar un valor al nodo y su subárbol
template <class T>
void TreeNode<T>::add(T val) {
	if (val < value) {
		if (left != 0) {
			left->add(val);
		} else {
			left = new TreeNode<T>(val);
		}
	} else {
		if (right != 0) {
			right->add(val);
		} else {
			right = new TreeNode<T>(val);
		}
	}
}

// Método para buscar un valor en el nodo y su subárbol
template <class T>
bool TreeNode<T>::find(T val) {
	if (val == value) {
		return true; 
	}
	else if (val < value) {
		return (left != 0 && left->find(val)); 
	}
	else if (val > value) {
		return (right != 0 && right->find(val)); 
	}
	return false; 
}

// Método para eliminar todos los descendientes del nodo
template <class T>
void TreeNode<T>::removeChilds() {
	if (left != 0) {
		left->removeChilds();
		delete left;
		left = 0;
	}
	if (right != 0) {
		right->removeChilds();
		delete right;
		right = 0;
	}
}

// Método para encontrar los ancestros de un valor en el nodo y su subárbol
template <class T>
void TreeNode<T>::ancestors(std::stringstream &aux, T val) const {
    if (value != val) {
        if (aux.tellp() != 1) {
            aux << " ";
        }
        aux << value;

        if (val < value && left != nullptr) {
            left->ancestors(aux, val);
        }
        if (val > value && right != nullptr) {
            right->ancestors(aux, val);
        }
    }
}

// Métodos para realizar recorridos en el árbol (inorden, preorden, postorden)
template <class T>
void TreeNode<T>::inorder(std::stringstream &aux) const {
	if (left != 0) {
		left->inorder(aux);
	}
	if (aux.tellp() != 1) {
		aux << " ";
	}
	aux << value;
	if (right != 0) {
		right->inorder(aux);
	}
}

template <class T>
void TreeNode<T>::preorder(std::stringstream &aux) const {
	aux << value;
	if (left != 0) {
		aux << " ";
		left->preorder(aux);
	}
	if (right != 0) {
		aux << " ";
		right->preorder(aux);
	}
}

template <class T>
void TreeNode<T>::postorder(std::stringstream &aux) const {
	if (left != 0) {
		left->postorder(aux);
	}
	if (right != 0) {
		right->postorder(aux);
	}
	if (aux.tellp() != 1) {
		aux << " ";
	}
	aux << value;
}

// Método para recorrer el árbol nivel por nivel
template <class T>
void TreeNode<T>::levelbylevel(std::stringstream &aux, const TreeNode<T>* node, int level) const {
    if (level == 1) {
		if (aux.tellp() != 1) {
			aux << " ";
		}
        aux << node->value;
    } else if (level > 1) {
        if (node->left != nullptr) {
            levelbylevel(aux, node->left, level - 1);
        }
        if (node->right != nullptr) {
            levelbylevel(aux, node->right, level - 1);
        }
    }
}

// Declaración de la clase BST (Árbol de Búsqueda Binaria)
template <class T>
class BST {
private:
	TreeNode<T> *root;

public:
	// Constructores y destructor del árbol
	BST();
	~BST();

	// Métodos para verificar si el árbol está vacío y agregar valores
	bool empty() const;
	void add(T);
	bool find(T) const;
	void removeAll();
	
	// Métodos para recorrer el árbol y obtener representaciones en cadena
	std::string preorder() const;
	std::string inorder() const;
	std::string postorder() const;
	std::string levelbylevelstring() const;
	std::string visit() const;

	// Métodos para obtener la altura del árbol y encontrar ancestros
	int height() const;
	int heightAux(const TreeNode<T>*) const;
	std::string ancestors(T) const;
	int whatlevelamI(T) const;
	int findLevel(TreeNode<T>*, T, int) const;
};

// Implementación de los métodos de la clase BST
template <class T>
BST<T>::BST() : root(0) {}

template <class T>
BST<T>::~BST() {
	removeAll();
}

template <class T>
void BST<T>::removeAll() {
	if (root != 0) {
		root->removeChilds();
	}
	delete root;
	root = 0;
}

template <class T>
bool BST<T>::empty() const {
	return (root == 0);
}

template <class T>
void BST<T>::add(T val) {
	if (root != 0) {
		if (!root->find(val)) {
			root->add(val);
		}
	} else {
		root = new TreeNode<T>(val);
	}
}

template <class T>	
bool BST<T>::find(T val) const {
	if (root != 0) {
		return root->find(val);
	} else {
		return false;
	}
}

template <class T>
std::string BST<T>::preorder() const {
	std::stringstream aux;

	aux << "[";
	if (!empty()) {
		root->preorder(aux);
	}
	aux << "]";
	return aux.str();
}

template <class T>
std::string BST<T>::inorder() const {
	std::stringstream aux;

	aux << "[";
	if (!empty()) {
		root->inorder(aux);
	}
	aux << "]";
	return aux.str();
}

template <class T>
std::string BST<T>::postorder() const {
	std::stringstream aux;

	aux << "[";
	if (!empty()) {
		root->postorder(aux);
	}
	aux << "]";
	return aux.str();
}

template <class T>
std::string BST<T>::levelbylevelstring() const {
	std::stringstream aux;
	int h = height();

	aux << "[";
	if (!empty()) {
    	for (int i = 1; i <= h; i++) {
        	root->levelbylevel(aux, root, i);
    	}
	}
	aux << "]";
	return aux.str();
}

template <class T>
std::string BST<T>::visit() const {
	std::stringstream aux;

	aux << preorder() << "\n";
	aux << inorder() << "\n";
	aux << postorder() << "\n";	
	aux << levelbylevelstring();

	return aux.str();
}

template <class T>
int BST<T>::heightAux(const TreeNode<T>* node) const {
	int lheight = 0, rheight = 0;
    if (node == 0) {
        return 0;
    } else {
        lheight = heightAux(node->left);
        rheight = heightAux(node->right);
        if (lheight > rheight) {
            return(lheight + 1);
        } else {
            return(rheight + 1);
        }
    }
}

template <class T>
int BST<T>::height() const {
    return heightAux(root);
}

template <class T>
std::string BST<T>::ancestors(T val) const {
    std::stringstream aux;
	if (!find(val)) {
		return "[]";
	}
    aux << "[";
    root->ancestors(aux, val);
    aux << "]";
    return aux.str();
}

template <class T>
int BST<T>::whatlevelamI(T val) const {
    return findLevel(root, val, 1); 
}

template <class T>
int BST<T>::findLevel(TreeNode<T>* node, T val, int level) const {
    if (node == nullptr) {
        return -1; 
    }

    if (val == node->value) {
        return level;
    } else if (val < node->value) {
        return findLevel(node->left, val, level + 1); 
    } else {
        return findLevel(node->right, val, level + 1); 
    }
}

#endif
