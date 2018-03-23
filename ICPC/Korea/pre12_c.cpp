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
#include <utility>
#include <bitset>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<int, int> pi;

int n;

struct disj{
    int pa[10006];
    void init(int n){
        iota(pa, pa + n + 1, 0);
    }
    int find(int x){
        return pa[x] = (pa[x] == x ? x : find(pa[x]));
    }
    bool uni(int p, int q){
        p = find(p);
        q = find(q);
        if(p == q) return 0;
        pa[q] = p; return 1;
    }
}disj;

struct edg{int x, s, e;};

struct fff{ 
    int first, second, idx; 
    bool operator<(const fff &f)const{return pi(first, second) < pi(f.first, f.second); }
};

fff a[10005];

bool solve(){
    vector<edg> vx, vy;
    scanf("%d",&n);
    disj.init(n);
    for(int i=0; i<n; i++){
        scanf("%d %d",&a[i].first,&a[i].second);
        a[i].idx = i;
    }
    sort(a, a+n);
    for(int i=0; i<n; i++){
        int e = i;
        while(e < n && a[e].first == a[i].first) e++;
        if(e%2 != i%2) return 0;
        for(int j=i; j<e; j+=2){
            disj.uni(a[j].idx, a[j+1].idx);
            vx.push_back({a[j].first, a[j].second, a[j+1].second});
        }
        i = e-1;
    }
    for(int i=0; i<n; i++){
        swap(a[i].first, a[i].second);
    }
    sort(a, a+n);
    for(int i=0; i<n; i++){
        int e = i;
        while(e < n && a[e].first == a[i].first) e++;
        if(e%2 != i%2) return 0;
        for(int j=i; j<e; j+=2){
            vy.push_back({a[j].first, a[j].second, a[j+1].second});
            disj.uni(a[j].idx, a[j+1].idx);
        }
        i = e-1;
    }
    int cross = 0;
    for(auto &i : vx){
        for(auto &j : vy){
            if((i.x < j.e && i.x > j.s) && (j.x < i.e && j.x > i.s)) return 0;
            if((i.x == j.e || i.x == j.s) && (j.x == i.e || j.x == i.s)) cross++;
        }
    }
    for(int i=1; i<n; i++){
        if(disj.uni(0, i)) return 0;
    }
    return cross == n;
}

int main(){
    int t;
    scanf("%d",&t);
    while(t--){
        puts(solve() ? "YES" : "NO");
    }
}

