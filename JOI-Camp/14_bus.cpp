#include <cstdio>
#include <queue>
#include <algorithm>
#include <utility>
using namespace std;
typedef pair<int,int> pi;

int res[100005];
pi query[100005];

struct ln{int pos,s,e;};
bool operator<(ln a, ln b){return a.e > b.e;}
struct cmp{bool operator()(ln a, ln b){return a.s < b.s;}};
struct cmp2{bool operator()(ln a, ln b){return a.e > b.e;}};
priority_queue<ln,vector<ln>,cmp2> graph[100005];

int n,m,q,v[100005];

void process(int lim, int save){
    priority_queue<ln,vector<ln>,cmp> pq;
    int pos = n;
    while (!graph[pos].empty()) {
        ln t = graph[pos].top();
        if(t.e > lim) break;
        graph[pos].pop();
        if(v[t.pos] > t.s) continue;
        pq.push(t);
    }
    while (!pq.empty()) {
        ln t = pq.top();
        pos = t.pos;
        v[pos] = t.s;
        pq.pop();
        if(pos == 1) break;
        while (!graph[pos].empty()) {
            ln u = graph[pos].top();
            if(u.e > t.s) break;
            graph[pos].pop();
            if(v[u.pos] > u.s) continue;
            pq.push(u);
        }
    }
    res[save] = v[1];
}

int main(){
    v[1] = -1;
    int p,q,r,s;
    scanf("%d %d",&n,&m);
    for (int i=0; i<m; i++) {
        scanf("%d %d %d %d",&p,&q,&r,&s);
        graph[q].push({ p,r,s});
    }
    scanf("%d",&q);
    for (int i=0; i<q; i++) {
        scanf("%d",&query[i].first);
        query[i].second = i;
    }
    sort(query,query+q);
    for (int i=0; i<q; i++) {
        process(query[i].first,query[i].second);
    }
    for (int i=0; i<q; i++) {
        printf("%d\n",res[i]);
    }
}