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
 
int n, a[100005];
int che[200005];
 
int moebius(int x){
	int lst = -1, cnt = 0;
	while(x > 1){
		if(lst == che[x]) return 0;
		lst = che[x];
		x /= che[x];
		cnt++;
	}
	if(cnt % 2 == 0) return 1;
	return -1;
}
 
lint trial(lint x){
	lint ret = x;
	for(int i=1; 1ll*i*i<=x; i++){
		ret -= 1ll * moebius(i) * (x / (1ll * i * i));
	}
	return ret;
}
 
int main(){
	for(int i=2; i<=200000; i++){
		for(int j=i; j<=200000; j+=i){
			if(!che[j]) che[j] = i;
		}
	}
	lint s = 1, e = 4e10, n;
		scanf("%lld",&n);
		while(s != e){
			lint m = (s+e)/2;
			if(trial(m) >= n) e = m;
			else s = m+1;
		}
		printf("%lld\n",s);
}