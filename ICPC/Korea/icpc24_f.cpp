#include <bits/stdc++.h>
using namespace std;

#define rng(i,a,b) for(int i=int(a);i<=int(b);i++)
#define rep(i,b) rng(i,0,b-1)
#define gnr(i,b,a) for(int i=int(b);i>=int(a);i--)
#define per(i,b) gnr(i,b-1,0)
#define pb push_back
#define eb emplace_back
#define fi first
#define se second
#define bg begin()
#define edd end()
#define all(x) x.bg,x.edd
#define si(x) int(x.size())
template<class t> using vc=vector<t>;
template<class t> using vvc=vc<vc<t>>;
typedef long long ll;
using pii=pair<int,int>;
using vi=vc<int>;
using uint=unsigned;
using ull=unsigned long long;
using pil=pair<int,ll>;
using pli=pair<ll,int>;
using pll=pair<ll,ll>;
using t3=tuple<int,int,int>;

ll rand_int(ll l, ll r) { //[l, r]
	#ifdef LOCAL
	static mt19937_64 gen;
	#else
	static mt19937_64 gen(chrono::steady_clock::now().time_since_epoch().count());
	#endif
	return uniform_int_distribution<ll>(l, r)(gen);
}


struct modinfo{uint mod,root;};
template<modinfo const&ref>
struct modular{
	static constexpr uint const &mod=ref.mod;
	static modular root(){return modular(ref.root);}
	uint v;
	//modular(initializer_list<uint>ls):v(*ls.bg){}
	modular(ll vv=0){s(vv%mod+mod);}
	modular& s(uint vv){
		v=vv<mod?vv:vv-mod;
		return *this;
	}
	modular operator-()const{return modular()-*this;}
	modular& operator+=(const modular&rhs){return s(v+rhs.v);}
	modular&operator-=(const modular&rhs){return s(v+mod-rhs.v);}
	modular&operator*=(const modular&rhs){
		v=ull(v)*rhs.v%mod;
		return *this;
	}
	modular&operator/=(const modular&rhs){return *this*=rhs.inv();}
	modular operator+(const modular&rhs)const{return modular(*this)+=rhs;}
	modular operator-(const modular&rhs)const{return modular(*this)-=rhs;}
	modular operator*(const modular&rhs)const{return modular(*this)*=rhs;}
	modular operator/(const modular&rhs)const{return modular(*this)/=rhs;}
	modular pow(int n)const{
		modular res(1),x(*this);
		while(n){
			if(n&1)res*=x;
			x*=x;
			n>>=1;
		}
		return res;
	}
	modular inv()const{return pow(mod-2);}
	/*modular inv()const{
		int x,y;
		int g=extgcd(v,mod,x,y);
		assert(g==1);
		if(x<0)x+=mod;
		return modular(x);
	}*/
	friend modular operator+(int x,const modular&y){
		return modular(x)+y;
	}
	friend modular operator-(int x,const modular&y){
		return modular(x)-y;
	}
	friend modular operator*(int x,const modular&y){
		return modular(x)*y;
	}
	friend modular operator/(int x,const modular&y){
		return modular(x)/y;
	}
	friend ostream& operator<<(ostream&os,const modular&m){
		return os<<m.v;
	}
	friend istream& operator>>(istream&is,modular&m){
		ll x;is>>x;
		m=modular(x);
		return is;
	}
	bool operator<(const modular&r)const{return v<r.v;}
	bool operator==(const modular&r)const{return v==r.v;}
	bool operator!=(const modular&r)const{return v!=r.v;}
	explicit operator bool()const{
		return v;
	}
};
extern constexpr modinfo base{1000000007,0};
using mint=modular<base>;
using pdi = pair<double, int>;
using ld = long double;

int n, res=0;

int w[110][2];
vc<array<int,3>>V;
void Go(int a, int b, int c){
	if(a==c)return;
	res++;
	if(w[a+1][0] <= w[a+1][1]){
		V.pb({a,c,w[a+1][0]});
		swap(w[a][b],w[a+1][0]);
		Go(a+1,0,c);
	}
	else{
		V.pb({a,c,w[a+1][1]});
		swap(w[a][b],w[a+1][1]);
		Go(a+1,1,c);
	}
}

void Solve(){
	scanf("%d",&n);
	rng(i,1,n){
		w[i][0]=w[i][1]=n-i+1;
	}
	gnr(i,n,1){
		rng(j,1,n){
			rep(ck,2){
				if(w[j][ck] == i){
					assert(j <= i);
					if(j==i)continue;
					Go(j,ck,i);
				}
			}
		}
	}
	printf("%d\n",si(V));
	for(auto &t:V){
		printf("%d %d %d\n",t[0],t[1],t[2]);
	}
	

}

int main(){
	int TC=1;
	//scanf("%d",&TC);
	rng(T,1,TC){
		Solve();
	}
}


/*
4321
4321

1432
3214

1132
3244

1332
1244

1334
1224

6 swaps




126543
126543 -> 12 swaps needed

126543
432165


123456
123456

-> 

123543
412656

165432
543216*/