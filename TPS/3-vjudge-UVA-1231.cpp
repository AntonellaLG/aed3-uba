#include <iostream>
#include <vector>

using namespace std;

int c, t, h, f, a, n, zero;; // 1 ≤ t, h ≤ 2000,  1 ≤ f ≤ 500,    0 ≤ a ≤ 2000.
vector<vector<int>> acorns;
vector<vector<int>> memo_max_acorns;
vector<int> max_height, res;


void max_acorns_forest(){
    max_height.resize(h+1, 0); 

    for(int i=0; i<t; i++){
        
        //Inicio con las bellotas que se encuentran en la base de los arboles
        memo_max_acorns[i][0] = acorns[i][0];
        max_height[0] = max(memo_max_acorns[i][0], max_height[0]);
    }

    for(int current_height=1; current_height<=h; current_height++){
        for(int tree=0; tree<t; tree++){

            //Sigo en el mismo arbol (subo 1 paso de altura)
            //Altura anterior (vengo subiendo) + bellotas actuales
            memo_max_acorns[tree][current_height] = memo_max_acorns[tree][current_height-1] + acorns[tree][current_height]; 
            
            //Puedo saltar a otro arbol (subo losed_jumping pasos de altura)
            //Para cambiar de arbol, cambio el lugar que veo en la memo (arbol y altura de salto) y consulto cuanto pudo haber juntado hasta esa altura
            //Sumo las bellotas del arbol y altura actual. 
            if(current_height - f >= 0){
                /*DABA TIME LIMIT EXCEED
                for(int other_tree=0; other_tree<t; other_tree++){
                    
                    memo_max_acorns[tree][current_height] = max(memo_max_acorns[tree][current_height],
                                                memo_max_acorns[other_tree][current_height - f] + acorns[tree][current_height]);
                }*/

                //En vez de recorrer todos los arboles como antes, me voy guardando el maximo en otro vector y solo salto desde ese arbol a la altura actual
                memo_max_acorns[tree][current_height] = max(memo_max_acorns[tree][current_height],
                                                max_height[current_height-f] + acorns[tree][current_height]);
            }
            
            //Actualizo el maximo en la altura actual
            max_height[current_height] = max(memo_max_acorns[tree][current_height],
                                            max_height[current_height]);
        }
    }
}


//Tengo en la cima todos los maximos posibles. Busco el mayor
int max_can_collect(){
    int max_acorns = 0;
    
    for(int tree=0; tree<t; tree++){
            max_acorns = max(memo_max_acorns[tree][h], max_acorns);
    }
    return max_acorns;
}


int main(){
    cin >> c;
    res.resize(c);
    
    for(int i=0; i<c; i++){
        cin >> t >> h >> f; // t:number trees, h: height trees, f: height loses flying
        acorns.clear();
        acorns.resize(t, vector<int>(h + 1, 0)); //va a guardar en cada arbol la cantidad de bellotas en su altura correspondiente

        for(int j=0; j<t; j++){
            cin >> a; // a: number acorns in the j-th tree

            for(int k=0; k<a; k++){
                cin >> n; // n: height of the acorn on the j-th tree. Are sorted in ascending order

                acorns[j][n] += 1; 
                // da <0,0,0,1,0,1,0,1,1,2,0> en el ejemplo del ejc
            }
        }
        
        memo_max_acorns.clear();
        memo_max_acorns.resize(t, vector<int> (h + 1, 0));
        max_height.clear();
        max_acorns_forest();
        
        res[i]=max_can_collect();
    }
    
    cin >> zero;
    if(zero==0){  
        for(int i=0; i<c; i++){ 
            cout << res[i] << endl; 
        }
    }
    
    return 0;
}