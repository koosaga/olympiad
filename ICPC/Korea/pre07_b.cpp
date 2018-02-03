#include <cstdio>
#include <algorithm>
using namespace std;
typedef pair<int,int> pi;

int k, n;
int a[105];
vector<int> lset;
int vis[105];

int main(){
    scanf("%d %d",&k,&n);
    for(int i=0; i<n; i++){
        scanf("%d",&a[i]);
    }
    int cnt = 0;
    for(int i=0; i<n; i++){
        if(!vis[a[i]]){
            if(lset.size() == k){
                int nextocc = 0, pos;
                for(auto &P : lset){
                    int pocc = 1e9;
                    for(int j=i+1; j<n; j++){
                        if(P == a[j]){
                            pocc = j;
                            break; 
                        }
                    }
                    if(nextocc < pocc){
                        nextocc = pocc;
                        pos =P;
                    }
                }
                vis[pos] = 0;
                cnt++;
                lset.erase(find(lset.begin(), lset.end(), pos));
            }
            lset.push_back(a[i]);
            vis[a[i]] = 1;
        }
    }
    printf("%d",cnt);
}