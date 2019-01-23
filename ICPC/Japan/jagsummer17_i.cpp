#include <bits/stdc++.h>
using namespace std;
using pi = pair<int, int>;
using lint = long long;
using real_t = double;
const int mod = 1e9 + 7;
const int MAXN = 100005;
const int MAXT = 270000;

struct bit{
    lint tree[MAXN];
    void add(int x, int v){
        while(x < MAXN){
            tree[x] += v;
            x += x & -x;
        }
    }
    lint query(int x){
        lint ret = 0;
        while(x){
            ret += tree[x];
            x -= x & -x;
        }
        return ret;
    }
}bit1, bit2, bit;

struct item{
    int x, y, z;
    bool operator<(const item &i)const{
        return x < i.x;
    }
};
vector<item> v;

int n, c, b[MAXN], w[MAXN];
int cnt[MAXN];
int rev[MAXN];

void dnc(int s, int e){
    if(s == e) return;
    int m = (s+e)/2;
    dnc(s, m);
    dnc(m + 1, e);
    vector<pi> l, r;
    for(int i=s; i<=m; i++) l.emplace_back(v[i].y, v[i].z);
    for(int i=m+1; i<=e; i++) r.emplace_back(v[i].y, v[i].z);
    sort(l.begin(), l.end());
    sort(r.begin(), r.end());
    int ptr = 0;
    for(auto &i : l){
        while(ptr < r.size() && r[ptr].first <= i.first){
            bit.add(r[ptr++].second, 1);
        }
        cnt[rev[i.second]] += bit.query(n) - bit.query(i.second);
    }
    for(int i=0; i<ptr; i++) bit.add(r[i].second, -1);
    for(auto &i : l) swap(i.first, i.second);
    for(auto &i : r) swap(i.first, i.second);
    sort(l.begin(), l.end());
    sort(r.begin(), r.end());
    ptr = 0;
    for(auto &i : l){
        while(ptr < r.size() && r[ptr].first <= i.first){
            bit.add(r[ptr++].second, 1);
        }
        cnt[rev[i.first]] += bit.query(n) - bit.query(i.second);
    }
    for(int i=0; i<ptr; i++) bit.add(r[i].second, -1);
}

int main(){
    scanf("%d %d",&n,&c);
    for(int i=1; i<=n; i++){
        scanf("%d %d",&b[i],&w[i]);
    }
    lint ret = 0;
    for(int i=1; i<=n; i++){
        ret += w[i] * (bit1.query(n) - bit1.query(b[i]));
        ret += bit2.query(n) - bit2.query(b[i]);
        bit1.add(b[i], 1);
        bit2.add(b[i], w[i]);
    }
    for(int i=1; i<=n; i++){
        v.push_back({w[i], b[i], i});
    }
    sort(v.begin(), v.end());
    for(int i=0; i<n; i++){
        rev[v[i].z] = i;
    }
    dnc(0, n - 1);
    for(int i=0; i<v.size(); i++){
        ret += 1ll * (c - 1) * cnt[i] * v[i].x;
    }
    cout << ret << endl;
}
