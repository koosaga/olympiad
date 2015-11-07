#include <cstdio>
#include <algorithm>
#include <map>
#include <vector>
#include <utility>
using namespace std;
typedef pair<int,int> pi;
 
int n;
pi a[50005];
double lambda[50005];
double low_hull[50005], high_hull[50005];
 
struct cht{
    map<int,int> mp;
    double cross(pi a, pi b){
        return 1.0 * (b.second - a.second) / (a.first - b.first);
    }
    void add(int x, int y){
        if(mp.find(x) != mp.end()){
            if(mp[x] >= y) return;
            mp.erase(x);
        }
        auto it = mp.lower_bound(x);
        if(it != mp.end()){
            auto it2 = ++mp.lower_bound(x);
            while(it2 != mp.end()){
                if(cross(pi(x, y), *it) > cross(*it, *it2)){
                    mp.erase(it);
                    it = it2;
                    it2++;
                }
                else break;
            }
        }
        it = mp.lower_bound(x);
        if(it != mp.begin()){
            it--;
            auto it2 = it;
            if(it2 != mp.begin()){
                it2--;
                while(1){
                    if(cross(*it2, *it) > cross(*it, pi(x, y))){
                        mp.erase(it);
                        it = it2;
                        if(it2 == mp.begin()) break;
                        else it2--;
                    }
                    else break;
                }
            }
        }
        mp[x] = y;
    }
    double query(double t){
        if(mp.empty()) return -1e9;
        auto it = --mp.end();
        while(it != mp.begin()){
            auto nxt = it;
            nxt--;
            if(cross(*nxt, *it) > t){
                mp.erase(it);
                it = nxt;
            }
            else break;
        }
        it = --mp.end();
        return it->first * t + it->second;
    }
    double query2(double t){
        if(mp.empty()) return -1e9;
        auto it = mp.begin();
        auto it2 = ++mp.begin();
        while(it2 != mp.end()){
            if(cross(*it, *it2) < t){
                mp.erase(it);
                it = it2;
                it2++;
            }
            else break;
        }
        return it->first * t + it->second;
    }
    void clear(){
        mp.clear();
    }
}cht;
 
void input(){
    scanf("%d",&n);
    for (int i=1; i<=n; i++) {
        scanf("%d %d",&a[i].first,&a[i].second);
    }
    sort(a+1,a+n+1,[&](const pi &a, const pi &b){
            return a.first * b.second < b.first * a.second;
            });
    int t_sum = a[n].first, p_sum = a[n].second;
    lambda[n] = 1e9;
    for (int i=n-1; i; i--) {
        lambda[i] = 1.0 * t_sum / p_sum;
        t_sum += a[i].first;
        p_sum += a[i].second;
    }
}
 
int main(){
    input();
    for (int i=1; i<=n; i++) {
        cht.add(-a[i].second,a[i].first);
        high_hull[i] = cht.query(lambda[i]);
    }
    cht.clear();
    for (int i=n; i; i--) {
        low_hull[i] = -cht.query2(lambda[i]);
        cht.add(a[i].second,-a[i].first);
    }
    vector<int> ret;
    for (int i=1; i<n; i++) {
        if(low_hull[i] < high_hull[i]) ret.push_back(i);
    }
    printf("%d\n",(int)ret.size());
    for (int i=0; i<ret.size(); i++) {
        printf("%d\n",ret[i]);
    }
}