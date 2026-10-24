# CTCPU ve Hunter: Hunter'a Giden Yol

> **Silikon yok.** MHz ve watt değerleri ile donanıma ilişkin cycle tahminleri model değerleridir. Arşivdeki emülatör ölçümleri bu paket için yeniden çalıştırılmadı. Burada çalıştırılabilen kod, aşağıdaki matematik testleridir.

**Kısaca.** CTCPU, üzerinde çalıştığım ve sonradan Hunter olan bir işlemci fikri. En küçük birimi üç bit, yani sekiz renkten biri. Sayılar ayrıca asal üslerden oluşan ikinci bir "gölge" biçiminde de tutulabiliyor. Bu depoda araştırma günlüğüm, makine ve parçaları üzerine kısa sayfalar ve günlükteki matematiksel iddialara ait 22 test var: 15'i tutuyor, 4'ü bir karşı örnekle yanlış çıkıyor, 3'ü burada test edilemiyor. Elde çip yok, ölçülmüş bir hız ya da enerji sonucu da yok. Önce [CTCPU sayfasına](CTCPU.md) bak, sonra günlüğü oku.

Bu, CT-CPU ve Hunter'a uzanan fikirlerim üzerine tuttuğum araştırma günlüğü. Ne denediğimi, neyin işe yaradığını, neyin tutmadığını ve neyin zaten bilindiğini sonradan öğrendiğimi anlatıyor. Sayı gösterimleri, Pascal üçgeni ve Mersenne sayıları üzerine notlarımın yanında hesaplar, kaynaklar ve kişisel düşüncelerim var.

Bu depo, CTCPU/HUNTER çalışmasının sayı gösterimi ve Pascal yapıları üzerine matematiksel temelini ve doğrulama deneylerini içerir.

Bunu neden yapıyorum: [Küçük Mesaj](KUCUK_MESAJ.md).

Bilgi, ego ve sıra üzerine: [Bir Not](NOT.md).

Makinenin tanımı ve parçaları: [CTCPU](CTCPU.md) · [CTCPU parçaları](CTCPU_PARCALAR/README.md) · [Resolver](CTCPU_PARCALAR/Resolver.md).

## Günlüğü oku

- **Türkçe:** [Hunter’a Giden Yol — PDF](YOL.pdf) · [Markdown](YOL.md)
- **English:** [The Road So Far — PDF](../THE_ROAD_SO_FAR.pdf) · [Markdown](../THE_ROAD_SO_FAR.md)

İki sürüm aynı kayıtları, formülleri ve test sonuçlarını içerir. Günlük kendi ağzımdan anlatılıyor; yeniden anlattığım sohbet notları doğrudan alıntılardan ayrılıyor.

Bu, devam eden bir çalışmanın kaydı; bitmiş bir işlemci değil. Bazı eski deneyler arşiv kayıtlarından anlatılıyor ve bu depodan yeniden çalıştırılamıyor. Buradaki 22 test, belirli matematiksel iddiaları kontrol ediyor.

Mersenne satırı çalışması ayrı [Pascal Mersenne Rows](https://github.com/JamesAugustus/pascal-mersenne-rows) deposunda bulunuyor. Günlükteki Pascigon şekli de ayrıca açılabilir: [Türkçe](Pascigon.pdf) · [İngilizce](../Pascigon.pdf).

## Testleri çalıştır

C99 derleyicisi bulunan bir bilgisayarda, deponun ana klasöründen şu komutları çalıştır:

```sh
cc -std=c99 -O2 -Wall -Wextra -o journal_tests journal_tests.c -lm
./journal_tests
```

Üçüncü taraf kütüphane gerekmez. [Kaynak kod](../journal_tests.c) ve [beklenen çıktı](../TEST_OUTPUT.txt) pakette bulunur. Beklenen özet:

```text
HOLDS=15 | FAILS=4 | UNTESTED=3 | ERROR=0 | tests=22
```

`HOLDS`, iddianın denenen durumlarda tuttuğunu gösterir. `FAILS`, iddiaya karşı örnek bulunduğu anlamına gelir; test programının bozulduğu anlamına gelmez. `UNTESTED`, bu paketin iddiayı sınayamadığını belirtir. `ERROR`, uygulanmış bir kontrolün beklenen sonucu vermediğini gösterir. Çıkış kodu 0, böyle bir hata oluşmadığı anlamına gelir; günlükteki bütün iddiaları kanıtlamaz.

## Lisans ve atıf

C kodu [MIT](../LICENSE) lisanslıdır. Türkçe ve İngilizce metinler, PDF'ler, şekiller, test çıktısı ve atıf bilgileri, James Augustus'a atıf şartıyla [CC BY 4.0](../LICENSE-CC-BY-4.0.txt) lisanslıdır. Bu lisanslar günlükte kaynak gösterilen üçüncü taraf eserleri yeniden lisanslamaz. Atıf bilgileri [CITATION.cff](../CITATION.cff) dosyasındadır.
