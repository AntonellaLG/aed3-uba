#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <algorithm>
#include <climits>

using namespace std;

int T, N;
vector<string> keys; //Dejo las claves como strings porque es mas facil comparar digitos
vector<int> res;

//Calculo la mínima cantidad de movimientos para cambiar de una combinación a otra
int min_rolls(const string &a, const string &b) {
    int rolls = 0;
    for(int i=0; i<4; i++){
        int diff = abs(a[i] - b[i]); //Comparo digito a digito
        rolls += min(diff, 10 - diff); //rolling-up or rolling-down
    }
    return rolls;
}

int prim_agm(const vector<string> &keys) {
    vector<int> min_edge(N, INT_MAX); //Almacena el costo minimo de agregar un nodo al agm
    vector<bool> in_agm(N, false); //Indica si el nodo ya esta en el agm
    
    min_edge[0] = 0;
    int total_cost = 0;

    for(int i=0; i<N; i++){
        int u = -1;

        //Busco el nodo con el menor peso que no está en el agm
        for(int j=0; j<N; j++){
            if(!in_agm[j] && (u == -1 || min_edge[j] < min_edge[u])){
                u = j;
            }
        }

        in_agm[u] = true; //Agrego el nodo al agm
        total_cost += min_edge[u]; //Agrego el costo del nodo al costo total del agm

        //Actualizo los costos minimos de los nodos adyacentes al agm
        for(int v=0; v<N; v++){
            if(!in_agm[v]){
                int weight = min_rolls(keys[u], keys[v]);
                if(weight < min_edge[v]){
                    min_edge[v] = weight;
                }
            }
        }
    }

    return total_cost;
}

int solve_case(const vector<string> &keys) {
    //Calculo el costo mínimo para ir de "0000" a cada una de las claves
    int min_bfs_cost = INT_MAX;
    for(const string &key : keys){
        min_bfs_cost = min(min_bfs_cost, min_rolls("0000", key));
    }

    //Calculo el costo del Arbol Generador Minimo sobre las claves, usando el algo de Prim
    int agm_cost = prim_agm(keys);

    //Sumo el costo mínimo desde "0000" y el costo del agm
    return min_bfs_cost + agm_cost;
}

int main() {
    cin >> T;
    for(int i=0; i<T; i++) {
        cin >> N;
        keys.clear();
        keys.resize(N);
        
        for(int j=0; j<N; j++){
            cin >> keys[j];
        }

        int result = solve_case(keys);
        res.push_back(result);
    }
    
    for(int k=0; k<res.size(); k++){
        cout << res[k] << endl;
    }
    
    return 0;
}