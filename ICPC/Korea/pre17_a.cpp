#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;
const int MAXN = 1000005;
const int mod = 1e9 + 7;

pi a[MAXN];

int main(){
    int n, m, c1, c2; scanf("%d %d %d %d",&n,&m,&c1,&c2);
    for(int i=0; i<n; i++) scanf("%d",&a[i].first), a[i].second = 0;
    for(int i=n; i<n+m; i++) scanf("%d",&a[i].first), a[i].second = 1;
    sort(a, a+n+m);
    int cur = 1e9, cnt = 0;
    for(int i=1; i<n+m; i++){
        if(a[i-1].second != a[i].second){
            if(cur > a[i].first - a[i-1].first){
                cur = a[i].first - a[i-1].first;
                cnt = 0;
            }
            if(cur == a[i].first - a[i-1].first) cnt++;
        }
    }
    cout << (cur + abs(c1 - c2)) << " " << cnt;
}
