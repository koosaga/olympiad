#include <cstdio>
#include <queue>
#include <algorithm>
using namespace std;
typedef pair<int,int> pi;

struct seg{int s,e,x;};
bool cmp(seg a, seg b){return a.s < b.s;}

int n,m;
pi a[400005];
seg b[400005];

priority_queue<pi,vector<pi>,greater<pi> > pq;
vector<pi> ans;

int main(){
    scanf("%d %d",&n,&m);
    for (int i=0; i<n; i++) {
        scanf("%d",&a[i].first);
        a[i].second = i;
    }
    sort(a,a+n);
    for (int i=0; i<m; i++) {
        scanf("%d %d",&b[i].s,&b[i].e);
        b[i].x = i;
    }
    sort(a,a+n);
    sort(b,b+m,cmp);
    int p1 = 0;
    for (int i=0; i<n; ) {
        int e = i;
        while (e < n && a[e].first == a[i].first) e++;
        while (p1 < m && b[p1].s <= a[i].first) {
            pq.push(pi(b[p1].e,b[p1].x));
            p1++;
        }
        while (!pq.empty() && pq.top().first < a[i].first) {
            pq.pop();
        }
        for (int j=i; j<e; j++) {
            if(pq.empty()) continue;
            ans.push_back(pi(a[j].second,pq.top().second));
            pq.pop();
        }
        i = e;
    }
    printf("%d\n",(int)ans.size());
    for (int i=0; i<ans.size(); i++) {
        printf("%d %d\n",ans[i].first+1,ans[i].second+1);
    }
}