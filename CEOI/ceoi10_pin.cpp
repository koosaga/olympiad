#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <limits.h>
#include <math.h>
#include <time.h>
#include <iostream>
#include <functional>
#include <numeric>
#include <algorithm>
#include <stack>
#include <queue>
#include <deque>
#include <vector>
#include <string>
#include <bitset>
#include <map>
#include <set>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<int, int> pi;

int a[37][37][37][37];

int toi(char t){
	if(t <= 'z' && t >= 'a') return t - 'a' + 10;
	return t - '0';
}

lint cnt[5], ret[5];

void backtrack(int x, int *d){
	if(x == 4){
		int p = a[d[0]][d[1]][d[2]][d[3]];
		int pos = 0;
		for(int k=0; k<4; k++){
			if(d[k] != 36) pos++;
		}
		cnt[pos] += 1ll * p * (p-1) / 2;
		return;
	}
	for(int i=0; i<=36; i++){
		d[x] = i;
		backtrack(x+1, d);
	}
}

int main(){
	int n, d;
	cin >> n >> d;
	for(int i=0; i<n; i++){
		string s;
		cin >> s;
		for(int j=0; j<16; j++){
			int pos[4];
			for(int k=0; k<4; k++){
				if((j >> k) & 1) pos[k] = 36;
				else pos[k] = toi(s[k]);
			}
			a[pos[0]][pos[1]][pos[2]][pos[3]]++;
		}
	}
	int pos[4];
	backtrack(0, pos);
	ret[3] = cnt[3];
	ret[2] = cnt[2] - 3ll * ret[3];
	ret[1] = cnt[1] - 2ll * ret[2] - 3ll * ret[3];
	ret[0] = 1ll * n * (n-1) / 2 - ret[1] - ret[2] - ret[3];
	cout << ret[4-d];
}