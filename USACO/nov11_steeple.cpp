#include <cstdio>
#include <queue>
#include <vector>
using namespace std;
 
struct ln{int s,e,x;};
vector<ln> x,y;
 
struct edge{int pos,cap,rev;};
vector<edge> graph[260];
 
void add_edge(int s, int e){
    graph[s].push_back({e,1,(int)graph[e].size()});
    graph[e].push_back({s,0,(int)graph[s].size()-1});
}
 
int n;
 
bool cross(int i, int j){
    return (x[i].s <= y[j].x && y[j].x <= x[i].e) && (y[j].s <= x[i].x && x[i].x <= y[j].e);
}
 
int match(){
    int r = 0;
    while (1) {
        queue<int> q;
        int v[255] = {}, pa[255] = {}, pe[255] = {};
        v[0] = 1;
        q.push(0);
        while (!q.empty()) {
            int t = q.front();
            q.pop();
            v[t] = 1;
            if(t == n+1) break;
            for (int i=0; i<graph[t].size(); i++) {
                int pos = graph[t][i].pos;
                if(graph[t][i].cap >0 && !v[pos]){
                    v[pos] = 1;
                    pa[pos] = t;
                    pe[pos] = i;
                    q.push(pos);
                }
            }
        }
        if(!v[n+1]) break;
        r++;
        for (int i=n+1; i; i = pa[i]) {
            int rev = graph[pa[i]][pe[i]].rev;
            graph[pa[i]][pe[i]].cap--;
            graph[i][rev].cap++;
        }
    }
    return r;
}
 
int main(){
    scanf("%d",&n);
    for (int i=0; i<n; i++) {
        int a,b,c,d;
        scanf("%d %d %d %d",&a,&b,&c,&d);
        if(a > c) swap(a,c);
        if(b > d) swap(b,d);
        if(b == d) x.push_back({a,c,b});
        else y.push_back({b,d,a});
    }
    for (int i=0; i<x.size(); i++) {
        add_edge(0,1+i);
    }
    for (int i=0; i<y.size(); i++) {
        add_edge(n-i,n+1);
    }
    for (int i=0; i<x.size(); i++) {
        for (int j=0; j<y.size(); j++) {
            if(cross(i,j)){
                add_edge(i+1,(int)x.size()+1+j);
            }
        }
    }
    printf("%d",n-match());
}