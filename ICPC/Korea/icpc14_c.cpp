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
#include <utility>
#include <bitset>
#include <iostream>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<int, int> pi;

int main(){
	vector<int> v;
	for(int i=1; (i*i+i)/2 <= 1000; i++){
		v.push_back((i * i + i) / 2);
	}
	int t;
	scanf("%d",&t);
	while(t--){
		int u;
		scanf("%d",&u);
		int ok = 0;
		for(int i=0; i<v.size(); i++){
			for(int j=0; j<=i; j++){
				for(int k=0; k<=j; k++){
					if(v[i] + v[j] + v[k] == u){
						ok = 1;
					}
				}
			}
		}
		printf("%d\n",ok);
	}
}