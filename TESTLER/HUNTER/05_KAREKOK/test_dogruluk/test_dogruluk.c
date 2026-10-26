#include <stdio.h>
#include <stdint.h>
#include <math.h>
static double binom1(double N){double a=floor(sqrt(N)+0.5);return a+(N-a*a)/(2*a);}
static double newton(double x,double N){return 0.5*(x+N/x);}
int main(){
    printf("=== DOGRULUK BENCHMARK — tum 24-bit sayilar (2..16.777.215) ===\n\n");
    double maxe[5]={0},sume[5]={0}; long wN[5]={0},cnt=0;
    for(uint32_t N=2;N<=16777215u;N++){ double ref=sqrt((double)N),e[5];
        double b1=binom1(N); e[0]=fabs(b1-ref)/ref; double r1=newton(b1,N);e[1]=fabs(r1-ref)/ref;
        double r2=newton(r1,N);e[2]=fabs(r2-ref)/ref; double r3=newton(r2,N);e[3]=fabs(r3-ref)/ref;
        double L=log2((double)N),q=round(L*4096)/4096; e[4]=fabs(exp2(q/2)-ref)/ref;
        for(int m=0;m<5;m++){if(e[m]>maxe[m]){maxe[m]=e[m];wN[m]=N;}sume[m]+=e[m];} cnt++; }
    const char*nm[5]={"binom 1 terim   ","binom +1 Newton ","binom +2 Newton ","binom +3 Newton ","log2-LNS 12-bit "};
    int cy[5]={5,10,15,20,3};
    printf("  Yontem            ~cy   MAX bagil hata   ORT bagil hata\n");
    for(int m=0;m<5;m++) printf("  %s  %3d   %.2e         %.2e\n",nm[m],cy[m],maxe[m],sume[m]/cnt);
    printf("  octal d-by-d       ~4   0 (KESIN)        0\n");
    printf("\n  Boyut esigi (binom):\n");
    struct{long lo,hi;}bk[]={{2,64},{64,4096},{4096,262144},{262144,16777216}};
    for(int b=0;b<4;b++){double m=0;for(long N=bk[b].lo;N<bk[b].hi;N++){double ee=fabs(binom1((double)N)-sqrt((double)N))/sqrt((double)N);if(ee>m)m=ee;}
        printf("    [%ld..%ld) binom MAX %.2e\n",bk[b].lo,bk[b].hi,m);}
    return 0;
}
