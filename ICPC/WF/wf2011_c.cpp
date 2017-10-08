#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
#include <string>
using namespace std;
 
int w, h;
bool str[205][205];
 
int sex(int t){
    if(t <= '9' && t >= '0') return t - '0';
    return t - 'a' + 10;
}

int dx[4] = {1,0,-1,0}, dy[4] ={0,1,0,-1};
vector<int> vx, vy;
 
int chk(int x, int y){
    return (x < 0 || y < 0 || x >= w || y >= h) ;
}

int chk2(int x, int y){
    return (x < 0 || y < 0 || x >= 209 || y >= 209) ;
}

void dfs(int x, int y){
    if(str[x][y] == 0) return;
    str[x][y] = 0;
    vx.push_back(x);
    vy.push_back(y);
    for(int i=0; i<4; i++){
        if(chk(x + dx[i],y + dy[i])) continue;
        dfs(x + dx[i],y + dy[i]);
    }
}
 
bool tmp[209][209];
 
void fill(int x, int y){
    if(tmp[x][y] == 1) return;
    tmp[x][y] = 1;
    for(int i=0; i<4; i++){
        if(chk2(x + dx[i], y + dy[i])) continue;
        fill(x + dx[i], y + dy[i]);
    }
}
 
char s2[7] = "WAKJSD";
 
char process(){
    memset(tmp,0,sizeof(tmp));
    int p = *min_element(vx.begin(),vx.end());
    int q = *min_element(vy.begin(),vy.end());
    for(int i=0; i<vx.size(); i++){
        vx[i] -= p-1;
        vy[i] -= q-1;
        tmp[vx[i]][vy[i]] = 1;
    }
    fill(0,0);
    int cnt = 0;
    for(int i=0; i<209; i++){
        for(int j=0; j<209; j++){
            if(tmp[i][j] == 0){
                cnt++;
                fill(i,j);
            }
        }
    }
    return s2[cnt];
}
 
int cases;
 
char ret[50005];
int piv;

bool solve(){
    cases++;
    piv = 0;
    if(scanf("%d %d",&w,&h) == -1) return 0;
    if(w == 0 && h == 0) return 0;
    memset(str,0,sizeof(str));
    for(int i=0; i<w; i++){
        char buf[55];
        scanf("%s",buf);
        for(int j=0; j<h; j++){
            int bit = sex(buf[j]);
            for(int k=3; k>=0; k--){
                str[i][j * 4 + k] = bit % 2;
                bit >>= 1;
            }
        }
    }
    h *= 4;
    memset(ret,0,sizeof(ret));
    printf("Case %d: ",cases);
    for(int i=0; i<w; i++){
        for(int j=0; j<h; j++){
            if(str[i][j]){
                dfs(i,j);
                ret[piv++] = process();
                vx.clear();
                vy.clear();
            }
        }
    }
    sort(ret,ret+piv);
    puts(ret);
    return 1;
}
int main(){
    while(solve());
}