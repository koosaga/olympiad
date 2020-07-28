// Ivan Carvalho
// Solution to https://dmoj.ca/problem/coci14c5p3
#include <bits/stdc++.h>
using namespace std;

int main(){

	map<int,int> m[4];

	int N,K;
	scanf("%d %d",&N,&K);

	for(int i = 1;i<=N;i++){
		int x,y;
		scanf("%d %d",&x,&y);
		if(++m[0][x] == K){
			printf("%d\n",i);
			return 0;
		}
		if(++m[1][y] == K){
			printf("%d\n",i);
			return 0;
		}
		if(++m[2][x-y] == K){
			printf("%d\n",i);
			return 0;
		}
		if(++m[3][y+x] == K){
			printf("%d\n",i);
			return 0;
		}
	}

	printf("-1\n");

	return 0;
}