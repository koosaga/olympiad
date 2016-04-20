#include <cstdio>
#include <cstring>
#include <algorithm>
#include <set>
#include <queue>
using namespace std;

struct pt{int x,y;}pos[200005];
int cmp1(pt a, pt b){return a.x<b.x;}
int cmp2(pt a, pt b){return a.y<b.y;}

struct x{int key, sub, type;};
bool operator<(x a, x b){return a.key == b.key ? (a.type < b.type) : (a.key > b.key);}

int a[200005],n;

int lim, tree[270000];

void add(int x){
    while (x <= lim) {
        tree[x]++;
        x += x & -x;
    }
}
int sum(int x){
    int res = 0;
    while (x) {
        res += tree[x];
        x -= x & -x;
    }
    return res;
}

long long f(int s, int e){
    long long res = 0;
    if(e - s < 400){
        for (int i=s; i<=e; i++) {
            int upper=1e9;
            for (int j=i+1; j<=e; j++) {
                if(a[i] < a[j] && a[j] < upper){
                    upper = a[j];
                    res++;
                }
            }
        }
        return res;
    }
    int m = (s+e)/2;
    res = f(s,m) + f(m+1,e);
    
    memset(tree,0,sizeof(tree));
    set<int> s_left, s_right;
    set<int> ::iterator it;
    priority_queue<x> pq;
    int lim;
    
    for (int i=m; i>=s; i--) {
        it = s_left.upper_bound(a[i]);
        if(it == s_left.end()) lim = n+1;
        else lim = *it - 1;
        s_left.insert(a[i]);
        pq.push({a[i],lim,0});
    }
    
    for (int i=m+1; i<=e; i++) {
        it = s_right.upper_bound(a[i]);
        if(it == s_right.begin()) lim = -1;
        else lim = *--it;
        pq.push({lim,a[i],1});
        s_right.insert(a[i]);
    }
    for (int i=s; i<=e; i++) {
        x c = pq.top();
        pq.pop();
        if(c.type) add(c.sub);
        else res += sum(c.sub) - sum(c.key - 1);
    }
    return res;
}

int main(){
    scanf("%d",&n);
    for (int i=0; i<n; i++) {
        scanf("%d %d",&pos[i].x,&pos[i].y);
    }
    sort(pos,pos+n,cmp2);
    for (int i=0; i<n; i++) {
        pos[i].y = i+1;
    }
    sort(pos,pos+n,cmp1);
    for (int i=0; i<n; i++) {
        a[i] = pos[i].y;
    }
    for(lim = 1; lim <= n+1; lim <<= 1);
    long long r = f(0,n-1);
    printf("%lld",r);
}