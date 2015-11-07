#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;

vector<int> graph[100005];

int n, inp[100005], a[100005];
int sz[100005], piv;

int dfs(int x, int par){
    int num = piv++;
    a[num] = inp[x];
    sz[num] = 1;
    for (int i=0; i<graph[x].size(); i++) {
        if(graph[x][i] == par) continue;
        sz[num] += dfs(graph[x][i],x);
    }
    return sz[num];
}

int dpl[100005], dpu[100005], idx[100005];
int ret;

bool cmp(int p, int q){return a[p] < a[q];}

struct rmq{
    int lim, tree[263000];
    void init(int n){
        memset(tree,0,sizeof(tree));
        for(lim = 1; lim <= n; lim <<= 1);
    }
    void add(int x, int v){
        x += lim;
        tree[x] = max(tree[x],v);
        while(x > 1){
            x >>= 1;
            tree[x] = max(tree[2*x],tree[2*x+1]);
        }
    }
    int q(int s, int e){
        s += lim;
        e += lim;
        int r = 0;
        while(s < e){
            if(s%2 == 1) r = max(r,tree[s++]);
            if(e%2 == 0) r = max(r,tree[e--]);
            s >>= 1;
            e >>= 1;
        }
        if(s == e) r = max(r,tree[s]);
        return r;
    }
}rmq,rmq2;

void make_dp(){
    rmq.init(n);
    for (int i=n-1; i>=0; i--) {
        int e = i;
        while (e >= 0 && a[idx[e]] == a[idx[i]]) e--;
        for (int j=e+1; j<=i; j++) {
            dpu[idx[j]] = rmq.q(idx[j] + 1, idx[j] + sz[idx[j]] - 1) + 1;
            ret = max(ret,dpu[idx[j]]);
        }
        for (int j=e+1; j<=i; j++) {
            rmq.add(idx[j],dpu[idx[j]]);
        }
        i = e+1;
    }
    rmq2.init(n);
    for (int i=0; i<n; i++) {
        int e = i;
        while(e < n && a[idx[e]] == a[idx[i]]) e++;
        for (int j=i; j<e; j++) {
            dpl[idx[j]] = rmq2.q(idx[j] + 1, idx[j] + sz[idx[j]] - 1) + 1;
            ret = max(ret,dpl[idx[j]]);
        }
        for (int j=i; j<e; j++) {
            rmq2.add(idx[j],dpl[idx[j]]);
        }
        i = e-1;
    }
}

void solve1(){
    rmq.init(n);
    for (int i=n-1; i>=0; i--) {
        int e = i;
        while (e >= 0 && a[idx[e]] == a[idx[i]]) e--;
        for (int j=e+1; j<=i; j++) {
            ret = max(ret,rmq.q(idx[j] + sz[idx[j]], n-1) + dpl[idx[j]]);
        }
        for (int j=e+1; j<=i; j++) {
            rmq.add(idx[j],dpu[idx[j]]);
        }
        i = e+1;
    }
    rmq2.init(n);
    for (int i=0; i<n; i++) {
        int e = i;
        while(e < n && a[idx[e]] == a[idx[i]]) e++;
        for (int j=i; j<e; j++) {
            ret = max(ret,rmq2.q(idx[j] + sz[idx[j]], n-1) + dpu[idx[j]]);
        }
        for (int j=i; j<e; j++) {
            rmq2.add(idx[j],dpl[idx[j]]);
        }
        i = e-1;
    }
}

vector<int> st_min[100005], st_max[100005];

void solve2(){
    rmq.init(n);
    for (int i=n-1; i>=0; i--) {
        int e = i;
        while (e >= 0 && a[idx[e]] == a[idx[i]]) e--;
        for (int j=e+1; j<=i; j++) {
            int p = idx[j];
            for (int k=p+1; k<p+sz[p]; ) {
                st_max[p].push_back(rmq.q(k,k+sz[k]-1));
                k += sz[k];
            }
        }
        for (int j=e+1; j<=i; j++) {
            rmq.add(idx[j],dpu[idx[j]]);
        }
        i = e+1;
    }
    rmq2.init(n);
    for (int i=0; i<n; i++) {
        int e = i;
        while(e < n && a[idx[e]] == a[idx[i]]) e++;
        for (int j=i; j<e; j++) {
            int p = idx[j];
            for (int k=p+1; k<p+sz[p]; ) {
                st_min[p].push_back(rmq2.q(k,k+sz[k]-1));
                k += sz[k];
            }
        }
        for (int j=i; j<e; j++) {
            rmq2.add(idx[j],dpl[idx[j]]);
        }
        i = e-1;
    }
    for (int i=0; i<n; i++) {
        vector<int> suff_mx;
        st_min[i].push_back(0);
        st_max[i].push_back(0);
        suff_mx.resize(st_min[i].size());
        for (int j=(int)suff_mx.size()-2; j>=0; j--) {
            suff_mx[j] = max(suff_mx[j+1],st_min[i][j]);
        }
        int pref = 0;
        for (int j=0; j<st_max[i].size(); j++) {
            if(j+1 < st_max[i].size()) ret = max(ret,max(suff_mx[j+1],pref) + 1 + st_max[i][j]);
            else ret = max(ret,1 + st_max[i][j] + pref);
            pref = max(pref,st_min[i][j]);
        }
    }
}

void input(){
    scanf("%d",&n);
    for (int i=1; i<=n; i++) {
        scanf("%d",&inp[i]);
        idx[i] = i;
    }
    for (int i=0; i<n-1; i++) {
        int x,y;
        scanf("%d %d",&x,&y);
        graph[x].push_back(y);
        graph[y].push_back(x);
    }
    dfs(1,0);
    sort(idx,idx+n,cmp);
}

int main(){
    input();
    make_dp();
    solve1();
    solve2();
    printf("%d",ret);
}