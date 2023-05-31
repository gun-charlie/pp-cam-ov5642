/*
  UTFT_SPI.h - Arduino library support for Color TFT LCD Boards
  This is special porting for ArduCAM shield LCD screen. 
  Use SPI bus interface and SSD1289 controller. Only work on 
  ArduCAM shield Rev.C.
  For more information about ArduCAM shield please visit
  www.arducam.com
  Copyright (C)2010-2014 Henning Karlsen. All right reserved
  
  This library is the continuation of my ITDB02_Graph, ITDB02_Graph16
  and RGB_GLCD libraries for Arduino and chipKit. As the number of 
  supported display modules and controllers started to increase I felt 
  it was time to make a single, universal library as it will be much 
  easier to maintain in the future.

  Basic functionality of this library was origianlly based on the 
  demo-code provided by ITead studio (for the ITDB02 modules) and 
  NKC Electronics (for the RGB GLCD module/shield).

  This library supports a number of 8bit, 16bit and serial graphic 
  displays, and will work with both Arduino and chipKit boards. For a 
  full list of tested display modules and controllers, see the 
  document UTFT_Supported_display_modules_&_controllers.pdf.

  When using 8bit and 16bit display modules there are some 
  requirements you must adhere to. These requirements can be found 
  in the document UTFT_Requirements.pdf.
  There are no special requirements when using serial displays.

  You can always find the latest version of the library at 
  http://electronics.henningkarlsen.com/

  If you make any modifications or improvements to the code, I would 
  appreciate that you share the code with me so that I might include 
  it in the next release. I can be contacted through 
  http://electronics.henningkarlsen.com/contact.php.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#define UTFT_SPI_h

#define UTFT_cbi(reg, bitmask) *reg &= ~bitmask
#define UTFT_sbi(reg, bitmask) *reg |= bitmask

#define cport(port, data) port &= data
#define sport(port, data) port |= data

#define swap(type, i, j) {type t = i; i = j; j = t;}

#define fontbyte(x) cfont.font[x]  

#define pgm_read_word(data) *data
#define pgm_read_byte(data) *data
#define bitmapdatatype unsigned short*

#define regtype volatile uint32_t
#define regsize uint32_t

#define LEFT 0
#define RIGHT 9999
#define CENTER 9998

#define PORTRAIT 0
#define LANDSCAPE 1

#define HX8347A         0
#define ILI9327         1
#define SSD1289         2
#define ILI9325C        3
#define ILI9325D_8      4
#define ILI9325D_16     5
#define HX8340B_8       6
#define HX8340B_S       7
#define HX8352A         8
#define ST7735          9
#define PCF8833         10
#define S1D19122        11
#define SSD1963_480     12
#define SSD1963_800     13
#define S6D1121_8       14
#define S6D1121_16      15
#define SSD1289LATCHED  16
//#define NOT_IN_USE    17
//#define NOT_IN_USE    18
#define SSD1289_8       19
#define SSD1963_800ALT  20
#define ILI9481         21
#define ILI9325D_16ALT  22
#define S6D0164         23
#define ST7735S         24
#define ILI9341_S5P     25
#define ILI9341_S4P     26
#define R61581          27
#define ILI9486         28
#define CPLD            29
#define HX8353C         30
#define ST7735_ALT      31

#define ITDB32          0   // HX8347-A (16bit)
#define ITDB32WC        1   // ILI9327  (16bit)
#define TFT01_32W       1   // ILI9327  (16bit)
#define ITDB32S         2   // SSD1289  (16bit)
#define TFT01_32        2   // SSD1289  (16bit)
#define CTE32           2   // SSD1289  (16bit)
#define ITDB24          3   // ILI9325C (8bit)
#define ITDB24D         4   // ILI9325D (8bit)
#define ITDB24DWOT      4   // ILI9325D (8bit)
#define ITDB28          4   // ILI9325D (8bit)
#define TFT01_24_8      4   // ILI9325D (8bit)
#define DMTFT24104      4   // ILI9325D (8bit)
#define DMTFT28103      4   // ILI9325D (8bit)
#define TFT01_24_16     5   // ILI9325D (16bit)
#define ITDB22          6   // HX8340-B (8bit)
#define ITDB22SP        7   // HX8340-B (Serial 4Pin)
#define ITDB32WD        8   // HX8352-A (16bit)
#define TFT01_32WD      8   // HX8352-A (16bit)
#define CTE32W          8   // HX8352-A (16bit)
#define ITDB18SP        9   // ST7735   (Serial 5Pin)
#define LPH9135         10  // PCF8833  (Serial 5Pin)
#define ITDB25H         11  // S1D19122 (16bit)
#define ITDB43          12  // SSD1963  (16bit) 480x272
#define TFT01_43        12  // SSD1963  (16bit) 480x272
#define ITDB50          13  // SSD1963  (16bit) 800x480
#define TFT01_50        13  // SSD1963  (16bit) 800x480
#define CTE50           13  // SSD1963  (16bit) 800x480
#define EHOUSE50        13  // SSD1963  (16bit) 800x480
#define ITDB24E_8       14  // S6D1121  (8bit)
#define TFT01_24R2      14  // S6D1121  (8bit)
#define ITDB24E_16      15  // S6D1121  (16bit)
#define INFINIT32       16  // SSD1289  (Latched 16bit) -- Legacy, will be removed later
#define ELEE32_REVA     16  // SSD1289  (Latched 16bit)
//#define NOT_IN_USE    17  
//#define NOT_IN_USE    18  
#define ELEE32_REVB     19  // SSD1289  (8bit)
#define TFT01_70        20  // SSD1963  (16bit) 800x480 Alternative Init
#define CTE70           20  // SSD1963  (16bit) 800x480 Alternative Init
#define EHOUSE70        20  // SSD1963  (16bit) 800x480 Alternative Init
#define CTE32HR         21  // ILI9481  (16bit)
#define CTE28           22  // ILI9325D (16bit) Alternative Init
#define TFT01_28        22  // ILI9325D (16bit) Alternative Init
#define CTE22           23  // S6D0164  (8bit)
#define TFT01_22        23  // S6D0164  (8bit)
#define DMTFT22102      23  // S6D0164  (8bit)
#define TFT01_18SP      24  // ST7735S  (Serial 5Pin)
#define TFT01_22SP      25  // ILI9341  (Serial 5Pin)
#define TFT01_24SP      25  // ILI9341  (Serial 5Pin)
#define TFT22SHLD       25  // ILI9341  (Serial 5Pin)
#define DMTFT28105      25  // ILI9341  (Serial 5Pin)
#define MI0283QT9       26  // ILI9341  (Serial 4Pin)
#define CTE35IPS        27  // R61581   (16bit)
#define CTE40           28  // ILI9486  (16bit)
#define EHOUSE50CPLD    29  // CPLD     (16bit)
#define CTE50CPLD       29  // CPLD     (16bit)
#define CTE70CPLD       29  // CPLD     (16bit)
#define DMTFT18101      30  // HX8353C  (Serial 5Pin)
#define TFT18SHLD       31  // ST7735   (Serial 5Pin) Alternative Init

#define SERIAL_4PIN     4
#define SERIAL_5PIN     5
#define LATCHED_16      17

#define NOTINUSE        255

//*********************************
// COLORS
//*********************************
// VGA color palette
#define VGA_BLACK       0x0000
#define VGA_WHITE       0xFFFF
#define VGA_RED         0xF800
#define VGA_GREEN       0x0400
#define VGA_BLUE        0x001F
#define VGA_SILVER      0xC618
#define VGA_GRAY        0x8410
#define VGA_MAROON      0x8000
#define VGA_YELLOW      0xFFE0
#define VGA_OLIVE       0x8400
#define VGA_LIME        0x07E0
#define VGA_AQUA        0x07FF
#define VGA_TEAL        0x0410
#define VGA_NAVY        0x0010
#define VGA_FUCHSIA     0xF81F
#define VGA_PURPLE      0x8010
#define VGA_TRANSPARENT 0xFFFFFFFF

#define BMPIMAGEOFFSET 66
    
struct _current_font
{
    uint8_t* font;
    uint8_t x_size;
    uint8_t y_size;
    uint8_t offset;
    uint8_t numchars;
};

class ArduLCD
{
    public:
        ArduLCD(PinName mosi, PinName miso, PinName sck, PinName cs);
        void    InitLCD(uint8_t orientation=LANDSCAPE);
        void    clrScr();
        void    drawPixel(int x, int y);
        void    drawLine(int x1, int y1, int x2, int y2);
        void    fillScr(uint8_t r, uint8_t g, uint8_t b);
        void    fillScr(uint16_t color);
        void    drawRect(int x1, int y1, int x2, int y2);
        void    drawRoundRect(int x1, int y1, int x2, int y2);
        void    fillRect(int x1, int y1, int x2, int y2);
        void    fillRoundRect(int x1, int y1, int x2, int y2);
        void    drawCircle(int x, int y, int radius);
        void    fillCircle(int x, int y, int radius);
        void    setColor(uint8_t r, uint8_t g, uint8_t b);
        void    setColor(uint16_t color);
        uint16_t    getColor();
        void    setBackColor(uint8_t r, uint8_t g, uint8_t b);
        void    setBackColor(uint32_t color);
        uint16_t    getBackColor();
/*        void    printNumI(long num, int x, int y, int length=0, char filler=' ');
        void    printNumF(double num, uint8_t dec, int x, int y, char divider='.', int length=0, char filler=' ');
        void    setFont(uint8_t* font);
        uint8_t* getFont();
        uint8_t getFontXsize();
        uint8_t getFontYsize();*/
        void    drawBitmap(int x, int y, int sx, int sy, bitmapdatatype data, int scale=1);
        void    drawBitmap(int x, int y, int sx, int sy, bitmapdatatype data, int deg, int rox, int roy);
        int     getDisplayXSize();
        int     getDisplayYSize();
        
        //***********not  use*****************
        void    lcdOff();
        void    lcdOn();
        void    setContrast(char c);
        void    setBrightness(uint8_t br);
        void    setDisplayPage(uint8_t page);
        void    setWritePage(uint8_t page);
        //***********************************
        
        int bus_write(int address, int value);
        uint8_t bus_read(int address);
        
        //void dispBitmap(File inFile);

/*
    The functions and variables below should not normally be used.
    They have been left publicly available for use in add-on libraries
*/
        uint8_t            fch, fcl, bch, bcl;
        uint8_t            orient;
        uint8_t            model;
        long            disp_x_size, disp_y_size;
        uint8_t            display_model, display_transfer_mode, display_serial_mode;
        regtype         *P_RS, *P_WR, *P_CS, *P_RST, *P_SDA, *P_SCL, *P_ALE;
        regsize         B_RS, B_WR, B_CS, B_RST, B_SDA, B_SCL, B_ALE;
        uint8_t            __p1, __p2, __p3, __p4, __p5;
        _current_font   cfont;
        bool         _transparent;

        void LCD_Writ_Bus(char VH,char VL);
        void LCD_Write_COM(char VL);
        void LCD_Write_DATA(char VH,char VL);
        void LCD_Write_COM_DATA(char com1,int dat1);
        void setPixel(uint16_t color);
        void drawHLine(int x, int y, int l);
        void drawVLine(int x, int y, int l);
//        void printChar(uint8_t c, int x, int y);
        void setXY(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);
        void clrXY();
        void resetXY();
//        void rotateChar(uint8_t c, int x, int y, int pos, int deg);
        void _set_direction_registers(uint8_t mode);
        void _fast_fill_16(int ch, int cl, long pix);
        void _fast_fill_8(int ch, long pix);
        void _convert_float(char *buf, double num, int width, uint8_t prec);
        
    protected:
        SPI spi;                // does SPI MOSI, MISO and SCK        
        DigitalOut _cs;         // does SPI CE
};

