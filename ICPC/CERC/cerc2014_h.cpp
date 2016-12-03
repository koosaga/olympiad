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
#include <bitset>
#include <iostream>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<int, int> pi;

bool ok(int a, int b){
	if(a == 0){
		return b == 0;
	}
	if(b == 0){
		return (a%3 == 1 || a%3 == 2);
	}
	int ax = (a-1) / 3, ay = (a-1)%3;
	int bx = (b-1) / 3, by = (b-1)%3;
	return ax <= bx && ay <= by; 
}

int main(){
	int t;
	set<int> s;
	for(int i=0; i<=9; i++){
		s.insert(i);
	}
	for(int i=1; i<=9; i++){
		for(int j=0; j<=9; j++){
			if(ok(i, j)) s.insert(10*i+j);
		}
	}
	for(int i=1; i<=2; i++){
		for(int j=0; j<=9; j++){
			for(int k=0; k<=9; k++){
				if(ok(i, j) && ok(j, k)){
					s.insert(100*i+10*j+k);
				}
			}
		}
	}
	cin >> t;
	while(t--){
		int x;
		cin >> x;
		auto ed = s.upper_bound(x);
		auto st = --s.upper_bound(x);
		if(x - *st <= *ed - x){
			printf("%d\n",*st);
		}
		else{
			printf("%d\n",*ed);
		}
	}
}