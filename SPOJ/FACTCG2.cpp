// Ivan Carvalho
// Solution to https://www.spoj.com/problems/FACTCG2/
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1e7 + 2;
int biggest[MAXN];
int main(){
	for(int i = 2;i<MAXN;i++){
		if(biggest[i] != 0) continue;
		biggest[i] = i;
		for(int j = i;j < MAXN;j+=i) biggest[j] = i;
	}
	int n;
	while(scanf("%d",&n) != EOF){
		vector<int> resp;
		while(n != 1){
			resp.push_back(biggest[n]);
			n /= biggest[n];
		}
		resp.push_back(1);
		reverse(resp.begin(),resp.end());
		int primeiro = 0;
		for(int i : resp){
			if(primeiro) printf(" x ");
			else primeiro = 1;
			printf("%d",i);
		}
		printf("\n");
	}
	return 0;
}