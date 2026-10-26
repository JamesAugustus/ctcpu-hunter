#ifndef SHADOW_H
#define SHADOW_H

#include "xbit.h"

void shadow_resolve(Shadow *s, uint32_t value);
void shadow_clear(Shadow *s);

/* GOLGE CARPMA — merdiven bir SAKLAMA formatidir, aritmetik formati degil:
   1. AC (us vektoru + rough)  2. usleri TOPLA + rough BINOM  3. yeniden ENCODE
   Doner: 1 = OVF (deger 2^24'u asti; GOLGE DEGERI YINE TAM) */
int shadow_mul(Shadow *dst, const Shadow *a, const Shadow *b);

/* GOLGE BOLME — ayni iskelet: AC -> usleri CIKAR + rough BOL -> ENCODE.
   Doner: -1 = tam bolunmuyor (cagiran pozisyonel yola duser) */
int shadow_div(Shadow *dst, const Shadow *a, const Shadow *b);

/* i'inci asalin TOPLAM ussu (merdivende birden fazla satira yayilmis olabilir) */
uint8_t shadow_total_exp(const Shadow *s, int i);

/* golgenin tasidigi tam deger (2^24 assa bile bozulmaz) */
uint64_t shadow_value(const Shadow *s);

void shadow_print(const Shadow *s);   /* OKTAL basar (Cem kurali) */

/* mod 7 via digit sum (LOG-025) */
uint32_t xbit_mod7(uint32_t value);

#endif
