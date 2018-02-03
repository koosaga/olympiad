#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;
typedef pair<int, int> pi;

int n, l;
char str[100005];
int dx[100005];
int st, ed;
double val;

bool ccw(pi a, pi b, pi c){
    int dy1 = b.first - a.first;
    int dx1 = b.second - a.second;
    int dy2 = c.first - a.first;
    int dx2 = c.second - a.second;
    return 1ll * dx1 * dy2 > 1ll * dy1 * dx2;
}

double slope(pi a, pi b){

    return 1.0 * (b.first - a.first) / (b.second - a.second);
}
int main(){
    int t;
    scanf("%d",&t);
    while(t--){
        vector<pi> hull;
        val = 0;
        scanf("%d %d",&n,&l);
        scanf("%s",str+1);
        for(int i=1; i<=n; i++){
            dx[i] = dx[i-1] + (str[i] == '1');
        }
        for(int i=1; i<=n; i++){
            if(i >= l){
                pi obj = pi(dx[i-l], i-l);
                while(hull.size() >= 2 && !ccw(hull[hull.size() - 2], hull.back(),obj)){
                    hull.pop_back();
                }
                hull.push_back(obj);
            }
            if(hull.empty()) continue;
            int s = 0, e = (int)hull.size() - 1;
            while(e - s > 3){
                int m1 = (2 * s + e) / 3;
                int m2 = (s + 2 * e) / 3;
                if(slope(hull[m1],pi(dx[i], i)) <= slope(hull[m2], pi(dx[i], i))){
                    s = m1;
                }
                else e = m2;
            }
            while(s <= e){
                if(val < slope(hull[s], pi(dx[i], i)) - 1e-8){
                    val = slope(hull[s], pi(dx[i],i));

                    st = hull[s].second;
                    ed = i;
                }
                else if(val < slope(hull[s], pi(dx[i], i)) + 1e-8){
                    if(ed - st > i - hull[s].second){
                        ed = i;
                        st = hull[s].second;
                    }
                    else if(ed - st == i - hull[s].second && st > hull[s].second){
                        ed = i;
                        st = hull[s].second;
                    }
                }
                s++;
            }
        }
        printf("%d %d\n",st+1, ed);
    }
}