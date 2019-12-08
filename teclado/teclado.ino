//Librerias necesarias

#include<Keypad.h>
#include<EEPROM.h>

//Declaración de variables y constantes

int ledPresion = A1;
int ledClave = A0;
int buzzer = A2;
char tecla;
bool cambio = false;
char cambioClave[4] = { '*', '9', '9', '#' };
char claveDigitada[4];
int contadorDigitos = 0;
char claveGuardada[4];
bool cambioAutorizado;
bool IngresoAutorizado;

// Código necesario para matriz de teclado----
const byte filas = 4;
const byte columnas = 3;
byte pinsFilas[filas] = {8, 7, 6, 5};
byte pinsColumnas[columnas] = {4, 3, 2};

char teclas[filas][columnas] =
{
  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'},
  {'*', '0', '#'},
};

Keypad teclado = Keypad(makeKeymap(teclas), pinsFilas, pinsColumnas, filas, columnas);

//--------------------------------------------


void setup() {
  // put your setup code here, to run once:
  pinMode(ledPresion, OUTPUT);
  pinMode(ledClave, OUTPUT);
  pinMode(buzzer, OUTPUT);
  Serial.begin(9600);

  claveGuardada[ 0 ] = EEPROM.read( 0 );                // Asigna el primer digito de la clave
  claveGuardada[ 1 ] = EEPROM.read( 1 );                // Asigna el segundo digito de la clave
  claveGuardada[ 2 ] = EEPROM.read( 2 );                // Asigna el tercer digito de la clave
  claveGuardada[ 3 ] = EEPROM.read( 3 );
  
  /*Serial.print("claveGuardada: ");
  Serial.print(claveGuardada[0]);
  Serial.print(claveGuardada[1]);
  Serial.print(claveGuardada[2]);
  Serial.println(claveGuardada[3]);*/

}

void loop() {
  // put your main code here, to run repeatedly:
  tecla = teclado.getKey();
  if (tecla != NO_KEY) {
    //claveDigitada = claveDigitada + tecla;
    claveDigitada[contadorDigitos] = tecla;
    contadorDigitos = contadorDigitos + 1;
    if (contadorDigitos == 4) {
      contadorDigitos = 0;
      revisarClave();
    }
    else {
      presionTecla();
    }
  }


}

void presionTecla() {
  digitalWrite(ledPresion, HIGH);
  tone (buzzer, 30);
  delay(80);
  noTone (buzzer);
  digitalWrite(ledPresion, LOW);
}
void revisarClave() {
  if (cambio) {
    //Serial.println("Clave guardada ");
    EEPROM.write( 0, claveDigitada[ 0 ] );              // Almacena el primer digito de la clave maestra
    claveGuardada[0] = claveDigitada[ 0 ];
    EEPROM.write( 1, claveDigitada[ 1 ] );              // Almacena el segundo digito de la clave maestra
    claveGuardada[1] = claveDigitada[ 1 ];
    EEPROM.write( 2, claveDigitada[ 2 ] );              // Almacena el tercer digito de la clave maestra
    claveGuardada[2] = claveDigitada[ 2 ];
    EEPROM.write( 3, claveDigitada[ 3 ] );              // Almacena el cuarto digito de la clave maestra
    claveGuardada[3] = claveDigitada[ 3 ];
    EEPROM.write( 4, 0x55 );


    /*
      Serial.print("claveGuardada: ");
      Serial.print(EEPROM.read( 0 ));
      Serial.print(EEPROM.read( 1 ));
      Serial.print(EEPROM.read( 2 ));
      Serial.println(EEPROM.read( 3 ));

    */



    digitalWrite(ledClave, LOW);
    //guarda en eeprom
    cambio = false;
    return;
  }
  // comprueba clave
  cambioAutorizado = true;
  for ( int DigitNum = 0; DigitNum < 4; DigitNum++ )
  {
    if ( cambioClave[ DigitNum ] != claveDigitada[ DigitNum ] )
      cambioAutorizado = false;
  }
  if (cambioAutorizado) {
    cambioAutorizado = false;
    //cambiarclave();
    Serial.println("ingresar nueva clave: ");
    cambio = true;
    digitalWrite(ledClave, HIGH);
    //      claveDigitada = "";
    return;
  }
  IngresoAutorizado = true;
  for ( int DigitNum = 0; DigitNum < 4; DigitNum++ )
  {
    if ( claveGuardada[ DigitNum ] != claveDigitada[ DigitNum ] )
      IngresoAutorizado = false;
  }
  //obtener clave eeprom
  //    Serial.println("clave ingresada: "+ claveDigitada);

  //EEPROM.get(0,claveGuardada);
  //    Serial.println("clave guardada: " + claveGuardada);
  if (IngresoAutorizado) {
    digitalWrite(ledPresion, HIGH);
    //encender electroiman
    delay(3000);
    digitalWrite(ledPresion, LOW);
  }
  else {
    digitalWrite(ledClave, HIGH);
    tone (buzzer, 261);
    delay(1000);
    digitalWrite(ledClave, LOW);
    noTone(buzzer);
  }
  //claveDigitada = "";
  // si es igual abra, y sonido

}
