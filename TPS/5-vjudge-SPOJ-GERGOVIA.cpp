#include <iostream>
#include <cmath>
#include <vector>
#include <cstdlib> // Para que tome abs en enteros

using namespace std;


long long int min_amount_work_units(const vector<int> &inhabitants){
    long long int inhabitants_want = 0;
    long long int units_work = 0;
    
    for(int i=0; i<inhabitants.size(); i++){
        units_work += abs(inhabitants_want + inhabitants[i]);
        inhabitants_want += inhabitants[i];
    }
    
    return units_work;
}


int main(){
    int N;
    cin >> N;
    vector<long long int> res;

    while(N!=0){
        vector<int> inhabitants(N);

        for(int j=0; j<N; j++){
            int a_j;
            cin >> a_j;
            inhabitants[j] = a_j;
        } 
        
        long long int res_i = min_amount_work_units(inhabitants);
        res.push_back(res_i);
        
        cin >> N; // Ingreso la cantidad de habitantes para el siguiente caso de test, si es cero imprimo el output
    }

    for(int k=0; k<res.size(); k++){
        if(k!=res.size()-1){
            cout << res[k] << endl;
        }else{
            cout << res[k];
        }
    }

    return 0;
}