#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;
 
int n,a[500005];
vector<int> v;
 
struct bit{
    int tree[500005], lim;
    void init(int n){
        lim = n;
    }
    void add(int x){
        while(x <= lim){
            tree[x]++;
            x += x & -x;
        }
    }
    int sum(int x){
        int r = 0;
        while(x){
            r += tree[x];
            x -= x & -x;
        }
        return r;
    }
}bit;
 
int main(){
    scanf("%d",&n);
    v.push_back(-1);
    bit.init(n);
    for (int i=0; i<n; i++) {
        scanf("%d",&a[i]);
        v.push_back(a[i]);
    }
    sort(v.begin(),v.end());
    for (int i=0; i<n; i++) {
        a[i] = (int)(lower_bound(v.begin(),v.end(),a[i]) - v.begin());
    }
    for (int i=0; i<n; i++) {
        printf("%d\n",i + 1 - bit.sum(a[i]));
        bit.add(a[i]);
    }
}