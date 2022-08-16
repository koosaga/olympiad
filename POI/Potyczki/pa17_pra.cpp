#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<int, int> pi;
const int MAXN = 1050000;

struct node{
    int l, r;
    int val;
}tree[25 * MAXN];

int root[MAXN];
int piv;

vector<int> nodes[21];
int n, q, m = (1<<19);

int newnode(int d){
    nodes[d].push_back(++piv);
    return piv;
}

void init(int s, int e, int p, int d, int *a){
    if(s == e){
        tree[p].val = a[s];
        return;
    }
    if(s == e) return;
    int m = (s+e)/2;
    tree[p].l = newnode(d + 1);
    tree[p].r = newnode(d + 1);
    init(s, m, tree[p].l, d + 1, a);
    init(m+1, e, tree[p].r, d + 1, a);
}

void upd(int pos, int val, int s, int e, int prv, int nxt, int d){
    if(s == e){
        tree[nxt].val = val;
        return;
    }
    int m = (s+e)/2;
    if(pos <= m){
        tree[nxt].l = newnode(d+1);
        tree[nxt].r = tree[prv].r;
        upd(pos, val, s, m, tree[prv].l, tree[nxt].l, d+1);
    }
    else{
        tree[nxt].l = tree[prv].l;
        tree[nxt].r = newnode(d+1);
        upd(pos, val, m+1, e, tree[prv].r, tree[nxt].r, d+1);
    }
}

pi sons(int v){
    return pi(tree[tree[v].l].val, tree[tree[v].r].val);
}

int cnt[MAXN * 3];
int renpos[MAXN * 3];

void count_sort(int d){
    vector<pi> nxt;
    for(auto &i : nodes[d]){
        nxt.push_back(sons(i));
    }
    for(auto &i : nxt){
        cnt[i.second]++;
    }
    for(int i=1; i<3*MAXN; i++){
        cnt[i] += cnt[i-1];
    }
    for(int i=(int)nxt.size()-1; i>=0; i--){
        renpos[--cnt[nxt[i].second]] = nodes[d][i];
    }
    for(int i=0; i<nodes[d].size(); i++){
        nodes[d][i] = renpos[i];
    }
    memset(cnt, 0, sizeof(cnt));
    nxt.clear();
    for(auto &i : nodes[d]){
        nxt.push_back(sons(i));
    }
    for(auto &i : nxt){
        cnt[i.first]++;
    }
    for(int i=1; i<3*MAXN; i++){
        cnt[i] += cnt[i-1];
    }
    for(int i=(int)nodes[d].size()-1; i>=0; i--){
        int v = nodes[d][i];
        renpos[--cnt[nxt[i].first]] = v;
    }
    for(int i=0; i<nodes[d].size(); i++){
        nodes[d][i] = renpos[i];
    }
    memset(cnt, 0, sizeof(cnt));
}

int a[MAXN];
pi up[MAXN];
vector<int> crd;

int main(){
    scanf("%d %d",&n,&q);
    for(int i=0; i<n; i++){
        scanf("%d",&a[i]);
        crd.push_back(a[i]);
    }
    for(int i=1; i<q; i++){
        scanf("%d %d",&up[i].first,&up[i].second);
        up[i].first--;
        crd.push_back(up[i].second);
    }
    crd.push_back(-1);
    sort(all(crd));
    crd.resize(unique(all(crd)) - crd.begin());
    for(int i=0; i<n; i++){
        a[i] = lower_bound(all(crd), a[i]) - crd.begin();
    }
    for(int i=1; i<q; i++){
        up[i].second = lower_bound(all(crd), up[i].second) - crd.begin();
    }
    root[0] = newnode(0);
    init(0, m-1, root[0], 0, a);
    for(int i=1; i<q; i++){
        root[i] = newnode(0);
        upd(up[i].first, up[i].second, 0, m-1, root[i-1], root[i], 0);
    }
    for(int i=18; i>=0; i--){
        count_sort(i);
        int cnt = 0;
        for(int j=0; j<nodes[i].size(); ){
            int e = j;
            while(e < nodes[i].size() && sons(nodes[i][j]) == sons(nodes[i][e])){
                tree[nodes[i][e++]].val = cnt;
            }
            cnt++;
            j = e;
        }
    }
    vector<int> ans;
    for(int i=0; i<q; i++) ans.push_back(i);
    sort(ans.begin(), ans.end(), [&](const int &a, const int &b){
        return pi(tree[root[a]].val, a) < pi(tree[root[b]].val, b);
    });
    for(auto &i : ans) printf("%d ", i + 1);
}

