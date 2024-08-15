#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

//Resuelto con bottom-up, la solución con top-down no me pasaba los casos grandes

int N, number_cases;
vector<vector<int>> heights, widths; 
vector<vector<int>> memo_longest_increasing, memo_longest_decreasing;

/*  case_n ∈ [1,..., number_cases],
    n ∈ [1,..., N]
Cantidad de estados: O(N*number_cases)
*/

vector<int> WIS(int case_n, int n){ // Como en el ejercicio del CD
    for(int i=0; i<n; i++){
        memo_longest_increasing[case_n][i] = widths[case_n][i];
        for(int j=0; j<i; j++){
            if(heights[case_n][i] > heights[case_n][j]){ // Si el edificio en el que estoy es mas alto que el edificio j, actualizo la memo
                memo_longest_increasing[case_n][i] = max(memo_longest_increasing[case_n][i], // memo actual
                                                        memo_longest_increasing[case_n][j] + widths[case_n][i]); //memo en j más el ancho del edificio i (agrego el edificio i a los que venia acumulando)
            }
        }
    }
    return memo_longest_increasing[case_n]; 
}


vector<int> WDS(int case_n, int n){
    for(int i=0; i<n; i++){
        memo_longest_decreasing[case_n][i] = widths[case_n][i];
        for(int j=0; j<i; j++){
            if(heights[case_n][i] < heights[case_n][j]){
                memo_longest_decreasing[case_n][i] = max(memo_longest_decreasing[case_n][i], 
                                                        memo_longest_decreasing[case_n][j] + widths[case_n][i]);
            }
        }
    }   
    return memo_longest_decreasing[case_n];
}


int max_WIS(int k){
    int aux_increasing = 0;
    
    for(int j=0; j<memo_longest_increasing[k].size(); j++){ 
        if(memo_longest_increasing[k][j] > aux_increasing){
            aux_increasing = memo_longest_increasing[k][j];
        }
    }
    return aux_increasing;
}


int max_WDS(int k){
    int aux_decreasing = 0;

    for(int j=0; j<memo_longest_increasing[k].size(); j++){
        if(memo_longest_decreasing[k][j] > aux_decreasing){
            aux_decreasing = memo_longest_decreasing[k][j];
        }
    }
    return aux_decreasing;
}


int main() {
    cin >> number_cases;
    heights.resize(number_cases), widths.resize(number_cases); 
    memo_longest_increasing.resize(number_cases), memo_longest_decreasing.resize(number_cases);
    
    for(int case_num = 0; case_num<number_cases; case_num++){
        cin >> N;

        heights[case_num].resize(N), widths[case_num].resize(N); 
        memo_longest_increasing[case_num].resize(N), memo_longest_decreasing[case_num].resize(N);

        for(int i=0; i<N; i++){
            cin >> heights[case_num][i];
        }

        for(int i=0; i<N; i++){
            cin >> widths[case_num][i];
        }

        WIS(case_num, N);
        WDS(case_num, N);
        
    }
    
    for(int k=0; k<number_cases; k++){

        int max_memo_longest_increasing = max_WIS(k); //Busco la mayor suma creciente de anchos
        int max_memo_longest_decreasing = max_WDS(k); //Busco la mayor suma decreciente de anchos

        cout << "Case " << k+1 << ". ";
        if(max_memo_longest_increasing >= max_memo_longest_decreasing){
            cout << "Increasing (" << max_memo_longest_increasing << "). Decreasing (" << max_memo_longest_decreasing << ")." << endl;
        } else {
            cout << "Decreasing (" << max_memo_longest_decreasing << "). Increasing (" << max_memo_longest_increasing << ")." << endl; 
        }
    }
    return 0;
}