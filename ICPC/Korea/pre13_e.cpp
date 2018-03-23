#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <queue>
using namespace std;
typedef pair<int,int> pi;

int n,l,k;
int a[100005];

vector<int> left, right;

void solve(){
    left.clear();
    right.clear();
    scanf("%d %d %d",&n,&l,&k);
    for (int i=0; i<n; i++) {
        int t;
        scanf("%d %d",&t,&a[i]);
        if(a[i] < 0){
            left.push_back(t);
        }
        else{
            right.push_back(l-t);
        }
    }
    sort(left.begin(),left.end());
    sort(right.begin(),right.end());
    left.push_back(2e9);
    right.push_back(2e9);
    int lp = 0, rp = 0;
    for (int i=0; i<k; i++) {
        if(left[lp] < right[rp]){
            if(i == k-1) printf("%d",a[lp]);
            lp++;
        }
        else if(left[lp] > right[rp]){
            if(i == k-1) printf("%d",a[n-1-rp]);
            rp++;
        }
        else{
            if(a[lp] < a[n-1-rp]){
                if(i == k-1) printf("%d",a[lp]);
                lp++;
            }
            else{
                if(i == k-1) printf("%d",a[n-1-rp]);
                rp++;
            }
        }
    }
}

int main(){
    int t;
    scanf("%d",&t);
    while (t--) {
        solve();
        puts("");
    }
}