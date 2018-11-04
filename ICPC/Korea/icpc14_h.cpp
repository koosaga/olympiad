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
	int t;
	scanf("%d",&t);
	while(t--){
		char s1[100005], s2[100005];
		scanf("%s %s",s1,s2);
		vector<int> v1, v2;
		for(int i=0; s1[i]; i++){
			if(s1[i] == 'b') v1.push_back(i);
			if(s2[i] == 'b') v2.push_back(i);
		}
		lint ret = 0;
		for(int i=0; i<v1.size(); i++){
			ret += abs(v1[i] - v2[i]);
		}
		printf("%lld\n",ret);
	}
}