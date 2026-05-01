#include "i2c-lcd.h"

/* main.c dosyasında tanımlanan I2C birimine erişim */
extern I2C_HandleTypeDef hi2c1;

/* I2C Modül Adresi (Slave Address) */
/* NOT: Kullanılan modüle göre bu adres 0x27 veya 0x4E olabilir */
#define SLAVE_ADDRESS_LCD 0x4E

/* LCD'ye Komut Gönderme Fonksiyonu */
void lcd_send_cmd (char cmd)
{
  char data_u, data_l;
  uint8_t data_t[4];
  data_u = (cmd&0xf0);
  data_l = ((cmd<<4)&0xf0);
  data_t[0] = data_u|0x0C;  //en=1, rs=0
  data_t[1] = data_u|0x08;  //en=0, rs=0
  data_t[2] = data_l|0x0C;  //en=1, rs=0
  data_t[3] = data_l|0x08;  //en=0, rs=0
  HAL_I2C_Master_Transmit (&hi2c1, SLAVE_ADDRESS_LCD,(uint8_t *) data_t, 4, 100);
}

/* LCD'ye Veri Gönderme Fonksiyonu */
void lcd_send_data (char data)
{
  char data_u, data_l;
  uint8_t data_t[4];
  data_u = (data&0xf0);
  data_l = ((data<<4)&0xf0);
  data_t[0] = data_u|0x0D;  //en=1, rs=1
  data_t[1] = data_u|0x09;  //en=0, rs=1
  data_t[2] = data_l|0x0D;  //en=1, rs=1
  data_t[3] = data_l|0x09;  //en=0, rs=1
  HAL_I2C_Master_Transmit (&hi2c1, SLAVE_ADDRESS_LCD,(uint8_t *) data_t, 4, 100);
}

/* Ekran Temizleme Fonksiyonu */
void lcd_clear (void)
{
	lcd_send_cmd (0x80);
	for (int i=0; i<70; i++)
	{
		lcd_send_data (' ');
	}
}

/* İmleç Konumlandırma Fonksiyonu */
void lcd_put_cur(int row, int col)
{
    switch (row)
    {
        case 0:
            col |= 0x80;
            break;
        case 1:
            col |= 0xC0;
            break;
    }
    lcd_send_cmd (col);
}

/* LCD Başlatma (Initialization) Algoritması */
void lcd_init (void)
{
	// 4-bit Modu Başlatma Sırası
	HAL_Delay(50);
	lcd_send_cmd (0x30);
	HAL_Delay(5);
	lcd_send_cmd (0x30);
	HAL_Delay(1);
	lcd_send_cmd (0x30);
	HAL_Delay(10);
	lcd_send_cmd (0x20);
	HAL_Delay(10);

	// Ekran Konfigürasyonu
	lcd_send_cmd (0x28); // 4-bit modu, 2 satır, 5x8 font
	HAL_Delay(1);
	lcd_send_cmd (0x08); // Ekran Kapalı
	HAL_Delay(1);
	lcd_send_cmd (0x01); // Ekranı Temizle
	HAL_Delay(1);
	HAL_Delay(1);
	lcd_send_cmd (0x06); // İmleç artış modu
	HAL_Delay(1);
	lcd_send_cmd (0x0C); // Ekran Açık, İmleç Kapalı
}

/* String Yazdırma Fonksiyonu */
void lcd_send_string (char *str)
{
	while (*str) lcd_send_data (*str++);
}
