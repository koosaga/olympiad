#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;
 
vector<int> graph[1000005];
 
int n,dp[1000005][2];
 
int f(int x, int e, int pa){
    if(~dp[x][e]) return dp[x][e];
    int r = e;
    for (int i=0; i<graph[x].size(); i++) {
        if(graph[x][i] != pa){
            if(e == 1) r += min(f(graph[x][i],!e,x),f(graph[x][i],e,x));
            else r += f(graph[x][i],1,x);
        }
    }
    return dp[x][e] = r;
}
 
int main(){
    memset(dp,-1,sizeof(dp));
    scanf("%d",&n);
    for (int i=0; i<n-1; i++) {
        int p,q;
        scanf("%d %d",&p,&q);
        graph[p].push_back(q);
        graph[q].push_back(p);
    }
    printf("%d",n-min(f(1,0,-1),f(1,1,-1)));
}