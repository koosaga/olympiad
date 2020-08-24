#include <stdio.h> 
#include <stdlib.h>
#include <string.h> 
#include <memory.h> 
#include <math.h> 
#include <assert.h> 
#include <stack> 
#include <queue> 
#include <map> 
#include <set> 
#include <string> 
#include <algorithm> 
#include <iostream> 
#include <functional>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
typedef pair<int, int> pi;
const int MAXN = 1000005;
const int mod = 1e9 + 7; 

char buf[MAXN];
int cnt[256];
string dap[1005];

int n, l, k;
int main(){
	scanf("%d %d %d",&n,&l,&k);
	scanf("%s", buf);
	for(int i=0; buf[i]; i++) cnt[buf[i]]++;
	int curSame = k;
	int alph = 'a';
	for(int i=0; i<l; i++){
		for(int j=k-curSame; j<=k-1; j++){
			while(!cnt[alph]) alph++;
			dap[j].push_back(alph), cnt[alph]--;
		}
		int j = k - 1;
		while(j >= 0 && sz(dap[j]) == i + 1 && dap[j][i] == alph) j--;
		curSame = k - 1 - j;
	}
	for(int i=0; i<n; i++){
		while(sz(dap[i]) < l){
			while(!cnt[alph]) alph++;
			dap[i].push_back(alph), cnt[alph]--;
		}
	}
	sort(dap, dap + n);
	for(int i=0; i<n; i++) cout << dap[i] << endl;
}
