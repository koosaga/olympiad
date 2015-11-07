#include <cstdio>
#include <vector>
using namespace std;

vector<int> graph[1001];
int reach[1001][1001];
int n,m;

void dfs(int st, int i){
    if(reach[st][i]) return;
    reach[st][i] = 1;
    for (int j=0; j<graph[i].size(); j++) {
        dfs(st,graph[i][j]);
    }
}

int main(){
    scanf("%d %d",&n,&m);
    for (int i=0; i<m; i++) {
        int x,y;
        scanf("%d %d",&x,&y);
        graph[x].push_back(y);
    }
    for (int i=1; i<=n; i++) {
        dfs(i,i);
    }
    int ret = 0;
    for (int i=1; i<=n; i++) {
        for (int j=i+1; j<=n; j++) {
            if(!reach[i][j] && !reach[j][i]) ret++;
        }
    }
    printf("%d",ret);
}