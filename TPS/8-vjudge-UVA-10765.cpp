/*Me guie con la idea de buscar puntos de articulacion de este link:
https://aprende.olimpiada-informatica.org/dfs-tree
*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int n, m;
vector<vector<int>> G;
vector<int> low, disc, cant_estaciones_candidatas;
vector<pair<int,int>> ap; // articulation points seran las estaciones candidatas a bombardear, acompaniadas de la cant de cc que quedarian al extraer cada AP (y eso seria la cant de palomas necesarias)
vector<pair<int,int>> res;


/*Tenemos dos condiciones para comprobar si un vertice es un articulation point.

Condicion 1: Para el vertice donde se empieza el DFS hay que ver si tiene mas de un hijo.
Condicion 2: Para el resto de vertices hay que ver si para alguno de sus hijos ese subarbol 
no tiene ningun back-edge que vaya "hacia detras" del vertice. */

// ap = articulation points, ap[i] = True sii i es un articulation point
// disc[u] = posicion en la que se ha visitado (descubierto)
// low[u] = backedge que apunta mas arriba del subarbol de u (menor valor de descubrimiento alcanzable durante el recorrido)

// esta variable nos servira para saber en que orden visitamos los nodos
int nodos_visitados = 0;
// devuelve el numero de hijos para comprobar la condicion 1
int dfsAP(int v, int padre){
    int numero_hijos = 0;
    low[v] = disc[v] = nodos_visitados;
    nodos_visitados++;
    for(int i=0; i<G[v].size(); i++){ //iteramos por todos los vecinos
        int u = G[v][i];
        if(u == padre){ // no queremos visitar el padre
            continue;
        } 
        if(disc[u]==-1){ // vamos a abrir un subarbol con un nodo que todavia no habiamos visitado
            numero_hijos++;
            dfsAP(u, v); // visitamos el hijo
            if(disc[v] <= low[u] && padre!=-1){ // comprobamos la condicion 2
                ap[v].first = v;
                ap[v].second += 1; //aumento la cant de cc que quedarian al sacarlo
            }
            low[v] = min(low[v], low[u]); // actualizamos low[v] para reflejar los backedges del subarbol
        }else{ // nos encontramos con un backedge y actualizamos low[v] acordemente
          low[v] = min(low[v], disc[u]);
        }
    }
    
    ap[v].first = v; // en cada posicion fijo en el primer lugar al nro de estacion
    // Condicion 1: Si es la raiz del DFS y tiene mas de un hijo, es un punto de articulacion
    if(padre == -1 && numero_hijos > 1){
        ap[v].second = numero_hijos;
    }

    return numero_hijos;
}


bool sort_palomas_estaciones(const pair<int,int> &ap1, const pair<int,int> &ap2) {
    if(ap1.second != ap2.second) {
        return ap1.second > ap2.second; // Orden decreciente por el valor paloma (cant cc de ap en v)
    }else{
        return ap1.first < ap2.first; // Orden creciente por el numero de estacion
    }
}


int main(){
    cin >> n >> m;
    
    while(n!=0 && m!=0){
        cant_estaciones_candidatas.push_back(m);
        G.clear();
        G.resize(n);

        int x, y;
        cin >> x >> y;
        while(x!=-1 && y!=-1){
            G[x].push_back(y);
            G[y].push_back(x);  
            cin >> x >> y;
        }

        low.clear();
        low.resize(n, -1);
        disc.clear();
        disc.resize(n, -1);
        ap.clear();
        ap.resize(n, make_pair(0,1)); //todos los nodos comienzan formando parte de una cc, si no son ap entonces la cant de cc al extraerlo es 1
        
        dfsAP(0,-1);
        
        sort(ap.begin(), ap.end(), sort_palomas_estaciones);
            
        //solo quedarme con m estaciones candidatas y esas guardarlas en res
        for(int i=0; i<m; i++){
            res.push_back(ap[i]);
        }

        cin >> n >> m;
    }

    int ult_estacion_caso_anterior = 0;
    for(int j=0; j<cant_estaciones_candidatas.size(); j++){
        int estaciones = cant_estaciones_candidatas[j];
        for(int k=ult_estacion_caso_anterior; k<ult_estacion_caso_anterior+estaciones; k++){
            cout << res[k].first << " " << res[k].second << endl;
        }
        ult_estacion_caso_anterior += estaciones;
        cout << "" << endl;
        }
    
    return 0;
}