///////////////////////////
//
// fast input
//
///////////////////////////
int INP,AM;
#define BUFSIZE 1024
char BUF[BUFSIZE+1],*inp=BUF;
#define GET(INP) {if(!*inp){fread(BUF,1,BUFSIZE,stdin);inp=BUF;}INP=*inp++;}
#define DIG(a) (((a)>='0')&&((a)<='9'))
#define CHA(a) (((a)>='A')&&((a)<='Z')||((a)=='-'))
#define GN(i) {while(CHA(INP))GET(INP);GET(INP);while(!DIG(INP)&&INP!='-')GET(INP);if(INP=='-'){AM=1;GET(INP);}else AM=0;i=INP-'0';GET(INP);while(DIG(INP)){i=i*10+(INP-'0');GET(INP);}if(AM)i=-i;}
#define GC(i) {GET(INP);while(!CHA(INP))GET(INP);i=INP;}
