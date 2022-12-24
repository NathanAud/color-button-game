#include<avr/wdt.h>
#include<Adafruit_NeoPixel.h>
#include<LiquidCrystal.h>

#define NUMLEDS 3
#define NUMCOLORS 8
#define DITEKAN LOW
#define DILEPAS HIGH

enum Pin : uint8_t{
    ledPin,
    tombol1=1, tombol2=7, tombol3=12, start=2,
    D7=A0,D6,D5,D4,En,RS
};
enum Color : uint8_t{hitam, biru, hijau, cyan, merah, magenta, kuning, putih};

Adafruit_NeoPixel leds(NUMLEDS, ledPin, NEO_GRB + NEO_KHZ800);
LiquidCrystal lcd(RS,En,D4,D5,D6,D7);
constexpr int timelimit = 1000;
unsigned long startTime;
const uint32_t colors[]{
    leds.Color(0,0,0),
    leds.Color(0,0,255),
    leds.Color(0,255,0),
    leds.Color(0,255,255),
    leds.Color(255,0,0),
    leds.Color(255,0,255),
    leds.Color(255,255,0),
    leds.Color(255,255,255)
};
constexpr char colorNames[][8]{
    "Hitam", "Biru", "Hijau", "Cyan",
    "Merah", "Magenta", "Kuning", "Putih"
};
constexpr Pin buttons[]{tombol1, tombol2, tombol3, start};

void setup(){
    MCUSR &= ~(1<<WDRF); // Clear WDRF in MCUSR
    wdt_disable();
    delay(2000);
    
    for(Pin tombol : buttons) 
      pinMode(tombol, INPUT_PULLUP);

    leds.begin();
    leds.setBrightness(255);
    lcd.begin(16,2);

    welcomeMessage();
    randomSeed(micros());

    wdt_enable(WDTO_8S);
}

void loop(){
    uint8_t jawaban = showQuestion();
    waitForAnswer();
    judgeAnswer(jawaban);
}

void welcomeMessage(){
    lcd.clear();
    lcd.print("Selamat Datang");
    delay(2000);

    lcd.clear();
    lcd.print("Tekan tombol");
    lcd.setCursor(0,1);
    lcd.print("lampu yang benar");
    delay(2000);
    
    lcd.clear();
    lcd.print("Tekan tombol");
    lcd.setCursor(0,1);
    lcd.print("start u/ mulai");
    while(digitalRead(start) == DILEPAS);
    
    lcd.clear();
    lcd.print("Game Dimulai");
    delay(2000);
}

void matikanLED(){
    for(uint8_t i=0; i<NUMLEDS; i++) leds.setPixelColor(i, colors[hitam]);
    leds.show();
}

bool waktuHabis(){
    return millis() - startTime > timelimit;
}

uint8_t showQuestion(){
    const Color warnaBenar = (Color)random(NUMCOLORS);
    const uint8_t ledYangBenar = random(NUMLEDS);

    Color warnaRandom;
    bool sudahTerpakai[NUMLEDS]{false};
    for(uint8_t i=0; i<NUMLEDS; i++){
        if(i == ledYangBenar){
            leds.setPixelColor(i, colors[warnaBenar]);
            sudahTerpakai[warnaBenar] = true;
        }
        else{
            do warnaRandom = (Color)random(NUMCOLORS);
            while(warnaRandom == warnaBenar || sudahTerpakai[warnaRandom]);
            leds.setPixelColor(i, colors[warnaRandom]);
            sudahTerpakai[warnaRandom] = true;
        }
    }
    leds.show();
    lcd.clear();
    lcd.print(colorNames[warnaBenar]);

    return ledYangBenar;
}

void waitForAnswer(){
    wdt_reset();
    startTime = millis();
    while(
        digitalRead(tombol1) == DILEPAS &&
        digitalRead(tombol2) == DILEPAS &&
        digitalRead(tombol3) == DILEPAS &&
        !waktuHabis()
    );
}

void judgeAnswer(uint8_t jawaban){
    lcd.clear();

    static int skor = 0;
    if(digitalRead(buttons[jawaban]) == DITEKAN){
        wdt_reset();
        lcd.print("BETULL!!!");
        ++skor;
        delay(1000);
    }
    else{
        if(waktuHabis()) lcd.print("WAKTU HABIS!!!");
        else lcd.print("SALAH!!!");
        delay(2000);

        lcd.clear();
        lcd.print("Game Over");
        lcd.setCursor(0,1);
        lcd.print("Skor: "); lcd.print(skor);
        matikanLED();
        while(1);
    }
}