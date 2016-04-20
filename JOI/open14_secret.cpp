#include "secret.h"
#include <algorithm>
using namespace std;
 
int t[10][1005];
 
void make(int depth, int A[], int N, int piv){
    if(depth == -1) return;
    make(depth-1,A,N,piv - (1<<(depth-1)));
    make(depth-1,A,N,piv + (1<<(depth-1)));
    int np = min(piv-1,N-1);
    if(np >= piv - (1<<depth)) t[depth][np] = A[np];
    for (int i=np-1; i>=piv - (1<<depth); i--) {
        t[depth][i] = Secret(A[i],t[depth][i+1]);
    }
    if(N > piv) t[depth][piv] = A[piv];
    for (int i=piv+1; i<piv + (1<<depth) && i < N; i++) {
        t[depth][i] = Secret(t[depth][i-1],A[i]);
    }
}
 
void Init(int N, int A[]){
    make(9,A,N,512);
}
 
int q(int p, int l, int r, int d){
    if(l <= p-1 && p <= r) return Secret(t[d][l],t[d][r]);
    if(r == p-1) return t[d][l];
    if(l == p) return t[d][r];
    if(r <= p-1) return q(p-(1<<(d-1)),l,r,d-1);
    return q(p+(1<<(d-1)),l,r,d-1);
}
 
int Query(int L, int R){
    return q(512,L,R,9);
}