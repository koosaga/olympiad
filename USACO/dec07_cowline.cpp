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

int n;
char s[30001];
string ret;

char buf[60005];
int sfx[60005], ord[60005], nord[60005], rev[60005], p = 1;

bool cmp(int a, int b){
	if(ord[a] != ord[b]) return ord[a] < ord[b];
	return ord[a+p] < ord[b+p];
}

bool select(int l, int r){
	r = 2 * n - r;
	return rev[l] < rev[r];
}

void getsfx(){
    for(int i=0; i<=2*n; i++){
    	sfx[i] = i;
    	ord[i] = buf[i];
    }
    ord[2*n+1] = -1;
    while(1){
    	sort(sfx, sfx + 2*n+1, cmp);
    	if(p * 2 >= 2*n+1) break;
    	nord[sfx[0]] = 0;
    	for(int i=1; i<=2*n; i++){
    		if(cmp(sfx[i-1], sfx[i])){
    			nord[sfx[i]] = nord[sfx[i-1]] + 1;
    		}
    		else nord[sfx[i]] = nord[sfx[i-1]];
    	}
    	memcpy(ord, nord, (2*n+1) * sizeof(int));
    	p <<= 1;
    }
    for(int i=0; i<=2*n; i++){
    	rev[sfx[i]] = i;
    }
}

int main(){
    scanf("%d",&n);
    for (int i=0; i<n; i++) {
        scanf(" %c",&s[i]);
    }
    for(int i=0; i<n; i++){
    	buf[i] = buf[2*n-i] = s[i];
    }
    buf[n] = -1;
    getsfx();
    int l=0,r=n-1;
    while (l<=r) {
        if(select(l, r)) ret.push_back(s[l++]);
        else ret.push_back(s[r--]);
    }
    for (int i=0; i<n; i++) {
        putchar(ret[i]);
        if(i%80 == 79) puts("");
    }
}