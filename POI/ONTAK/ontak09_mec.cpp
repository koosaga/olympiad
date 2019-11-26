#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;
const int mod = 1e9 + 7;
 
struct pnt{
    int x, y, idx;
    bool operator<(const pnt &p)const{
        return pi(x, y) < pi(p.x, p.y);
    }
}a[2005];
 
struct line{
    int dx, dy, i1, i2;
};
 
vector<line> v;
int n, rev[2005];
lint p, q;
 
lint ccw(pnt a, pnt b, pnt c){
    int dx1 = b.x - a.x;
    int dy1 = b.y - a.y;
    int dx2 = c.x - a.x;
    int dy2 = c.y - a.y;
    lint dap = abs(1ll * dx1 * dy2 - 1ll * dy1 * dx2);
    if(dap == 0) dap = 9e18;
    return dap;
}
 
int main(){
    cin >> n;
    for(int i=0; i<n; i++){
        cin >> a[i].x >> a[i].y;
    }
    sort(a, a+n);
    for(int i=0; i<n; i++){
        a[i].idx = i;
        rev[i] = i;
    }
    for(int i=0; i<n; i++){
        for(int j=i+1; j<n; j++){
            v.push_back({a[j].x - a[i].x, a[j].y - a[i].y, a[i].idx, a[j].idx});
        }
    }
    sort(v.begin(), v.end(), [&](const line &a, const line &b){
        lint cw = 1ll * a.dx * b.dy - 1ll * b.dx * a.dy;
        if(cw != 0) return cw > 0;
        return pi(a.i1, a.i2) < pi(b.i1, b.i2);
    });
    lint ret = 9e18;
    for(int i=0; i<v.size(); i++){
        int c1 = rev[v[i].i1], c2 = rev[v[i].i2];
        if(c1 > c2) swap(c1, c2);
        if(c2 < n - 1) ret = min(ret, ccw(a[c1], a[c2], a[c2 + 1]));
        if(c1 > 0) ret = min(ret, ccw(a[c1], a[c2], a[c1 - 1]));
        swap(a[c1], a[c2]);
        swap(rev[v[i].i1], rev[v[i].i2]);
    }
    cout << ret;
}
