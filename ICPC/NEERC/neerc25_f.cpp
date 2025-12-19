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
int n, w[N_];
map<vi,int>Map;
void Do(int s, vi &Z, int M){
    if(!s){
        vi U;
        int chk=1;
        rep(j,si(Z))U.pb(Z[j]);

        sort(all(U));
        rep(j,si(U)){
            int t=U[j];
            int ck=0;
            rng(k,1,t-1){
                vi TP = U;
                TP[j]-=k;
                sort(all(TP));
                if(Map[TP] == 0)ck=1;
            }
            vi TP;
            rep(k,si(U)){
                if(k!=j)TP.pb(U[k]);
            }
            sort(all(TP));
            if(Map[TP]==0)ck=1;
            if(!ck){
                chk=0;
                break;
            }
        }
        Map[U]=chk;
        for(auto &t: U)printf("%d ",t);
        printf(": %d\n",chk);
        return;
    }
    gnr(i,M,1){
        if(i<=s){
            Z.pb(i);
            Do(s-i,Z,i);
            Z.pop_back();
        }
    }
}
void Solve(){
    scanf("%d",&n);
    rng(i,1,n){
        scanf("%d",&w[i]);
    }
    int c=0;
    rng(i,1,n){
        if(w[i]==1){
            c++;
        }
    }
    if(c==n){
        if(n%2==0)printf("Bob\n");
        else printf("Alice\n");
    }
    else{
        if(c%2==1)printf("Bob\n");
        else printf("Alice\n");
    }
}

int main(){
	int TC=1;
    scanf("%d",&TC);
    rng(T,1,TC){
        Solve();
    }

}