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
 
ll rand_int(ll l, ll r) { //[l, r]
    #ifdef LOCAL
    static mt19937_64 gen;
    #else
    static mt19937_64 gen(chrono::steady_clock::now().time_since_epoch().count());
    #endif
    return uniform_int_distribution<ll>(l, r)(gen);
}
 
template <uint MD> struct ModInt {
    using M = ModInt;
    const static M G;
    uint v;
    ModInt(ll _v = 0) { set_v(_v % MD + MD); }
    M& set_v(uint _v) {
        v = (_v < MD) ? _v : _v - MD;
        return *this;
    }
    explicit operator bool() const { return v != 0; }
    M operator-() const { return M() - *this; }
    M operator+(const M& r) const { return M().set_v(v + r.v); }
    M operator-(const M& r) const { return M().set_v(v + MD - r.v); }
    M operator*(const M& r) const { return M().set_v(ull(v) * r.v % MD); }
    M operator/(const M& r) const { return *this * r.inv(); }
    M& operator+=(const M& r) { return *this = *this + r; }
    M& operator-=(const M& r) { return *this = *this - r; }
    M& operator*=(const M& r) { return *this = *this * r; }
    M& operator/=(const M& r) { return *this = *this / r; }
    bool operator==(const M& r) const { return v == r.v; }
    M pow(ll n) const {
        M x = *this, r = 1;
        while (n) {
            if (n & 1) r *= x;
            x *= x;
            n >>= 1;
        }
        return r;
    }
    M inv() const { return pow(MD - 2); }
    friend ostream& operator<<(ostream& os, const M& r) { return os << r.v; }
};
using Mint = ModInt<998244353>;
template<> const Mint Mint::G = Mint(3);


const int SZ = (1<<18);
#define N_ 401000

int n, w[4320][4320], DEB = 0;

char res[4320][4320]={
    "",
    ".........",
    ".........",
    "........",
    ".........",
    ".........",
    ".........",
    ".........",
    ".........",
};

int Query(int a, int x, int y){
    char p[10]=".^>v<", q[10];
    if(!DEB)printf("%c\n",p[a]);
    fflush(stdout);
    if(!DEB){
        scanf("%s",q);
    }
    else{
        q[0] = res[x][y];
        //printf("%c\n",q[0]);
    }
    if(q[0]=='G'){
        exit(0);
    }
    if(q[0]=='^')return 1;
    if(q[0]=='>')return 2;
    if(q[0]=='v')return 3;
    if(q[0]=='<')return 4;
    return 0;
}

void Go(int &x, int &y, int rx, int ry){
    while(x>rx){
        w[x-1][y] = Query(1,x-1,y); x--;
    }
    while(x<rx){
        w[x+1][y] = Query(3,x+1,y); x++;
    }
    while(y>ry){
        w[x][y-1] = Query(4,x,y-1); y--;
    }
    while(y<ry){
        w[x][y+1] = Query(2,x,y+1); y++;
    }
}

void Do(int bx, int by, int ex, int ey, int x, int y){
    if(DEB)printf("%d %d %d %d\n",bx,by,ex,ey);
    
    if(ex-bx<=1 && ey-by<=1)return;

    if(ex-bx<=3 || ey-by<=3){
        rng(i,bx,ex){
            rng(j,by,ey){
                Go(x,y,i,j);
            }
        }

    }
    int mx = (bx+ex)/2;
    int my = (by+ey)/2;

    if(ex-bx > ey-by){ // [mx,mx+1] x [by, ey]
        Go(x,y,mx,y);
        Go(x,y,mx,by);
        Go(x,y,mx,ey);
        Go(x,y,mx+1,ey);
        Go(x,y,mx+1,by);
        Go(x,y,mx+1,my);

        int in = 0, out = 0;
        rng(i,by,ey){
            if(w[mx+1][i] == 1)in+=2;
            if(w[mx][i] == 3)out+=2;
            
            if(w[bx][i] == 1)out+=2;
            if(w[bx-1][i] == 3)in+=2;
        }
        rng(i,bx,mx){
            if(w[i][ey+1] == 4)in+=2;
            if(w[i][ey] == 2)out+=2;

            if(w[i][by] == 4)out+=2;
            if(w[i][by-1] == 2)in+=2;
        }
        //printf("%d %d %d %d %d %d\n",in,out, bx, mx, by, ey);
        if(bx<=n+1 && n+1<=mx && by<=n+1 &&n+1<=ey)in++;
        else out++;

        if(in>out)Do(bx,by,mx,ey,x,y);
        else Do(mx+1,by,ex,ey,x,y);
    }
    else{
        Go(x,y,x,my);
        Go(x,y,bx,my);
        Go(x,y,ex,my);
        Go(x,y,ex,my+1);
        Go(x,y,bx,my+1);
        Go(x,y,mx,my+1);

        int in = 0, out = 0;
        rng(i,by,my){
            
            if(w[bx][i] == 1)out+=2;
            if(w[bx-1][i] == 3)in+=2;

            if(w[ex+1][i] == 1)in+=2;
            if(w[ex][i] == 3)out+=2;
        }
        //if(bx==3502&&by== 3877&&ex== 3626&&ey== 4001)printf("in out %d %d\n",in,out);

        rng(i,bx,ex){
            if(w[i][my+1] == 4)in+=2;
            if(w[i][my] == 2)out+=2;

            if(w[i][by] == 4)out+=2;
            if(w[i][by-1] == 2)in+=2;

            //if(bx==3502&&by== 3877&&ex== 3626&&ey== 4001)printf("%d%d%d%d\n",w[i][by-1],w[i][by],w[i][my],w[i][my+1]);
        }
        //printf("! %d %d %d %d %d %d\n",in,out, bx, ex, by, my);
        if(bx<=n+1 && n+1<=ex && by<=n+1 &&n+1<=my)in++;
        else out++;

        if(in>out)Do(bx,by,ex,my,x,y);
        else Do(bx,my+1,ex,ey,x,y);
    }
}
void Solve(){
    scanf("%d",&n);
    if(DEB){
        rng(i,3,n+1){
            res[i][n+1]='^';
            res[2][n-2+i]='>';
        }
        rng(i,2,n*2-1){
            res[i][n*2]='v';
        }
        gnr(i,n*2,3){
            res[n*2][i]='<';
        }
        gnr(i,n*2,n*2-468){
            if(i%2==0){
                res[i][2]='^';
                rng(j,2,n*2-5)res[i-1][j]='>';
            }
            else{
                res[i][2*n-4]='^';
                rng(j,3,n*2-4)res[i-1][j]='<';
            }
        }
        res[n*2-468-1][n*2-4]='G';
        rng(i,1,2*n+1){
            rng(j,1,2*n+1){
                //printf("%c",res[i][j]);
            }
            //puts("");
        }
        printf("R %d %d\n",n*2-468-1,n*2-4);
    }
    w[n+1][n+1] = 1;
    Do(1,1,2*n+1,2*n+1,n+1,n+1);
}
 
int main(){
    
    int TC=1;
    //scanf("%d",&TC);
    while(TC--){
        Solve();
    }
}
