#include <bits/stdc++.h>
using namespace std;
using pi = pair<int, int>;
const int MAXN = 100005;

int n, m;
int dist[2][MAXN];
vector<int> gph[MAXN];

int main(){
    scanf("%d %d",&n,&m);
    for(int i=0; i<m; i++){
        int s, e; scanf("%d %d",&s,&e);
        gph[s].push_back(e);
        gph[e].push_back(s);
    }
    memset(dist, 0x3f, sizeof(dist));
    queue<pi> que;
    que.emplace(0, 1);
    dist[0][1] = 0;
    while(!que.empty()){
        auto x = que.front();
        que.pop();
        for(auto &i : gph[x.second]){
            if(dist[x.first ^ 1][i] > dist[x.first][x.second] + 1){
                dist[x.first ^ 1][i] = dist[x.first][x.second] + 1;
                que.emplace(x.first ^ 1, i);
            }
        }
    }
    int ret = 1e9;
    for(int i=0; i<2; i++){
        int w = *max_element(dist[i] + 1, dist[i] + n + 1);
        ret = min(ret, w);
    }
    if(ret > 1e8) ret = -1;
    cout << ret << endl;
}
