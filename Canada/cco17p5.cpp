#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;

priority_queue<int> pq;

int n;
pi a[200005];

int main(){
    scanf("%d",&n);
    for(int i=0; i<n; i++) scanf("%d %d",&a[i].first,&a[i].second);
    sort(a, a+n);
    int ans = 0, j = 0;
    for(int i=0; i<n; i++) ans += a[i].second;
    for(int i=0; i<n; i++){
        while(j < n && a[j].first <= i) pq.push(a[j++].second);
        if(!pq.empty()){
            ans -= pq.top();
            pq.pop();
        }
    }
    cout << ans;
}
