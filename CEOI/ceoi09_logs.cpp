#include <cstdio>
#include <algorithm>
#include <vector>
#include <cstring>
using namespace std;
 
int n,m;
int up[1505];
char str[1505];
int cnt[15005];
 
vector<int> v;
int main(){
    int ret = 0;
    scanf("%d %d\n",&n,&m);
    for (int i=1; i<=n; i++) {
        scanf("%s",str);
        int count = 0;
        for (int j=0; j<m; j++) {
            if(str[j] == '1'){
                if(up[j] == 0) count++;
                up[j]++;
            }
            else{
                if(up[j] != 0) cnt[up[j]]++;
                up[j] = 0;
            }
        }
        vector<int> ins(count,0);
        v.insert(v.begin(),ins.begin(),ins.end());
        for (auto &j : v){
            if(cnt[j]){
                cnt[j]--;
                j = -1;
            }
        }
        int pt = (int)v.size();
        for (int j=(int)v.size()-1; j>=0; j--){
            pt--;
            while (pt >= 0 && v[pt] == -1) pt--;
            if(pt >= 0) v[j] = v[pt];
            else v[j] = -1;
        }
        v.erase(v.begin(),lower_bound(v.begin(),v.end(),0));
        for (auto &j : v){
            j++;
        }
        int piv = (int)v.size();
        for (auto &j : v){
            ret = max(ret,j * piv--);
        }
    }
    printf("%d",ret);
}