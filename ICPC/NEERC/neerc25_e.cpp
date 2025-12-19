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
#define ed end()
#define all(x) x.bg,x.ed
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
using namespace std;
#define N_ 201000
int D[1<<20][20];
set<int>Set;
map<int, vc<vc<pii>>>Map;
void Calc(vc<pii> U){
    /*for(auto &t: U){
        printf("%d %d\n",t.fi,t.se);
    }*/
    int n = si(U);
    vi H(2*n);
    rep(i,n){
        H[i*2] = U[i].fi;
        H[i*2+1]=U[i].se;
    }
    rep(i,(1<<(2*n)))rep(j,2*n)D[i][j]=-1e9;
    rep(i,n){
        D[1<<(2*i)][2*i] = U[i].fi - 1;
    }
    rep(i,(1<<(2*n))){
        if(!i)continue;
        rep(j,2*n){
            if(D[i][j]<0)continue;
            rep(k,2*n){
                if((i>>k)&1)continue;
                if(k%2==1 && ((i>>(k-1))&1)==0)continue;
                D[i|(1<<k)][k] = max(D[i|(1<<k)][k], D[i][j] + abs(H[k]-H[j]));
            }
        }
    }
    int r=-1e9;
    rep(i,2*n)r=max(r, D[(1<<(2*n))-1][i]);

    Map[r].push_back(U);
    Set.insert(r);
    //printf("%d\n\n",r);


}

ll Calc2(vc<pii> U){
    /*for(auto &t: U){
        printf("%d %d\n",t.fi,t.se);
    }*/
    int n = si(U);
    vi H(2*n);
    rep(i,n){
        H[i*2] = U[i].fi;
        H[i*2+1]=U[i].se;
    }
    rep(i,(1<<(2*n)))rep(j,2*n)D[i][j]=-1e9;
    rep(i,n){
        D[1<<(2*i)][2*i] = U[i].fi - 1;
    }
    rep(i,(1<<(2*n))){
        if(!i)continue;
        rep(j,2*n){
            if(D[i][j]<0)continue;
            rep(k,2*n){
                if((i>>k)&1)continue;
                if(k%2==1 && ((i>>(k-1))&1)==0)continue;
                D[i|(1<<k)][k] = max(D[i|(1<<k)][k], D[i][j] + abs(H[k]-H[j]));
            }
        }
    }
    int r=-1e9;
    rep(i,2*n)r=max(r, D[(1<<(2*n))-1][i]);
    return r;

}
ll rand_int(ll l, ll r) { //[l, r]
	#ifdef LOCAL
	static mt19937_64 gen;
	#else
    static mt19937_64 gen(chrono::steady_clock::now().time_since_epoch().count());
    #endif
    return uniform_int_distribution<ll>(l, r)(gen);
}

ll Get(vc<pii>w){
    
/*1. n-th is right => Optimal.

2. if small n is all left

Z = (smallest right big but not pair of nth - nth) is possible
    (smallest right big - nth) * 2 is possible

3. if not
X = (n-th - biggest right small) is possible
Y = (smallest right big - nth) is possible*/

    int n = si(w);
    vc<pii>U;
    rep(i,n){
        auto [x,y] = w[i];
        U.pb({x,i*2});
        U.pb({y,i*2+1});
    }
    sort(all(U));

    ll opt = 0;
    opt-=1;
    rep(i,n){
        opt-=U[i].fi*2;
        opt+=U[n+i].fi*2;
    }
    ll x = U[n-1].fi;
    opt += x;

    if(U[n-1].se%2 == 1){
        return opt;
    }
    ll ans = 0;
    int chk=0;
    rep(i,n){
        if(U[i].se%2 == 1){
            ans=max(ans, opt - (x - U[i].fi));
            chk=1;
        }
    }
    if(chk){
        rep(i,n){
            if(U[n+i].se%2==1){
                ans=max(ans, opt - (U[n+i].fi - x));
            }
        }
    }
    //possibly, right-x + (x-x')*2 
    //ok, but, somet
    rep(i,n){
        if(U[n+i].se%2==1 && U[n+i].se-U[n-1].se != 1){
            ans=max(ans, opt - (U[n+i].fi - x));
        }
        if(U[n+i].se%2==1){
            ans=max(ans, opt - (U[n+i].fi - x)*3);
        }
    }
    if(!chk)ans=max(ans, opt - ( U[n-1].fi+U[n].fi - U[n-2].fi*2));
    return ans;
}
/*void Do(int n){
    vi Z(2*n);
    rep(i,2*n){
        Z[i]=rand_int(2,100);
    }
    Map.clear();
    Set.clear();
    sort(all(Z));
    int Mn = Z[0];
   // for(auto &t: Z)printf("%d ",t);
   // puts("");
    do{
        if(Z[0]!=Mn)break;
        vc<pii>U;
        rep(j,n){
            U.pb({Z[j*2],Z[j*2+1]});
        }
        Calc(U);
    }while(next_permutation(all(Z)));
    random_device rd;
    mt19937_64 g(rd());
    for(auto &t: Set){
        printf("%d\n",t);
        shuffle(all(Map[t]),g);
        rep(j,min(si(Map[t]),5)){
            for(auto &z: Map[t][j])printf("%d %d\n",z.fi,z.se);
            puts("");
        }
    }
    //puts("");
}*/
void Solve(){
    int n;
    scanf("%d",&n);
    vc<pii>w;
    rep(i,n){
        int a,b;
        scanf("%d%d",&a,&b);
        w.pb({a,b});
    }
    printf("%lld\n",Get(w));
}

int main(){
	int TC=1;
    scanf("%d",&TC);
    rng(T,1,TC){
        Solve();
    }

}