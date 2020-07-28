// Ivan Carvalho
// Solution to https://www.spoj.com/problems/APIO10A/
#include <cstdio>
#include <algorithm>
#include <set>
#define gc getchar_unlocked
using namespace std;
typedef long long ll;
void getll(ll &x){
    register ll c = gc();
    x = 0;
    for(;(c<48 || c>57);c = gc());
    for(;c>47 && c<58;c = gc()) {x = (x<<1) + (x<<3) + c - 48;}
}
struct line{
	ll a,b;
	double xleft;
	bool type;
	line(long long _a,long long _b){
		a = _a;
		b = _b;
		type = 0;
	}
	bool operator <(const line &other) const{
		if(other.type) return xleft < other.xleft;
		return a > other.a;
	}
};
double meet(line x,line y){
	return 1.0 * (y.b - x.b)/(x.a-y.a);
}
struct cht{
	set<line> hull;
	cht(){
		hull.clear();
	}
	typedef set<line>::iterator ite;
	bool hasleft(ite node){
		return node != hull.begin();
	}
	bool hasright(ite node){
		return node != prev(hull.end());
	}
	void updateborder(ite node){
		if(hasright(node)){
			line temp = *next(node);
			hull.erase(temp);
			temp.xleft = meet(*node,temp);
			hull.insert(temp);
		}
		if(hasleft(node)){
			line temp = *node;
			temp.xleft = meet(*prev(node),temp);
			hull.erase(node);
			hull.insert(temp);
		}
		else{
			line temp = *node;
			hull.erase(node);
			temp.xleft = -1e16;
			hull.insert(temp);
		}
	}
	bool useless(line left,line mid,line right){
		double x = meet(left,right);
		double y = x*mid.a + mid.b;
		double ly = left.a*x + left.b;
		return y > ly;
	}
	bool useless(ite node){
		if(hasleft(node) && hasright(node)){
			return useless(*prev(node),*node,*next(node));
		}
		return 0;
	}
	void addline(ll a,ll b){
		line temp = line(a,b);
		ite it = hull.lower_bound(temp);
		if(it != hull.end() && it->a == a){
			if(it->b > b){
				hull.erase(it);
			}
			else{
				return;
			}
		}
		hull.insert(temp);
		it = hull.find(temp);
		if(useless(it)){
			hull.erase(it);
			return;
		}
		while(hasleft(it) && useless(prev(it))){
			hull.erase(prev(it));
		}
		while(hasright(it) && useless(next(it))){
			hull.erase(next(it));
		}
		updateborder(it);
	}
	ll getbest(ll x){
		line query(0,0);
		query.xleft = x;
		query.type =1;
		ite it = hull.lower_bound(query);
		it = prev(it);
		return it->a *x + it->b;
 	}
};
int main(){
	int TC;
	scanf("%d",&TC);
	cht dp;
	while(TC--){
		dp.hull.clear();
		int n;
		scanf("%d",&n);
		ll a,b,c;
		scanf("%lld %lld %lld",&a,&b,&c);
		dp.addline(0LL,0LL);
		ll davez, soma = 0;
		for(int i=1;i<n;i++){
			getll(davez);
			soma += davez;
			ll best = -dp.getbest(soma) + a*soma*soma + b*soma + c;
			dp.addline(-(-2*a*soma),-(best + a*soma*soma - b*soma));
		}
		scanf("%lld",&davez);
		soma += davez;
		ll best = -dp.getbest(soma) + a*soma*soma + b*soma + c;
		printf("%lld\n",best);
	}
	return 0;
}