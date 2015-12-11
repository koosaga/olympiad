#include <cstdio>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;
typedef pair<int,int> pi;
 
map<int,int> mp, dx;
 
int n;
pi a[100005];
 
int main(){
    scanf("%d",&n);
    int pmin = 1e9, pmax = 0;
    for(int i=0; i<n; i++){
        scanf("%d %d",&a[i].first,&a[i].second);
        pmin = min(pmin,a[i].second);
        pmax = max(pmax,a[i].second);
    }
    sort(a,a+n);
    for(int i=n-1; i>=0; i--){
        auto t = mp.upper_bound(a[i].second);
        if(t != mp.end()){
            if(t->first - a[i].second <= a[i].first){
                dx[a[i].second]++;
                dx[t->first]--;
            }
        }
        if(t != mp.begin()){
            t--;
            if(a[i].second- t->first <= a[i].first){
                dx[t->first]++;
                dx[a[i].second]--;
            }
        }
        mp[a[i].second] = a[i].first;
    }
    int cur = 0, ret = 0;
    auto nxt = ++dx.begin();
    for (auto &i : dx){
        cur += i.second;
        if(cur){
            ret += nxt->first - i.first;
        }
        nxt++;
        if(nxt == mp.end()) break;
    }
    printf("%d",ret);
}