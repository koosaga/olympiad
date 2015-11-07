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

int n, a[1005];  
int nd[1005], vis[1005];  

int main(){
	scanf("%d",&n);
	for(int i=0; i<n; i++){
		scanf("%d",&a[i]);
	}  
	for(int i=0; i<n; i++){  
		for(int j=0; j<n; j++){  
			if(a[j] < a[i]) nd[i]++;  
		}
	}
	int ret = 0, minvv = *min_element(a, a+n);
	for(int i=0; i<n; i++){
		if(!vis[i]){
			int minp = 1e9;
			int cnt = 0;
			int p = i;
			while(!vis[p]){
				cnt++;
				ret += a[p];
				minp = min(minp, a[p]);
				vis[p] = 1;
				p = nd[p];
			}
			ret += min((cnt - 2) * minp, minp + minvv + cnt * minvv);
		}
	}
	printf("%d",ret);  
}