/**
 * Santiago Vázquez - A01177850
 * Adrian Gomez - A00835254
 * Saul Ortega Figueroa - A01252717 
 * v1
 * 
 * Fecha de creación: 11/11/2023
 * Fecha de modificación: 11/11/2023
 * 
 * Descripción: 
 * Programa para la propagación en un grafo utilizando una lista de adyacencia.
 *
 * Este programa tiene como objetivo crear un grafo no dirigido a partir de una cantidad especificada
 * de nodos y aristas. Luego, realiza una propagación desde un nodo de inicio hasta un tiempo específico
 * utilizando una estructura de cola para explorar los nodos alcanzables dentro del límite de tiempo.
 * Finalmente, muestra el nodo más lejano alcanzado durante la propagación.
 *
 * El programa utiliza la clase Graph, que representa un grafo mediante una lista de adyacencia.
 * 
 * Referencias:
 * M, G. P. (2023, May 18). Explicación de algoritmos y estructuras de datos de grafos con Ejemplos en Java y C++. freeCodeCamp.org. https://www.freecodecamp.org/espanol/news/explicacion-de-algoritmos-y-estructuras-de-datos-de-grafos-con-ejemplos-en-java-y-c/
 * GRAFOS. (n.d.). https://ccia.ugr.es/~jfv/ed1/c++/cdrom4/paginaWeb/grafos.htm
 * GeeksforGeeks. (2023h, August 1). Graph and its representations. https://www.geeksforgeeks.org/graph-and-its-representations/
*/
#include <iostream>
#include <stack>
#include <queue>
#include <vector>
using namespace std;

/**
 * @class Graph
 * Representa un grafo utilizando una estructura de lista de adyacencia.
 *
 * Esta clase proporciona una representación de un grafo mediante una lista de adyacencia.
 * El grafo puede ser dirigido o no dirigido, y mantiene un registro de las conexiones entre
 * los vértices. La clase Graph permite agregar, eliminar y consultar la presencia de aristas
 * entre los vértices.
*/
class Graph{
    private:
        vector<vector<int>> adjList; /// Lista de adyacencia que almacena las conexiones entre los vértices.
        int numVertices; /// Número total de vértices en el grafo.
    public:
        /**
         * @brief Constructor de la clase Graph.
         * @param numVertices Número total de vértices en el grafo.
        */
        Graph(int numVertices){
            this->numVertices = numVertices;
            adjList = vector<vector<int>>(numVertices);
        }
        /**
         * @brief Destructor de la clase Graph.
         * Libera los recursos utilizados por la lista de adyacencia.
        */
        ~Graph(){
            adjList.clear();
        }
        /**
         * @brief Agrega una arista al grafo entre los vértices i y j.
         *
         * Esta función agrega una arista no dirigida entre los vértices i y j al grafo.
         *
         * @param i Primer vértice de la arista.
         * @param j Segundo vértice de la arista.
         *
         * @note Complejidad de tiempo: O(1) - La adición de una arista no requiere recorrer la lista de adyacencia.
         * @note Complejidad de espacio: O(1) - No se asignan nuevas estructuras de datos en función de la entrada.
        */
        void addEdge(int i, int j){
            adjList[i].push_back(j);
        }
        /**
         * @brief Convierte el grafo a una representación de cadena para su visualización.
         *
         * Esta función imprime la representación del grafo como una lista de adyacencia, donde cada línea
         * muestra los vértices adyacentes al vértice correspondiente.
         *
         * @note Complejidad de tiempo: O(V + E), donde V es el número de vértices y E es el número de aristas.
         * @note Complejidad de espacio: O(1) - No se asignan nuevas estructuras de datos en función de la entrada.
        */
        void toString(){
            for(int i = 0; i < numVertices; i++){
                cout << i << ": ";
                for(int j = 0; j < adjList[i].size(); j++){
                    cout << adjList[i][j] << " ";
                }
                cout << endl;
            }
        }
        /**
         * @brief Encuentra el nodo con la máxima propagación en el grafo.
         *
         * Esta función realiza un recorrido en anchura (BFS) desde cada nodo del grafo y determina
         * cuántos nodos puede alcanzar. El nodo de inicio que produce la máxima cantidad de nodos
         * alcanzados se considera el nodo con la máxima propagación.
         *
         * @return El índice del nodo que tiene la máxima propagación en el grafo.
         *
         * @note Complejidad de tiempo: O(V * (V + E)), donde V es el número de vértices y E es el número de aristas.
         * @note Complejidad de espacio: O(V) - Se utiliza una estructura de datos de tamaño V (cola y vector de visitados).
        */
        int maxPropagacion(){
            int maxCount = 0; // Máxima cantidad de nodos alcanzados
            int inicio = -1;  // Nodo de inicio que produce la máxima propagación
            for(int i = 0; i < numVertices; i++){
                vector<bool> visited(numVertices, false);
                queue<int> q;
                q.push(i);
                visited[i] = true;
                int count = 0;
                while(!q.empty()){
                    int current = q.front();
                    q.pop();
                    count++;
                    for(int j = 0; j < adjList[current].size(); j++){
                        if(!visited[adjList[current][j]]){
                            q.push(adjList[current][j]);
                            visited[adjList[current][j]] = true;
                        }
                    }
                }
                if(count > maxCount){
                    maxCount = count;
                    inicio = i;
                }
            }
            return inicio;
        }

        /**
         * @brief Realiza una propagación desde el vértice de inicio hasta el tiempo especificado.
         *
         * Esta función realiza una propagación desde el vértice de inicio hasta el tiempo especificado t.
         * Se utiliza una cola para explorar los vecinos en función del tiempo y contar los vértices alcanzables
         * dentro del límite de tiempo.
         *
         * @param start Vértice de inicio para la propagación.
         * @param t Tiempo límite para la propagación.
         *
         * @return El número de vértices alcanzables dentro del límite de tiempo t.
         *
         * @note Complejidad de tiempo: O(V + E), donde V es el número de vértices y E es el número de aristas.
         * @note Complejidad de espacio: O(V) - Se utiliza una estructura de datos de tamaño V (cola y vector de visitados).
        */
        int propagacion(int start, int t){
            vector<bool> visited(numVertices, false);
            queue<pair<int,int>> q;
            q.push({start,0});
            visited[start] = true;
            int count = 0;
            while(!q.empty()){
                int current = q.front().first;
                int time = q.front().second;
                q.pop();
                if(time > t){
                    continue;
                }
                count++;
                for(int i = 0; i < adjList[current].size(); i++){
                    if(!visited[adjList[current][i]]){
                        q.push({adjList[current][i], time+1});
                        visited[adjList[current][i]] = true;
                    }
                }
            }
            return count;
        }

};


int main(){
    int n, m, t;
    cout << "Elige la cantidad de nodos a crear" << endl;
    cin >> n;
    cout << "Elige la cantidad de aristas a crear" << endl;
    cin >> m;
    cout << "Elige la cantidad de unidades de tiempo de propagación" << endl;
    cin >> t;
    Graph g(n);

    cout << "Ingresa el grafo" << endl;
    for(int i = 0; i < m; i++){
        int a, b;
        cin >> a >> b;
        g.addEdge(a,b);
    }

    g.toString();

    int start = g.maxPropagacion();
    cout << "Nodo con mayor propagación: " << start << endl;

    cout << "Nodos infectados " << g.propagacion(start,t) << endl;
    return 0;
}


/**
 * Casos de prueba utilizados y código para probarlos
 * Caso 1:
 * n = 10
 * m = 9
 * t = 2
 * (0,1) (0,2) (1,3) (1,4) (2,5) (2,6) (3,7) (4,8) (5,9)
 * 
 * Caso 2:
 * n = 15
 * m = 13
 * t = 2
 * (1,0) (2,4) (3,1) (3,2) (3,4) (3,5) (5,11) (5,13) (5,14) (6,7) (6,8) (9,10) (11,12)
 * 
 * Caso 3:
 * n = 14
 * m = 15
 * t = 8
 * (0,2) (1,5) (2,3) (3,1) (4,5) (4,6) (7,4) (7,8) (8,9) (9,10) (9,13) (10,11) (11,1) (11,12) (12,0) 
*/
