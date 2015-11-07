#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;

vector<int> graph[10005];

int n,dp[10005][2][2];

int f(int x, int e, int pa, int g){ // eat me
    if(~dp[x][e][g]) return dp[x][e][g];
    int r = e;
    if(e == 1 || g == 1){
        for (int i=0; i<graph[x].size(); i++) {
            if(graph[x][i] != pa){
                r += min(f(graph[x][i],0,x,e),f(graph[x][i],1,x,e));
            }
        }
    }
    else{
        int min_delta = 1e9, ret = 0;
        for (int i=0; i<graph[x].size(); i++) {
            if(graph[x][i] != pa){
                int p1 = f(graph[x][i],1,x,0);
                int p2 = f(graph[x][i],0,x,0);
                ret += min(p1,p2);
                min_delta = min(min_delta,max(p1 - p2,0));
            }
        }
        r = ret + min_delta;
    }
    return dp[x][e][g] = r;
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
    printf("%d",min(f(1,0,-1,0),f(1,1,-1,0)));
}