#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;
typedef pair<int,int> pi;

struct pyra{
	int x;
	char str[6];
};

pyra db[321];

void makepyr(){
	int pt = 1;
	for(int i=2; i<200; i++){
		db[pt].x = 0;
		for(int j=i; j>=0; j--){
			db[pt].x += j * j;
		}
		if(db[pt].x > 1000000) break;
		sprintf(db[pt].str,"%dH",i);
		pt++;
	}
	for(int i=3; i<200; i++){
		db[pt].x = 0;
		for(int j=i; j>=0; j-=2){
			db[pt].x += j * j;
		}
		if(db[pt].x > 1000000) break;
		sprintf(db[pt].str,"%dL",i);
		pt++;
	}
	sort(db+1,db+321,[&](const pyra &a, const pyra &b){return a.x < b.x;});
}

char dp[321][1000005];

int main(){
	makepyr();
	memset(dp,0x3e,sizeof(dp));
	dp[0][0] = 0;
	for(int i=1; i<=320; i++){
		for(int j=0; j<=1000000; j++){
			dp[i][j] = dp[i-1][j];
			if(j >= db[i].x && dp[i][j] >= dp[i-1][j - db[i].x] + 1) dp[i][j] = dp[i-1][j - db[i].x] + 1;
		}
	}
	int cases = 0;
	while(1){
		int t;
		scanf("%d",&t);
		if(t == 0) break;
		cases++;
		printf("Case %d: ",cases);
		vector<int> ans;
		for(int j=320; j; j--){
			if(t >= db[j].x && dp[j-1][t - db[j].x] == dp[j][t] - 1){
				t -= db[j].x;
				ans.push_back(j);
			}
		}
		if(t){
			puts("impossible");
		}
		else{
			for(auto &j : ans){
				printf("%s ",db[j].str);
			}
			puts("");
		}
	}
}