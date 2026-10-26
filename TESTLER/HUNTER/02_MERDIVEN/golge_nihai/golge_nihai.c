/* CEM ILKESI: "256 diye bir sey yok, 256 bizim icin 128x2'dir."
   Yani TASMA istisna degil TEMSILIN KENDISI. Bir satirin degeri BIRDEN FAZLA
   SATIRA yayilabilir; a=0 satirlari KENDINDEN ONCEKI merdiven satirinin
   degerine carpilir (en dista degil, +a UYGULANMADAN ONCE).  */
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#define MAXN 16777216u
#define LIM 2097151u
static const uint32_t P[7]={2,3,5,7,11,13,17};
typedef struct { uint8_t e[7]; uint8_t a; } Row;
static uint64_t sv(const Row*w){uint64_t v=1;for(int i=0;i<7;i++)for(int k=0;k<w->e[i];k++)v*=P[i];return v;}
static uint64_t pv(const Row*w){uint64_t v=0;for(int i=0;i<7;i++)v|=(uint64_t)w->e[i]<<(3*i);return v;}
static void setpos(Row*w,uint64_t x){for(int i=0;i<7;i++)w->e[i]=(x>>(3*i))&7;w->a=2;}
static uint64_t fill(Row*w,uint64_t x){uint64_t f=1;
    for(int i=0;i<7;i++){int c=0;while(x%P[i]==0){x/=P[i];c++;}
        w->e[i]=(c>7)?7:(uint8_t)c; for(int t=7;t<c;t++)f*=P[i];} return f*x;}
static void okt(uint64_t v,char*b){char t[32];int n=0;if(!v){b[0]='0';b[1]=0;return;}
    while(v){t[n++]='0'+(v&7);v>>=3;}for(int i=0;i<n;i++)b[i]=t[n-1-i];b[n]=0;}

static int dene(uint32_t N,int derin,Row r[4],uint32_t*RR){
    memset(r,0,4*sizeof(Row)); *RR=0;
    uint64_t cur=N; int k=0, inis=0;
    for(;;){
        uint64_t x=cur, sm=1;
        for(int i=0;i<7;i++) while(x%P[i]==0){x/=P[i];sm*=P[i];}
        uint64_t rg=x;
        uint64_t f=fill(&r[k],sm);
        int nx=k+1;
        while(f>1){                       /* TASMA: sonraki satirlara YAYIL (a=0) */
            if(nx>3) return 0;
            f=fill(&r[nx],f); r[nx].a=0; nx++; }
        if(rg==1) break;                  /* rough bitti */
        if(nx>3 || inis>=derin){          /* merdiven icin yer/kota yok */
            if(rg>LIM) return 0;
            if(nx<=3){ setpos(&r[nx],rg); } else { *RR=(uint32_t)rg; }
            break; }
        r[nx].a=(uint8_t)(rg&7); cur=rg>>3; k=nx; inis++;
        if(cur==0) return 0;
    }
    return 1;
}
static int encode(uint32_t N,Row r[4],uint32_t*RR){
    for(int d=3;d>=0;d--) if(dene(N,d,r,RR)) return d;
    return -1;
}
/* a=0 satirlari, kendinden onceki merdiven satirinin degerine carpilir */
static uint64_t val(const Row r[4],int k,uint32_t RR){
    if(k>3) return 1;
    uint64_t v=sv(&r[k]); int m=k+1;
    while(m<=3 && r[m].a==0){ v*=sv(&r[m]); m++; }
    if(m<=3){ if(r[m].a==2) v*=pv(&r[m]); else v*=(8*val(r,m,RR)+r[m].a); }
    else if(RR) v*=RR;
    return v;
}
static void pr(uint32_t N){ Row w[4];uint32_t RR;int d=encode(N,w,&RR);
    char b[32];okt(N,b); printf("%9u = %10s_8  ",N,b);
    if(d<0){printf("SIGMADI\n");return;}
    for(int k=0;k<4;k++){printf("R%d[",k+1);
        if(k&&w[k].a==2){char c[32];okt(pv(&w[k]),c);printf("POZ=%s_8|TUR=2",c);}
        else{int f=1;for(int i=0;i<7;i++)if(w[k].e[i]){printf("%se%u=%u",f?"":",",P[i],w[k].e[i]);f=0;}
             if(f)printf("-"); if(k)printf("|a=%u",w[k].a);}
        printf("] ");}
    if(RR){char c[32];okt(RR,c);printf("RR=%s_8 ",c);}
    uint64_t v=val(w,0,RR);printf(" = %llu %s\n",(unsigned long long)v,v==N?"OK":"**HATA**");}
int main(void){ setvbuf(stdout,NULL,_IONBF,0);
    printf("=== ORNEKLER ===\n");
    pr(738);pr(9728);pr(2048);pr(256);pr(8388608);pr(1566857);pr(16777213);pr(1);
    printf("\n=== TAM 2^24 ===\n");
    long hata=0,sig=0; uint64_t*H=(uint64_t*)malloc(8ULL*MAXN);
    for(uint32_t n=1;n<MAXN;n++){ Row w[4];uint32_t RR;int d=encode(n,w,&RR);
        if(d<0){sig++;H[n]=0;continue;}
        if(val(w,0,RR)!=n) hata++;
        uint64_t h=1469598103934665603ULL;
        for(int k=0;k<4;k++){for(int i=0;i<7;i++){h^=w[k].e[i];h*=1099511628211ULL;}h^=w[k].a;h*=1099511628211ULL;}
        h^=RR;h*=1099511628211ULL;H[n]=h?h:1; }
    printf("  round-trip hata = %ld\n  KAPSAMA = %.4f%%  (sigmayan %ld)\n",
        hata,100.0-100.0*sig/(MAXN-1),sig);
    size_t TS=1u<<26;uint32_t*t=(uint32_t*)calloc(TS,4);long c=0;
    for(uint32_t n=1;n<MAXN;n++){if(!H[n])continue;size_t s=H[n]&(TS-1);
        while(t[s]){if(H[t[s]]==H[n]){c++;break;}s=(s+1)&(TS-1);}if(!t[s])t[s]=n;}
    printf("  CARPISMA = %ld\n",c);
    return 0;}
