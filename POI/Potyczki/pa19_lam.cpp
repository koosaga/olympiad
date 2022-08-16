#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = pair<int, int>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
const int MAXN = 300005;

string s; 
lint cnt[16][16], occ[16];

int main(){ 
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin >> s;
    for(int i = 0; i < sz(s); i++){
        for(int j = 0; j < 16; j++){
            cnt[j][s[i] - 'a'] += occ[j];
        }
        occ[s[i] - 'a']++;
    }
    lint ret = 0;
    for(int i = 0; i < (1<<16); i++){
        lint foo = 0;
        for(int j = 0; j < 16; j++){
            for(int k = 0; k < 16; k++){
                if((i >> j) % 2 == 1 && (i >> k) % 2 == 0) foo += cnt[j][k];
            }
        }
        ret = max(ret, foo);
    }
    cout << ret << "\n";
}
