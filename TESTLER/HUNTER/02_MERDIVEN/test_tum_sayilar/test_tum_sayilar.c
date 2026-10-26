/* ===========================================================================
   TUM SAYILAR — EXHAUSTIVE MERDIVEN round-trip testi  (E1 2/2, 26 Tem 2026)
   TUM 24-bit sayilari tek tek MERDIVEN SAKLAMASINA sokar ve geri okur:
       mval(mstore(n)) == n ?
   Ek istatistik: smooth sayisi, max usler, satir histogrami, RR kullanimi.
   (Eski surum duz us-vektoru round-trip'iydi — saklama katmanini test
    ETMIYORDU. Simdi test edilen sey N6 merdiven modelinin ta kendisi;
    referans cekirdek CEM_MODELI/golge_nihai.c ile birebir.)
   Derle: gcc -O2 -o test_tum test_tum_sayilar.c   Calistir: ./test_tum
   =========================================================================== */
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <time.h>

#define LIM 2097151u
static const uint32_t P[7] = {2,3,5,7,11,13,17};
typedef struct { uint8_t e[7]; uint8_t a; } Row;

static uint64_t sv(const Row*w){uint64_t v=1;for(int i=0;i<7;i++)for(int k=0;k<w->e[i];k++)v*=P[i];return v;}
static uint64_t pvx(const Row*w){uint64_t v=0;for(int i=0;i<7;i++)v|=(uint64_t)w->e[i]<<(3*i);return v;}
static void setpos(Row*w,uint64_t x){for(int i=0;i<7;i++)w->e[i]=(x>>(3*i))&7;w->a=2;}
static uint64_t fillr(Row*w,uint64_t x){uint64_t f=1;
    for(int i=0;i<7;i++){int c=0;while(x%P[i]==0){x/=P[i];c++;}
        w->e[i]=(c>7)?7:(uint8_t)c; for(int t=7;t<c;t++)f*=P[i];} return f*x;}
static int dene(uint32_t N,int derin,Row r[4],uint32_t*RR){
    memset(r,0,4*sizeof(Row)); *RR=0;
    uint64_t cur=N; int k=0, inis=0;
    for(;;){ uint64_t x=cur, sm=1;
        for(int i=0;i<7;i++) while(x%P[i]==0){x/=P[i];sm*=P[i];}
        uint64_t rg=x; uint64_t f=fillr(&r[k],sm); int nx=k+1;
        while(f>1){ if(nx>3) return 0; f=fillr(&r[nx],f); r[nx].a=0; nx++; }
        if(rg==1) break;
        if(nx>3 || inis>=derin){ if(rg>LIM) return 0;
            if(nx<=3){ setpos(&r[nx],rg); } else { *RR=(uint32_t)rg; } break; }
        r[nx].a=(uint8_t)(rg&7); cur=rg>>3; k=nx; inis++;
        if(cur==0) return 0; }
    return 1; }
static int m_encode(uint32_t N,Row r[4],uint32_t*RR){
    for(int d=3;d>=0;d--) if(dene(N,d,r,RR)) return d; return -1; }
static uint64_t val(const Row r[4],int k,uint32_t RR){
    if(k>3) return 1;
    uint64_t v=sv(&r[k]); int m=k+1;
    while(m<=3 && r[m].a==0){ v*=sv(&r[m]); m++; }
    if(m<=3){ if(r[m].a==2) v*=pvx(&r[m]); else v*=(8*val(r,m,RR)+r[m].a); }
    else if(RR) v*=RR;
    return v; }
static void ac(const Row r[4],uint32_t RR,uint32_t us[7],uint64_t*rough){
    for(int i=0;i<7;i++) us[i]=r[0].e[i];
    int m=1;
    while(m<=3 && r[m].a==0){ for(int i=0;i<7;i++) us[i]+=r[m].e[i]; m++; }
    if(m<=3){ if(r[m].a==2) *rough=pvx(&r[m]);
              else          *rough=8*val(r,m,RR)+r[m].a; }
    else *rough = RR ? RR : 1;
}

int main(void){
    const uint32_t MAXV = 0xFFFFFFu;               /* 16.777.215 */
    uint64_t hata=0, sigmadi=0, smooth=0, roughn=0, maxrough=0, ilk_hata=0;
    uint64_t rr_kullanan=0;
    int hata_var=0;
    uint64_t maxexp[7]={0,0,0,0,0,0,0};
    uint64_t satirh[5]={0,0,0,0,0};                /* kullanilan satir sayisi 1..4 */

    clock_t t0=clock();
    for(uint32_t n=1; n<=MAXV; n++){               /* n=0: golge-yoklugu (ZERO kisa devre) */
        Row r[4]; uint32_t RR;
        int d=m_encode(n,r,&RR);
        if(d<0){ sigmadi++; continue; }
        if(val(r,0,RR)!=n){ hata++; if(!hata_var){ilk_hata=n; hata_var=1;} }
        int rows=0; for(int k=0;k<4;k++){ int bos=1;
            for(int i=0;i<7;i++) if(r[k].e[i]) bos=0;
            if(!bos || (k && r[k].a)) rows=k+1; }
        if(rows<1) rows=1;
        satirh[rows]++;
        if(RR) rr_kullanan++;
        uint32_t us[7]; uint64_t rg; ac(r,RR,us,&rg);
        if(rg==1) smooth++;
        else { roughn++; if(rg>maxrough) maxrough=rg; }
        for(int i=0;i<7;i++) if(us[i]>maxexp[i]) maxexp[i]=us[i];
    }
    double sec=(double)(clock()-t0)/CLOCKS_PER_SEC;

    int sabit_ok = (smooth==15748) && (maxexp[0]==23)&&(maxexp[1]==15)&&(maxexp[2]==10)
                 &&(maxexp[3]==8)&&(maxexp[4]==6)&&(maxexp[5]==6)&&(maxexp[6]==5);

    printf("==================================================================\n");
    printf("  TUM SAYILAR — EXHAUSTIVE MERDIVEN round-trip (N6 saklama)\n");
    printf("==================================================================\n");
    printf("  Aralik           : 1 .. %u  (tum 24-bit; 0 = ZERO kisa devre)\n", MAXV);
    printf("  Round-trip HATA  : %llu   %s\n",
           (unsigned long long)hata, hata? "(!!)":"-> SIFIR HATA");
    if(hata) printf("  Ilk hata sayisi  : %llu\n",(unsigned long long)ilk_hata);
    printf("  SIGMAYAN (kapsama): %llu  %s\n",(unsigned long long)sigmadi,
           sigmadi? "(!!)":"-> KAPSAMA %100");
    printf("\n");
    printf("  SMOOTH (rough=1) : %llu  (%%%.4f)  [beklenen 15.748]\n",
           (unsigned long long)smooth, 100.0*smooth/(double)MAXV);
    printf("  ROUGH            : %llu  (%%%.3f)\n",
           (unsigned long long)roughn, 100.0*roughn/(double)MAXV);
    printf("  En buyuk rough   : %llu\n",(unsigned long long)maxrough);
    printf("  RR kullanan sayi : %llu\n",(unsigned long long)rr_kullanan);
    printf("\n");
    printf("  SATIR HISTOGRAMI : 1:%llu  2:%llu  3:%llu  4:%llu\n",
           (unsigned long long)satirh[1],(unsigned long long)satirh[2],
           (unsigned long long)satirh[3],(unsigned long long)satirh[4]);
    printf("  Gorulen MAX us   : 2^%llu 3^%llu 5^%llu 7^%llu 11^%llu 13^%llu 17^%llu\n",
           (unsigned long long)maxexp[0],(unsigned long long)maxexp[1],
           (unsigned long long)maxexp[2],(unsigned long long)maxexp[3],
           (unsigned long long)maxexp[4],(unsigned long long)maxexp[5],
           (unsigned long long)maxexp[6]);
    printf("  (Beklenen max us : 2^23 3^15 5^10 7^8 11^6 13^6 17^5)\n");
    printf("  KAPANIS SABITLERI: %s\n", sabit_ok? "BIREBIR TUTTU":"SAPMA VAR (!!)");
    printf("\n");
    printf("  Sure             : %.2f saniye\n", sec);
    printf("==================================================================\n");
    printf("  HUKUM: %s\n", (hata||sigmadi||!sabit_ok)?
           "SAPMA VAR -> merdiven saklama bozuk!" :
           "TUM 24-bit sayi MERDIVENE kayipsiz gidip geri donuyor. KANIT.");
    printf("==================================================================\n");
    return (hata||sigmadi||!sabit_ok)?1:0;
}
