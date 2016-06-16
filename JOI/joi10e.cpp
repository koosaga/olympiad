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
  
int n, h;
  
int a[100005], b[100005];
int th[100005];

priority_queue<pi> pq;

struct bit{
	int tree[100005];
	void add(int x, int v){
		while(x <= n){
			tree[x] += v;
			x += x & -x;
		}
	}
	void range_add(int s, int e, int x){
		add(s, x);
		add(e+1, -x);
	}
	int get(int x){
		int ret = 0;
		while(x){
			ret += tree[x];
			x -= x & -x;
		}
		return ret;
	}
}bit;

int main(){
    int ret = 0;
    cin >> n >> th[1];
    int s = 1, dmax = 0;
    bit.range_add(1, 1, th[1]);
    for(int i=1; i<n; i++){
        scanf("%d %d",&a[i], &b[i]);
        pq.push(pi(b[i], i));
        while(bit.get(i) <= a[i]){
            while(!pq.empty() && (pq.top().second < s || th[1] - bit.get(pq.top().second) < pq.top().first)){
                dmax = max(dmax, pq.top().second);
                pq.pop();
            }
            pi t(-1, -1);
            if(dmax >= s){
                t = max(t, pi(th[1] - bit.get(dmax), dmax));
            }
            if(!pq.empty()){
                t = max(t, pq.top());
            }
            s = t.second;
            if(th[1] - bit.get(s) <= b[s]){
                bit.range_add(s, i, t.first);
                ret++;
            }
            else{
                int up = (th[1] - bit.get(s)) / b[s];
                up = min(up, (a[i] - bit.get(i)) / b[s] + 1);
                bit.range_add(s, i, up * t.first);
                ret += up;
            }
        }
        th[i+1] = bit.get(i) - a[i];
        bit.range_add(i+1, i+1, th[i+1]);
    }
    cout << ret;
}