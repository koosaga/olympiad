#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <limits.h>
#include <stack>
#include <queue>
#include <map>
#include <set>
#include <algorithm>
#include <string>
#include <functional>
#include <vector>
#include <numeric>
#include <deque>
#include <utility>
#include <bitset>
#include <iostream>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<int, int> pi;

struct intv{
    int cnt[4];
    void init(){
        for(int i=0; i<4; i++){
            cnt[i] = 0;
        }
    }
    bool operator<(const intv &a)const{
        for(int i=0; i<4; i++){
            if(cnt[i] != a.cnt[i]) return cnt[i] < a.cnt[i];
        }
        return 0;
    }
    bool operator==(const intv &a)const{
        for(int i=0; i<4; i++){
            if(cnt[i] != a.cnt[i]) return 0;
        }
        return 1;
    }
};

int k;
char str[60005];
int mp[256];
int main(){
    mp['A'] = 0;
    mp['C'] = 1;
    mp['T'] = 2;
    mp['G'] = 3;
    int t;
    scanf("%d",&t);
    while(t--){
        intv ii;
        ii.init();
        scanf("%d %s",&k,str);
        for(int i=0; i<k; i++){
            ii.cnt[mp[str[i]]]++;
        }
        vector<intv> v;
        v.push_back(ii);
        for(int i=0; str[i + k]; i++){
            ii.cnt[mp[str[i]]]--;
            ii.cnt[mp[str[i+k]]]++;
            v.push_back(ii);
        }
        sort(v.begin(), v.end());
        int ret = 0;
        for(int i=0; i<v.size();){
            int e = i;
            while(v[e] == v[i]) e++;
            ret = max(ret, e - i);
            i = e;
        }
        printf("%d\n",ret);
    }
}