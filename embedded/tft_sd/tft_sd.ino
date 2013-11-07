/*
  SD card basic file example
 
 This example shows how to create and destroy an SD card file 	
 The circuit:
 * SD card attached to SPI bus as follows:
 ** MOSI - pin 11
 ** MISO - pin 12
 ** CLK - pin 13
 ** CS - pin 4
 
 created   Nov 204
 by David A. Mellis
 modified 9 Apr 2012
 by Tom Igoe
 
 This example code is in the public domain.
 	 
 */
 
#define cs   10
#define dc   9
#define rst  8  // you can also connect this to the Arduino reset

#include <SD.h>
#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library
#include <SPI.h>

Adafruit_ST7735 tft = Adafruit_ST7735(cs, dc, rst);

/** All the files */
static String files = "";

File root;

void setup()
{
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }


  Serial.print("Initializing SD card...");
  // On the Ethernet Shield, CS is pin 4. It's set as an output by default.
  // Note that even if it's not used as the CS pin, the hardware SS pin 
  // (4 on most Arduino boards, 53 on the Mega) must be left as an output 
  // or the SD library functions will not work. 
  pinMode(4, OUTPUT);

  if (!SD.begin(4)) {
    Serial.println("initialization failed!");
    return;
  }
  Serial.println("initialization done.");
  
  tft.initR(INITR_REDTAB);   // initialize a ST7735R chip, red tab

  root = SD.open("/");

  findFiles(root, 0);


  Serial.println(files);

  char buf[255];
    
  files.toCharArray(buf, 255);
  
  
  tft.fillScreen(ST7735_BLACK);
  
  testdrawtext(buf, ST7735_WHITE);
}

void loop()
{
  // nothing happens after setup finishes.
}

void findFiles(File dir, int numTabs) {

  // All files
  while(true) {

    File entry = dir.openNextFile();

    if (!entry) break; // no more files, move along

    for (uint8_t i = 0; i < numTabs; i++) {
      files += "  ";
    }

    files += entry.name();
    
    if (entry.isDirectory()) {
       files += "/"; 
    }

    files += "\n";

    // ... in each folder (depth first)
    if (entry.isDirectory()) {
      findFiles(entry, numTabs + 1);
    }

    entry.close();
  }
}

void testdrawtext(char *text, uint16_t color) {
  tft.setCursor(0, 0);
  tft.setTextColor(color);
  tft.setTextWrap(true);
  tft.print(text);
}



