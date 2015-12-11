#include <cstdio>
#include <cmath>
#include <algorithm>
#include <vector>
using namespace std;
typedef long double ld;
typedef long long lint;
typedef pair<ld,ld> pi;
const ld PI = 3.141592653;
   
int n, r;
int x[50005], y[50005];
   
vector<pi> obj;
vector<ld> v;
vector<ld> st, ed;
 
int main(){
    scanf("%d %d",&n,&r);
    for(int i=0; i<n; i++){
        scanf("%d %d",&x[i],&y[i]);
        ld stang = atan2(y[i], x[i]) - acos(1.0 * r / hypot(x[i],y[i])) + 2 * PI;
        ld edang = atan2(y[i], x[i]) + acos(1.0 * r / hypot(x[i],y[i])) + 2 * PI;
        stang = fmod(stang,2 * PI);
        edang = fmod(edang,2 * PI);
        if(stang < edang){
            st.push_back(stang);
            ed.push_back(edang);
            obj.push_back(pi(stang, edang));
        }
        else{
            st.push_back(stang);
            ed.push_back(2 * PI);
            obj.push_back(pi(stang, 2 * PI));
            v.push_back(edang);
        }
    }
    sort(st.begin(), st.end());
    sort(ed.begin(), ed.end());
    long long ret = 0;
    for(auto &i : v){
        ret += 2 * (int)(lower_bound(st.begin(), st.end(),i) - st.begin());
    }
    for(auto &i : obj){
        int tmp = (int)obj.size() - 1;
        tmp -= (int)(st.end() - lower_bound(st.begin(), st.end(), i.second));
        tmp -= (int)(lower_bound(ed.begin(), ed.end(), i.first) - ed.begin());
        ret += tmp;
    }
    printf("%lld",ret/2);
}