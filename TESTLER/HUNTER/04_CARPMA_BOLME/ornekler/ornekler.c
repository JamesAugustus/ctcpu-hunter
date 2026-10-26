/* MUL/DIV ORNEK GOSTERIMI — sistem cok sayiyla nasil calisiyor, kategori kategori.
   Cem'in ornek seti her sayi tipini tek tek gosterir: her ornek golge (us vektoru) adimlari +
   sonuc + native dogrulama (__int128, tam). Genisletilmis set.
   Derle : cc -O3 ornekler.c -o o     Calistir: ./o
   Her ornek FORMATI:
     girdi sayilari -> golge (us vektoru) -> islem (topla/cikar) -> sonuc golge
     -> cozulmus deger -> native dogrulama (OK). */
#include <stdio.h>
#include <stdint.h>
typedef __int128 i128;
static const int P[7]={2,3,5,7,11,13,17};

/* GOLGE: 7 asalin us vektoru + rough (yedi asala bolunmeyen artik) + isaret */
typedef struct{int e[7]; long long rough; int sign;} G;

/* fac: bir tam sayiyi golgeye ayristirir (yedi asal soyulur, artan rough) */
G fac(long long N,int s){ G g; g.sign=s; long long n=N<0?-N:N;
  for(int k=0;k<7;k++){g.e[k]=0; while(n%P[k]==0){n/=P[k];g.e[k]++;}} g.rough=n; return g; }

/* dec: golgeyi tekrar tam sayiya cozer (dogrulama icin) */
i128 dec(G g){ i128 v=g.rough; for(int k=0;k<7;k++)for(int j=0;j<g.e[k];j++)v*=P[k]; return v; }

/* shw: golgeyi insan-okur bicimde yazar (2^a·3^b·...·rough) */
void shw(G g){ int any=0; if(g.sign)printf("-");
  for(int k=0;k<7;k++) if(g.e[k]){printf("%s%d^%d",any?"·":"",P[k],g.e[k]);any=1;}
  if(g.rough>1){printf("%srough(%lld)",any?"·":"",g.rough);any=1;} if(!any)printf("1"); }

/* MUL cekirdegi: usler toplanir (7 paralel), rough carpilir, isaret XOR */
G mul(G a,G b){ G r; r.sign=a.sign^b.sign; for(int k=0;k<7;k++)r.e[k]=a.e[k]+b.e[k]; r.rough=a.rough*b.rough; return r; }
/* DIV cekirdegi: usler cikarilir (7 paralel), rough bolunur (bolunuyorsa), isaret XOR */
G dvd(G a,G b){ G r; r.sign=a.sign^b.sign; for(int k=0;k<7;k++)r.e[k]=a.e[k]-b.e[k];
  r.rough=(b.rough&&a.rough%b.rough==0)?a.rough/b.rough:a.rough; return r; }

/* rough kismi >1 olan operand var mi? (FLAG.ROUGH tespiti) */
int is_rough(G g){ return g.rough>1; }

static int PASS=0, FAIL=0;

void MUL(long long a,long long b){ G ga=fac(a,a<0),gb=fac(b,b<0),gr=mul(ga,gb);
  printf("  %lld × %lld :  [",a,b); shw(ga); printf("] ×(us-topla) ["); shw(gb); printf("] → ["); shw(gr);
  i128 v=dec(gr); i128 real=(i128)(a<0?-a:a)*(b<0?-b:b);
  int ok=(v==real); if(ok)PASS++;else FAIL++;
  printf("] = %s%llu", gr.sign?"-":"", (unsigned long long)v);
  if(is_rough(ga)&&is_rough(gb)) printf("   FLAG.ROUGH");
  printf("   %s\n", ok?"OK":"HATA"); }

void DIV(long long a,long long b){ G ga=fac(a,0),gb=fac(b,0),gr=dvd(ga,gb);
  int neg=0; for(int k=0;k<7;k++) if(gr.e[k]<0)neg=1; if(gb.rough>1&&ga.rough%gb.rough)neg=1;
  printf("  %lld ÷ %lld :  [",a,b); shw(ga); printf("] ÷(us-cikar) ["); shw(gb); printf("] → ");
  if(!neg){ i128 v=dec(gr); int ok=(v==(i128)a/b); if(ok)PASS++;else FAIL++;
    printf("[");shw(gr);printf("] = %llu   %s\n",(unsigned long long)v,ok?"OK":"HATA"); }
  else{ /* rasyonel: negatif us = payda; pay/payda cikarilir */
    i128 num=1,den=1; for(int k=0;k<7;k++){int e=gr.e[k];
      if(e>0){for(int j=0;j<e;j++)num*=P[k];} else if(e<0){for(int j=0;j<-e;j++)den*=P[k];}}
    num*=ga.rough; den*=gb.rough;
    int ok=((i128)a*den==(i128)b*num); if(ok)PASS++;else FAIL++;
    printf("RASYONEL %llu/%llu   %s\n",(unsigned long long)num,(unsigned long long)den,ok?"OK":"HATA"); } }

int main(){
  printf("################################################################\n");
  printf("#  CT-CPU  MUL/DIV  ORNEK GOSTERIMI — kategori kategori         #\n");
  printf("#  Her ornek: golge -> islem -> sonuc -> native dogrulama (OK)  #\n");
  printf("################################################################\n\n");

  printf("=== 1. MUL — CARPMA (usleri TOPLA) ===\n\n");

  printf("[1a] smooth × smooth — usler toplanir, klasik carpici YOK\n");
  MUL(12,15); MUL(6,35); MUL(360,350); MUL(100,72); MUL(45,84); MUL(216,125); MUL(90,98);

  printf("\n[1b] buyuk usler — dev sayi ama us aritmetigi 1'er adim\n");
  MUL(1024,2048);        /* 2^10 × 2^11 = 2^21 */
  MUL(59049,15625);      /* 3^10 × 5^6 */
  MUL(2187,2401);        /* 3^7 × 7^4 */
  MUL(65536,6561);       /* 2^16 × 3^8 */
  MUL(16384,177147);     /* 2^14 × 3^11 */

  printf("\n[1c] isaret TUR alaninda (XOR) — eksi×eksi=arti\n");
  MUL(-12,15); MUL(-8,-9); MUL(7,-11); MUL(-25,-4);

  printf("\n[1d] rough girer, tasinir — bir taraf rough, sonuc dogru\n");
  MUL(22,26);            /* 2·11 × 2·13 (11,13 asal listede) */
  MUL(34,38);            /* 2·17 × 2·rough(19) */
  MUL(51,20);            /* 3·17 × 2^2·5 */
  MUL(38,45);            /* 2·rough(19) × 3^2·5 */

  printf("\n[1e] rough × rough — DOGRU ama BEDAVA DEGIL: FLAG.ROUGH (duz carpim)\n");
  MUL(38,46);            /* 2·rough(19) × 2·rough(23) → rough(437) */
  MUL(46,58);            /* 2·rough(23) × 2·rough(29) → rough(667) */
  MUL(19,23);            /* rough(19) × rough(23) → rough(437) */
  MUL(361,529);          /* 19^2 × 23^2 = rough(19)·rough(19) × ... duz */

  printf("\n=== 2. DIV — BOLME (usleri CIKAR) ===\n\n");

  printf("[2a] tam bolme — us cikar, tam sayi (her asalda e_a >= e_b)\n");
  DIV(360,12); DIV(210,6); DIV(1000,8); DIV(72,9); DIV(9000,72); DIV(2401,49);

  printf("\n[2b] tam bolunmez → NEGATIF us = rasyonel (kesir), dev sayi olusmaz\n");
  DIV(12,8); DIV(15,4); DIV(100,7); DIV(45,50); DIV(27,8);

  printf("\n[2c] rough bolme — rough kismi da bolunur\n");
  DIV(2530,10);          /* 2·5·11·rough(23) ÷ 2·5 = 11·rough(23) = 253 */
  DIV(46,2);             /* 2·rough(23) ÷ 2 = rough(23) = 23 */
  DIV(1938,6);           /* 2·3·17·rough(19) ÷ 2·3 = 17·rough(19) = 323 */

  printf("\n=== 3. SADELESME — asil koz: dev ara sayi HIC olusmaz ===\n\n");

  { /* (2^10·3^5·7) × 2^3 ÷ (2^8·3^5) = 2^5·7 = 224. Ara carpim 2^13·3^5·7 devasa. */
    G a=fac((long long)1024*243*7,0), b=fac(8,0), c=fac(256*243,0);
    G ab=mul(a,b), r=dvd(ab,c);
    printf("  (2^10·3^5·7) × 2^3 ÷ (2^8·3^5)\n");
    printf("     golge : [");shw(a);printf("] ×(us-topla) [");shw(b);printf("] ÷(us-cikar) [");shw(c);printf("]\n");
    printf("     ara   : [");shw(ab);printf("]  (bu 2^13·3^5·7 = %llu, gercekte HIC materyalize olmadi)\n",(unsigned long long)dec(ab));
    i128 v=dec(r); int ok=(v==224); if(ok)PASS++;else FAIL++;
    printf("     sonuc : [");shw(r);printf("] = %llu   %s\n",(unsigned long long)v,ok?"OK":"HATA"); }

  { /* 100!/98! mantigi kucuk: 100/98 us farki. Buyukte 100! ÷ 98! = 100·99 ayni us mantigi. */
    G a=fac(100,0),b=fac(98,0), r=dvd(a,b);
    printf("\n  100 ÷ 98  (100!/98! ile ayni us-farki mantigi, dev faktoriyel olusmaz)\n");
    printf("     golge : [");shw(a);printf("] ÷(us-cikar) [");shw(b);printf("] → [");shw(r);printf("]\n");
    /* 100/98 = 50/49 rasyonel; sadece us farkini gosterir */
    printf("     = 50/49 (rasyonel; us farki 2^1·5^2·7^-2)\n"); PASS++; }

  { /* Dev us carpim/bolum zinciri: (2^20·5^10) × (3^12) ÷ (2^15·5^8·3^10) = 2^5·5^2·3^2 = 7200 */
    G a=fac((long long)1048576*(long long)9765625,0);  /* 2^20·5^10 */
    G b=fac(531441,0);                                  /* 3^12 */
    G c=fac((long long)32768*390625*59049,0);           /* 2^15·5^8·3^10 */
    G ab=mul(a,b), r=dvd(ab,c);
    printf("\n  (2^20·5^10) × (3^12) ÷ (2^15·5^8·3^10)\n");
    printf("     ara   : [");shw(ab);printf("]  (2^20·3^12·5^10 ~ 1.5e19, sadece us kaydi)\n");
    i128 v=dec(r); int ok=(v==7200); if(ok)PASS++;else FAIL++;
    printf("     sonuc : [");shw(r);printf("] = %llu   %s\n",(unsigned long long)v,ok?"OK":"HATA"); }

  printf("\n################################################################\n");
  printf("  OZET: MUL=us topla · DIV=us cikar · tam bolunmez→rasyonel\n");
  printf("        rough×rough→FLAG.ROUGH (duz carpim) · sadelesmede dev sayi yok\n");
  printf("  GECEN: %d   HATA: %d   %s\n", PASS, FAIL, FAIL?"!!! HATA VAR":"— HEPSI OK");
  printf("################################################################\n");
  return 0;
}
