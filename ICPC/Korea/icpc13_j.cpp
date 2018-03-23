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

int g(int x, int y){
	return y ? g(y, x%y) : x;
}

int main(){
	vector<int> v;
	for(int i=1; i<=10000; i++){
		for(int j=i+1; 2ll * i * j<=10000; j++){
			int a = 2 * i * j;
			int b = j * j - i * i;
			if(g(a, b) == 1){
				v.push_back(2*a+2*b);
			}
		}
	}
	sort(v.begin(), v.end());
	//v.resize(unique(v.begin(), v.end()) - v.begin());
	int t;
	cin >> t;
	while(t--){
		int u;
		scanf("%d",&u);
		for(int i=0; i<v.size(); i++){
			if(u >= v[i]){
				u -= v[i];
			}
			else{
				printf("%d\n",i);
				break;
			}
		}
	}
}