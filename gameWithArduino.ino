//YWROBOT

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
            lcd.clear();
          }
          break;
        case 's':
          if (y < 4) {
            y++;
            lcd.clear();
          }
          break;
        case 'd':
          if (x < 20) {
            x++;
            lcd.clear();
          }
          break;
        case 'a':
          if (x > 0) {
            x--;
            lcd.clear();
          }

          break;
        default:

          break;
      }
      lcd.setCursor(x, y);
      lcd.write(body);

    }
};

class enemy {
  private:
    char m[4] = "asdw";
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
    int x = 0, y = 0;

    void mover( LiquidCrystal_I2C lcd) {
      int t = millis();

      if ( t %  642) {

        movements(random(sizeof(m)));
      }

      lcd.setCursor(x, y);
      lcd.write(body);
    }

    void movements(char m) {
      switch (m) {
        case 'w':
          y--;
          lcd.clear();
          break;
        case 's':
          y++;
          lcd.clear();
          break;
        case 'd':
          x++;
          lcd.clear();
          break;
        case 'a':
          x--;
          lcd.clear();

          break;
        default:
          break;
      }
    }


};
char m[] = "helloWorld";
int a = 0;
protagonist pro;
enemy ene[2];
void setup() {
  Serial.begin(9600);
  lcd.init();
  lcd.home();
  lcd.backlight();

}
void loop() {
  int t = millis();
  pro.dmove(lcd);
  for (int i = 0; i < 2; i++) {
    ene[i].mover(lcd);
    if(ene[i].x==pro.x&&ene[i].y==pro.y){
    Serial.println("haz perdido");  
    }
  }
  /*
  here is the enemy
  */
 
  if ( t % 1000) {
    lcd.clear();
  }
}
