#include <cstdio>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;
typedef pair<int,int> pi;
typedef long long lint;
 
int n, m;
int deg[100005];
bool vis[100005];
 
int a[100005];
int ret[100005];
 
vector<pi> graph[100005];
queue<int> q;
 
int curval[100005], nxt[100005], cycsz;
 
int main(){
    scanf("%d %d",&n,&m);
    if(n < m){
        puts("0");
        return 0;
    }
    for(int i=1; i<=n; i++){
        scanf("%d",&a[i]);
    }
    for(int i=0; i<m; i++){
        int s, e;
        scanf("%d %d",&s,&e);
        graph[s].push_back(pi(i, e));
        graph[e].push_back(pi(i, s));
        deg[s]++, deg[e]++;
    }
    for(int i=1; i<=n; i++){
        if(deg[i] == 1){
            q.push(i);
        }
    }
    while(!q.empty()){
        int x = q.front();
        q.pop();
        deg[x] = 0;
        vis[x] = 1;
        for(int i=0; i<graph[x].size(); i++){
            int pos = graph[x][i].second;
            if(vis[pos]) continue;
            deg[pos]--;
            ret[graph[x][i].first] = 2 * a[x];
            a[pos]-=a[x];
            if(deg[pos] == 1){
                q.push(pos);
            }
        }
    }
    int pos;
    for(int i=1; i<=n; i++){
        if(deg[i]) cycsz++, pos = i;
    }
    if(n == m && cycsz % 2 == 0){
        puts("0");
        return 0;
    }
    lint sum = 0;
    for(int i=0; i<cycsz; i++){
        curval[i] = pos;
        sum += a[pos];
        for(int j=0; j<graph[pos].size(); j++){
            pi edg = graph[pos][j];
            if(deg[edg.second]){
                deg[edg.second] = 0;
                nxt[i] = edg.first;
                pos = edg.second;
                break;
            }
        }
    }
    if(cycsz){
        sum /= 2;
        lint tsum = 0;
        for(int i=0; i<cycsz/2; i++){
            tsum += a[curval[(2+2*i) % cycsz]];
        }
        ret[nxt[0]] = 2 * (sum - tsum);
        int pt = 0;
        for(int i=2; i!=0; i = (i + 2) % cycsz){
            tsum -= a[curval[i]];
            tsum += a[curval[(i + cycsz / 2 * 2) % cycsz]];
            ret[nxt[i]] = 2 * (sum - tsum);
        }
    }
    for(int i=0; i<m; i++){
        printf("%d\n",ret[i]);
    }
}