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

vector<int> v;

int main(){
	int t;
	scanf("%d",&t);
	while(t--){
		int n, m, p, q;
		scanf("%d %d %d %d",&m,&n,&p,&q);
		p--, q--;
		int ret = -1;
		for(int i=0; i<n; i++){
			int t = p + i * m;
			if(t % n == q){
				ret = t + 1;
				break;
			}
		}
		printf("%d\n",ret);
	}
}