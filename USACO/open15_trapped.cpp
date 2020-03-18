#include <bits/stdc++.h>
using namespace std;
typedef pair<int,int> pi;

map<int,int> mp;
vector<pi> dx;

int n;
pi a[100005];

int main(){
    scanf("%d",&n);
    for(int i=0; i<n; i++){
        scanf("%d %d",&a[i].first,&a[i].second);
    }
    sort(a,a+n);
    for(int i=n-1; i>=0; i--){
        auto t = mp.upper_bound(a[i].second);
        if(t != mp.end() && t->first - a[i].second <= a[i].first){
            dx.emplace_back(a[i].second, +1);
            dx.emplace_back(t->first, -1);
        }
        if(t != mp.begin() && a[i].second - prev(t)->first <= a[i].first){
            dx.emplace_back(a[i].second, -1);
            dx.emplace_back(prev(t)->first, +1);
        }
        mp[a[i].second] = a[i].first;
    }
    sort(dx.begin(), dx.end());
    int cur = 0, ret = 0;
    for(int i=0; i+1<dx.size(); i++){
        cur += dx[i].second;
        if(cur) ret += dx[i+1].first-dx[i].first;
    }
    printf("%d",ret);
}