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
 
int n, cnt[10000];
int m;
int nxt[10005][10];
char str[10005];
 
int main(){
	cin >> n;
	for(int i=0; i<n; i++){
		cin >> m >>  str;
		for(int j=0; j<10; j++) nxt[m][j] = m;
		for(int j=m-1; j>=0; j--){
			for(int k=0; k<10; k++){
				nxt[j][k] = nxt[j+1][k];
				if(str[j] == k + '0') nxt[j][k] = j;
			}
		}
		int pp[4];
		for(int i=0; i<10000; i++){
			for(int j=3, v = i; j>=0; j--){
				pp[j] = v % 10; v /= 10;
			}
			int p = 0;
			for(int j=0; j<4; j++){
				p = nxt[p][pp[j]];
			}
			if(p < m) cnt[i]++;
		}
	}
	cout << count(cnt, cnt + 10000, n);
}