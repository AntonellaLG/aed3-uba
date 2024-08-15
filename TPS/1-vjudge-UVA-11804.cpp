#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;


int T;
int N=10;
int cota = 100; // Es O(n), ya que cota = 10*players.size()
int number_attack = N/2, number_defend = N/2;
int counter_attack, counter_defend;
int best_attack, best_defend;
vector<pair<string, pair<int, int>>> aux_attacks, aux_defends, sol_attacks, sol_defends, players;


int sum_attack(vector<pair<string, pair<int, int>>> v){
    int aux=0;
    for(int i=0; i<v.size(); i++){
        aux+=v[i].second.first;
    }
    return aux;
}


int sum_defend(vector<pair<string, pair<int, int>>> v){
    int aux=0;
    for(int i=0; i<v.size(); i++){
        aux+=v[i].second.second;
    }
    return aux;
}


bool lexicographically(pair<string, pair<int, int>> player1, pair<string, pair<int, int>> player2) {
  if ((player1.first < player2.first) || (player1.first == player2.first)){
    return true;
  } else {
     return false;
  }
}


bool best_lexicographically(vector<pair<string, pair<int, int>>> v1, vector<pair<string, pair<int, int>>> w1, vector<pair<string, pair<int, int>>> v2, vector<pair<string, pair<int, int>>> w2){
    for(int i=0; i<N/2; i++){
        if (v1[i].first != w1[i].first){
            return v1[i].first < w1[i].first;
        } 
        if (v2[i].first != w2[i].first){
            return v2[i].first > w2[i].first; //Quiero que se priorice el orden lexicográfico de los atacantes, entonces en defensores invierto desigualdad para que el menor jugador lexicográfico sea atacante
        }
    }
    return false; // Si los nombres son iguales, no hay diferencia lexicográfica
}



void formation(int number_players, vector<pair<string, pair<int, int>>> &aux_attacks, vector<pair<string, pair<int, int>>> &aux_defends, vector<pair<string, pair<int, int>>> &sub_vector){
    if((aux_attacks.size()==number_attack) && (aux_defends.size()==number_defend)){
        counter_attack = sum_attack(aux_attacks);
        counter_defend = sum_defend(aux_defends);
        if ((counter_attack>best_attack) ||
            (counter_attack==best_attack && counter_defend>best_defend) || 
            (counter_attack==best_attack && counter_defend==best_defend && best_lexicographically(aux_attacks, sol_attacks, aux_defends, sol_defends))){
            best_attack=counter_attack;
            best_defend=counter_defend;
            sol_attacks=aux_attacks;
            sol_defends=aux_defends;
        }
        return;
    
    }else{
        
        if(aux_attacks.size()<number_attack){
            aux_attacks.push_back(sub_vector[number_players]);
            formation(number_players+1, aux_attacks, aux_defends, sub_vector);
            aux_attacks.pop_back();
        }

        if(aux_defends.size()<number_defend){
            aux_defends.push_back(sub_vector[number_players]);
            formation(number_players+1, aux_attacks, aux_defends, sub_vector);
            aux_defends.pop_back();
        }
    }
}




int main() {
    cin >> T;
    
    vector<pair<string, pair<int, int>>> sub_players;       
    for(int i = 0; i < T*N; i++){

        string name;
        int attack, defend;
        cin >> name >> attack >> defend;

        pair<string, pair<int, int>> player;
        player.first = name;
        (player.second).first = attack;
        (player.second).second = defend;
        players.push_back(player);
    }
    
    for(int j = 0; j < T; j++){

        sub_players.clear(); //Receteo
        aux_attacks.clear(); 
        aux_defends.clear();
        sol_attacks.clear();
        sol_defends.clear();
        counter_attack=0, counter_defend=0;
        best_attack=0, best_defend=0;

        int index_sub_players=j*N;
        for(int l=index_sub_players; l<j*N+N; l++){
            sub_players.push_back(players[l]);
        }

        formation(0, aux_attacks, aux_defends, sub_players);


        //https://aprende.olimpiada-informatica.org/cpp-sort
        sort(sol_attacks.begin(), sol_attacks.end(), lexicographically);
        sort(sol_defends.begin(), sol_defends.end(), lexicographically);

     
        cout << "Case " << j+1 << ":"<< endl; //Devuelvo nro de caso
            
        cout << "(";
        for(int k=0; k<sol_attacks.size(); k++){ // Devuelvo nombre de jugadores
            if(k!=sol_attacks.size()-1){
                cout << sol_attacks[k].first << ", ";                
            }
            else{
                cout << sol_attacks[k].first << ")"<< endl;
            }
        }

        cout << "(";
        for(int k=0; k<sol_defends.size(); k++){
            if(k!=sol_defends.size()-1){               
                cout << sol_defends[k].first << ", ";
            }
            else{
                   cout << sol_defends[k].first << ")" << endl;
            }
        }
    }

    return 0;
}