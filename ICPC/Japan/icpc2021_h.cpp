#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = pair<int, int>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
const int mod = 1e9 + 7;
const int MAXN = 100005;
const string P = "ACGT";

int main(){ 
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n, m; cin >> m >> n;
    vector<string> s(n);
    for(int i = 0; i < n; i++){
        cin >> s[i];
    }
    sort(all(s), [&](const string &a, const string &b){
        return count(all(a), '?') < count(all(a), '?');
    });
    double ret = 0;
    for(int i = 0; i < n; i++){
        double base = 1;
        int cnt = 0;
        for(int j = 0; j < m; j++){
            if(s[i][j] != '?') base *= 0.25;
        }
        for(int j = 0; j < 1557; j++){
            string t = s[i];
            for(int k = 0; k < m; k++){
                if(t[k] == '?') t[k] = P[rand() % 4];
            }
            bool newV = 1;
            for(int k = 0; k < i; k++){
                bool ok = 1;
                for(int l = 0; l < m; l++){
                    if(s[k][l] != '?' && t[l] != s[k][l]){
                        ok = 0;
                        break;
                    }
                }
                if(ok){
                    newV = 0;
                    break;
                }
            }
            if(newV) cnt++;
        }
        ret += base * cnt / 1557;
    }
    cout << setprecision(69) << ret << "\n";
}

