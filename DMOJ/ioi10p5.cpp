// Ivan Carvalho
// Solution to https://dmoj.ca/problem/ioi10p5
#include "memory.h"
#include <bits/stdc++.h>
using namespace std;

void play(){
   
   int minimo[300],maximo[300];
   for(int i = 0;i<300;i++){
   		minimo[i] = 300;
   		maximo[i] = 0;
	}

	for(int i = 1;i<=50;i++){
		int x = faceup(i);
		minimo[x] = min(minimo[x],i);
		maximo[x] = max(maximo[x],i);
	}

	for(char c = 'A';c<='Y';c++){
		//printf("FUP %d %d\n",minimo[c],maximo[c]);
		faceup(minimo[c]);
		faceup(maximo[c]);
	}

}
