#include "ramen.h"
#include <vector>
using namespace std;

vector<int> mild, jin;

void Ramen(int N) {
    for (int i=0; i<N/2; i++) {
        if(Compare(2*i,2*i+1) == 1){
            jin.push_back(2*i);
            mild.push_back(2*i+1);
        }
        else{
            mild.push_back(2*i);
            jin.push_back(2*i+1);
        }
    }
    if(N&1){
        mild.push_back(N-1);
        jin.push_back(N-1);
    }
    while (mild.size() > 1) {
        if(Compare(mild.back(),mild[mild.size()-2]) == 1){
            mild.pop_back();
        }
        else{
            mild[mild.size()-2] = mild.back();
            mild.pop_back();
        }
    }
    while (jin.size() > 1){
        if(Compare(jin.back(),jin[jin.size()-2]) == -1){
            jin.pop_back();
        }
        else{
            jin[jin.size()-2] = jin.back();
            jin.pop_back();
        }
    }
    Answer(mild.front(),jin.front());
}