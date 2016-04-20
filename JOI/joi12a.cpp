#include <cstdio>
#include <algorithm>
int K,O,I,max,mode;
int modemata[4][3]={{1,0,0},{1,2,0},{1,2,3},{1,0,3}};
 
int returnMax(){
    int r=std::min(std::min(I,K),O);
    return r==O?r:0;
}
 
int returnKOInumber(char a){return a=='J'?0:a=='O'?1:2;}
 
int main(){
    char s[1000001];
    scanf("%s",s);
    for (int i=0; s[i]; i++) {
        if(mode==0 && s[i]=='J') K++;
        else if(mode==1 && s[i]=='J') K++;
        else if(mode==1 && s[i]=='O') O++;
        else if(mode==1 && s[i]=='I'){
            K=O=I=0;
        }
        else if(mode==2 && s[i]=='J'){
            K=1;
            O=I=0;
        }
        else if(mode==2 && s[i]=='O') O++;
        else if(mode==2 && s[i]=='I') I++;
        else if(mode==3 && s[i]=='J'){
            if(max<returnMax()) max=returnMax();
            K=1;
            O=I=0;
        }
        else if(mode==3 && s[i]=='O'){
            if(max<returnMax()) max=returnMax();
            K=O=I=0;
        }
        else if(mode==3 && s[i]=='I') I++;
        mode=modemata[mode][returnKOInumber(s[i])];
         
    }
    if(mode==3 && max<returnMax()) max=returnMax();
    printf("%d",max);
}