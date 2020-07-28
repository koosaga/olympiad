// Ivan Carvalho
// Solution to https://www.spoj.com/problems/GOODG/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MAXN = 1e6 + 10;
const ll NEG = -1e16;
struct line{
	ll a,b;
	line() : a(0),b(0){}
	line(ll _a,ll _b) : a(_a),b(_b){}
	ll get(ll x){
		return a*x + b;
	}
};
int vis[4*MAXN];
line seg[4*MAXN];
void update(int pos,ll left,ll right,line g){
	if(!vis[pos]){vis[pos] = 1;seg[pos] = g;return;}
	ll trl = seg[pos].get(left), trr = seg[pos].get(right);
	ll gl = g.get(left),gr = g.get(right);
	if(gl >= trl && gr >= trr){
		seg[pos] = g;
		return;
	} 
	if(trl >= gl && trr >= gr) return;
	ll mid = (left+right)/2;
	if(trl < gl) swap(seg[pos],g);
	if(seg[pos].get(mid) > g.get(mid)) update(2*pos+1,mid+1,right,g);
	else{
		swap(seg[pos],g);
		update(2*pos,left,mid,g);
	}
}
ll query(int pos,ll left,ll right,ll x){
	if(!vis[pos]) return NEG;
	if(left == right) return seg[pos].get(x);
	ll mid = (left+right)/2;
	if(x <= mid) return max(seg[pos].get(x), query(2*pos,left,mid,x) );
	return max(seg[pos].get(x), query(2*pos+1,mid+1,right,x) );
}
int main(){
	int N;
	scanf("%d",&N);
	update(1,1,N+1,line(0,0));
	for(int i = 1;i<=N;i++){
		int a,d;
		scanf("%d %d",&a,&d);
		ll best = query(1,1,N+1,i);
		update(1,1,N+1, line(-d, 1LL*d*i + a + best ) );
	}
	printf("%lld\n",query(1,1,N+1,N+1));
	return 0;
}