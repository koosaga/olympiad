#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
 
int n,x1[10005], x2[10005], y1[10005], y2[10005];
vector<int> vx,vy;
 
struct q{int piv,s,e,x;}a[20005];
bool operator<(q a, q b){return a.piv < b.piv;}
 
struct seg{
    int tree[140000], tree2[140000];
    void add(int s, int e, int x, int ps, int pe, int p){
        if(e <= ps || pe <= s) return;
        if(s <= ps && pe <= e){
            tree2[p] += x;
            if(tree2[p] == 0){
                if(ps != pe) tree[p] = tree[2*p] + tree[2*p+1];
            }
            else tree[p] = vx[pe] - vx[ps];
        }
        else{
            int pm = (ps+pe)/2;
            add(s,e,x,ps,pm,2*p);
            add(s,e,x,pm,pe,2*p+1);
            if(tree2[p] == 0 && ps != pe) tree[p] = tree[2*p] + tree[2*p+1];
        }
    }
    int q(){return tree[1];}
}seg;
 
int main(){
    scanf("%d",&n);
    for (int i=0; i<n; i++) {
        scanf("%d %d %d %d",&x1[i],&y1[i],&x2[i],&y2[i]);
        vx.push_back(x1[i]);
        vx.push_back(x2[i]);
        vy.push_back(y1[i]);
        vy.push_back(y2[i]);
    }
    sort(vx.begin(),vx.end());
    sort(vy.begin(),vy.end());
    vx.resize(unique(vx.begin(),vx.end()) - vx.begin());
    vy.resize(unique(vy.begin(),vy.end()) - vy.begin());
    for (int i=0; i<n; i++) {
        x1[i] = (int)(lower_bound(vx.begin(),vx.end(),x1[i]) - vx.begin());
        x2[i] = (int)(lower_bound(vx.begin(),vx.end(),x2[i]) - vx.begin());
        y1[i] = (int)(lower_bound(vy.begin(),vy.end(),y1[i]) - vy.begin());
        y2[i] = (int)(lower_bound(vy.begin(),vy.end(),y2[i]) - vy.begin());
        a[2*i] = {y1[i],x1[i],x2[i],1};
        a[2*i+1] = {y2[i],x1[i],x2[i],-1};
    }
    sort(a,a+2*n);
    long long res = 0;
    for (int i=0; i<2*n;) {
        int e = i;
        while (a[i].piv == a[e].piv) e++;
        for (int j=i; j<e; j++) {
            seg.add(a[j].s,a[j].e,a[j].x,0,2*n-1,1);
        }
        if(a[i].piv + 1 != vy.size()) res += 1ll * seg.q() * (vy[a[i].piv+1] - vy[a[i].piv]);
        i = e;
    }
    printf("%lld",res);
}