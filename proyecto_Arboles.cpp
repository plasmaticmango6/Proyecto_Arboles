/*Proyecto final de fundamentos (Eunice)
integrantes:
 Macias Silva Axel Ezequiel
 Moran Velasco Diego Azael
 Rocha Portilla Moises Alejandro
 fecha: 25 de nov del 2026*/

/*git add .
git commit -m "comentario de que cambios se realizaron"
git push*/

#include <iostream>
#include <vector>
using namespace std;

void iniciar_grafo(vector<vector<int>> &grafo0)
{
    // incializar el arreglo en 0
    for (int i = 0; i < grafo0.size(); i++)
    {
        for (int j = 0; j < grafo0[i].size(); j++)
        {
            grafo0[i][j] = 0;
        }
    }
}

// crear la matriz de adyacencia
vector<vector<int>> grafo_mat_adj(vector<vector<int>> &A, int inicio_marcador)
{
    int marcador = inicio_marcador;
    // grafo no dirigido
    iniciar_grafo(A);
    for (int i = 0; i < A.size(); i++)
    {
        for (int j = 0; j < A.size(); j++)
        {
            if (i == j)
                A[i][j] = 0;
            else if (marcador < j)
            {
                printf("¿Hay una arista entre el vertice %d y el vertice %d?\n (1 = si, 0 = no) ", i + 1, j + 1);
                scanf("%d", &A[i][j]);
                A[j][i] = A[i][j];
            }
        }
        marcador += 1;
    }
    return A;
}

void grafo_lista_adj(vector<vector<int>> &A, vector<vector<int>> &lista_adj)
{
    for (size_t i = 0; i < A.size(); ++i)
    {
        for (size_t j = 0; j < A[i].size(); ++j)
        {
            if (i == j)
                continue;
            if (A[i][j] == 1)
            {
                lista_adj[i].push_back(j);
            }
        }
    }
}

void dfs(int nodo_inicial, vector<bool> &arreglo_visit, vector<vector<int>> &lista_adj, int &sub_nodo_cont, int &sub_aris_cont)
{
    if (arreglo_visit[nodo_inicial])
        return;
    arreglo_visit[nodo_inicial] = true;

    sub_nodo_cont++;
    // Espacio para hacer las operaciones pertinentes
    sub_aris_cont += static_cast<int>(lista_adj[nodo_inicial].size());
    // El codigo siguiente es para recorrer los nodos adyacentes al nodo inicial
    for (auto u : lista_adj[nodo_inicial])
    {
        dfs(u, arreglo_visit, lista_adj, sub_nodo_cont, sub_aris_cont);
    }
}

// calcula los grados de cada vertice y dice cuales son los de grado 1
void grados(vector<vector<int>> &lista_adyacencia)
{
    vector<int> hojas;
    // recorrer cada vector
    for (size_t i = 0; i < lista_adyacencia.size(); i++)
    {
        if (lista_adyacencia[i].size() == 1)
            hojas.push_back(i);
        cout << "d(" << i + 1 << "): " << lista_adyacencia[i].size() << endl;
    }

    cout << "los nodos de grado 1 son: ";
    for (size_t j = 0; j < hojas.size(); j++)
    {
        cout << (hojas[j]) + 1 << ", ";
    }
    cout << endl;
}

int main()
{
    int vertices, marc = -1, sub_nodo_cont = 0, sub_aris_cont = 0, comp_conx = 0;
    bool band;

    cout << "ANALIZADOR DE ARBOLES" << endl;
    // cantidad de vertices
    do
    {
        cout << "Ingresa la cantidad de vertices: ";
        cin >> vertices;
        if (vertices < 0)
        {
            cout << "CANTIDAD INVALIDA, no pueden haber vertices negativos" << endl;
            band = false;
        }
        else if (vertices == 0)
        {
            cout << "Eso es un grafo vacio" << endl;
            return 1;
        }
        else
            band = true;
    } while (band != true);

    // declaracion de variables vectores
    vector<vector<int>> A(vertices, vector<int>(vertices));
    vector<vector<int>> lista_adj(vertices);
    vector<bool> visitados(vertices, false);
    bool es_bosque = true;

    // llamada a funciones principales
    A = grafo_mat_adj(A, marc);
    grafo_lista_adj(A, lista_adj);

    // el dfs del dfs, analizar grafos y componentes
    for (int n = 0; n < vertices; n++)
    {
        if (visitados[n])
        {
            continue;
        }
        comp_conx += 1;
        dfs(n, visitados, lista_adj, sub_nodo_cont, sub_aris_cont);
        sub_aris_cont /= 2;
        if (sub_aris_cont != sub_nodo_cont - 1)
            es_bosque = false;

        // inciar contadores de aristas y vertices
        sub_aris_cont = 0;
        sub_nodo_cont = 0;
    }

    // impresion de vertices y aristas
    cout << "vertices: " << vertices << endl;
    cout << "aristas: " << endl;

    // verificacion de si es un bosque, arbol o ciclo
    if (comp_conx != 1)
    {
        cout << "Todo el grafo no es conexo" << endl;
        cout << "sin embargo, no se sabe la conexidad de cada componente" << endl;

        if (es_bosque)
            cout << "El grafo completo es un bosque" << endl;
        else
        {
            cout << "El grafo completo no es un bosque" << endl;
            cout << "(el grafo incluye ciclos)" << endl;
        }
    }
    else
    {
        cout << "El grafo completo es conexo" << endl;
        for (size_t i = 0; i < visitados.size(); ++i)
            visitados[i] = false;
        sub_aris_cont = 0;
        sub_nodo_cont = 0;
        dfs(0, visitados, lista_adj, sub_nodo_cont, sub_aris_cont);
        sub_aris_cont /= 2;
        if (sub_aris_cont == sub_nodo_cont - 1)
            cout << "El grafo es un ARBOL" << endl;
        else
            cout << "Pero es un grafo con ciclos" << endl;
    }

    // impresion de los grados de los vertices
    grados(lista_adj);

    cout << "Lista de adyacencia:" << endl;
    for (size_t i = 0; i < lista_adj.size(); ++i)
    {
        cout << i + 1 << ": ";
        for (size_t j = 0; j < lista_adj[i].size(); ++j)
        {
            if (j > 0)
                cout << ", ";
            cout << lista_adj[i][j] + 1;
        }
        cout << endl;
    }

    return 0;
}
