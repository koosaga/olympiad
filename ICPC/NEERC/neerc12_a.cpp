#include <cstdio>

char res[11][11];
int dx = 1,h,w;
int pivx = 0, pivy = 0;
void color(int x, char piv){
    while (x) {
        res[pivy][pivx] = piv;
        pivx += dx;
        if(pivx == w){
            pivx = w-1;
            dx = -1;
            pivy++;
        }
        else if(pivx == -1){
            pivx = 0;
            dx = 1;
            pivy++;
        }
        x--;
    }
}
int main(){
    int c,t;
    scanf("%d %d %d",&h,&w,&c);
    for (int i=0; i<c; i++) {
        scanf("%d",&t);
        color(t,i+'1');
    }
    for (int i=0; i<h; i++) {
        puts(res[i]);
    }
}