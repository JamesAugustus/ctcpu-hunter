# Reddetme ve karantina karşılaştırması

## Ne sınar

Rastgele temiz işlem zincirlerinin iki kesir modelinde kesin referansla aynı olmasını denetler. Sıfıra bölme durumunda karantina kilidinin sayı sızdırmamasını ve kaynak izini korumasını sınar.

## Nasıl çalışır

Bir milyon örneğin her birinde beş işlemli zincir kurulur. v1.3 ve v1.4 sonuçları bağımsız kesir referansıyla r.n×ref.d=ref.n×r.d eşitliği üzerinden karşılaştırılır. Sıfıra bölme enjekte edilen zincirde kilidin korunması ve iz değerinin kalan çarpanların bağımsız çarpımına eşitliği aranır. Fark veya yanlış karantina davranışı ilgili sayacı artırır.

## Neden önemli

Asal üs ve rough bileşenleriyle yapılan çarpma ve bölmenin referans aritmetiğe bağlanmasını sağlar.

## Çalıştırma

```sh
cd TESTLER/HUNTER/04_CARPMA_BOLME/kesir_v13_v14_kiyas
gcc -std=c11 -O2 kesir_v13_v14_kiyas.c -o ./test_programi -lm && ./test_programi
```

Gerekenler: gcc, libm.

## Kaynak

Kaynak: [kesir_v13_v14_kiyas.c](../../../../../TESTLER/HUNTER/04_CARPMA_BOLME/kesir_v13_v14_kiyas/kesir_v13_v14_kiyas.c)

Arşivdeki satır sayısı: 125.
