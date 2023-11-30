#ifndef Graph_H_
#define Graph_H_

#include <string>
#include <stdio.h>
#include <sstream>
#include <fstream>
#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <list>
#include <algorithm>

using namespace std;

class Graph {
private:
    int edgesList;
    int edgesMat;
    int nodes;
    vector<int> *adjList;
    int *adjMatrix;

public:

    void loadGraphList(string, int);
    void loadGraphMat(string, int, int);
    Graph(int);
    Graph();
    void addEdgeAdjList(int, int);
    void addEdgeAdjMatrix(int, int);
    string printAdjList();
    string printAdjMat();
    string printAdjMat_clean();
    string DFS(int, int);
    string depthHelper(int, int, stack<int>&, list<int>&, vector<vector<int>>&);
    string BFS(int, int);
    string breadthHelper(int, int, queue<int>&, list<int>&, vector<vector<int>>&);
    string print_visited(list<int>);
    string print_path(vector<vector<int>>&,int ,int);
    bool contains(list<int>, int);
    void sortAdjList();
};

Graph::Graph() {
    // Inicializa los miembros de la clase según sea necesario.
    edgesList = 0;
    edgesMat = 0;
    nodes = 0;
    adjList = nullptr;
    adjMatrix = nullptr;
}

// Constructor con un parámetro para el número de nodos
Graph::Graph(int n) {
    // Inicializa los miembros de la clase según sea necesario y crea las estructuras de datos.
    nodes = n;
    edgesList = 0;
    edgesMat = 0;
    adjList = new vector<int>[n];
    adjMatrix = new int[n * n]();
}

//lIST STUFF

void Graph::loadGraphList(string data, int numVertices) {
    // Inicializa las listas de adyacencia
    nodes = numVertices;
    adjList = new vector<int>[nodes];
    
    // Usa stringstream para dividir la cadena en aristas
    stringstream ss(data);
    char openParenthesis, comma, closeParenthesis;
    int u, v;

    while (ss >> openParenthesis >> u >> comma >> v >> closeParenthesis) {
        // Agrega la arista a la lista de adyacencia
        adjList[u].push_back(v);
        adjList[v].push_back(u); // Si es un grafo no dirigido
        edgesList++;
    }
}

void Graph::addEdgeAdjList(int u, int v) {
    if (u >= 0 && u < nodes && v >= 0 && v < nodes) {
        // Agregar v a la lista de adyacencia de u
        adjList[u].push_back(v);

        // Si el grafo es no dirigido, agrega u a la lista de adyacencia de v
        adjList[v].push_back(u);

        edgesList++;
    }
}

string Graph::printAdjList() {
    string result;

    for (int i = 0; i < nodes; i++) {
        result += "vertex " + to_string(i) + " : ";

        // Ordena la lista de adyacencia para imprimir los vecinos en orden ascendente
        sort(adjList[i].begin(), adjList[i].end());

        for (int j = 0; j < adjList[i].size(); j++) {
            result += to_string(adjList[i][j]) + " ";
        }

  
    }

    return result;
}

//Matrix sTUFF

void Graph::loadGraphMat(string data, int a, int b) {
    nodes = a; // Establece el número de nodos
    adjMatrix = new int[a * a](); // Inicializa la matriz de adyacencia con ceros

    // Analiza la cadena 'data' para agregar las aristas a la matriz de adyacencia
    stringstream ss(data);
    char openParenthesis, comma, closeParenthesis;
    int u, v;

    while (ss >> openParenthesis >> u >> comma >> v >> closeParenthesis) {
        // Agrega la arista a la matriz de adyacencia
        adjMatrix[u * a + v] = 1;
        adjMatrix[v * a + u] = 1; // Si es un grafo no dirigido
        edgesMat++;
    }
}


void Graph::addEdgeAdjMatrix(int u, int v) {
    if (u >= 0 && u < nodes && v >= 0 && v < nodes) {
        // Marca la casilla correspondiente en la matriz de adyacencia para indicar la arista
        adjMatrix[u * nodes + v] = 1;
        adjMatrix[v * nodes + u] = 1; // Si es un grafo no dirigido
        edgesMat++;
    }
}


// Función para imprimir la matriz de adyacencia
string Graph::printAdjMat() {
    string result;
    
    for (int i = 0; i < nodes; i++) {
        for (int j = 0; j < nodes; j++) {
            result += to_string(adjMatrix[i * nodes + j]) + " ";
        }
        
    }
    
    return result;
}


std::string Graph::DFS(int start, int end) {
    stack<int> s;
    list<int> visited;
    vector<vector<int>> path(nodes, vector<int>(1, -1));

    s.push(start);
    string ans = depthHelper(start, end, s, visited, path);
    ans = ans + print_path(path, start, end);
    return ans;
}

std::string Graph::depthHelper(int current, int end, std::stack<int>& s, std::list<int>& visited, std::vector<std::vector<int>>& path) {
   if (current == end){
        return print_visited(visited);
   } else if (s.empty()){
        return "node not found";
   } else {
        current = s.top();
        s.pop();
        visited.push_back(current);
        for (int i = 0; i < adjList[current].size(); i++)
           if (!contains(visited, adjList[current][i])){
                s.push(adjList[current][i]);
                path[adjList[current][i]][0] = current;
           }
        return depthHelper(current, end, s, visited, path);
   }
}



std::string Graph::BFS(int start, int end) {
    queue<int> qu;
    list<int> visited;
    vector<vector<int>> path(nodes, vector<int>(1, -1));

    qu.push(start);
    string ans = breadthHelper(start, end, qu, visited, path);
    ans = ans + print_path(path, start, end);
    return ans;
}

string Graph::breadthHelper(int current, int goal, queue<int> &qu, list<int> &visited, vector<vector<int>> &path){
        if(current == goal){
            return print_visited(visited);
        } else if (qu.empty()){
            return "node not found";
        }else{
            current = qu.front();
            qu.pop();
            visited.push_back(current);
            
            for (int i = 0; i < adjList[current].size(); i++){
                if (!contains(visited, adjList[current][i])){    
                    qu.push(adjList[current][i]);    
                    if (path[adjList[current][i]][0] == -1){
                        path[adjList[current][i]][0] = current;
                    }
                }
            }
            return breadthHelper(current, goal, qu, visited, path);
   }
}

bool Graph::contains(list<int> ls, int node){
		list<int>::iterator it;
		it = find(ls.begin(), ls.end(), node);
		if(it != ls.end())
			return true;
		else
			return false;
}

string Graph::print_visited(list<int> q){
	stringstream aux;
	aux << "visited: ";
	while (!q.empty()){
    aux << q.front() << " ";
    q.pop_front();
  }
	return aux.str();
}

string Graph::print_path(vector<vector <int>> &path, int start, int goal){
	int node =  path[goal][0];
	stack<int> reverse;
	reverse.push(goal);
	stringstream aux;
	aux  << "path:";
	while (node != start) {
		reverse.push(node);
    node = path[node][0];
}
	reverse.push(start);
	while (!reverse.empty()) {
		aux << " " << reverse.top() ;
		reverse.pop();
}
	return aux.str();
}


#endif /* Graph_H_ */