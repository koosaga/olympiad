#include <cstdio>
#include <vector>
#include <algorithm>
#include <utility>
using namespace std;
typedef pair<int,int> pi;

vector<int> vx, vy;
int n;
pi a[300005];

vector<int> px[300005], py[300005];

int count_range(vector<int> &v, int s, int e){
    return (int)(lower_bound(v.begin(),v.end(),e+1) - lower_bound(v.begin(),v.end(),s));
}

void solve(){
    int sx, sy, ex, ey;
    scanf("%d %d %d %d",&sx,&sy,&ex,&ey);
    int pos = (int)(lower_bound(vx.begin(),vx.end(),sx) - vx.begin());
    int ret = 0;
    if(pos != vx.size() && vx[pos] == sx){
        ret += count_range(px[pos],sy+1,ey-1);
    }
    pos = (int)(lower_bound(vx.begin(),vx.end(),ex) - vx.begin());
    if(pos != vx.size() && vx[pos] == ex){
        ret += count_range(px[pos],sy+1,ey-1);
    }
    pos = (int)(lower_bound(vy.begin(),vy.end(),sy) - vy.begin());
    if(pos != vy.size() && vy[pos] == sy){
        ret += count_range(py[pos],sx,ex);
    }
    pos = (int)(lower_bound(vy.begin(),vy.end(),ey) - vy.begin());
    if(pos != vy.size() && vy[pos] == ey){
        ret += count_range(py[pos],sx,ex);
    }
    printf("%d\n",ret);
}

int main(){
    scanf("%d",&n);
    for (int i=0; i<n; i++) {
        scanf("%d %d",&a[i].first,&a[i].second);
        vx.push_back(a[i].first);
        vy.push_back(a[i].second);
    }
    vx.push_back(-1);
    vy.push_back(-1);
    sort(vx.begin(),vx.end());
    sort(vy.begin(),vy.end());
    vx.resize(unique(vx.begin(),vx.end()) - vx.begin());
    vy.resize(unique(vy.begin(),vy.end()) - vy.begin());
    for (int i=0; i<n; i++) {
        a[i].first = (int)(lower_bound(vx.begin(),vx.end(),a[i].first) - vx.begin());
        a[i].second = (int)(lower_bound(vy.begin(),vy.end(),a[i].second) - vy.begin());
        px[a[i].first].push_back(vy[a[i].second]);
        py[a[i].second].push_back(vx[a[i].first]);
    }
    for (int i=1; i<=n; i++) {
        sort(px[i].begin(),px[i].end());
        sort(py[i].begin(),py[i].end());
    }
    int q;
    scanf("%d",&q);
    while (q--) {
        solve();
    }
}
