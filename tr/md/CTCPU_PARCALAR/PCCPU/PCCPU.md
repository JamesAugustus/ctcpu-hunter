# PCCPU

James Augustus

## Bir cümleyle

PCCPU, hesap yapmayan ve işi dağıtan ayrı bir denetleyici birimi. Üzerinde çalıştığım bir tasarım. Henüz bitmedi ve Hunter'ın tek çekirdekli hâline yerleştirmedim.

## Fikir

Eski CT-CPU tasarımımda 4096 çekirdek vardı. Bunlara 4097. bir çekirdek ekledim ve ona PCCPU (Program Counter CPU) dedim. Hesap yapmaz, düdük çalar. Ritmi belirler, yani saati. Sırayı tutar, yani sayacı. Kime ne gideceğini söyler, yani adresi. Komutun içeriğini bilmek zorunda değil, yalnız dağıtır. Bir trafik polisi ya da bir iskambil dağıtıcısı gibi.

Tasarımda bir yanlışımı düzelttim. İlk başta PCCPU'nun her saat vuruşunda komut beslediğini sanıyordum. Dört bin çekirdeği tek tek beslemek darboğaz olurdu. Doğrusu şu: PCCPU işi başlatır ve geri çekilir, çekirdekler bağımsız çalışır, her birinin kendi sayacı ve kendi döngüsü vardır. PCCPU'ya yalnız dışarıyla bir iş çıktığında dönülür: bir taşma olduğunda, çekirdekler arasında veri geçeceğinde, bir iş bittiğinde ve senkronizasyon gerektiğinde. Düdükçü "başla" der, sporcular kendi çalışmasını yapar. Düdük yalnız çarpışma, zaman ya da değişim için çalar, her hareketi söylemez.

## Üç çalışma biçimi

Merkez biçiminde PCCPU her komutu tek tek yollar ve çekirdekler söyleneni yapar. Bu sıralıdır, paralellik yoktur. Bağımsız biçimde PCCPU işi dağıtır ve izler, her çekirdek kendi programını çalıştırır. Küp ve lider biçiminde çekirdekler küplere ayrılır, PCCPU yalnız liderlerle konuşur ve işçi çekirdekler yalnız hesap yapar.

Bence tek biçim seçmek yanlış, üçü birlikte çalışmalı. Sistem açılınca veriyi merkez biçimiyle yüklerim, sonra küpleri kurarım, boştaki çekirdekler bağımsız çalışır ve PCCPU hangisinin ne zaman etkin olacağına karar verir.

## Henüz açık olanlar

Programın nerede tutulacağı açık: registerlarda mı, her çekirdekte küçük bir komut tamponunda mı, yoksa PCCPU'dan yayınla mı. PCCPU'nun kendisinin nereye oturacağı da açık: ızgaranın dışına mı, içine mi, yoksa yazılımla mı. İçinde ne olacağını tartışıyorum: program sayacı, adres çözücü, komut çözücü ve belki çekirdeklerin meşgul mü boş mu olduğunu tutan bir tablo. Birden fazla PCCPU gerekir mi, buna şimdilik tek PCCPU ile başlayıp darboğaz çıkarsa bakacağım.

Hunter bugün tek çekirdekli. Orada komut kaynağının ve program sayacının yeri henüz belli değil. Eski PCCPU'yu bu boşluğa bitmiş bir parça gibi yerleştirmiyorum. Bu belge tasarımın şimdiki durumunu anlatıyor, test edilmiş bir devre göstermiyor.
