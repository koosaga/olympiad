#include <cstdio>
#include <utility>
#include <vector>
#include <cstring>
using namespace std;
typedef pair<int,int> pi;

vector<pi> graph[1005];
int n,dist[10005];

int main(){
    int ml,md,p,q,r;
    scanf("%d %d %d",&n,&ml,&md);
    for (int i=0; i<ml; i++) {
        scanf("%d %d %d",&p,&q,&r);
        graph[p].push_back(pi(q,r));
    }
    for (int i=0; i<md; i++) {
        scanf("%d %d %d",&p,&q,&r);
        graph[q].push_back(pi(p,-r));
    }
    memset(dist,0x3f,sizeof(dist));
    bool update = 1;
    dist[1] = 0;
    while (update) {
        update = 0;
        for (int i=1; i<=n; i++) {
            for (int j=0; j<graph[i].size(); j++) {
                if(dist[graph[i][j].first] > dist[i] + graph[i][j].second){
                    update = 1;
                    dist[graph[i][j].first] = dist[i] + graph[i][j].second;
                }
            }
        }
    }
    if(dist[n] > 1e9) printf("-2");
    else if(dist[n] < 0) printf("-1");
    else printf("%d",dist[n]);
}