#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> pi;

vector<int> gph[20005];

void add_edge(int s, int e){
    gph[s].push_back(e);
    gph[e].push_back(s);
}

void del_edge(int s, int e){
    gph[s].erase(find(gph[s].begin(), gph[s].end(), e));
    gph[e].erase(find(gph[e].begin(), gph[e].end(), s));
}

void dfs(int x, int p, vector<int> &v){
    v.push_back(x);
    for(auto &i : gph[x]){
        if(i == p) continue;
        dfs(i, x, v);
    }
}

vector<int> solve(int a, int b, int c){
    a--;
    add_edge(0, 1);
    int p = 2;
    while(b){
        add_edge(p-2, p);
        p++;
        b--;
    }
    add_edge(p, p+1);
    a--;
    p--;
    int chk[3] = {0, 1, 1};
    while(c){
        add_edge(p, p+3);
        rotate(chk, chk+1, chk+3);
        p++;
        c--;
    }
    if(chk[0] && chk[1]){
        del_edge(0, 1);
        del_edge(0, 2);
        del_edge(1, 3);
        add_edge(2, 3);
        add_edge(p, p+2);
        add_edge(p+1, p+3);
        b--;
        p += 4;
    }
    else{
        add_edge(p, p+1);
        a--;
        p += 3;
    }
    while(a){
        add_edge(p, p-1);
        p++;
        a--;
    }
    for(int i=20000; i>=0; i--){
        if(gph[i].size() == 1){
            vector<int> v;
            dfs(i, -1, v);
            return v;
        }
    }
    assert(0);
}

int main(){
    int t;
    cin >> t;
    while(t--){
        for(int i=0; i<20005; i++) gph[i].clear();
        int a, b, c;
        cin >> a >> b >> c;
        vector<int> v = solve(a, b, c);
        assert(v.size() == a + b + c + 1);
        int l = *max_element(v.begin(), v.end());
        assert(v[0] == l);
        for(auto &i : v) printf("%d ", l - i);
        puts("");
    }
}
