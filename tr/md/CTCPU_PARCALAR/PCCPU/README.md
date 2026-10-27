# PCCPU belgeleri

James Augustus

Bu bölüm PCCPU tasarımını, çalışan C hücre modelini ve simetrik thread/RAM önerisini bir araya getirir. Matematiksel bağlantı Pascal katsayılarının simetrisi ve Mersenne tabanındaki N(p) eldesiz satır sınırıdır.


| Belge | Markdown | PDF |
|---|---|---|
| PCCPU tasarımı, N(p) ve simetrik thread | [Metin](PCCPU.md) | [PDF](../../../pdf/CTCPU_PARCALAR/PCCPU/PCCPU.pdf) |
| C testinin adım adım açıklaması | [Metin](PCCPU_C_TESTI_ACIKLAMA.md) | [PDF](../../../pdf/CTCPU_PARCALAR/PCCPU/PCCPU_C_TESTI_ACIKLAMA.pdf) |
| Yeniden çalıştırılan testlerin sonuçları | [Sonuçlar](TEST_SONUCLARI.md) | Ham çıktı aşağıdadır |

[C kaynağı](../../../../kod/PCCPU/pccpu_address_model.c), [çalıştırma betiği](../../../../kod/PCCPU/calistir.sh) ve [ham test çıktısı](../../../../kod/PCCPU/TEST_OUTPUT.txt) aynı kod klasöründedir.

Depo kökünden:

```sh
bash kod/PCCPU/calistir.sh
```

Çalışan C modeli iki üretici, bir toplayıcı ve denetleyici durumunu içerir. Bir thread içinde iki simetrik konumu tutan RAM düzeni henüz tasarım önerisidir. Mevcut test sonuçları bu önerinin donanımda veya C kodunda uygulanmış olduğunu göstermez.

[CTCPU parçaları](../README.md) | [English](../../../../md/CTCPU_PARTS/PCCPU/README.md)

## CTMemTensor ve adresleme seçenekleri

[CTMemTensor](../CTMemTensor/CTMemTensor.md) ayrı bir CTCPU parçası olarak sayı ve konum gösterimini ele alır. Merkezden başlayan sistemde N(9,0) = 126 ve [1,4,6,4,1] satırının adresleri -2,-1,0,+1,+2 olur. PCCPU örneğindeki C(9,4) klasik binom sütunudur. Önceki kenar başlangıçlı thread örneği de düşünülen seçenekler arasında korunur.

C modelinin asıl kaynağı [kod/PCCPU/pccpu_address_model.c](../../../../kod/PCCPU/pccpu_address_model.c) dosyasıdır. Pascal deposunda aynı çevrimdışı örneğin kopyası bulunur.
