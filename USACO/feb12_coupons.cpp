#include <cstdio>
#include <queue>
#include <algorithm>
using namespace std;
typedef long long lint;
typedef pair<lint,lint> pi;
 
priority_queue<lint,vector<lint>,greater<lint> > pq; // queue for refund
 
int n,k;
lint m;
 
int main(){
    lint refund[50005];
    pi low[50005], high[50005];
    int vis[50005];
    scanf("%d %d %lld",&n,&k,&m);
    for (int i=0; i<n; i++) {
        scanf("%lld %lld",&high[i].first,&low[i].first);
        low[i].second = high[i].second = i;
        refund[i] = high[i].first - low[i].first;
    }
    for (int i=0; i<k; i++) {
        pq.push(0);
    }
    sort(low,low+n);
    sort(high,high+n);
    low[n] = high[n] = pi(1e18,0);
    lint cost = 0;
    int cnt = 0, pl = 0, ph = 0;
    while (cost <= m) {
        while (pl < n && vis[low[pl].second]) pl++;
        while (ph < n && vis[high[ph].second]) ph++;
        if(pl == n && ph == n) break;
        if(low[pl].first + pq.top() < high[ph].first){
            cost += low[pl].first + pq.top();
            vis[low[pl].second] = 1;
            pq.pop();
            pq.push(refund[low[pl].second]);
            pl++;
        }
        else{
            cost += high[ph].first;
            vis[high[ph].second] = 1;
            ph++;
        }
        if(cost > m) break;
        else cnt++;
    }
    printf("%d",cnt);
}