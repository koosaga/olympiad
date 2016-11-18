#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;

vector<int> graph[100005];

int dp[100005][10], n;

int f(int pos, int c, int pa){
	if(~dp[pos][c]) return dp[pos][c];
	int ret = c+1;
	for(auto &i : graph[pos]){
		if(i == pa) continue;
		int tmp = 1e9;
		for(int j=0; j<10; j++){
			if(j == c) continue;
			tmp = min(tmp,f(i,j,pos));
		}
		ret += tmp;
	}
	return dp[pos][c] = ret;
}

int main(){
	memset(dp,-1,sizeof(dp));
	scanf("%d",&n);
	for(int i=0; i<n-1; i++){
		int u,v;
		scanf("%d %d",&u,&v);
		graph[u].push_back(v);
		graph[v].push_back(u);
	}
	int ret = 1e9;
	for(int i=0; i<10; i++) ret= min(ret,f(1,i,0));
	printf("%d",ret);
}