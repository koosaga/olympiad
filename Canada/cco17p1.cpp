#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
using namespace std;
const int MAXN = 1005;
using lint = long long;
using pi = pair<int, int>;
const int dx[4] = {1, 0, -1, 0};
const int dy[4] = {0, 1, 0, -1};

int main(){
    int k; cin >> k;
    int x = 0;
    vector<pi> v;
    while(k > 0){
        int n = 1;
        while((n) * (n + 1) / 2 <= k) n++;
        v.emplace_back(x + n, x + 1);
        for(int i=x+1; i<x+n; i++){
            v.emplace_back(i, i + 1);
        }
        if(x != 0){
            v.emplace_back(1, x + 1);
        }
        k -= n * (n - 1) / 2;
        x += n;
    }
    cout << x << " " << sz(v) << endl;
    for(auto &i : v) cout << i.first << " " << i.second << endl;
}
