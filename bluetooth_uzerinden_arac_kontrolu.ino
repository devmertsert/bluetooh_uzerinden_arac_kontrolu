#include<SoftwareSerial.h>

SoftwareSerial bt_iletisim(6, 7);
String readString;

int n1 = 9;
int n2 = 10;
int n3 = 11;
int n4 = 12;

int solMotorHiz = 5;
int sagMotorHiz = 3;

bool ileriMi = false;
bool geriMi = false;
bool solMu = false;
bool sagMi = false;

int hiz = 255;

void setup()
{
  bt_iletisim.begin(9600);

  pinMode(n1, OUTPUT);
  pinMode(n2, OUTPUT);
  pinMode(n3, OUTPUT);
  pinMode(n4, OUTPUT);
  pinMode(solMotorHiz, OUTPUT);
  pinMode(sagMotorHiz, OUTPUT);
  
}

void loop()
{
  while (bt_iletisim.available()) {
    delay(10);

    char c = bt_iletisim.read();
    if (c == ',') {
      break;
    }
    readString += c;
  }

  if (readString.length() >0) {
    
    if(readString == "ileri1") {
      ileriMi = true;
    }
    else if(readString == "ileri0") {
      ileriMi = false;
    }
    else if(readString == "sol1") {
      solMu = true;
    }
    else if(readString == "sol0") {
      solMu = false;
    }
    else if(readString == "sag1") {
      sagMi = true;
    }
    else if(readString == "sag0") {
      sagMi = false;
    }
    else if(readString == "geri1") {
      geriMi = true;
    }
    else if(readString == "geri0") {
      geriMi = false;
    }
    else if(readString == "hizlan") {
      if((hiz+50) <= 255) {
        hiz += 50;
      }
    }
    else if(readString == "yavasla") {
      if((hiz-50) >= 100) {
        hiz -= 50;
      }
    }
    else if(readString == "dur") {
      ileriMi = false;
      solMu = false;
      sagMi = false;
      geriMi = false;
    }

    if(ileriMi == true && solMu == false && sagMi == false && geriMi == false) {
      ileri();
    }
    else if(ileriMi == false && solMu == true && sagMi == false && geriMi == false) {
      sol();
    }
    else if(ileriMi == false && solMu == false && sagMi == true && geriMi == false) {
      sag();
    }
    else if(ileriMi == false && solMu == false && sagMi == false && geriMi == true) {
      geri();
    }
    else {
      dur();
    }

    analogWrite(solMotorHiz, hiz);
    analogWrite(sagMotorHiz, hiz);

    readString="";
  }
  
}

void ileri() {
  digitalWrite(n1, HIGH);
  digitalWrite(n2, LOW);
  digitalWrite(n3, HIGH);
  digitalWrite(n4, LOW);
}

void geri() {
  digitalWrite(n1, LOW);
  digitalWrite(n2, HIGH);
  digitalWrite(n3, LOW);
  digitalWrite(n4, HIGH);
}

void sag() {
  digitalWrite(n1, LOW);
  digitalWrite(n2, HIGH);
  digitalWrite(n3, HIGH);
  digitalWrite(n4, LOW);
}

void sol() {
  digitalWrite(n1, HIGH);
  digitalWrite(n2, LOW);
  digitalWrite(n3, LOW);
  digitalWrite(n4, HIGH);
}

void dur() {
  digitalWrite(n1, HIGH);
  digitalWrite(n2, HIGH);
  digitalWrite(n3, HIGH);
  digitalWrite(n4, HIGH);
}
