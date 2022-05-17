#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
using pi = pair<lint, lint>;

struct strongly_connected{
    vector<vector<int>> gph;

    void init(int n){
        gph.clear();
        gph.resize(n);
    }

    void add_edge(int s, int e){
        gph[s].push_back(e);
    }

    vector<int> val, comp, z, cont;
    int Time, ncomps;
    template<class G, class F> int dfs(int j, G& g, F f) {
        int low = val[j] = ++Time, x; z.push_back(j);
        for(auto e : g[j]) if (comp[e] < 0)
            low = min(low, val[e] ?: dfs(e,g,f));

        if (low == val[j]) {
            do {
                x = z.back(); z.pop_back();
                comp[x] = ncomps;
                cont.push_back(x);
            } while (x != j);
            f(cont); cont.clear();
            ncomps++;
        }
        return val[j] = low;
    }
    template<class G, class F> void scc(G& g, F f) {
        int n = sz(g);
        val.assign(n, 0); comp.assign(n, -1);
        Time = ncomps = 0;
        for(int i=0; i<n; i++) if (comp[i] < 0) dfs(i, g, f);
    }

    int piv;
    void get_scc(int n){
        scc(gph, [&](vector<int> &v){});
        for(int i=0; i<n; i++){
            comp[i] = ncomps - comp[i];
        }
        piv = ncomps;
    }
}scc;

int main(){
        int n, m;
        scanf("%d %d",&n,&m);
        scc.init(n);
        vector<pi> v;
        for(int i=0; i<m; i++){
            int s, e; scanf("%d %d",&s,&e);
            swap(s, e);
            scc.add_edge(s-1, e-1);
            v.emplace_back(s-1, e-1);
        }
        scc.get_scc(n);
        vector<int> chk(n + 1);
        for(auto &[x, y] : v){
            if(scc.comp[x] != scc.comp[y]) chk[scc.comp[x]] = 1;
        }
    set<int> s;
    vector<int> ans;
        for(int i=0; i<n; i++){
            if(chk[scc.comp[i]] == 0){
                s.insert(scc.comp[i]);
                ans.push_back(i);
            }
        }
    if(sz(s) > 1) ans.clear();
    printf("%d\n", sz(ans));
    for(auto &i : ans) printf("%d ", i+1);
    
}
