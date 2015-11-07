    #include <stdio.h>  
    #include <stdlib.h>  
    #include <string.h>  
    #include <math.h>  
    #include <limits.h>  
    #include <stack>  
    #include <queue>  
    #include <map>  
    #include <set>  
    #include <algorithm>  
    #include <string>  
    #include <functional>  
    #include <vector>  
    #include <numeric>  
    #include <deque>  
    #include <utility>  
    #include <bitset>  
    #include <iostream>  
    using namespace std;  
    typedef long long lint;  
    typedef long double llf;  
    typedef pair<int, int> pi;  
    const int mod = 1e7;
     
    int n;
    char str[300005];
    int nxt[300005][26];
    int adj[26][26];
    int dp[300005];
     
    int f(int x){
    	if(x == n+1) return 0;
    	if(~dp[x]) return dp[x];
    	int ret = 1;
    	for(int i=0; i<26; i++){
    		int nxtp = nxt[x][i];
    		if(x == 0 || !adj[str[x] - 'A'][i]){
    			ret += f(nxtp);
    			ret %= mod;
    		}
    	}
    	return dp[x] = ret % mod;
    }
     
    int main(){
    	memset(dp,-1,sizeof(dp));
    	scanf("%d %s",&n,str+1);
    	for(int i=n; i>=0; i--){
    		for(int j=0; j<26; j++){
    			if(i == n) nxt[i][j] = n+1;
    			else nxt[i][j] = nxt[i+1][j];
    		}
    		if(i != n) nxt[i][str[i+1] - 'A'] = i+1;
    	}
    	int q;
    	scanf("%d",&q);
    	while(q--){		
    		char a[2],b[2];
    		scanf("%s%s",a,b);
    		adj[a[0]-'A'][b[0]-'A']=1;
    	}
    	printf("%d\n",(f(0) + mod - 1) % mod);
    }