# PCCPU C modeli: test sonuçları

James Augustus

Çalıştırma tarihi: 27 Ekim 2026.

## Sonuç

C kaynağı yeniden derlendi ve testler çalıştırıldı. **60.353 kontrol geçti, 0 hata.** Çalıştırma betiği 0 çıkış koduyla tamamlandı. Küçük örnek 210, büyük örnek aşağıdaki 59 haneli sonucu verdi:

```text
90548514656103281165404177077484163874504589675413336841320
```

[Ham çıktı](../../../../kod/PCCPU/TEST_OUTPUT.txt), derleme mesajı, test özeti ve iki gösterimin çıktısını içerir. Kullanıcı adı, makine adı veya mutlak yerel dosya yolu içermez.

## Yeniden çalıştırma

Depo kökünden:

```sh
bash kod/PCCPU/calistir.sh
```

Bash, C11 destekleyen bir C derleyicisi ve GMP geliştirme dosyaları gerekir. Derleme seçenekleri `-std=c11 -O2 -Wall -Wextra -Werror -pedantic` ve `-lgmp`'dir. Derlenen program önce `--test`, sonra `--demo` ile çalıştırılır. Geçici derleme çıktısı sonunda kaldırılır. Ağ bağlantısı gerekmez.

## Kontrol edilen davranışlar

| Kontrol | Gözlenen sonuç |
|---|---|
| Altı hücre ve koordinat sınırları | Adresler ayrı, geçersiz koordinat reddedildi |
| Geçersiz satır ve yinelenen işçi sırası | İstek reddedildi, sayaçlar değişmedi |
| Hazır olmayan sonuç ve geçersiz adres okuması | Okuma reddedildi |
| Tüketicinin üreticileri beklemesi | İlk turda yalnız A ve B, ikinci turda C tamamlandı |
| Altı farklı işçi inceleme sırası | Aynı sonuç, 3 tamamlanan iş, 2 mantıksal tur |
| Bitmiş modeli yeniden çalıştırma | Yeni iş oluşmadı, sayaçlar artmadı |
| 20.100 komşu Pascal toplamı | Yalnız toplama ile kurulan bağımsız satır hesabıyla aynı |
| Sabit 64 bit sınırını aşan değer | GMP tam sayılarıyla doğru sonuç |
| Eldesiz satır çarpımı kararı | Taban 10, 3 ve 127 sınır örnekleri geçti |
| Katsayının tabana eşit olması | Eldesiz kabul edilmedi |
| Geçersiz taban ve satır toplamı taşması | İstek reddedildi |

Pascal karşılaştırması n = 1..200 satırlarının bütün komşu çiftlerini kapsar. Çift sayısı 1 + 2 + ... + 200 = 20.100'dür. Her çiftte kurulum, yürütme ve değer eşitliği kontrol edilir. Diğer kontrollerle toplam 60.353 koşul değerlendirilir. Bu sayı, 60.353 ayrı algoritma veya donanım deneyi anlamına gelmez.

Karşılaştırma tarafı binom katsayısı yordamını kullanmaz, satırları yalnız toplama ile kurar. Ancak iki taraf da büyük tam sayı aritmetiği için GMP kullanır. Ayrı bir aritmetik kütüphanesiyle doğrulama yapılmış sayılmaz.

## Gösterim sonuçları

| Gösterim | Değer | Denetleyici |
|---|---|---|
| C(9,3) + C(9,4) | 84 + 126 = 210 | 3 iş, 2 tur |
| C(199,99) + C(199,100) | C(200,100), 59 hane | 3 iş, 2 tur |

Terminaldeki 121 × 121 ve 1331 × 121 çarpım cümleleri açıklama metnidir. Otomatik test, bu satırların eldesiz gösterim kararını denetler. Tam sayıları bu iki çarpımla yeniden üretip karşılaştıran ayrı bir test içermez.

## Bu sonuçların kapsamadıkları

Simetrik thread kaydı, iki taraflı RAM alanı, taraf seçimi ve yazma sonrası geçersizleştirme henüz bu C programında uygulanmadı. Bu test sayısı onların doğrulandığı anlamına gelmez. C modeli N(p)'yi hesaplamaz. Fiziksel PCCPU, gerçek eşzamanlı yürütme, saat çevrimi, hız, enerji ve toplam bellek kazancı ölçülmedi.

Kodun mevcut yürütme modeli [sade açıklamada](PCCPU_C_TESTI_ACIKLAMA.md), önerilen mimari genişletme ise [PCCPU belgesinde](PCCPU.md) anlatılır.

Adresleme notu: Buradaki C(n,j), test programının klasik binom notasyonudur. CTMemTensor merkez gösteriminde aynı orta katsayı N(9,0) = 126 olur. Adresleme seçenekleri [ayrı belgede](../CTMemTensor/CTMemTensor.md) tanımlanır.


## CTMemTensor sayısal gösterimi

CTMemTensor HTML gösteriminde n = 0..16 ve x = 2..255 aralığı üç adresleme kipinde kontrol edildi: merkez çifti, soldan sütun ve iki kat geometrik koordinat. Toplam 12.954 satır, taban ve kip birleşiminde ağırlıklı toplam (x+1)^n ile eşleşti. Katsayılar yalnız toplama ile oluşturulan bağımsız Pascal satırlarıyla karşılaştırıldı. Her sütunun tam bir kez kapsandığı ve tek merkez konumunun iki kez toplanmadığı kontrol edildi.

N(9,0) = 126 ve N(4,-2..+2) = [1,4,6,4,1] örnekleri doğrulandı. On üç geçersiz girdi reddedildi. Bu sonuçlar tarayıcıdaki matematiksel gösterime aittir. C adres çözücüsünü, eşzamanlı thread yürütmesini veya fiziksel RAM protokolünü doğrulamaz.
