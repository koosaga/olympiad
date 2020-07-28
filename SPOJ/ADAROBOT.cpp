// Ivan Carvalho
// Solution to https://www.spoj.com/problems/ADAROBOT/
    #include <bits/stdc++.h>
    using namespace std;
    const int MAXN = 2*1e8 + 2;
    long dp[MAXN];
    int main(){
    	for(int i = 2;i<MAXN;i++){
    		long long davez = 1LL*(i)*(i-1);
    		long fn = __builtin_ffsll(davez);
    		dp[i] = dp[i-2] + fn*fn*fn;
    	}
    	int Q;
    	scanf("%d",&Q);
    	while(Q--){
    		int x;
    		scanf("%d",&x);
    		printf("%ld\n",dp[x]);
    	}
    	return 0;
    } 