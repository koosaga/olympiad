#include "grader.h"

bool vis[40];
int val[40];
int _n;

void startgame(int n){
	_n = n;
	for(int i=0; i<n; i++){
		for(int j=0; j<n; j++){
			val[i] += valueat(i,j);
			val[j] += valueat(i,j);
		}
	}
}

void opponentmove(int token){
	vis[token] = 1;
}

int play(){
	int pos = -1, ret = -1;
	for(int i=0; i<_n; i++){
		if(!vis[i] && ret < val[i]) pos = i, ret = val[i];
	}
	if(pos != -1) vis[pos] = 1;
	return pos;
}

