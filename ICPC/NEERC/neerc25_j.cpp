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
int n, w[N_], K;
long double P[32][32], U[110][32][32], Z[32][32][110];
long double R[32][32], D[32][32];
int C[110];
void Solve(){
    scanf("%d%d",&n,&K);
    rng(i,1,n){
        scanf("%d",&w[i]);
        C[w[i]]++;
    }
    rng(i,0,100){
        U[i][0][0]=1;
        rng(j,1,K){
            rng(k,0,j){
                if(k!=j) U[i][j][k] += U[i][j-1][k] * (100-i)/100;
                if(k) U[i][j][k] += U[i][j-1][k-1] * i/100;
            }
        }
    }
    rng(i,0,K){
        rng(j,0,i){
            long double s=0;
            rng(k,0,100){
                s += C[k] * U[k][i][j];
            }
            //printf("%Lf\n",s);

            if(s<1e-40)continue;
            rng(k,0,100){
                Z[i][j][k] =  C[k] * U[k][i][j] / s;
            }
        }
    }
    D[0][0]=1;
    rng(i,0,K){
        rng(j,0,i){
            rng(k,0,100){
                D[i+1][j+1] += D[i][j] * C[k] * k/100 / n;
                D[i+1][j] += D[i][j] * C[k] * (100-k)/100 / n;
            }
        }
    }
    gnr(i,K,0){
        rng(j,0,i){
            if(i==K){
                R[i][j] = 1000;
                continue;
            }
            else{
                if(D[i][j] < 1e-40)continue;
                //*(2k)/100^T
                long double s=0;
                long double pp = 0;
                rng(k,0,100){
                    s += powl(0.02L*k, K-i)* 1000 * Z[i][j][k] ;
                    pp += Z[i][j][k]* k/100;
                }

                //printf("%d %f\n",i,pp);
                R[i][j]=max(pp * R[i+1][j+1] + R[i+1][j] * (1-pp), s);
            }
        }
    }
    printf("%.12Lf\n",R[0][0]-1000);
}

int main(){
	int TC=1;
    //scanf("%d",&TC);
    rng(T,1,TC){
        Solve();
    }

}