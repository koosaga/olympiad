#include <cstdio>
#include <cstdlib>
typedef long long lint;

lint x, y, k, n, c;

bool trial(lint x, lint y){return (x%c == 0 && y%c == 0);}

lint g(lint x, lint y){return y ? g(y,x%y) : x;}

bool solve(){
    lint x1, x2, y1, y2;
    scanf("%lld %lld %lld %lld %lld %lld",&k,&n,&x1,&y1,&x2,&y2);
    c = g(2*k,2*n);
    x = x2 - x1, y = y2 - y1;
    return trial(x+k,y+n) || trial(x,y) || trial(x+n,y+k) || trial(x+n+k,y+n+k);
}

int main(){
    lint t;
    scanf("%lld",&t);
    while (t--) {
        puts(solve()?"TAK":"NIE");
    }
}