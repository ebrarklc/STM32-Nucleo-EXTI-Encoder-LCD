#ifndef INC_I2C_LCD_H_
#define INC_I2C_LCD_H_

#include "stm32f0xx_hal.h"

/* Fonksiyon Prototipleri */
void lcd_init (void);         // LCD modülünü başlatma ve yapılandırma
void lcd_send_cmd (char cmd); // LCD'ye komut gönderme (Örn: Ekranı temizle)
void lcd_send_data (char data); // LCD'ye veri (karakter) gönderme
void lcd_send_string (char *str); // LCD'ye metin (string) yazdırma
void lcd_put_cur(int row, int col); // İmleci belirtilen satır ve sütuna konumlandırma
void lcd_clear (void);        // Ekranı temizleme fonksiyonu

#endif /* INC_I2C_LCD_H_ */
