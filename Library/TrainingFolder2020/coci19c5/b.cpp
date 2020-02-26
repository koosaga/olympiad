#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using pi = pair<int, int>;
using lint = long long;
const int MAXN = 250005;
 
int n; lint k;
int nxt[66][MAXN];
 
int main(){
    scanf("%d %lld",&n,&k);
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            int x; scanf("%d",&x);
            if(x){
                x--;
                nxt[0][i * n + j] = x * n + i;
            }
        }
    }
    int pos = n;
    k--;
    for(int i=1; i<60; i++){
        for(int j=0; j<n*n; j++){
            nxt[i][j] = nxt[i-1][nxt[i-1][j]];
        }
    }
    for(int i=0; i<60; i++){
        if(k & 1) pos = nxt[i][pos];
        k >>= 1;
    }
    cout << (pos % n) + 1 << endl;
}