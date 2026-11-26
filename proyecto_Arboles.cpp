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

void grafo_lista_adj(vector<vector<int>> &A, vector<int> lista_adj[])
{
    int marcador = -1;
    for (size_t i = 0; i < A.size(); ++i)
    {
        for (size_t j = 0; j < A[i].size(); ++j)
        {
            if (i == j)
                break;
            if (A[i][j] == 1)
            {
                lista_adj[i].push_back(j);
            }
        }
    }
}

void dfs(int nodo_inicial)
{
    if (visitados[nodo_inicial])
        return;
    visitados[nodo_inicial] = true;

    // Espacio para hacer las operaciones pertinentes

    // El codigo siguiente es para recorrer los nodos adyacentes al nodo inicial
    for (auto u : lista_adj[nodo_inicial])
    {
        dfs(u);
    }
}

int main()
{
    int vertices, marc = -1;
    bool band;

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

    vector<vector<int>> A(vertices, vector<int>(vertices));
    vector<int> lista_adj[vertices];
    bool visitados[vertices];
    A = grafo_mat_adj(A, marc);
    grafo_lista_adj(A, lista_adj);
    return 0;
}
