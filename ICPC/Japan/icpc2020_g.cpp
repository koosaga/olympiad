#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using llf = long double;
using pi = pair<int, int>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
const int MAXN = 100005;
const int mod = 1e9 + 7;

struct disj{
    int pa[MAXN], sz[MAXN];
    int comp;
    int totvtx;
    void init(int n){
        comp = totvtx = 0;
        iota(pa, pa + n + 1, 0);
        fill(sz, sz + n + 1, 0);
    }
    int find(int x){
        return pa[x] = (pa[x] == x ? x : find(pa[x]));
    }
    void activate(int x, int v){
        x = find(x);
        sz[x]++;
        comp++;
        totvtx++;
    }
    bool uni(int p, int q){
        p = find(p);
        q = find(q);
        if(p == q) return 0;
        pa[q] = p;
        sz[p] += sz[q]; 
        comp--;
        return 1;
    }
    pi query(){
        return pi(totvtx - comp, comp);
    }
}disj;

int n, m;
pi a[MAXN];
vector<int> gph[MAXN];
int w[MAXN];
#define data fuk

pi data[2][MAXN];

int main(){
    scanf("%d %d",&n,&m);
    for(int i = 1; i <= n; i++){
        scanf("%d",&a[i].first);
        a[i].second = i;
    }
    for(int i = 0; i < m; i++){
        int s, e; scanf("%d %d",&s,&e);
        gph[s].push_back(e);
        gph[e].push_back(s);
    }
    sort(a + 1, a + n + 1);
    for(int i = 1; i <= n; i++) w[a[i].second] = i;
    disj.init(n);
    for(int i = 1; i <= n; i++){
        int x = a[i].second;
        disj.activate(x, 1);
        for(auto &y : gph[x]){
            if(w[y] < w[x]) disj.uni(y, x);
        }
        data[0][i] = disj.query();
    }
    disj.init(n);
    for(int i = n; i >= 1; i--){
        int x = a[i].second;
        disj.activate(x, 1);
        for(auto &y : gph[x]){
            if(w[y] > w[x]) disj.uni(y, x);
        }
        data[1][i] = disj.query();
    }
    for(int i = 1; i < n; i++){
        if(a[i].first != a[i + 1].first){
            int delta1 = data[0][i].first - data[1][i+1].second;
            int delta2 = data[1][i+1].first - data[0][i].second;
            if(delta1 >= -1 && delta2 >= -1){
                cout << a[i].first << endl;
                return 0;
            }
        }
    }
    puts("-1");
}
