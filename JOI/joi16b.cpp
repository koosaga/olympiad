#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <limits.h>
#include <math.h>
#include <time.h>
#include <iostream>
#include <functional>
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
 
char str[100005];
int n;
 
int main(){
	cin >> n >> (str+1);
	lint ret = 0;
	lint s1 = 0, s2 = 0;
	for(int i=n; i; i--){
		if(str[i] == 'I') s2++;
		if(str[i] == 'O') s1 += s2;
		ret = max(ret, s1);
	}
	s1 = 0, s2 = 0;
	for(int i=1; i<=n; i++){
		if(str[i] == 'J') s2++;
		if(str[i] == 'O') s1 += s2;
		ret = max(ret, s1);
	}
	s1 = 0, s2 = 0;
	for(int i=1; i<=n; i++){
		if(str[i] == 'I') s1++;
	}
	for(int i=1; i<=n; i++){
		if(str[i] == 'J') s2++;
		if(str[i] == 'I') s1--;
		ret = max(ret, s1 * s2);
	}
	s1 = 0, s2 = 0;
	for(int i=1; i<=n; i++){
		if(str[i] == 'J') s1++;
		if(str[i] == 'O') s2+=s1;
		if(str[i] == 'I') ret += s2;
	}
	cout << ret;
}
