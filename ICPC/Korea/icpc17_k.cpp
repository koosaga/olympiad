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
const int MAXN = 300005;
const int mod = 1e9 + 7;
const int dx[4] = {0, -1, 0, 1};
const int dy[4] = {1, 0, -1, 0};
int n;

int main(){
	scanf("%d",&n);
	int sx = 0, sy = 0, ex = 0, ey = 1;
	int dir = 0;
	int cx = 0, cy = 1;
	printf("1 ");
	for(int i=1; i<=n-1; i++){
		int y;
		scanf("%*d %d",&y);
		dir = (dir + 4 + y) % 4;
		if(dir == 0){
			printf("%d ", ey + 1 - cy);
			cy = ++ey;
		}
		if(dir == 1){
			printf("%d ", cx + 1 - sx);
			cx = --sx;
		}
		if(dir == 2){
			printf("%d ", cy + 1 - sy);
			cy = --sy;
		}
		if(dir == 3){
			printf("%d ", ex + 1 - cx);
			cx = ++ex;
		}
	}
}
