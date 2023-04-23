#include <cstdio>
#include <queue>
#include <algorithm>
using namespace std;
typedef pair<int,int> pi;

int n, m;
int a[100005], b[100005];
priority_queue<int> pq;

vector<pi> v;

int main(){
    scanf("%d %d",&n,&m);
    for(int i=1; i<=n; i++){
        scanf("%d %d",&a[i],&b[i]);
    }
    int cur = a[m];
    for(int i=1; i<=n; i++){
        if(i == m) continue;
        v.push_back(pi(b[i], a[i] - b[i]));
    }
    sort(v.begin(), v.end());
    int p = 0;
    while(1){
        while(p < v.size() && v[p].first <= cur){
            pq.push(v[p++].second);
        }
        if(pq.empty() || pq.top() < 0) break;
        cur += pq.top();
        pq.pop();
    }
    printf("%d\n%d",cur,n - pq.size() - (v.size() - p));
}