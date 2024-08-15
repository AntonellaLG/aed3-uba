#include <iostream>
#include <string>
#include <vector>

using namespace std;

vector<pair<int, int>> res;

bool equal_amount_letters(const string s, const string t){
    int amount_a_in_s=0, amount_a_in_t=0;  
    // si s y t tienen la misma longitud y la misma cantidad de a's, entonces van a tener la misma cantidad de b's. Basta comparar cantidad de a's para saber si tienen la misma cantidad de letras 
    for(int i=0; i<s.size(); i++){
        if(s[i]=='a'){
            amount_a_in_s++;
        }
        if(t[i]=='a'){
            amount_a_in_t++;
        }        
    }
    bool is_amount_pair = ((amount_a_in_s+amount_a_in_t) % 2) == 0;
    return is_amount_pair;
}


void swap_letters(string &s, string &t){
    int first_last_change = -1;
    int second_last_change = -1;
    for(int i=0; i<s.size(); i++){
        if(s[i]!=t[i]){
            if(first_last_change==-1){
                //guardo el primer indice que debo cambiar
                first_last_change=i;
            } else {
                if(second_last_change==-1){
                    if(s[i]==t[first_last_change]){
                        //no tiene sentido cambiar nada porque tendria las mismas palabras
                        //guardo el segundo indice que debo cambiar
                        second_last_change=i;
                    }else{ 
                        //swappeo en el primer indice que debo cambiar
                        res.push_back(make_pair(i, first_last_change));
                        swap(s[i], t[first_last_change]);
                        first_last_change=-1;
                    }
                }else{
                    if(s[i]!=t[first_last_change]){
                        //swappeo en el primer indice que debo cambiar
                        res.push_back(make_pair(i, first_last_change));
                        swap(s[i], t[first_last_change]);
                        //en mis auxiliares, actualizo los indices que debo cambiar porque ya swapee el primero
                        first_last_change=second_last_change;
                        second_last_change=-1;                      
                    }else{
                        //swappeo en el segundo indice que debo cambiar
                        res.push_back(make_pair(i, second_last_change));
                        swap(s[i], t[second_last_change]);
                        //actualizo el auxiliar porque ya swapee el segundo
                        second_last_change=-1;
                    }
                }
            }
        }
    }
    //si al terminar de recorrer los strings me quedaron swaps por hacer en el medio (por no comparar con un tercer valor como arriba)
    if(first_last_change!=-1 && second_last_change!=-1){
        //si los indices que me quedaron por cambiar son distintos, los swapeo 
        if(s[second_last_change] != t[first_last_change]){
            res.push_back(make_pair(second_last_change, first_last_change));
            swap(s[second_last_change], t[first_last_change]);
        }else{
            //si los indices que me quedaron por swapear son iguales, tengo que "swapear cruzado" (ie, hacer dos swaps para acomodar)
            res.push_back(make_pair(second_last_change, second_last_change));
            swap(s[second_last_change], t[second_last_change]);
            res.push_back(make_pair(first_last_change, second_last_change));
            swap(s[first_last_change], t[second_last_change]);
        }
    }
}


int main(){
    int n;
    cin >> n;

    string s, t;
    cin >> s >> t;

    if(equal_amount_letters(s,t)){
        swap_letters(s, t);
        cout << res.size() << endl;
        for(int j=0; j<res.size(); j++){
            // Para el problema, los indices arrancaban desde 1, asi que sumo uno a cada par
            cout << res[j].first+1 << " " << res[j].second+1 << endl;
        }
    } else {
        cout << -1 << endl;
    }
    return 0;
}