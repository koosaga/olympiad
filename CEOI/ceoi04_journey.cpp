#include <cstdio>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;
typedef pair<int,int> pi;

int n,s;
vector<pi> graph[50005];

int needy[50005], d[50005];
int sum, maxv;

void dfs(int pos, int pa){
    for(int j=0; j<graph[pos].size(); j++){
        pi i = graph[pos][j];
        if(i.second == pa) continue;
        d[i.second] = d[pos] + i.first;
        dfs(i.second,pos);
        needy[pos] |= needy[i.second];
    }
    if(needy[pos]){
        sum += 2 * (d[pos] - d[pa]);
        maxv = max(maxv,d[pos]);
    }
}

int main(){
    scanf("%d %d",&n,&s);
    for (int i=0; i<n-1; i++) {
        int s,e,x;
        scanf("%d %d %d",&s,&e,&x);
        graph[s].push_back(pi(x,e));
        graph[e].push_back(pi(x,s));
    }
    int t;
    scanf("%d",&t);
    while (t--) {
        int u;
        scanf("%d",&u);
        needy[u] = 1;
    }
    dfs(s,0);
    printf("%d",sum- maxv);
}