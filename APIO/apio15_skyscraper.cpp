#include <cstdio>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <utility>
#include <queue>
using namespace std;
typedef pair<int,int> pi;
const int B = 150;
 
int m, n;
 
bool r_dir[30005][B], l_dir[30005][B];
bool vis[30005 * B];
vector<pi> graph[30005];
queue<int> pq[30005];
 
int dijkstra(int st, int ed){
    pq[0].push(st);
    int dist = 0, cnt = 1;
    while (cnt) {
        while (!pq[dist%n].empty()) {
            int t = pq[dist%n].front();
            pq[dist%n].pop();
            cnt--;
            if(t == ed){
                return dist;
            }
            if(vis[t]) continue;
            vis[t] = 1;
            if(t < n){
                for (auto &i : graph[t]){
                    if(!vis[i.second])
                        pq[(i.first + dist)%n].push(i.second), cnt++;
                }
            }
            int px = t % n;
            int py = t / n;
            if(r_dir[px][py] && px + py < n){
                if(!vis[py * n + px + py]){
                    cnt++;
                    pq[(dist + 1)%n].push(py * n + px + py);
                }
            }
            if(l_dir[px][py] && px - py >= 0){
                if(!vis[py * n + px - py]){
                    cnt++;
                    pq[(dist + 1)%n].push(py * n + px - py);
                }
            }
            if(py){
                if(!vis[px]){
                    cnt++;
                    pq[dist%n].push(px);
                }
            }
        }
        dist++;
    }
    return -1;
}
 
int main(){
    int st = 0, ed = 0;
    scanf("%d %d",&n,&m);
    for (int i=0; i<m; i++) {
        int x,y;
        scanf("%d %d",&x,&y);
        if(i == 0){
            st = x;
        }
        else if(i == 1){
            ed = x;
        }
        if(y < B){
            r_dir[x][y] = 1;
            l_dir[x][y] = 1;
            graph[x].push_back(pi(0,x + n * y));
        }
        else{
            for (int j=1; x - j * y >= 0; j++) {
                graph[x].push_back(pi(j,x - j * y));
            }
            for (int j=1; x + j * y < n; j++) {
                graph[x].push_back(pi(j,x + j * y));
            }
        }
    }
    for (int i=1; i<B; i++) {
        for (int j=i; j<n; j++) {
            r_dir[j][i] |= r_dir[j - i][i];
        }
        for (int j=n-i-1; j>=0; j--) {
            l_dir[j][i] |= l_dir[j + i][i];
        }
    }
    printf("%d",dijkstra(st,ed));
}
