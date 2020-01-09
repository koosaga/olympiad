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

char str[1005][55];
int n, m;

int mp[256];
char mp2[5] = "ACGT";

int main(){
	for(int i=0; i<4; i++){
		mp[mp2[i]] = i;
	}
	scanf("%d %d",&n,&m);
	for(int i=0; i<n; i++){
		scanf("%s",str[i]);
	}
	int val = 0;
	for(int k=0; k<m; k++){
		int cnt[4] = {};
		for(int j=0; j<n; j++){
			cnt[mp[str[j][k]]]++;
		}
		int t = max_element(cnt, cnt+4) - cnt;
		putchar(mp2[t]);
		val += n - cnt[t];
	}
	printf("\n%d",val);
}