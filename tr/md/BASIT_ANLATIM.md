# Çok basit anlatım

James Augustus

## Bir cümleyle

Bir sayıyı iki biçimde birlikte tutan ve çarpmayı toplamaya çeviren bir işlemci fikri. Henüz çipi yok. Elimde bilgisayarda çalışan modeller ve testler var.

## Renkten başladım

Üç ışık kanalı vardır: kırmızı, yeşil ve mavi. Her kanal ya yanar ya söner, bu da sekiz renk eder. Sekiz durum, sekizlik sayı sisteminde tam bir hane eder, yani 0 ile 7 arası bir rakam. Böylece her hane bir renktir. 5 rakamı kırmızı ile mavinin birlikte yanmasıdır, yani macenta. Üç bitlik bu birime xbit diyorum. 360 sayısı sekizlikte 550 yazılır, yani macenta, macenta, siyah.

Renkler benim için yalnız bir gösterim değil. Renkler gerçek hayatta fiziksel bir olay olarak birleşir ve sonuç ışığın hızında ortaya çıkar. Fiziksel bir olay benim için doğal bir mantık kapısı. Bunu matematikte kullanmak istediğim için sekizlik sistemi seçtim ve 8 sayısı yaptığım her denemede çok iyi bir uyum gösteriyor. Gerçek renklerle kuracağım fiziksel tasarımlarım da var, ama o işlere daha çok var. Sekiz ışık rengi üzerine sekizlik mantık kuran benzer bir çalışmayı da buldum: [Talal, Abu-Elnasr ve Elmougy, 2021](https://doi.org/10.32604/cmc.2021.015759).

## Sayıyı iki biçimde tutmak

Toplamak için sayıyı hanelerde tutarım. Çarpmak için ise sayıyı asal çarpanlarına ayırır, her asalın kaç kere geçtiğini yazarım. Buna gölge diyorum. 360 = 2³ × 3² × 5 olduğundan gölgesi 2'den üç, 3'ten iki, 5'ten bir tanedir.

Gölgede çarpma toplamaya döner. 12 ile 30'u çarpalım. 12 = 2² × 3 ve 30 = 2 × 3 × 5. Üsleri toplarım: 2 için 2 + 1 = 3, 3 için 1 + 1 = 2, 5 için 0 + 1 = 1. Sonuç 2³ × 3² × 5 = 360. Bölme çıkarmaya, kök alma üsleri ikiye bölmeye döner. Cevabı hane hane hesaplamak yerine üsleri oynatıyorum.

## İnsan gibi hesaplamak

Bir insan 10 çarpı 9'u dokuz tane on toplayarak yapmaz, 90 der. 21 çarpı 36'yı 7 çarpı 108'e çevirir. Sınavda 3√2'yi on basamaklı bir ondalık sayıya çevirmez, olduğu gibi bırakır. Makinenin de böyle çalışmasını istedim: çarpanına ayırır, sembolü tutar, en sonda açar. Karekök, ters, toplam ve faktöriyel gibi şeyleri de tür olarak taşırım ve ancak bir değer gerektiğinde açarım.

## Gölgeyi kim çıkarıyor

Resolver denen parça bir sayıyı gölgesine çevirir. Bunu bölme olmadan, dişli ve kadranlarla anlatıyorum. Yedi küçük asalın (2, 3, 5, 7, 11, 13 ve 17) her biri için bir kadran, sayının sekizlik hanelerini soldan sağa okur ve o asalın kaç kere geçtiğini sayar. Bu asalların hiçbirine bölünmeyen artığa rough diyorum ve olduğu gibi saklıyorum. Ayrıntısı [Çark modeli](CTCPU_PARCALAR/Resolver/Cark.md) belgesinde.

## Ne olduğu, ne olmadığı

Silikon yok. Hız ya da enerji üstünlüğü iddiam da yok. Elimde fikir, çalışan modeller, 32 test paketi ve tutmayan iddialarımın kaydı var. Dört fikrim sınandı ve tutmadı, bunları günlükte bıraktım.

## Neden yapıyorum

Bu benim hobim ve hayatım. Bilim insanı kültürüyle büyüdüm ve okudum. Laboratuvar derslerinde raporları ve ölçümleri nefret ede ede yazdım, o zaman bunların bir anlamı ve amacı vardı. Şimdi elimizdeki teknolojiyle altmış yıl öncesinin hobileri gibi yazmayacağım. Çok şey araştırıp ince ince yazacağım, gerekirse dağılacağım. Amacım basit: biz hesap yaparken nasıl taktikler uyguluyorsak bilgisayar dilinde de aynı taktikleri uygulayabilmek. Bir de bir işlem yaparken kendim öğrenmek.

## Takıldığım yerler

Takıldığım sorular var, geliştirilmesini istediğim yerler var. İnsanlar kendileri geliştirsin isterim, önerilere açığım. Açık sorularım [Nihai Form](NIHAI_FORM/CTCPU_NIHAI.md)'un 16. bölümünde.

## Sonra nereye

Merak edersen önce [Çark modeli](CTCPU_PARCALAR/Resolver/Cark.md)ni, sonra [Nihai Form](NIHAI_FORM/CTCPU_NIHAI.md)'u, sonra [günlüğü](YOL.md) oku.
