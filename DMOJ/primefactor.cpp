// Ivan Carvalho
// Solution to https://dmoj.ca/problem/primefactor
#include <cstdio>
#include <vector>
#include <algorithm>
#define MAXN 10000001
int maior[MAXN];
using namespace std;
int main(){
	for(int i=2;i<MAXN;i++){
		if(maior[i] == 0){
			maior[i] = i;
			for(int j=2*i;j<MAXN;j+=i){
				maior[j] = i;
			}
		}
	}
	int n;
	scanf("%d",&n);
	while(n--){
		int m;
		scanf("%d",&m);
		vector<int> resp;
		while(m != 1){
			resp.push_back(maior[m]);
			m /= maior[m];
		}
		reverse(resp.begin(),resp.end());
		for(int i=0;i<resp.size();i++){
			printf("%d ",resp[i]);
		}
		printf("\n");
	}
	return 0;
}