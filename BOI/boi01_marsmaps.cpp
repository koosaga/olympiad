#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
 
int n, sx[10005], ex[10005], sy[10005], ey[10005];
vector<int> vx,vy;
 
struct q{int piv,s,e,x;}a[20005];
bool operator<(q a, q b){return a.piv < b.piv;}
 
struct seg{
    int tree[66000], tree2[66000];
    void add(int s, int e, int x, int ps, int pe, int p){
        if(e < ps || pe < s) return;
        if(s <= ps && pe <= e){
            tree2[p] += x;
            if(tree2[p] == 0){
                if(ps != pe) tree[p] = tree[2*p] + tree[2*p+1];
                else tree[p] = 0;   
            }
            else tree[p] = vx[pe+1] - vx[ps];
        }
        else{
            int pm = (ps+pe)/2;
            add(s,e,x,ps,pm,2*p);
            add(s,e,x,pm+1,pe,2*p+1);
            if(tree2[p] == 0) tree[p] = tree[2*p] + tree[2*p+1];
        }
    }
    int q(){return tree[1];}
}seg;
 
int main(){
    scanf("%d",&n);
    for (int i=0; i<n; i++) {
        scanf("%d %d %d %d",&sx[i],&sy[i],&ex[i],&ey[i]);
        vx.push_back(sx[i]);
        vx.push_back(ex[i]);
        vy.push_back(sy[i]);
        vy.push_back(ey[i]);
    }
    sort(vx.begin(),vx.end());
    sort(vy.begin(),vy.end());
    vx.resize(unique(vx.begin(),vx.end()) - vx.begin());
    vy.resize(unique(vy.begin(),vy.end()) - vy.begin());
    for (int i=0; i<n; i++) {
        sx[i] = (int)(lower_bound(vx.begin(),vx.end(),sx[i]) - vx.begin());
        ex[i] = (int)(lower_bound(vx.begin(),vx.end(),ex[i]) - vx.begin());
        sy[i] = (int)(lower_bound(vy.begin(),vy.end(),sy[i]) - vy.begin());
        ey[i] = (int)(lower_bound(vy.begin(),vy.end(),ey[i]) - vy.begin());
        a[2*i] = {sy[i],sx[i],ex[i],1};
        a[2*i+1] = {ey[i],sx[i],ex[i],-1};
    }
    sort(a,a+2*n);
    long long res = 0;
    for (int i=0; i<2*n;) {
        int e = i;
        while (a[i].piv == a[e].piv) e++;
        for (int j=i; j<e; j++) {
            seg.add(a[j].s,a[j].e-1,a[j].x,0,2*n-1,1);
        }
        if(a[i].piv + 1 != vy.size()) res += 1ll * seg.q() * (vy[a[i].piv+1] - vy[a[i].piv]);
        i = e;
    }
    printf("%lld",res);
}