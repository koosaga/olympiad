// given multiplicative function f, and g where prefix sum of g and f * g is easy, find the prefix sum of f
// https://en.wikipedia.org/wiki/Dirichlet_convolution#Related_concepts
namespace moe{
	lint moe[MAXN], sum[MAXN];
	lint inv;
	lint f(lint x){  return moe[x]; }
	lint gs(lint x){ return x; } 
	lint fgs(lint x){ return 1; }
	// if you take f(x) = mobius(x), g(x) = 1, then h(x) = sum f * g(x)  = 1
	void init(){
		moe[1] = 1;
		for(int i=1; i<MAXN; i++){
			for(int j=2*i; j<MAXN; j+=i){
				moe[j] -= moe[i];
			}
		}
		inv = gs(1);
		for(int i=1; i<MAXN; i++){
			sum[i] = sum[i-1] + f(i);
		}
	}
	unordered_map<lint, lint> mp;
	lint query(lint x){
		if(x < MAXN) return sum[x];
		if(mp.find(x) != mp.end()) return mp[x];
		lint ans = fgs(x);
		for(lint i=2; i<=x; ){
			lint cur = x / (x / i);
			ans -= (gs(cur) - gs(i - 1)) * query(x / i);
			i = cur + 1;
		}
		ans /= inv;
		return mp[x] = ans;
	}
};
