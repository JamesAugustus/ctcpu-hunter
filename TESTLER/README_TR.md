# Testler

[English](README.md)

Bu klasörde Nihai Form'daki iddialara dayanak olan testler var. Her test kendi klasöründe, kodu, Türkçe `TEST_TR.md` açıklaması ve İngilizce karşılığı `TEST.md` ile duruyor. Açıklamada testin neyi sınadığı, nasıl çalıştığı, neden önemli olduğu ve tek satırlık çalıştırma komutu yazılı.

Komutlar deponun kök klasöründen çalıştırılır. C testleri için GCC, Python testleri için Python 3 yeter.

Testleri 25 Ekim 2026'da yeniden çalıştırdım. Sonuçlar [Nihai Form'un Doğrulama bölümünde](../tr/md/NIHAI_FORM/CTCPU_NIHAI.md#14-doğrulama), her biri kendi testine bağlantıyla duruyor. Günlük iddialarındaki dört FAILS bir hata değil, o iddianın tutmadığını gösteren sonuçtur.

`HUNTER/` altındaki testler Hunter projesinin parçalarına göre ayrılmıştır. `NIHAI_EK/` altında Nihai Form için ayrıca yazılmış iki doğrulama programı var.
