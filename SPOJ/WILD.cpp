// Ivan Carvalho
// Solution to https://www.spoj.com/problems/WILD/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef tuple<ll,ll,ll> trinca;
typedef pair<ll,ll> ii;
const int MAXN = 1e5 + 10;
ll seg[4*MAXN],lazy[4*MAXN],N,M,maximo[4*MAXN],minimo[4*MAXN],ans;
set<ii> cjt;
vector<trinca> sweep;
void propagate(int pos,int left,int right){
	if(lazy[pos] == 0) return;
	seg[pos] = (right - left + 1)*lazy[pos];
	maximo[pos] = minimo[pos] = lazy[pos];
	if(left != right){
		lazy[2*pos] = max(lazy[pos],lazy[2*pos]);
		lazy[2*pos+1] = max(lazy[pos],lazy[2*pos+1]);
	}
	lazy[pos] = 0;
	return;
}
void update(int pos,int left,int right,int i,int j,ll val){
	propagate(pos,left,right);
	if(left > right||left>j||right<i || minimo[pos] >= val) return;
	if(left >= i && right <= j && maximo[pos] <= val){
		lazy[pos] = val;
		propagate(pos,left,right);
		return;
	}
	int mid = (left+right)/2;
	update(2*pos,left,mid,i,j,val);
	update(2*pos+1,mid+1,right,i,j,val);
	seg[pos] = seg[2*pos] + seg[2*pos+1];
	maximo[pos] = max(maximo[2*pos],maximo[2*pos+1]);
	minimo[pos] = min(minimo[2*pos],minimo[2*pos+1]);
}
void add(ll pos,ll val){
	update(1,1,M,1,pos,val);
}
int main(){
	cin.tie(0);ios_base::sync_with_stdio(0);
	while(cin >> N >> M && (N||M)){
		sweep.clear();
		cjt.clear();
		ans = 0;
		for(int i = 1;i<=4*M;i++){
			seg[i] = lazy[i] = maximo[i] = minimo[i] = 0;
		}
		for(int i = 1;i<=N;i++){
			ll a,b,c;
			cin >> a >> b >> c;
			sweep.push_back(make_tuple(a,b,c));
		}
		sort(sweep.begin(),sweep.end());
		for(int i = M;i>=1;i--){
			while(!sweep.empty() && get<0>(sweep.back()) == i){
				add(get<1>(sweep.back()),get<2>(sweep.back()));
				sweep.pop_back();
			}
			ans += M*M - seg[1];
		}
		cout << ans << endl;
	}
	return 0;
} 
