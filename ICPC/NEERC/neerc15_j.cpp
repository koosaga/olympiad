#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using llf = long double;
using pi = pair<int, int>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
const int MAXN = 2000;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
int randint(int lb, int ub){ return uniform_int_distribution<int>(lb, ub)(rng); }

int diff[MAXN];

int main(){
    int n; cin >> n;
    auto query = [&](string s){
        cout << s << endl;
        int val; cin >> val;
        if(val == n) exit(0);
        return val;
    };
    string t;
    while(true){
        t.clear();
        for(int j = 0; j < n; j++){
            t.push_back(randint('0', '1'));
        }
        if(query(t) == n / 2) break;
    }
    for(int i = 1; i < n; i++){
        t[0] ^= 1;
        t[i] ^= 1;
        if(query(t) == n / 2) diff[i] = 1;
        t[0] ^= 1;
        t[i] ^= 1;
    }
    for(int i = 1; i < n; i++){
        if(diff[i]) t[i] ^= 1;
    }
    query(t);
    for(auto &i : t) i ^= 1;
    query(t);
}
