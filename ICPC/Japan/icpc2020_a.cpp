#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using llf = long double;
using pi = pair<lint, lint>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
const int MAXN = 619;
const int mod = 998244353; // cringe prime

string s[3][MAXN];
string t[3][MAXN];
int main(){
    ios_base::sync_with_stdio(0); 
    cin.tie(0);
    int n; cin >> n;
    for(int i = 0; i < 3; i++){
        for(int j = n-1; j >= 0; j--){
            cin >> s[i][j];
            t[i][j] = string(n, '0');
        }
    }
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            for(int k = 0; k < n; k++){
                if(s[0][j][i] == '1' && s[1][k][j] == '1' && s[2][i][k] == '1'){
                    t[0][j][i] = t[1][k][j] = t[2][i][k] = '1';
                }
            }
        }
    }
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < n; j++){
            if(s[i][j] != t[i][j]){
                puts("No");
                return 0;
            }
        }
    }
    puts("Yes");
}
