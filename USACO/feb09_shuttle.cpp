#include <cstdio>
#include <algorithm>
#include <map>
using namespace std;
 
int n,m,c;
struct edg{int s,e,x;}a[50005];
bool cmp(edg a, edg b){return a.s < b.s;}
 
map<int,int> mp;
 
int main(){
    scanf("%d %d %d",&n,&m,&c);
    for (int i=0; i<n; i++) {
        scanf("%d %d %d",&a[i].s,&a[i].e,&a[i].x);
    }
    int ret = 0, cnt = 0;
    sort(a,a+n,cmp);
    int piv = 0;
    for (int i=1; i<=m; i++) {
        int e = piv;
        while (e < n && a[e].s == i) e++;
        ret += mp[i];
        cnt -= mp[i];
        mp.erase(mp.find(i));
        for (int j=piv; j<e; j++) {
            mp[a[j].e] += a[j].x;
            cnt += a[j].x;
        }
        while (cnt > c && !mp.empty()) {
            auto it = --mp.end();
            int val = min(cnt - c,it->second);
            mp[it->first] -= val;
            if(mp[it->first] == 0) mp.erase(it);
            cnt -= val;
        }
        piv = e;
    }
    printf("%d",ret);
}