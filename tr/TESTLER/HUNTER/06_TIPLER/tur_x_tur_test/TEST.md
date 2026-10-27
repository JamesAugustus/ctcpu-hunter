# Tür çarpım ve ters tabloları

## Ne sınar

Sekiz türün 64 çarpım hücresini işaret, imajiner birim, kesin kesir ve kök içi biçiminde bağımsız cebirle karşılaştırır. Ters alma ve işaret değiştirme tablolarını da denetler.

## Nasıl çalışır

Sekiz türün 64 çarpım çifti Svals girdileriyle denenir. Faktöriyel türünde 10 üstü örnekler taşmayı önlemek için atlanır. Makinenin tür tablosundan çıkan değer bağımsız kesin kesir ve kök cebrine çevrilip karşılaştırılır. Ters alma ve işaret değiştirme de aynı referansla denetlenir. exeq eşitliği sağlanmazsa hata sayılır.

## Neden önemli

Hunter tür ve ölçek kodlarının aritmetik anlamının korunmasını inceler.

## Çalıştırma

```sh
cd TESTLER/HUNTER/06_TIPLER/tur_x_tur_test
gcc -std=c11 -O2 tur_x_tur_test.c -o ./test_programi -lm && ./test_programi
```

Gerekenler: gcc, libm.

## Kaynak

Kaynak: [tur_x_tur_test.c](../../../../../TESTLER/HUNTER/06_TIPLER/tur_x_tur_test/tur_x_tur_test.c)

Arşivdeki satır sayısı: 154.
