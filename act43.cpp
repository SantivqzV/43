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
 * 
 * Referencias:
 * 
*/
#include <iostream>
#include <stack>
#include <queue>
#include <vector>
using namespace std;

/**
 * @class Graph
*/
class Graph{
    private:
        vector<vector<int>> adjList;
        int numVertices;
    public:
        Graph(int numVertices){
            this->numVertices = numVertices;
            adjList = vector<vector<int>>(numVertices);
        }
        ~Graph(){
            adjList.clear();
        }

        void addEdge(int i, int j){
            adjList[i].push_back(j);
            adjList[j].push_back(i);
        }

        void toString(){
            for(int i = 0; i < numVertices; i++){
                cout << i << ": ";
                for(int j = 0; j < adjList[i].size(); j++){
                    cout << adjList[i][j] << " ";
                }
                cout << endl;
            }
        }

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
    cout << "Crea la matriz de adyacencia" << endl;
    for(int i = 0; i < m; i++){
        int a, b;
        cin >> a >> b;
        g.addEdge(a, b);
    }
    cout << "Matriz de adyacencia" << endl;
    g.toString();

    cout << "Nodo más lejano de propagación " << g.propagacion(0,t) << endl;
    return 0;
}