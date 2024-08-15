#include <iostream>
#include <string>
using namespace std;

// Saqué substr de <string.h> porque copiaba los strings y me daba limit exceed 91
bool are_equivalent_words(const string &s, const string &t, int start_1, int start_2, int len){
    for(int i=0; i<len; i++){
        if(s[start_1+i] != t[start_2+i]){
            return false;
        }
    }
    return true;
}

bool is_equivalent(const string &first_string, const string &second_string, int start_1, int start_2, int length_words){ 
    // Casos base
    if(are_equivalent_words(first_string, second_string, start_1, start_2, length_words)){
        return true;
    }

    if(length_words % 2 !=0){
        return false;
    } else {
        // Voy dividiendo a la mitad los strings y comparando recursivamente
        int mid = length_words/2;

        return (is_equivalent(first_string, second_string, start_1, start_2, mid) 
                && is_equivalent(first_string, second_string, start_1+mid, start_2+mid, mid))
                || (is_equivalent(first_string, second_string, start_1, start_2+mid, mid) 
                && is_equivalent(first_string, second_string, start_1+mid, start_2, mid));      
    }
}


int main(){
    string a, b;
    cin >> a >> b;
    // Comienzo a evaluar desde el comienzo de cada string, a lo largo de toda su long
    bool solution = is_equivalent(a, b, 0, 0, a.length()); //a y b tienen la misma longitud

    if(solution){
        cout << "YES" << endl;
    } else {
        cout << "NO" << endl;
    }
    
    return 0;
}