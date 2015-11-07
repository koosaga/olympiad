#include <cstdio>
#include <algorithm>  
#include <cstring>  
using namespace std;  
typedef long long lint;
 
struct rmq{
	lint tree[270000];
	int lim;
	void init(int n){
		for(lim = 1; lim <= n; lim <<= 1);
	}
	void add(int x, lint v){
		x += lim;
		tree[x] = max(tree[x], v);
		while(x > 1){
			x >>= 1;
			tree[x] = max(tree[2*x],tree[2*x+1]);
		}
	}
	lint q(int s, int e){
		s += lim;
		e += lim;
		lint ret = 0;
		while(s < e){
			if(s%2 == 1) ret = max(ret,tree[s++]);
			if(e%2 == 0) ret = max(ret,tree[e--]);
			s >>= 1, e >>= 1;
		}
		if(s == e) ret = max(ret,tree[s]);
		return ret;
	}
}rmq;
 
int n, w[100005], a[100005];
lint dp[100005];
int main(){
	lint ret = 0;
	scanf("%d",&n);
	for(int i=1; i<=n; i++){
		scanf("%d",&w[i]);
		ret += 2 * w[i];
	}
	for(int i=1; i<=n; i++){
		scanf("%d",&a[i]);
	}
	rmq.init(n);
	for(int i=1; i<=n; i++){
		dp[i] = rmq.q(0, a[i] - 1) + w[a[i]];
		rmq.add(a[i], dp[i]);
	}
	ret -= rmq.tree[1] * 2;
	printf("%lld\n",ret);
}