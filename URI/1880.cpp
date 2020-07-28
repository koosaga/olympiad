// Ivan Carvalho
// Solution to https://www.urionlinejudge.com.br/judge/problems/view/1880
#include <bits/stdc++.h>
using namespace std;
int checa(int n,int base){
	if(n == 0) return 1;
	vector<int> v1,v2;
	while(n != 0){
		v1.push_back(n % base);
		n /= base;
	}
	v2 = v1;
	reverse(v2.begin(),v2.end());
	return v1 == v2;
}
int main(){
	int TC;
	scanf("%d",&TC);
	while(TC--){
		int n;
		scanf("%d",&n);
		int possivel = 0;
		for(int i=2;i<=16;i++){
			if(checa(n,i)){
				if(possivel) printf(" ");
				else possivel = 1;
				printf("%d",i);
			}
		}
		if(!possivel) printf("-1");
		printf("\n");
	}
	return 0;
}
