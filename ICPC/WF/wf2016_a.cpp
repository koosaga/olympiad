#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<lint, lint> pi;

int n, m, a[100005], sum;
int cur[100005];

pi getintv(int i){
    double t1 = (1.0 * cur[i]) / (1.0 * a[i] / sum);
    double t2 = (1.0 * cur[i] + 1) / (1.0 * a[i] / sum) + 1;
    return pi((int)ceil(t1 + 0.0000001), (int)floor(t2 - 0.0000001));
}

priority_queue<pi, vector<pi>, greater<pi> > upcoming;
priority_queue<pi, vector<pi>, greater<pi> > matching;

int main(){
    scanf("%d %d",&n,&m);
    for(int i=1; i<=n; i++){
        scanf("%d", &a[i]);
        sum += a[i];
    }
    for(int i=0; i<m; i++){
        int t;
        scanf("%d",&t);
        cur[t]++;
    }

    for(int i=1; i<=n; i++){
        upcoming.push(pi(getintv(i).first, i));
    }
    for(int i=m+1; i<=m+sum; i++){
        while(!upcoming.empty() && upcoming.top().first <= i){
            int idx = upcoming.top().second;
            upcoming.pop();
            matching.push(pi(getintv(idx).second, idx));
        }
        if(matching.empty() || matching.top().first < i){
            printf("%d", i - m - 2);
            return 0;
        }
        int p = matching.top().second;
        matching.pop();
        cur[p]++;
        upcoming.push(pi(getintv(p).first, p));
    }
    puts("forever");
}