#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;
typedef 
tree<int, null_type, less<int>, rb_tree_tag,
tree_order_statistics_node_update>
ordered_set;

ordered_set s;
const int MAXN = 200005;

int main(){
    int n;
    scanf("%d",&n);
    while(n--){
        int x;
        scanf("%d",&x);
        if(s.order_of_key(x + 1) == x){
            if(s.size() == x){
                puts("Yes");
                while(n--) puts("No");
                return 0;
            }
            puts("No");
            continue;
        }
        while(s.find(x) != s.end()){
            s.erase(s.find(x));
            x--;
        }
        s.insert(x);
        puts("Yes");
    }
}
