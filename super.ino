#include <LiquidCrystal_I2C.h> 
LiquidCrystal_I2C lcd (0x27, 16, 2);
const int fotoSensor = A2, voiceSensor = 2;
const int R_PIN = 9, G_PIN = 10, B_PIN = 11;
int lightsens, voice;
boolean heardsmthn;
 
const int xPin = A0, yPin = A1, butPin = 8;
int joyX, joyY, joySW;
int joyXs = 255, joyYs = 255, joySWs = 255;
int joyXi = 255, joyYi = 255, joySWi = 255;
 
int currentScreen = 0, x = 0;

/////////////////////////////////// H O R S E

byte chr[2][8][8] = {
  {
    {0x00, 0x00, 0x00, 0x00, 0x03, 0x07, 0x0E, 0x0E},
    {0x00, 0x00, 0x00, 0x00, 0x0F, 0x1F, 0x1F, 0x1F},
    {0x00, 0x00, 0x00, 0x03, 0x07, 0x1F, 0x1F, 0x1F},
    {0x00, 0x00, 0x05, 0x1F, 0x1D, 0x1F, 0x16, 0x06},
    {0x0C, 0x18, 0x10, 0x00, 0x01, 0x01, 0x01, 0x00},
    {0x1F, 0x1F, 0x1E, 0x17, 0x00, 0x00, 0x10, 0x00},
    {0x1F, 0x1F, 0x03, 0x02, 0x14, 0x04, 0x02, 0x00},
    {0x1C, 0x1C, 0x04, 0x04, 0x08, 0x00, 0x00, 0x00}
  },

  {
    {0x00, 0x00, 0x00, 0x07, 0x0F, 0x0E, 0x1C, 0x18},
    {0x00, 0x00, 0x00, 0x0F, 0x1F, 0x1F, 0x1F, 0x1F},
    {0x00, 0x00, 0x01, 0x03, 0x1F, 0x1F, 0x1F, 0x1F},
    {0x14, 0x1C, 0x1A, 0x1E, 0x1F, 0x13, 0x10, 0x10},
    {0x13, 0x13, 0x02, 0x02, 0x04, 0x00, 0x00, 0x00},
    {0x1F, 0x07, 0x0E, 0x06, 0x01, 0x00, 0x00, 0x00},
    {0x0F, 0x03, 0x03, 0x01, 0x01, 0x00, 0x00, 0x00},
    {0x10, 0x18, 0x0C, 0x02, 0x02, 0x11, 0x00, 0x00}
  }
};

/////////////////////////////////////
void setup() {
  Serial.begin(9600);
  pinMode(fotoSensor, INPUT);
  pinMode(voiceSensor, INPUT);
 
  pinMode(xPin, INPUT);
  pinMode(yPin, INPUT);
  pinMode(butPin, INPUT_PULLUP);
 
  pinMode(R_PIN, OUTPUT);
  pinMode(G_PIN, OUTPUT);
  pinMode(B_PIN, OUTPUT);
 
  lcd.begin(16,2);//lcd 
  lcd.init();
  lcd.backlight();
  lcd.clear(); 
  startScreen();
}
 
void loop() {
  joyX = analogRead(xPin);
  joyY = analogRead(yPin);
  joySW = digitalRead(butPin);

  if (currentScreen < 4){
  if (joyX > 700 && currentScreen < 3){currentScreen = currentScreen+1;delay(500);}
  if (joyX < 300 && currentScreen >= 0){currentScreen = currentScreen-1;delay(500);}}

  if (currentScreen < 4 || currentScreen == 8 || currentScreen == 9){setRGB(0, 0, 0);}
 
  //M E N U
  switch  (currentScreen){
      case 0:{
        
        lcd.clear();
        lcd.setCursor(6,0);
        lcd.print("MENU");
        lcd.setCursor(0,1);
        lcd.print("> SES SENSORU");}
        if (joySW == 0) {delay(500);currentScreen = 7;}
        break;
      case 1:{
        
        lcd.clear();
        lcd.setCursor(6,0);
        lcd.print("MENU");
        lcd.setCursor(0,1);
        lcd.print("> ISIK SENSORU");
        if (joySW == 0) {delay(500);currentScreen = 6;}
        break;}
      case 2:{
        
        lcd.clear();
        lcd.setCursor(6,0);
        lcd.print("MENU");
        lcd.setCursor(0,1);
        lcd.print("> RENK AYARLA");
        if (joySW == 0) {delay(500);currentScreen = 8;}
        break;}
      case 3:{
        
        lcd.clear();
        lcd.setCursor(6,0);
        lcd.print("MENU");
        lcd.setCursor(0,1);
        lcd.print("> SURPRIZ AT");
        if (joySW == 0) {delay(500);x=0;currentScreen = 14;}
        break;}
      case 6:{
        lcd.clear(); 
        lcd.setCursor(0,0);
        lcd.print("ISIK ALGILANIYOR");
        lcd.setCursor(6,1);
        lcd.print("....");
           lightsens = analogRead(fotoSensor); //FOTO SENSOR
            Serial.print("ISIK  :  ");
            Serial.println(lightsens);
            if (lightsens < 100) {
              setRGB(joyXi, joyYi, joySWi);
            }
            else{setRGB(0, 0, 0);}
            if (joySW == 0) {delay(500);currentScreen = 1;}
            break;
          }
       case 7:{
        lcd.clear(); 
        lcd.setCursor(1,0);
        lcd.print("SES DINLENIYOR");
        lcd.setCursor(6,1);
        lcd.print("....");
          voice = digitalRead(voiceSensor); //VOICE SENSOR
          Serial.println(voice);
          if(heardsmthn == true){
            setRGB(joyXs, joyYs, joySWs);
          }
          else {
            setRGB(0, 0, 0);   
          }
          if(voice == 1 && heardsmthn == false){
            heardsmthn = true;delay(1000);}
          else if(voice == 1 && heardsmthn == true){
            heardsmthn = false;delay(1000);}
          
          if (joySW == 0) {delay(500);currentScreen = 0;}break;
          }
        case 8:{
          lcd.clear(); 
          lcd.setCursor(0,0);
          lcd.print("SES SENSOR LED");
          lcd.setCursor(0,1);
          lcd.print("SECINIZ");
          if (joySW == 0) {delay(500);currentScreen = 10;lcd.clear(); }
          if (joyX > 700){currentScreen = 9;}}
          break;
        case 9:{
          lcd.clear(); 
          lcd.setCursor(0,0);
          lcd.print("ISIK SENSOR LED");
          lcd.setCursor(0,1);
          lcd.print("SECINIZ");
          if (joySW == 0) {delay(500);currentScreen = 11;lcd.clear(); }
          if (joyX < 300){currentScreen = 8;}}
          break;

        case 10:{
          
          lcd.clear(); 
          lcd.setCursor(0,0);
          lcd.print("SES SENSOR RENK");
          lcd.setCursor(2,1);
          lcd.print("AYARLANIYOR..");
          setRGB(joyX, joyY, joySW);
          if (joySW == 0) {joyXs = joyX, joyYs = joyY, joySWs = joySW;delay(500);currentScreen = 0;}break;
          }
        case 11:{
          lcd.clear(); 
          lcd.setCursor(0,0);
          lcd.print("ISIK SENSOR RENK");
          lcd.setCursor(2,1);
          lcd.print("AYARLANIYOR..");
          setRGB(joyX, joyY, joySW);
          if (joySW == 0) {joyXi = joyX, joyYi = joyY, joySWi = joySW;delay(500);currentScreen = 0;}break;
          } 
        case 14:{
          setRGB(255, 255, 255);
          if (x>16){x = -3;}
          if (joyX > 700){x++;}
          
          for (int f = 0; f < 2; f++) {
          lcd.clear();
          for (int i=0; i<8; i++) {
            lcd.createChar(i, chr[f][i]);
          }
          for (int c = 0; c < 4; c++) {
            int xc = x+c;
            if ((xc >= 0)&&(xc < 16)) {
              lcd.setCursor(x+c, 0); lcd.write(byte(c));
              lcd.setCursor(x+c, 1); lcd.write(byte(c+4));
            }
          }
          if (joySW == 0) {delay(500);x=0;currentScreen = 3;}
          delay(400);
        }
        
        break;}
        }
        if (currentScreen != 14){delay(300);}
}

void setRGB(int rLed, int gLed, int bLed) {
  analogWrite(R_PIN, rLed);
  analogWrite(G_PIN, gLed);
  analogWrite(B_PIN, bLed);
}
 
void startScreen() {
  lcd.setCursor(0,0);
  lcd.print("SLM CNM BHB");
  lcd.setCursor(0,1);
  lcd.print("BASLIYORUMM");
  for (int positionCounter = 0; positionCounter < 13; positionCounter++) {
    lcd.scrollDisplayRight();
    delay(400);
  }
  for (int positionCounter = 0; positionCounter < 28; positionCounter++) {
    lcd.scrollDisplayLeft();
    delay(400);
  }
  delay(100);
  lcd.clear();
}
