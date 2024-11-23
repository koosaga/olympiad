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

#define N_ 251000

int n, par[N_], chk[N_], C[N_], res;
ll W, Dis[N_];
vc<pil> E[N_];
vc<ll> U[N_];

int get_mid(int a, int pp, int K){
	for(auto &[x,l]:E[a]){
		if(chk[x] || x==pp || C[x]<=K)continue;
		return get_mid(x,a,K);
	}
	return a;
}

void DFS1(int a, int pp, ll d){
	Dis[a]=d;
	C[a]=1;
	for(auto &[x,l]: E[a]){
		if(chk[x] || x==pp)continue;
		DFS1(x,a,d+l);
		C[a]+=C[x];
	}
}

int M=0;
ll T[1010000], Y[1010000];
ll pL[N_];

void DFS2(int a, int pp, ll d, int c){
	if(a > pp){
		rep(i,si(U[a])){
			T[c+i+1] = min(T[c+i+1], d-pL[a] + U[a][i]);
		}
		c += si(U[a]);
	}
	else{
		rep(i,si(U[pp])){
			T[c+si(U[pp])-i] = min(T[c+si(U[pp])-i], d-U[pp][i]);
		}
		c += si(U[pp]);
	}
	M=max(M,c);
	for(auto &[x,l]: E[a]){
		if(chk[x] || x==pp)continue;
		DFS2(x,a,d+l,c);
	}
}


void Cent(int a){
	DFS1(a,0,0);
	if(C[a]==1)return;
	int m =get_mid(a, 0, C[a]/2);
	chk[m]=1;
	for(auto &[x,l]:E[m]){
		if(!chk[x]){
			Cent(x);
		}
	}
	//puts("?");
	chk[m]=0;

	vc<vc<ll>>Z;

	int mmm=0;
	for(auto &[x,l]:E[m]){
		if(!chk[x]){
			M=0;
			DFS2(x,m,l,0);
			mmm=max(mmm,M);
			//printf("%lld\n",M);

			
			rng(i,1,M){
				//printf("%lld ",T[i]);
				if(T[i]<=W){
					res=max(res,i);
					int pv = lower_bound(Y+1,Y+1000001,W-T[i]+1) - Y;
					if(pv>1){
						res=max(res, i + pv-1);
					}
				}
				
			}

			rng(i,1,M){
				Y[i]=min(Y[i],T[i]);
				T[i]=2e18;
			}


			/*while(si(Z) < si(T)){
				Z.pb(T[si(Z)]);
			}
			rep(i,si(T)){
				Z[i]=max(T[i],Z[i]);
			}*/
		}
	}
	rng(i,0,mmm)Y[i]=2e18;
	//puts("!");

}

void Solve(){
	scanf("%d%lld",&n,&W);
	rng(i,2,n){
		int a;
		scanf("%d",&a);
		//a=rand_int(1,i-1);
		ll l;
		scanf("%lld",&l);
		//l = rand_int(1,10000000000LL);
		E[a].pb({i,l});
		E[i].pb({a,l});
		
		pL[i] = l;
		
		int K;
		scanf("%d",&K);
		//K = rand_int(0,min(6ll,l-1));
		U[i].resize(K);
		rep(j,K){
			//U[i][j]=j+1;
			scanf("%lld",&U[i][j]);
		}
		rep(j,K){
			int pv = lower_bound(all(U[i]), U[i][j]-W)-U[i].begin();
			res=max(res,j-pv+1);
		}
	}
	rng(i,0,1000005)Y[i]=T[i]=2e18;
	Cent(1);
	printf("%d\n",res);
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