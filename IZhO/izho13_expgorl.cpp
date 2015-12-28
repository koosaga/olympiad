#include <cstdio>
#include <cmath>
#include <utility>
#include <algorithm>
using namespace std;
typedef long long lint;
typedef pair<lint,lint> pi;
 
int k;
char s[10005];
pi afterCycle, a[10005], laser, ainta, mp[150];
lint minv, maxv;
 
lint dist(pi x, pi y){
    return (y.second - x.second)*(y.second - x.second) + (y.first - x.first)*(y.first - x.first);
}
pi mv(pi x, int time){return pi(x.first + afterCycle.first * time, x.second + afterCycle.second * time);}
lint f(pi x, int t){return dist(laser,mv(x,t));}
 
void input(){
    scanf("%d %s",&k,s);
    scanf("%lld %lld %lld %lld",&laser.first,&laser.second,&ainta.first,&ainta.second);
    mp['I'] = pi(0ll,0ll);
    mp['L'] = pi(-1ll,0ll);
    mp['R'] = pi(1ll,0ll);
    mp['B'] = pi(0ll,-1ll);
    mp['F'] = pi(0ll,1ll);
}
 
int main(){
    input();
    minv = maxv = dist(laser,ainta);
    pi x = ainta;
    for (int i=0; s[i]; i++) {
        x.first += mp[s[i]].first;
        x.second += mp[s[i]].second;
        a[i] = x;
    }
    afterCycle = pi(x.first - ainta.first,x.second - ainta.second);
    for (int i=0; s[i]; i++) {
        int s = 0, e = k-1, m1, m2;
        for (int j=0; j<50; j++){
            m1 = (2*s + e)/3;
            m2 = (s + 2*e)/3;
            if(f(a[i],m1) < f(a[i],m2)) e = m2;
            else s = m1;
        }
        for (int j=s; j<=e; j++) {
            minv = min(minv,f(a[i],j));
        }
        maxv = max(maxv,f(a[i],0));
        maxv = max(maxv,f(a[i],k-1));
    }
    printf("%lf\n%lf",sqrt(minv),sqrt(maxv));
}