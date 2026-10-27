# CTCPU-Hunter

> **Silikon yok.** MHz ve watt değerleri ile donanıma ilişkin cycle tahminleri model değerleridir. Arşivdeki seçili emülatör kaynakları bu paket için yeniden çalıştırıldı. Önceki emülatör ölçümleri tarihsel kayıt olarak kalıyor. Burada çalıştırılabilen kod, 30 arşiv testini ve `TESTLER/NIHAI_EK/` altındaki iki doğrulama programını içeriyor.

CTCPU, üzerinde çalıştığım ve sonradan Hunter olan bir işlemci fikri. Bu işe renkten başladım. En küçük birimi üç bit, yani sekiz renkten biri. Sayılar ayrıca asal üslerden oluşan ikinci bir "gölge" biçiminde de tutulabiliyor. Makine insan gibi hesaplamaya çalışıyor: çarpanına ayırır, sembolü tutar, en sonda açar. Elde çip yok, ölçülmüş bir hız ya da enerji sonucu da yok. Bu, devam eden bir çalışmanın kaydı, bitmiş bir işlemci değil.

## Teknik metin

[Ana metin](md/CTCPU_HUNTER.md) ve [PDF](pdf/CTCPU_HUNTER.pdf).

James Augustus. [ORCID: 0009-0002-7286-7730](https://orcid.org/0009-0002-7286-7730).

## Nereden başlamalı

| Belge | Ne anlatıyor |
|---|---|
| [Çok basit anlatım](pdf/BASIT_ANLATIM.pdf) ([Markdown](md/BASIT_ANLATIM.md)) | Bütün fikir tek sayfada, sade sözlerle |
| [Nihai Form](pdf/NIHAI_FORM/CTCPU_NIHAI.pdf) ([Markdown](md/NIHAI_FORM/CTCPU_NIHAI.md)) | Bütün makine tek belgede: hücre, renk kapıları, register, Resolver, çarpma, bölme, karekök, türler, çekirdek ve doğrulama |
| [CTCPU](md/CTCPU.md) | Makinenin kısa tanımı |
| [CTCPU parçaları](md/CTCPU_PARCALAR/README.md) | Her parçanın ayrı belgesi |
| [Resolver](md/CTCPU_PARCALAR/Resolver/Resolver.md) | Sayıyı gölge biçimine çeviren parça, çalışan biçimler |
| [Resolver deneyleri](md/CTCPU_PARCALAR/Resolver/Deneyler/Deneyler.md) | Denediğim öteki biçimler |
| [Dişli modeli](md/CTCPU_PARCALAR/Resolver/Cark.md) | Resolver'ın dişlilerle anlatımı |
| [ISA](md/ISA.md) | Komut kümesi |
| [PCCPU](md/CTCPU_PARCALAR/PCCPU/README.md) ([PDF](pdf/CTCPU_PARCALAR/PCCPU/PCCPU.pdf)) | Hücre adresleme, C modeli, simetrik thread önerisi ve [test sonuçları](md/CTCPU_PARCALAR/PCCPU/TEST_SONUCLARI.md) |
| [CTMemTensor](md/CTCPU_PARCALAR/CTMemTensor/CTMemTensor.md) ([PDF](pdf/CTCPU_PARCALAR/CTMemTensor/CTMemTensor.pdf)) | Merkezden adresleme ve düşünülen bellek sistemleri |
| [Hunter'a Giden Yol](pdf/YOL.pdf) ([Markdown](md/YOL.md)) | Araştırma günlüğüm, ne denedim, ne tuttu, ne tutmadı |
| [Testler](TESTLER/README.md) | Nihai Form'daki iddiaların testleri |
| [Küçük Mesaj](md/KUCUK_MESAJ.md) | Bunu neden yapıyorum |
| [Bir Not](md/NOT.md) | Bilgi, ego ve sıra üzerine |
| [English](../README.md) | Deponun İngilizce girişi |

Ana metinleri `md/` altında Markdown, `pdf/` içindeki karşılık gelen klasörlerde PDF olarak tutuyorum. Türkçe için `tr/` altında aynı düzeni kullanıyorum. Bağımsız Pascigon şekli yalnız PDF olarak bulunuyor. SVG şekil dosyaları yalnız Markdown ağaçlarında, `TESTLER/` ise iki dil için ortak. Çok basit anlatım deponun kökünde duruyor, PDF'i pdf/ altında.

İngilizce günlük [The Road So Far](../pdf/THE_ROAD_SO_FAR.pdf) adıyla ana klasörde duruyor. Mersenne satırı çalışması ayrı [Pascal Mersenne Rows](https://github.com/JamesAugustus/pascal-mersenne-rows) deposunda. Günlükteki Pascigon şekli de ayrıca açılabilir: [Türkçe](pdf/Pascigon.pdf) ve [İngilizce](../pdf/Pascigon.pdf).

## Testleri çalıştır

Nihai Form'un dayandığı testlerin Türkçe açıklamaları [TESTLER](TESTLER/README.md) ağacındadır. Çalıştırılabilir kaynaklar depo kökündeki [TESTLER](../TESTLER/) ağacında kalır. Her testin kendi klasöründe ne yaptığını anlatan Türkçe bir `TEST.md` ve tek satırlık çalıştırma komutu var.

Günlükteki 22 iddianın testi ayrı bir programdır. C99 derleyicisi bulunan bir bilgisayarda, deponun ana klasöründen şu komutlarla çalışır:

```sh
cc -std=c99 -O2 -Wall -Wextra -o journal_tests journal_tests.c -lm
./journal_tests
```

Üçüncü taraf kütüphane gerekmez. [Kaynak kod](../journal_tests.c) ve [beklenen çıktı](../TEST_OUTPUT.txt) pakette bulunur. Beklenen özet:

```text
HOLDS=15 | FAILS=4 | UNTESTED=3 | ERROR=0 | tests=22
```

`HOLDS`, iddianın denenen durumlarda tuttuğunu gösterir. `FAILS`, iddiaya karşı örnek bulunduğu anlamına gelir, test programının bozulduğu anlamına gelmez. `UNTESTED`, bu paketin iddiayı sınayamadığını belirtir. `ERROR`, uygulanmış bir kontrolün beklenen sonucu vermediğini gösterir. Çıkış kodu 0, böyle bir hata oluşmadığı anlamına gelir. Günlükteki bütün iddiaları kanıtlamaz.

## Lisans ve atıf

C ve Python kodu [MIT](../LICENSE) lisanslıdır. Türkçe ve İngilizce metinler, PDF'ler, şekiller, test çıktısı ve atıf bilgileri, James Augustus'a atıf şartıyla [CC BY 4.0](../LICENSE-CC-BY-4.0.txt) lisanslıdır. Bu lisanslar kaynak gösterilen üçüncü taraf eserleri yeniden lisanslamaz. Atıf bilgileri [CITATION.cff](../CITATION.cff) dosyasındadır.

## Bu çalışma hakkında

Bu proje takıntılı bir hobi projesi olarak başladı, sonra bir meraka dönüştü ve şu anda da devam ediyorum. Kendimi geliştirmek ve bakış açımı içimde tutmamak için yapıyorum. Niyetim kendimi gerçek alanda geliştirebilmek, teorinin dışına çıkmak ve araştırmalarıma devam edebilmek.

Python dili benim için hâlâ çok iyi değil. C'de bile iyi değilim, bazen o bile bana yüksek seviye geliyor. Kodlama derslerim devam ediyor. Bilgisayarla ilgili sürekli yeni kitaplar ve yeni teknikler okuyorum. Bu süreçte yapay zekâ araçları tabii ki kullanılmıştır, hem derleme, yazı tipi ve sayfa düzeni için hem de öğrenirken bir mentor gibi. On yıl önce olsaydı büyük ihtimalle Microsoft Word'ün hazır şablonlarını ve WordArt'ı kullanırdım, yazı tipi ve sayfa düzeniyle bu kadar uğraşmazdım. Times New Roman'dan rahat klavye seçimime kadar, bu hayatta yardım aldığım doğrudur. Tek tek elimle yazdığım şeyleri o komik ve karışık halleriyle böyle bir paylaşıma dönüştüremezdim. Fikirler, hesaplar ve deneyler bana ait. Hedefim bu yöntemleri hiçbir programa ihtiyaç duymadan, yalnız bir not defteriyle yürütebilecek hale gelmek.

Çalışmanın çoğunu önce elle yaptım. Tek bir Pisagor üçgeninden karekök yöntemi aradığım yirmi sayfa, elle çapraz yaptığım binom açılımları ve bulduğum boş kağıtlara aldığım notlar evimde duruyor. Görmek isteyen gelip görebilir, ama hepsi epey kötü halde.

Atıf yaptığım kişilere ve adını anamadığım, bu çalışmaya bir şekilde katkısı olan herkese şimdiden teşekkür ederim.
