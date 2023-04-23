#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
using namespace std;
typedef pair<int,int> pi;
int dp[1<<18][18];
int n;
vector<pi> graph[19];

int f(int bit, int pos){
    if(pos == n-1) return 0;
    if(~dp[bit][pos]) return dp[bit][pos];
    int ret = -1e9;
    for(auto &i : graph[pos]){
        if((bit >> i.second) & 1) continue;
        ret = max(ret, i.first + f(bit|(1<<i.second), i.second));
    }
    return dp[bit][pos] = ret;
}

int main(){
    int m;
    scanf("%d %d",&n,&m);
    for(int i=0; i<m; i++){
        int s,e,x;
        scanf("%d %d %d",&s,&e,&x);
        graph[s].push_back(pi(x,e));
    }
    memset(dp,-1,sizeof(dp));
    printf("%d",f(1,0));
}