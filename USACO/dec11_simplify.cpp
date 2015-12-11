#include <cstdio>
#include <algorithm>
#include <set>
#include <utility>
using namespace std;
typedef pair<int,int> pi;
 
long long mod = 1e9 + 7;
 
struct edge{int s,e,x;}a[100005];
bool cmp(edge a, edge b){return a.x < b.x;}
 
struct uft{
    int pa[50005], r[50005];
    void init(int n){
        for(int i=0; i<=n; i++){
            pa[i] = i;
        }
    }
    int find(int x){
        if(pa[x] == x) return x;
        return pa[x] = find(pa[x]);
    }
    int diff(int s, int e){
        return find(s) != find(e);
    }
    void uni(int s, int e){
        s = find(s);
        e = find(e);
        if(r[s] < r[e]) pa[e] = s;
        else pa[s] = e;
        if(r[s] == r[e]) r[s]++;
    }
}uft;
 
int n,m;
 
int main(){
    scanf("%d %d",&n,&m);
    for (int i=0; i<m; i++) {
        scanf("%d %d %d",&a[i].s,&a[i].e,&a[i].x);
    }
    uft.init(n);
    sort(a,a+m,cmp);
    long long cnt = 1, len = 0;
    for (int i=0; i<m; i++) {
        int end = i;
        while (a[end].x == a[i].x) end++;
        end--;
        set<pi> s;
        int num = 0;
        for (int j=i; j<=end; j++) {
            a[j].s = uft.find(a[j].s);
            a[j].e = uft.find(a[j].e);
            if(a[j].s > a[j].e) swap(a[j].s,a[j].e);
            if(a[j].s != a[j].e) s.insert(pi(a[j].s,a[j].e)), num++;
        }
        int xcnt = 0;
        for (int j=i; j<=end; j++) {
            if(uft.diff(a[j].s,a[j].e)){
                xcnt++;
                uft.uni(a[j].s,a[j].e);
            }
        }
        len += xcnt * a[i].x;
        if(num == 2){
            if(xcnt == 1) cnt *= 2;
        }
        if(num == 3){
            if(xcnt == 2){
                if(s.size() == 3) cnt *= 3;
                else cnt *= 2;
            }
            else if(xcnt == 1) cnt *= 3;
        }
        cnt %= mod;
        i = end;
    }
    printf("%lld %lld",len,cnt);
}