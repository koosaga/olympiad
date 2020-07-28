// Ivan Carvalho
// Solution to https://www.spoj.com/problems/SUMFOUR/
#include <bits/stdc++.h>
using namespace std;
#define MAXN 4001
typedef pair<int,int> ii;
int A[MAXN],B[MAXN],C[MAXN],D[MAXN];
vector<int> V,U;
vector<ii> P,Q;
int resp,N;
int main(){
    cin >> N;
    for(int i = 1;i<=N;i++){
        cin >> A[i] >> B[i] >> C[i] >> D[i];
    }
    for(int i = 1;i<=N;i++){
        for(int j = 1;j<=N;j++){
            V.push_back(A[i] + B[j]);
            U.push_back(-(C[i] + D[j]));
        }
    }
    sort(V.begin(),V.end());
    sort(U.begin(),U.end());
    for(int i = 0;i<V.size();i++){
        if(i == 0 || V[i] != V[i-1]){
            P.push_back(ii(V[i],1));
        }
        else{
            P.back().second++;
        }
    }
    for(int i = 0;i<U.size();i++){
        if(i == 0 || U[i] != U[i-1]){
            Q.push_back(ii(U[i],1));
        }
        else{
            Q.back().second++;
        }
    }
    int ptr = 0;
    for(int i = 0;i<P.size();i++){
        while(ptr + 1 < Q.size() && Q[ptr].first < P[i].first ){
            ptr++;
        }
        if(P[i].first == Q[ptr].first) resp += P[i].second*Q[ptr].second;
    }
    printf("%d\n",resp);
    return 0;
}