#include <cstdio>
#include <vector>
#include <algorithm>
#include <utility>
#include <cstring>
#include <queue>
using namespace std;
typedef pair<int,int> pi;

int n;
int l[2005], r[2005];
int dp[4005][4005];
int stt[4005];

int calc(int start, int end){
    if(start > end) return 0;
    if(~dp[start][end]) return dp[start][end];
    int res = calc(start+1,end);
    int ns = stt[start];
    if(ns != n && r[ns] <= end) res = max(res,calc(l[ns]+1,r[ns]-1) + calc(r[ns]+1,end) + 1);
    return dp[start][end] = res;
}

int main(){
    vector<int> v;
    scanf("%d",&n);
    memset(dp,-1,sizeof(dp));
    for (int i=0; i<n; i++) {
        scanf("%d %d",&l[i],&r[i]);
        if(l[i] > r[i]) swap(l[i],r[i]);
        v.push_back(l[i]);
        v.push_back(r[i]);
    }
    sort(v.begin(),v.end());
    for (int i=0; i<n; i++) {
        l[i] = (int)(lower_bound(v.begin(),v.end(),l[i]) - v.begin());
        r[i] = (int)(lower_bound(v.begin(),v.end(),r[i]) - v.begin());
    }
    priority_queue<pi,vector<pi>,greater<pi> > pq;
    for (int i=0; i<n; i++) {
        pq.push(pi(l[i],r[i]));
    }
    for (int i=0; i<n; i++) {
        l[i] = pq.top().first;
        r[i] = pq.top().second;
        pq.pop();
    }
    for (int i=0; i<2*n; i++) {
        stt[i] = (int)(lower_bound(l,l+n,i) - l);
    }
    printf("%d",calc(0,2*n-1));
}