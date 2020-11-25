
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 20, 4);
unsigned long tiempoAnterior = 0;
class protagonist {
  public:
    char direct = "derecha";
    bool shoot = false;
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
      switch (m) {
        case 'w':
          if (y > 0) {
            y--;
            direct = "arriba";

          }
          break;
        case 's':
          if (y < 4) {
            y++;
            direct = "abajo";

          }
          break;
        case 'd':
          if (x < 20) {
            x++;
            direct = "derecha";


          }
          break;
        case 'a':
          if (x > 0) {
            x--;
            direct = "izquierda";

          }

          break;
        case 'x':
          shoot = true;
          break;
        default:

          break;
      }
      lcd.setCursor(x, y);
      lcd.write("y");
    }

};

class enemy {

  public:
    bool die = false;
    int x , y ;

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


    void set() {
      x = random(5, 19);
      y = random(4);

    }
    void mover( LiquidCrystal_I2C lcd, int xP, int yP, bool shoot, char direct) {


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
      if (shoot) {
        switch (direct) {
          case 'izquierda':
            die = y == yP;
            Serial.print(direct);
            Serial.print(xP, yP);
            Serial.println(x, y );

            break;
          case 'derecha':
            die = y == yP;
            Serial.print(direct);
            Serial.print(xP, yP);
            Serial.println(x, y );
            break;
          case 'abajo':
            die = x == xP;
            Serial.print(direct);
            Serial.print(xP, yP);
            Serial.println(x, y );
            break;
          case 'arriba':
            die = x == xP;
            Serial.print(direct);
            Serial.print(xP, yP);
            Serial.println(x, y );
            break;
          default:
            Serial.print(direct);
            Serial.print(xP, yP);
            Serial.println(x, y );
            break;
        }
      }
      // move to a point

      lcd.setCursor(x, y);
      lcd.print("e");

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
  Serial.println("welcome to this zombie game ");
  Serial.println("press 's' to start");
}
void loop() {

  String input = Serial.readString();
  char m = input.charAt(0);

  while (m == 's') {
    bool h = ene.x == pro.x && ene.y == pro.y;
    if (h) {
      lcd.clear();
      lcd.setCursor(10 - (sizeof("you lost") / 2), 2);
      lcd.print("you lost");
      delay(1000);
      lcd.clear();
      break;

    }
    else if (ene.die) {
      lcd.setCursor(10 - (sizeof("YOU WIN") / 2), 2);
      lcd.print("YOU WIN");
      delay(1000);
      lcd.clear();
      break;
    }
    else {
      pro.dmove(lcd);
      delay(500);
      ene.mover(lcd, pro.x, pro.y, pro.shoot, pro.direct);
      delay(1000);
      lcd.clear();
    }
  }
  ene.set();
  pro.x = 0, pro.y = 0;
  lcd.setCursor(20 - (sizeof("welcome to ZGame")), 0);
  lcd.print("welcome to ZGame");
  lcd.setCursor(20 - (sizeof("press s to start")), 1);
  lcd.print("press s to start");
}
