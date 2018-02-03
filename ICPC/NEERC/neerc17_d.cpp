#include <bits/stdc++.h>
using namespace std;
const int MAXN = 200005;
const int inf = 2e9 + 100;

typedef pair<int, int> pi;

int a[3], p[3];

vector<pi> solve(){
    vector<pi> v;
    set<pi> s;
    for(int i=0; i<a[1]; i++){
        v.push_back(pi(min(i, a[0]-1), i));
        s.insert(v.back());
    }
    for(int i=0; i<a[0]; i++){
        for(int j=0; j<a[1]; j++){
            if(s.find(pi(i, j)) == s.end() && s.size() < a[2]){
                s.insert(pi(i, j));
                v.push_back(pi(i, j));
            }
        }
    }
    return v;
}

int main(){
    cin >> a[2] >> a[1] >> a[0];
    iota(p, p + 3, 0);
    sort(p, p + 3, [&](const int &x, const int &y){
        return a[x] < a[y];
    });
    sort(a, a + 3);
    if(a[0] * a[1] < a[2]){
        puts("-1");
        return 0;
    }
    auto x = solve();
    printf("%d\n", x.size());
    for(auto &i : x){
        int w[3];
        w[p[0]] = i.second;
        w[p[1]] = i.first;
        w[p[2]] = 0;
        printf("%d %d %d\n", w[0], w[1], w[2]);
    }
}