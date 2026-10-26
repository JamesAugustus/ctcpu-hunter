# Ana emülatör merdiven kabulü

## Ne sınar

Ana shadow.c uygulamasının gölge saklamasını gerçek proje fonksiyonlarıyla çalıştırır. Sabit örnekler ve taramalarda geri okunan sayının girişe eşitliğini denetler.

## Nasıl çalışır

1..16777215 girdileri gerçek shadow_resolve ile saklanır ve shadow_value ile geri okunur. 1<=a<=b<4096 çiftlerinin tam taramasında çarpım kaydı a×b ile karşılaştırılır. 1<=a,b<4096 koşulundaki 1.000.000 rastgele çiftin ayrı taramasında çarpım kaydının b ile bölümü a değerini vermelidir. Sabit taşma ve rough örnekleri ayrıca yürütülür. Geri dönüş, çarpım veya bölüm hata sayacının artması başarısızlık koşuludur.

## Neden önemli

Gölge temsilindeki merdiven satırlarının değer korunumunu ve kayıt kapasitesini inceler.

## Çalıştırma

```sh
cd TESTLER/HUNTER/02_MERDIVEN/test_golge_merdiven/kod/SISTEM/ctcpu/05_KOD/TESTLER
gcc -std=c11 -O2 test_golge_merdiven.c ../EMULATOR/shadow.c -o ./test_programi -lm && ./test_programi
```

Gerekenler: gcc, libm.

kod/ dizini kaynakta kullanılan göreli hiyerarşiyi korur.

## Kaynak

Kaynak: [test_golge_merdiven.c](kod/SISTEM/ctcpu/05_KOD/TESTLER/test_golge_merdiven.c)

Arşivdeki satır sayısı: 132.
