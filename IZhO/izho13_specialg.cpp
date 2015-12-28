#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <limits.h>
#include <stack>
#include <queue>
#include <map>
#include <set>
#include <algorithm>
#include <string>
#include <functional>
#include <vector>
#include <numeric>
#include <deque>
#include <bitset>
#include <iostream>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<int,int> pi;
 
struct disj{
    int pa[100005];
    void init(int n){
        for(int i=0; i<=n; i++) pa[i] = i;
    }
    int find(int x){
        return pa[x] = (pa[x] == x ? x : find(pa[x]));
    }
    bool uni(int p, int q){
        p = find(p), q = find(q);
        if(p == q) return 0;
        pa[q] = p; return 1;
    }
}disj;
 
struct query{
    int t, a, b;
}q[100005];
 
int n, m, a[100005], kill[100005];
vector<int> rev[100005];
vector<int> bit[100005];
 
void add(vector<int> &tree, int p){
    while(p < tree.size()){
        tree[p]++;
        p += p & -p;
    }
}
 
int sum(vector<int> &tree, int p){
    int r = 0;
    while(p){
        r += tree[p];
        p -= p & -p;
    }
    return r;
}
 
int indeg[100005];
int cyclab[100005], cycidx[100005], cycsz[100005], cycp;
int treein[100005], treeout[100005], root[100005], dep[100005], treep;
 
void dfs(int x, int r){
    treein[x] = ++treep;
    root[x] = r;
    for(auto &i : rev[x]){
        if(cyclab[i]) continue;
        dep[i] = dep[x] + 1;
        dfs(i, r);
    }
    treeout[x] = ++treep;
}
 
void proc_tree(){
    for(int i=1; i<=n; i++){
        if(a[i] == 0 || cyclab[i]){
            dfs(i, i);
        }
    }
}
 
queue<int> que;
 
void proc_cycle(){
    for(int i=1; i<=n; i++){
        if(indeg[i] == 0) que.push(i);
    }
    while(!que.empty()){
        int x = que.front();
        que.pop();
        if(!a[x]) continue;
        indeg[a[x]]--;
        if(indeg[a[x]] == 0) que.push(a[x]);
    }
    for(int i=1; i<=n; i++){
        if(indeg[i] && !cyclab[i]){
            int p = i;
            cycp++;
            while(!cyclab[p]){
                cyclab[p] = cycp;
                cycidx[p] = ++cycsz[cycp];
                p = a[p];
            }
            bit[cycp].resize(cycsz[cycp] + 1);
            for(int i=0; i<cycsz[cycp]; i++){
                if(!kill[p]) add(bit[cycp], cycidx[p]);
                p = a[p];
            }
        }
    }
}
 
inline bool inside(int a, int b){
    return treein[a] <= treein[b] && treeout[b] <= treeout[a];
}
 
int solve(int p, int q){
    if(cyclab[p] && cyclab[q]){
        int pos = cyclab[p];
        if(cycidx[p] <= cycidx[q]){
            int ret = sum(bit[pos], cycidx[q] - 1) - sum(bit[pos], cycidx[p] - 1);
            if(ret != cycidx[q] - cycidx[p]) return -1;
            return ret;
        }
        else{
            int ret = sum(bit[pos], cycsz[pos]) - sum(bit[pos], cycidx[p] - 1);
            ret += sum(bit[pos], cycidx[q] - 1);
            if(ret != cycsz[pos] + cycidx[q] - cycidx[p]){
                return -1;
            }
            return ret;
        }
    }
    if(cyclab[p] && !cyclab[q]){
        return -1;
    }
    if(!cyclab[p] && cyclab[q]){
        int t = solve(root[p], q);
        if(t == -1) return -1;
        return dep[p] + t;
    }
    if(inside(q, p)){
        return dep[p] - dep[q];
    }
    return -1;
}
 
int main(){
    cin >> n;
    for(int i=1; i<=n; i++){
        scanf("%d",&a[i]);
        kill[i] = (a[i] == 0);
        if(a[i]){
            rev[a[i]].push_back(i);
            indeg[a[i]]++;
        }
    }
    cin >> m;
    for(int i=0; i<m; i++){
        scanf("%d",&q[i].t);
        if(q[i].t == 1){
            scanf("%d",&q[i].a);
            kill[q[i].a] = 1;
        }
        else{
            scanf("%d %d",&q[i].a, &q[i].b);
        }
    }
    reverse(q, q+m);
    proc_cycle();
    proc_tree();
    disj.init(n);
    for(int i=1; i<=n; i++){
        if(!kill[i]) disj.uni(i, a[i]);
    }
    vector<int> stk;
    for(int i=0; i<m; i++){
        if(q[i].t == 1){
            kill[q[i].a] = 0;
            if(cyclab[q[i].a]){
                add(bit[cyclab[q[i].a]], cycidx[q[i].a]);
            }
            disj.uni(q[i].a, a[q[i].a]);
        }
        else{
            if(disj.find(q[i].a) != disj.find(q[i].b)) stk.push_back(-1);
            else stk.push_back(solve(q[i].a, q[i].b));
        }
    }
    while(!stk.empty()){
        printf("%d\n",stk.back());
        stk.pop_back();
    }
}