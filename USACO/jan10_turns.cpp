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
typedef pair<lint, lint> pi;

pi B[700005], D[700005];
pi MB[700005], MD[700005];
int w[700005], n;

int main(){
	scanf("%d",&n);
	for(int i=1; i<=n; i++){
		scanf("%d",&w[i]);
	}
	for(int i=n+1; i>=1; i--){
		B[i] = MB[i+1];
		D[i] = MD[i+1];
		MB[i] = MB[i+1];
		MD[i] = MD[i+1];
		if(MB[i].first <= D[i].first + w[i-1]){
			MB[i] = D[i];
			MB[i].first += w[i-1];
		}
		if(MD[i].second <= B[i].second + w[i-1]){
			MD[i] = B[i];
			MD[i].second += w[i-1];
		}
	}
	cout << B[1].first << " " << B[1].second;
}