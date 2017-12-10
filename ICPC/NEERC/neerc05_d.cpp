#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<lint, lint> pi;

string s[9][4];
int chk[9];

int vis[2000000];
double dp[2000000];
double f(int dep){
    if(dep == 18) return 1;
    int bit = 0;
    for(int i=0; i<9; i++){
        bit = bit * 5 + chk[i];
    }
    if(vis[bit]) return dp[bit];
    vis[bit] = 1;
    vector<pi> v;
    for(int i=0; i<9; i++){
        if(chk[i] != 4){
            for(int j=i+1; j<9; j++){
                if(chk[j] != 4 && s[i][chk[i]][0] == s[j][chk[j]][0]){
                    v.push_back({i, j});
                }
            }
        }
    }
    double ret = 0;
    for(auto &i : v){
        chk[i.first]++;
        chk[i.second]++;
        ret += 1.0 * f(dep+1) / v.size();
        chk[i.first]--;
        chk[i.second]--;
    }
    return dp[bit] = ret;
}

int main(){
    for(int i=0; i<9; i++){
        for(int j=3; j>=0; j--){
            cin >> s[i][j];
        }
    }
    printf("%.6f", f(0));
}

