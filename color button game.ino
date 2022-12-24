#include<avr/wdt.h>
#include<Adafruit_NeoPixel.h>
#include<LiquidCrystal.h>

#define NUMLEDS 3
#define NUMCOLORS 8
#define DITEKAN LOW
#define DILEPAS HIGH

enum Pin{
    ledPin,
    tombol1=1, tombol2=7, tombol3=12, start=2,
    D7=A0,D6,D5,D4,En,RS
};
enum Color{hitam, biru, hijau, cyan, merah, magenta, kuning, putih};

void welcomeMessage();
int showQuestion();
void waitForAnswer();
void judgeAnswer(int);

Adafruit_NeoPixel leds(NUMLEDS, ledPin, NEO_GRB + NEO_KHZ800);
LiquidCrystal lcd(RS,En,D4,D5,D6,D7);
constexpr int timelimit = 1000;
unsigned long startTime;
uint32_t colors[]{
    leds.Color(0,0,0),
    leds.Color(0,0,255),
    leds.Color(0,255,0),
    leds.Color(0,255,255),
    leds.Color(255,0,0),
    leds.Color(255,0,255),
    leds.Color(255,255,0),
    leds.Color(255,255,255)
};
char colorNames[][8]{
    "Hitam", "Biru", "Hijau", "Cyan",
    "Merah", "Magenta", "Kuning", "Putih"
};
Pin buttons[]{tombol1, tombol2, tombol3, start};

void setup(){
    MCUSR &= ~(1<<WDRF); // Clear WDRF in MCUSR
    wdt_disable();
    delay(2000);
    
    for(Pin tombol : buttons) pinMode(tombol, INPUT_PULLUP);

    leds.begin();
    leds.setBrightness(255);
    lcd.begin(16,2);

    welcomeMessage();
    randomSeed(micros());

    wdt_enable(WDTO_8S);
}

void loop(){
    int jawaban = showQuestion();
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

bool sudahTerpakai(Color warnaRandom, Color terpakai[], int index){
    for(int i=0; i<index; i++) 
        if(warnaRandom == terpakai[i]) return true;
    return false;
}

void matikanLED(){
    for(int i=0; i<NUMLEDS; i++) leds.setPixelColor(i, colors[hitam]);
    leds.show();
}

bool waktuHabis(){
    return millis() - startTime > timelimit;
}

int showQuestion(){
    Color warnaBenar = (Color)random(NUMCOLORS);
    int ledYangBenar = random(NUMLEDS);

    Color warnaRandom;
    Color terpakai[NUMLEDS];
    for(int i=0; i<NUMLEDS; i++){
        if(i == ledYangBenar){
            leds.setPixelColor(i, colors[warnaBenar]);
            terpakai[i] = warnaBenar;
        }else{
            do warnaRandom = (Color)random(NUMCOLORS);
            while(warnaRandom == warnaBenar || sudahTerpakai(warnaRandom, terpakai, i));
            leds.setPixelColor(i, colors[warnaRandom]);
            terpakai[i] = warnaRandom;
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

void judgeAnswer(int jawaban){
    lcd.clear();

    static int skor = 0;
    if(digitalRead(buttons[jawaban]) == DITEKAN){
        wdt_reset();
        lcd.print("BETULL!!!");
        skor++;
        delay(1000);
    }else{
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