#include <bits/stdc++.h>
using namespace std;
using pi = pair<int, int>;
using lint = long long;
using real_t = double;
const int mod = 1e9 + 7;
const int MAXN = 14;

int n, a[MAXN], p[3][MAXN];
real_t dp[1 << MAXN];

int main(){
    cin >> n >> a[0];
    for(int i=1; i<n; i++) cin >> a[i] >> p[0][i] >> p[1][i] >> p[2][i];
    dp[1] = 1; // wow you win!
    for(int i=2; i<(1<<n); i++){
        if(i % 2 == 0) continue; // you lose
        real_t totProb = 0;
        vector<int> v;
        real_t W[3] = {};
        for(int j=1; j<n; j++){
            if((i >> j) & 1) v.push_back(j);
        }
        int noMe = i ^ 1;
        bool lost = 0;
        for(auto &i : v){
            if(a[i] > a[0]){
                lost = 1;
            }
        }
        for(int j=noMe; j; j=(j-1)&noMe){
            int L = j;
            int R = noMe ^ j;
            for(int k=0; k<3; k++){
                real_t curProb = 1;
                for(auto &player : v){
                    if((L >> player) & 1){
                        curProb *= p[k][player] * 0.01;
                    }
                    else{
                        curProb *= p[(k+1)%3][player] * 0.01;
                    }
                }
                totProb += curProb;
                if(!lost){
                    if(L == noMe) W[k] += curProb;
                    else W[(k+2)%3] += curProb;
                }
                W[(k+1)%3] += curProb * dp[R | 1];
            }
        }
        if(!lost){
            for(int i=0; i<3; i++) W[i] += 1 - totProb;
        }
        dp[i] = *max_element(W, W + 3);
    }
    printf("%.10f\n", dp[(1<<n) - 1]);
}
