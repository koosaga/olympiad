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
 
char str[155][155][155];
bool tab[155][155][155];
int p, q, r;
 
int maxr[155][155][155]; 
int h[155];

int maxrect(int n){
	int ret = 0;
	stack<int> stk;
	for(int i=1; i<=n; i++){
		while(!stk.empty() && h[stk.top()] >= h[i]){
			int l = stk.top();
			stk.pop();
			int bef = (!stk.empty() ? stk.top() : 0);
			ret = max(ret, (i - bef - 1) * h[l]);
		}
		stk.push(i);
	}
	while(!stk.empty()){
		int l = stk.top();
		stk.pop();
		int bef = (!stk.empty() ? stk.top(): 0);
		ret = max(ret, (n - bef) * h[l]);
	}
	return ret;
}

int solve(int p, int q, int r){
	memset(maxr, 0, sizeof(maxr));
	for(int i=1; i<=p; i++){
		for(int j=1; j<=q; j++){
			for(int k=1; k<=r; k++){
				maxr[i][j][k] = min(min(maxr[i][j-1][k], maxr[i][j][k-1]), maxr[i][j-1][k-1]) + 1;
				if(!tab[i][j][k]) maxr[i][j][k] = 0;
			}
		}
	}
	int ret = 0;
	for(int i=1; i<=q; i++){
		for(int j=1; j<=r; j++){
			for(int k=1; k<=p; k++){
				h[k] = maxr[k][i][j];
			}
			ret = max(ret, maxrect(p) * 4);
		}
	}
    return ret;
}
 
int main(){
    scanf("%d %d %d",&q,&p,&r);
    for(int i=1; i<=p; i++){
        for(int j=1; j<=q; j++){
            scanf("%s",str[i][j] + 1);
        }
    }
    for(int i=1; i<=p; i++){
        for(int j=1; j<=q; j++){
            for(int k=1; k<=r; k++){
                tab[i][j][k] = (str[i][j][k] == 'N');
            }
        }
    }
    int ret = solve(p, q, r);
    memset(tab, 0, sizeof(tab));
    for(int i=1; i<=q; i++){
        for(int j=1; j<=r; j++){
            for(int k=1; k<=p; k++){
                tab[i][j][k] = (str[k][i][j] == 'N');
            }
        }
    }
    ret = max(ret, solve(q, r, p));
    memset(tab, 0, sizeof(tab));
    for(int i=1; i<=r; i++){
        for(int j=1; j<=p; j++){
            for(int k=1; k<=q; k++){
                tab[i][j][k] = (str[j][k][i] == 'N');
            }
        }
    }
    ret = max(ret, solve(r, p, q));
    printf("%d",ret);
}