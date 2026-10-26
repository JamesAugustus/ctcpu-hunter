/* Kaynak çekirdek değişmeden dahil edilir. Derleyici -I ile geçici kopyayı seçer. */
#define main kaynak_main
#include "hunter_cekirdek.c"
#undef main
#include <assert.h>

int main(void) {
    static hunter h, a, b, r;
    static sayi s;
    unsigned e;
    int k, neden;
    for (k=0;k<KANAL;k++) {
        memset(&h,0,sizeof h);
        for(e=0;e<4095;e++) {
            assert(us(&h,k)==e);
            assert(sayac_tik(&h,k)>=0);
        }
        assert(us(&h,k)==4095);
        assert(sayac_tik(&h,k)==-1);
    }
    assert(oku(&s,"2^4095")); h_yukle(&a,&s);
    assert(resolver(&a,0)==1 && us(&a,0)==4095);
    assert(geri_kur(&a,0)==1 && kiyas(&a.rm,&s)==0);
    assert(oku(&s,"2")); h_yukle(&b,&s);
    assert(h_carp(&r,&a,&b)==-1);
    assert(oku(&s,"2^4096")); h_yukle(&a,&s);
    assert(resolver(&a,0)==-1);
    assert(oku(&s,"19")); h_yukle(&a,&s);
    assert(oku(&s,"23")); h_yukle(&b,&s);
    assert(h_bol(&r,&a,&b,&neden)==0 && neden==KANAL);
    assert(oku(&s,"0")); h_yukle(&b,&s);
    assert(h_bol(&r,&a,&b,&neden)==-1);
    printf("GECTI: yedi kanalda 0..4095 sayaç ve sonraki tıkta taşma reddi\n");
    printf("GECTI: 2^4095 geri kurma, 2^4096 ve 2^4095 çarpı 2 reddi\n");
    printf("GECTI: 19/23 tam bölünmez, kanal üsleri yeterli koşul değildir\n");
    printf("GECTI: sıfıra bölme reddi. Otomatik pozisyonel fallback sınanmadı\n");
    return 0;
}
