#include <cstdio>
#include <vector>
#include <cstring>
#include <utility>
using namespace std;
typedef pair<int,int> pi;
 
vector<pi> graph[505];
int dist[505];
 
void solve(){
    memset(dist,0x3f,sizeof(dist));
    int n,m,w;
    scanf("%d %d %d",&n,&m,&w);
    for (int i=1; i<=n; i++) {
        graph[i].clear();
    }
    for (int i=0; i<m + w; i++) {
        int x,y,z;
        scanf("%d %d %d",&x,&y,&z);
        if(i < m){
            graph[x].push_back(pi(y,z));
            graph[y].push_back(pi(x,z));
        }
        else{
            graph[x].push_back(pi(y,-z));
        }
    }
    int upd = 0;
    dist[1] = 0;
    for (int i=0; i<n; i++) {
        upd = 0;
        for (int j=1; j<=n; j++) {
            for (auto &k : graph[j]){
                if(dist[k.first] > dist[j] + k.second){
                    upd = 1;
                    dist[k.first] = dist[j] + k.second;
                }
            }
        }
        if(upd == 0) break;
    }
    puts(upd ? "YES" : "NO");
}
 
int main(){
    int t;
    scanf("%d",&t);
    while (t--) {
        solve();
    }
}