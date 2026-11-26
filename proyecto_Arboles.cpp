/*Proyecto final de fundamentos (Eunice)
integrantes:
 Macias Silva Axel Ezequiel
 Moran Velasco Diego Azael
 Rocha Portilla Moises Alejandro
 fecha: 25 de nov del 2026*/

/*git add .
git commit -m "comentario de que cambios se relaizaron"
git push*/

#include <iostream>
#include <vector>
using namespace std;

const int N = 1e5 + 5;
vector<int> lista_adj[N];
bool visitados[N];

void inicializar_grafo(int V){
    int total_adj, nodo_conectado;
    for(int i=0; i<V; i++){
        cout << "¿Con cuantos nodos está conectado el nodo " << i+1 << "?: ";
        cin >> total_adj;
        for(int j=0; j<total_adj; j++){
            cout << "Ingrese los nodos conectados al nodo " << i+1 << ": ";
            cin >> nodo_conectado;
            lista_adj[i].push_back(nodo_conectado-1);
        }
        
    }
}

void dfs(int nodo_inicial) {
    if(visitados[nodo_inicial]) return;
    visitados[nodo_inicial] = true;

    //Espacio para hacer las operaciones pertinentes

    // El codigo siguiente es para recorrer los nodos adyacentes al nodo inicial
    for(auto u : lista_adj[nodo_inicial]){
        dfs(u);
    }
    
}

int main() {
    int vertices;

    cout << "Ingrese el numero de vertices que tiene el grafo: ";
    cin >> vertices;
    inicializar_grafo(vertices);
    return 0;
}