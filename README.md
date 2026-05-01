# STM32 Nucleo EXTI ile Rotary Encoder ve I2C LCD Sistemi

Bu proje, gömülü sistemlerde asenkron sinyallerin işlemciyi meşgul eden "Sorgulama" (Polling) yöntemi yerine, donanımsal tetiklemeye dayalı **Harici Kesme (EXTI - External Interrupt)** mekanizması kullanılarak nasıl yakalanacağını göstermek amacıyla geliştirilmiştir[cite: 10].

Uygulamada bir elektromekanik giriş elemanı olan Rotary Encoder (Döner Kodlayıcı) kullanılarak; dönüş yönünün tespiti, adım sayma işlemleri ve bu verilerin I2C LCD ekran üzerinde anlık olarak görselleştirilmesi sağlanmıştır[cite: 10].

## 🚀 Öne Çıkan Özellikler (Highlights)

*   **Interrupt (Kesme) Tabanlı Okuma:** Rotary Encoder'dan gelen sinyaller, sadece değişim anında tetiklenen `EXTI` kesme yöntemiyle yakalanarak işlemci kaynakları (CPU Efficiency) optimize edilmiştir[cite: 10].
*   **Quadrature Decoding (Faz Farkı Analizi):** Encoder'ın ürettiği iki fazlı (A ve B) sinyaller arasındaki ilişki (`CLK` ve `DT` pinleri) `HAL_GPIO_EXTI_Callback` fonksiyonu içerisinde analiz edilerek dönüş yönü (CW/CCW) hatasız tespit edilmiştir[cite: 10].
*   **Dahili Direnç (Internal Pull-Up) Kullanımı:** Encoder modülünün kararlı çalışması ve sinyal gürültüsünün önlenmesi için STM32'nin Dahili `Pull-Up` dirençleri yazılımsal olarak aktif edilmiştir[cite: 10].
*   **Özel I2C LCD Sürücüsü:** Standart HAL kütüphanelerinde bulunmayan I2C LCD ekran kontrolü için, pin seviyesinde (`i2c-lcd.h` ve `i2c-lcd.c`) özel bir donanım soyutlama katmanı yazılarak ekran sürülmüştür[cite: 10].

## 🛠️ Donanım ve Pin Yapılandırması

Sistemdeki dış birimlerin STM32 Nucleo-F072RB üzerindeki pin atamaları ve yapılandırmaları aşağıdaki gibidir[cite: 10]:

| Bileşen | Pin Kodu | Kullanım Modu | Açıklama |
| :--- | :--- | :--- | :--- |
| **Encoder CLK** | `PA1` | GPIO_EXTI1 | Harici Kesme (Interrupt) Kaynağı (Düşen ve Yükselen Kenar - Rising/Falling)[cite: 10]. |
| **Encoder DT** | `PA4` | GPIO_Input (Pull-Up) | Dönüş Yönü (Data) Sinyali[cite: 10]. |
| **I2C SDA** | `PB7` | I2C1_SDA | LCD ekran veri iletişimi hattı[cite: 10]. |
| **I2C SCL** | `PB6` | I2C1_SCL | LCD ekran saat senkronizasyon hattı[cite: 10]. |

## 📂 Yazılım Mimarisi (Algoritma)

Sistem mimarisi, kesme yönetimine ve arka plan okumalarına dayanır[cite: 10].

1.  **Geri Çağırma (Callback) Mimarisi:** Encoder çevrildiğinde `PA1` pini bir kesme üretir[cite: 10]. İşlemci o anki işini durdurup otomatik olarak `HAL_GPIO_EXTI_Callback` fonksiyonuna dallanır[cite: 10].
2.  **Yön Tayini Algoritması:** Kesme anında `PA1` (CLK) ve `PA4` (DT) pinlerinin durumları karşılaştırılır[cite: 10]. Durumlar farklıysa Saat Yönünde (CW) dönülmüştür ve sayaç artırılır; aynıysa Saat Yönünün Tersine (CCW) dönülmüştür ve sayaç azaltılır[cite: 10].
3.  **Ana Döngü (Main Loop):** `while(1)` döngüsü içerisinde işlemci, kesme tarafından arka planda güncellenen `counter` değişkenini okuyarak LCD ekrana basar[cite: 10]. Bu yapı, ekranın anlık ve gecikmesiz olarak yenilenmesini sağlar[cite: 10].

## 💻 Nasıl Çalıştırılır?

1.  Projeyi `STM32CubeIDE` ile açın.
2.  Kodu derleyin (`Build`) ve STM32 Nucleo-F072RB kartına yükleyin[cite: 10].
3.  Sistem başlatıldığında LCD ekranda "Encoder Test" açılış mesajı görüntülenecektir[cite: 10].
4.  Breadboard üzerindeki Rotary Encoder modülünü sağa veya sola çevirerek; LCD ekrandaki pozisyon değerinin (`counter`) ve anlık dönüş yönünün ("Saga CW" / "Sola CCW") dinamik olarak nasıl güncellendiğini test edebilirsiniz[cite: 10].

    <img width="1536" height="1121" alt="dfhdfh" src="https://github.com/user-attachments/assets/a4308c69-2097-435a-a6e9-4f8f0e4f6f0a" />
