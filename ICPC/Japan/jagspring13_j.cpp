#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;

const int MAXN = 505;
struct disj{
    int pa[MAXN], sz[MAXN];
    void init(int n){
        for(int i=0; i<=n; i++){
            pa[i] = i;
            sz[i] = 1;
        }
    }
    int find(int x){
        return pa[x] = (pa[x] == x ? x : find(pa[x]));
    }
    bool uni(int p, int q){
        p = find(p);
        q = find(q);
        if(p == q) return 0;
        pa[q] = p;
        sz[p] += sz[q];
        return 1;
    }
}disj;

int main(){
    int n, m;
    cin >> n >> m;
    disj.init(n);
    int ans = m;
    while(m--){
        int x, y;
        cin >> x >> y;
        if(disj.uni(x, y)) ans--;
    }
    cout << ans;
}
