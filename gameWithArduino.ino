
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 20, 4);
class protagonist {
  public:
    int x = 0, y = 0;
    byte body[8] = {
      B11100,
      B11100,
      B01000,
      B11111,
      B11000,
      B01100,
      B01010,
      B01010
    };

    // the ide of arduino look like shit
    void dmove(LiquidCrystal_I2C lcd ) {
      String input = Serial.readString();
      char m = input.charAt(0);
      Serial.print(" el tu estas en las coordenadas x,y ");
      Serial.println(x, y);
      switch (m) {
        case 'w':
          if (y > 0) {
            y--;
         
          }
          break;
        case 's':
          if (y < 4) {
            y++;

          }
          break;
        case 'd':
          if (x < 20) {
            x++;
        
          }
          break;
        case 'a':
          if (x > 0) {
            x--;
      
          }

          break;
        default:

          break;
      }
      lcd.setCursor(x, y);
      lcd.write(byte(body));

    }
};

class enemy {

  public:

    byte body[8] = {
      B11111,
      B11011,
      B01110,
      B11111,
      B11110,
      B01100,
      B00000,
      B00000
    };

    int x , y ;
    void set() {
      x = random(5, 19);
      y = random(4);
    }
    void mover( LiquidCrystal_I2C lcd, int xP, int yP) {
      int t = millis();
      if (t % 1500) {
        // move to a point
        if ( x < xP) {
          
          x++;
        }
        else if (x > xP) {
          x--;
        }
        else {
          if (y < yP) {
            y++;
          }
          else if (y > yP) {
            y--;
          }
        }
      }
      // move to a point
      lcd.setCursor(x, y);
      lcd.write(body);
    }
};
char m[] = "helloWorld";
int a = 0;
protagonist pro;
enemy ene;
void setup() {
  Serial.begin(9600);
  lcd.init();
  ene.set();
  lcd.backlight();

}
void loop() {
  int t = millis();
  pro.dmove(lcd);

  ene.mover(lcd, pro.x, pro.y);
  if (ene.x == pro.x && ene.y == pro.y) {
    Serial.println("haz perdido");
  }
  if ( t % 1000) {
    lcd.clear();
  }
}
