#include <cstdio>
#include <algorithm>
#include <utility>
using namespace std;
typedef pair<int,int> pi;
 
const int U = 400;
const int B = 250;
 
int n,q;
int a[100005];
int sentinel;
 
int buck[405][655];
int size[405];
int master[405];
 
void make_arr(){
    int piv = 0;
    for (int i=0; i<sentinel; i++) {
        for (int j=0; j<size[i]; j++) {
            a[piv++] = buck[i][j];
        }
    }
}
 
void clear_bucket(){
    for (int i=0; i<sentinel; i++) {
        master[i] = 0;
        size[i] = min(B,n-i*B);
        for (int j=0; j<size[i]; j++) {
            master[i] = max(master[i],a[i*B+j]);
            buck[i][j] = a[i*B+j];
        }
    }
}
 
pi get_pos(int x){
    for (int i=0; i<sentinel; i++) {
        if(x < size[i]){
            return pi(i,x);
        }
        x -= size[i];
    }
    return pi(-1,-1);
}
 
int main(){
    scanf("%d %d",&n,&q);
    while (sentinel * B < n) sentinel++;
    for (int i=0; i<n; i++) {
        scanf("%d",&a[i]);
    }
    clear_bucket();
    for (int i=1; i<=q; i++) {
        int x,y;
        char str[5];
        scanf("%d %s %d",&x,str,&y);
        if(str[0] == 'D'){
            y = x + y;
        }
        else{
            y = x - y;
        }
        x--;
        y--;
        if(x <= y){
            pi sx = get_pos(x); // x의 원소를 지운 후
            pi sy = get_pos(y); // 반환 포지션 바로 뒤에 삽입
            int bx = sx.first;
            int px = sx.second;
            int by = sy.first;
            int py = sy.second;
            int ret = 0;
            if(bx == by){
                int bk = buck[bx][px];
                for (int j=px; j<py; j++) {
                    ret = max(ret,buck[bx][j+1]);
                    buck[bx][j] = buck[bx][j+1];
                }
                buck[bx][py] = bk;
            }
            else{
                int bk = buck[bx][px];
                for (int j=px; j<size[bx]-1; j++) {
                    ret = max(ret,buck[bx][j+1]);
                    buck[bx][j] = buck[bx][j+1];
                }
                size[bx]--;
                if(master[bx] == bk) master[bx] = *max_element(buck[bx],buck[bx] + size[bx]);
                for (int j=bx+1; j<by; j++) {
                    ret = max(ret,master[j]);
                }
                size[by]++;
                for (int j=size[by]-1; j>py+1; j--) {
                    buck[by][j] = buck[by][j-1];
                }
                buck[by][py+1] = bk;
                master[by] = max(master[by],bk);
                for (int j=0; j<=py; j++) {
                    ret= max(ret,buck[by][j]);
                }
            }
            printf("%d\n",ret);
        }
        else{
            pi sx = get_pos(x); // x의 원소를 지운 후
            pi sy = get_pos(y); // 반환 포지션 바로 왼쪽 앞에 삽입
            int bx = sx.first;
            int px = sx.second;
            int by = sy.first;
            int py = sy.second;
            int ret = 0;
            if(bx == by){
                int bk = buck[bx][px];
                for (int j=px; j>py; j--) {
                    buck[bx][j] = buck[bx][j-1];
                    ret = max(ret,buck[bx][j]);
                }
                buck[bx][py] = bk;
            }
            else{
                int bk = buck[bx][px];
                for (int j=px; j<size[bx]-1; j++) {
                    buck[bx][j] = buck[bx][j+1];
                }
                size[bx]--;
                if(master[bx] == bk)master[bx] = *max_element(buck[bx],buck[bx] + size[bx]);
                for (int j=0; j<px; j++) {
                    ret = max(ret,buck[bx][j]);
                }
                for (int j=by+1; j<bx; j++) {
                    ret = max(ret,master[j]);
                }
                size[by]++;
                for (int j=size[by]-1; j>py; j--) {
                    buck[by][j] = buck[by][j-1];
                    ret = max(ret,buck[by][j]);
                }
                buck[by][py] = bk;
                master[by] = max(master[by],bk);
            }
            printf("%d\n",ret);
        }
        if(i % U == 0){
            make_arr();
            clear_bucket();
        }
    }
}