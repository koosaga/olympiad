#include <stdio.h>
#include <map>
#include <algorithm>
using namespace std;
typedef long long lint;
typedef pair<int, char> pi;
typedef map<int, int> ::iterator aauto;

int n;
pi a[500001];

struct tup{
    int x, y, z;
}p[500005];

bool cmp(tup a, tup b){
    return a.x < b.x;
}

map<int, int> mp;

lint solve(){
    sort(p, p+n, cmp);
    int prevx = 1e9;
    lint area = 0;
    lint ret = 0;
    mp[0] = 1e9;
    mp[1e9] = 0;
    for(int i=n-1; i>=0; i--){
        ret += 1ll * (prevx - p[i].x) * area;
        int e = i;
        while(e >= 0 && p[e].x == p[i].x){
            e--;
        }
        for(int j=e+1; j<=i; j++){
            aauto it = mp.lower_bound(p[j].y);
            if(it->second >= p[j].z){
                continue;
            }
            int prevz = it->second;
            it--;
            while(it != mp.begin() && it->second <= p[j].z){
                area += 1ll * (it->second - prevz) * (p[j].y - it->first);
                prevz = it->second;
                aauto nxt = it;
                nxt--;
                mp.erase(it);
                it = nxt;
            }
            area += 1ll * (p[j].z - prevz) * (p[j].y - it->first);
            mp[p[j].y] = p[j].z;
        }
        prevx = p[i].x;
        i = e+1;
    }
    ret += 1ll * prevx * area;
    return ret;
}

int main(){
    scanf("%d",&n);
    for (int i=0; i<n; i++) {
        scanf("%d %c",&a[i].first,&a[i].second);
    }
    sort(a,a+n);
    int pt = 0;
    int r = 0, g = 0, b = 0;
    for (int i=0; i<n; i++) {
        while (pt < n && a[pt].first < 2*a[i].first){
            if(a[pt].second == 'R') r++;
            if(a[pt].second == 'G') g++;
            if(a[pt].second == 'B') b++;
            pt++;
        }
        p[i] = {r+1, g+1, b+1};
        if(a[i].second == 'R') r--;
        if(a[i].second == 'G') g--;
        if(a[i].second == 'B') b--;
    }
    printf("%lld",solve() - 1);
}