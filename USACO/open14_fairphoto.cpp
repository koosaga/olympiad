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
typedef long double llf;
typedef pair<int, int> pi;

typedef long long hsh;
const int line4 = 409433;

hsh vhash(vector<int> &v){
	hsh tmp = 0;
	for(int i=0; i<v.size(); i++){
		tmp = tmp * line4 + v[i];
	}
	return tmp;
}

int n, k;
pi a[100005];
int nxtl[100005][8], nxtr[100005][8], sum[100005][8];

int getnxtl(int pos, int bit){
	int ret = -1e9, retp = -1;
	for(int j=0; j<8; j++){
		if((bit >> j) % 2 == 0){
			if(ret < nxtl[pos][j]){
				ret = nxtl[pos][j];
				retp = j;
			}
		}
	}
	return retp;
}

int getnxtr(int pos, int bit){
	int ret = 1e9, retp = -1;
	for(int j=0; j<8; j++){
		if((bit >> j) % 2 == 0){
			if(ret > nxtr[pos][j]){
				ret = nxtr[pos][j];
				retp = j;
			}
		}
	}
	return retp;
}

vector<pair<hsh, int>> v;

int main(){
	scanf("%d %d",&n,&k);
	for(int i=1; i<=n; i++){
		scanf("%d %d",&a[i].first, &a[i].second);
		a[i].second--;
	}
	sort(a+1, a+n+1);
	for(int i=0; i<8; i++){
		nxtr[n+1][i] = 2e9;
		nxtl[0][i] = -2e9;
	}
	for(int i=1; i<=n; i++){
		for(int j=0; j<8; j++){
			nxtl[i][j] = nxtl[i-1][j];
			nxtr[n+1-i][j] = nxtr[n+2-i][j];
			sum[i][j] = sum[i-1][j];
		}
		nxtl[i][a[i].second] = i;
		nxtr[n+1-i][a[n+1-i].second] = n+1-i;
		sum[i][a[i].second]++;
	}
	int ret = 0;
	for(int i=0; i<n; i++){
		int cbit = 0, cpos = i+1;
		vector<int> construct;
		for(int j=0; j<8; j++){
			int nxt = getnxtr(cpos, cbit);
			if(nxt == -1) break;
			cbit |= 1<<nxt;
			construct.push_back(cbit);
			cpos = nxtr[cpos][nxt];
		}
		for(int j=k; j<=construct.size(); j++){
			int t = construct[j-1];
			vector<int> elem;
			for(int k=0; k<8; k++){
				if((t >> k) & 1) elem.push_back(sum[i][k]);
			}
			int tmp = *min_element(elem.begin(), elem.end());
			for(auto &j : elem){
				j -= tmp;
			}
			elem.push_back(t);
			v.push_back(make_pair(vhash(elem), i));
		}
	}
	sort(v.begin(), v.end());
	for(int i=1; i<=n; i++){
		int cbit = 0, cpos = i;
		for(int j=0; j<8; j++){
			int nxt = getnxtl(cpos, cbit);
			if(nxt == -1) break;
			cbit |= 1<<nxt;
			if(j >= k-1){
				int t = cbit;
				vector<int> elem;
				for(int k=0; k<8; k++){
					if((t >> k) & 1) elem.push_back(sum[i][k]);
				}
				int tmp = *min_element(elem.begin(), elem.end());
				for(auto &j : elem){
					j -= tmp;
				}
				elem.push_back(cbit);
				tmp = getnxtl(nxtl[cpos][nxt], cbit);
				int sentinel = 0;
				if(tmp != -1) sentinel = nxtl[nxtl[cpos][nxt]-1][tmp] - 1;
				auto it = lower_bound(v.begin(), v.end(), make_pair(vhash(elem), sentinel));
				if(it != v.end() && it->first == vhash(elem)){
					ret = max(ret, a[i].first - a[it->second + 1].first);
				}
			}
			cpos = nxtl[cpos][nxt];
		}
	}
	if(ret == 0) ret = -1;
	cout << ret;
}