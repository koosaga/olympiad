// Ivan Carvalho
// Solution to https://dmoj.ca/problem/ioi10p1
#include "cluedo.h"
#include <bits/stdc++.h>
using namespace std;

void Solve(){

	int marcado1[11],marcado2[11],marcado3[11];
	memset(marcado1,0,sizeof(marcado1));
	memset(marcado2,0,sizeof(marcado2));
	memset(marcado3,0,sizeof(marcado3));

	for(int i = 1;i<=6;i++){
		for(int j = 1;j<=10;j++){
			for(int k = 1;k <= 6;k++){
				if(!marcado1[i] && !marcado2[j] && !marcado3[k]){
					int x = Theory(i,j,k);
					if(x == 1) marcado1[i] = 1;
					else if(x == 2) marcado2[j] = 1;
					else if(x == 3) marcado3[k] = 1;
					else break;
				}
			}
		}
	}

}
