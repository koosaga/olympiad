#include <cstdio>
#include <algorithm>
#include <deque>
#include <set>
using namespace std;
typedef long long lint;
 
int n, l, a[100005], b[100005];
lint dp[100005], sum;
deque<int> dq, num;
multiset<lint> s;
 
int main(){
    scanf("%d %d",&n,&l);
    for (int i=1; i<=n; i++) {
        scanf("%d %d",&a[i],&b[i]);
    }
    int pt = 0;
    dq.push_back(1e9);
    num.push_back(0);
    for (int i=1; i<=n; i++) {
        sum += b[i];
        while (sum > l) {
            if(!num.empty() && num.front() == pt){
                if(dq.size() > 1) s.erase(s.find(dp[num.front()] + dq[1]));
                num.pop_front();
                dq.pop_front();
            }
            pt++;
            sum -= b[pt];
        }
        while (!dq.empty() && dq.back() < a[i]) {
            if(dq.size() > 1) s.erase(s.find(dp[num[num.size() - 2]] + dq.back()));
            dq.pop_back();
            num.pop_back();
        }
        if(!num.empty()) s.insert(dp[num.back()] + a[i]);
        dq.push_back(a[i]);
        num.push_back(i);
        lint ret = dp[pt] + dq.front();
        if(!s.empty()) ret = min(ret,*s.begin());
        dp[i] = ret;
    }
    printf("%lld",dp[n]);
}