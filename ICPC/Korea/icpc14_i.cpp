#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
typedef pair<int,int> pi;
 
pi a[100005];
int n;
 
vector<pi> v;
 
int trial2(int x){
    int maxv1 = 0, maxv2 = 0, minv1 = 2e9, minv2 = 2e9;
    for (int i=0; i<v.size(); i++) {
        if(v[i].first > x || v[i].second > x){
            maxv1 = max(maxv1,v[i].first);
            minv1 = min(minv1,v[i].first);
            maxv2 = max(maxv2,v[i].second);
            minv2 = min(minv2,v[i].second);
        }
    }
    return (maxv1 - minv1 <= x && maxv2 - minv2 <= x);
}
 
int trial(int x){
    v.clear();
    for (int i=0; i<n; i++) {
        if(a[i].first > x || a[i].second > x){
            v.push_back(a[i]);
        }
    }
    int minv = 2e9, minv2 = 2e9;
    for (int i=0; i<v.size(); i++) {
        minv = min(minv,v[i].first);
        minv2 = min(minv2,v[i].second);
    }
    for (int i=0; i<v.size(); i++) {
        v[i].first -= minv;
        v[i].second -= minv2;
    }
    int maxv = 0;
    for (int i=0; i<v.size(); i++) {
        maxv = max(maxv,v[i].first);
    }
    if(trial2(x)) return 1;
    for (int i=0; i<v.size(); i++) {
        v[i].first = maxv - v[i].first;
    }
    return trial2(x);
}
 
int bs(){
    long long s = 0, e = 2e9;
    while (s != e) {
        long long m = (s+e)/2;
        if(trial((int)m)) e = m;
        else s = m+1;
    }
    return (int)s;
}
 
void solve(){
    scanf("%d",&n);
    int mx1 = 1e9, mx2 = 1e9;
    int max1 = 0, max2 = 0;
    for (int i=0; i<n; i++) {
        scanf("%d %d",&a[i].first,&a[i].second);
        mx1 = min(mx1,a[i].first);
        mx2 = min(mx2,a[i].second);
    }
    for (int i=0; i<n; i++) {
        a[i].first -= mx1;
        a[i].second -= mx2;
        max1 = max(max1,a[i].first);
        max2 = max(max2,a[i].second);
    }
    int ret = bs();
    for (int i=0; i<n; i++) {
        a[i].first = max1 - a[i].first;
    }
    ret = min(ret,bs());
    for (int i=0; i<n; i++) {
        a[i].second = max2 - a[i].second;
    }
    ret = min(ret,bs());
    for (int i=0; i<n; i++) {
        a[i].first = max1 - a[i].first;
    }
    ret = min(ret,bs());
    printf("%d\n",ret);
}
 
int main(){
    int t;
    scanf("%d",&t);
    while (t--) {
        solve();
        v.clear();
    }
}