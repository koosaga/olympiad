#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<int, int> pi;
 
int n, x, y;
pi a[1000005];
 
vector<pi> d[4];
 
int solve(vector<pi> &v){
    sort(v.begin(), v.end());
    reverse(v.begin(), v.end());
    vector<int> lis;
    for(auto &i : v){
        auto p = lower_bound(lis.begin(), lis.end(), i.second);
        if(p == lis.end()){
            lis.push_back(i.second);
        }
        else{
            *p = i.second;
        }
    }
    return lis.size();
}
 
pi norm(pi x){
    return pi(abs(x.first), abs(x.second));
}
 
int main(){
    cin >> n >> x >> y;
    for(int i=0; i<n; i++){
        scanf("%d %d",&a[i].first, &a[i].second);
        a[i].first -= x;
        a[i].second -= y;
        if(a[i].first > 0 && a[i].second > 0){
            d[0].push_back(norm(a[i]));
        }
        if(a[i].first > 0 && a[i].second < 0){
            d[1].push_back(norm(a[i]));
        }
        if(a[i].first < 0 && a[i].second > 0){
            d[2].push_back(norm(a[i]));
        }
        if(a[i].first < 0 && a[i].second < 0){
            d[3].push_back(norm(a[i]));
        }
    }
    int ret = 0;
    for(int i=0; i<4; i++){
        ret += solve(d[i]);
    }
    cout << ret;
}
