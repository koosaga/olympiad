#include<bits/stdc++.h>
using namespace std;
int N, M, K;

struct strongly_connected{
    vector<int> gph[4040404];
    vector<int> rev[4040404];
    int comp[4040404], p;
    bool vis[4040404];
    vector<int> dfn;
    void add_edge(int s, int e){
    	gph[s].push_back(e);
    	rev[e].push_back(s);
	}
	void dfs(int x){
		if(vis[x]) return;
		vis[x] = 1;
		for(auto &i : gph[x]) dfs(i);
		dfn.push_back(x);
	}
	void rdfs(int x, int p){
		if(comp[x]) return;
		comp[x] = p;
		for(auto &i : rev[x]) rdfs(i, p);
	}
	void get_scc(int n){
		for(int i=0; i<n; i++){
			if(!vis[i]) dfs(i);
		}
		reverse(dfn.begin(), dfn.end());
		for(auto &i : dfn){
			if(!comp[i]) rdfs(i, ++p);
		}
	}
};

namespace sat
{
    strongly_connected scc;
    int n;
    void init(int _n){ n = _n;}
    int NOT(int x){ return x >= n ? (x - n) : (x + n); }
    void add_edge(int x, int y)
    {
        if((x>>31)&1) x = (~x)+n;
        if((y>>31)&1) y = (~y)+n;
        scc.add_edge(NOT(x), y);
        scc.add_edge(NOT(y), x);
    }
    bool satisfy(vector<bool> &res)
    {
        res.resize(n);
        scc.get_scc(2*n);
        for(int i=0; i<n; ++i)
        {
            if(scc.comp[i] == scc.comp[NOT(i)]) return 0;
            if(scc.comp[i] < scc.comp[NOT(i)]) res[i] = 0;
            else res[i] = 1;
        }
        return 1;
    }
}
const int MAXN = 1010101;
int incl[MAXN];
int main()
{
    scanf("%d%d%d", &N, &M, &K);
    sat::init(2*N+2);
    for(int i=0; i<M; ++i)
    {
        int u, v; scanf("%d%d", &u, &v);
        sat::add_edge(u, v);
    }
    int tp = N;
    for(int i=0; i<K; ++i)
    {
        int T; vector<int> v;
        scanf("%d", &T);
        v.resize(T);
        for(int j=0; j<T; ++j)
        {
            scanf("%d", &v[j]);
            incl[v[j]] = i;
        }
        for(int i=0; i<v.size(); ++i)
        {
            ++tp;
            sat::add_edge(~v[i], ~tp);
            if(i==v.size()-1) break;
            sat::add_edge(tp+1, ~tp);
            sat::add_edge(tp+1, ~v[i]);
        }
        /*
        for(int j=1; j<T; j*=2)
        {
            int targ = ++tp;
            for(int i=0; i<v.size(); ++i)
            {
                int x = v[i];
                if(i&j) sat::add_edge(~x, targ);
                else sat::add_edge(~x, ~targ);
                
                
            }
        }
        */
    }
    vector<bool> res;
    if(!sat::satisfy(res)){
    	puts("NIE");
    	return 0;
	}
    vector<int> ans(K);
    for(int i=1; i<=N; ++i)
    {
        //printf("%d", (int)res[i]);
        if(res[i])
            ans[incl[i]] = i;
    }
    //puts("");
    puts("TAK");
    for(int i=0; i<K; ++i)
        printf("%d ", ans[i]);
    puts("");
    return 0;    
}

