#include "Brunolib.h"

void Bruno(int K, int S, int F, int L, int P[], int Q[]){
    for (int i=0; i<L; i++) {
        if(P[i] < S){
            if(Q[i] != F){
                Answer(P[i]); return;
            }
        }
        else{
            if(Q[i] == F){
                Answer(P[i]);  return;
            }
        }
    }
    Answer(S);
}