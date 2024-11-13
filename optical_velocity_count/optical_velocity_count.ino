/* Programa que cuenta los pulsos y las revoluciones del encoder
foto eléctrico HC-020K con un Arduino MEGA O UNO.
*//// Variables ////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//
int encoder_pin = 2; // Pin 2, donde se conecta el encoder
unsigned int N; // [RPM] Revoluciones por minuto calculadas.
volatile byte n; // [pulses]Número de pulsos leídos por el Arduino
unsigned long timeold; // Tiempo almacenado
unsigned int S = 20; // Número de muescas que tiene el disco del encoder.
const int wheel_diameter = 64; // Diámetro de la rueda pequeña[mm]
float velocity = 0; // Velocity // Velocidad en [Km/h]
/////////////////////////// Función que cuenta los pulsos del encoder ///////////////////////////////////////////////////////
void counter(){
n++; // Incrementa los impulsos
}
//// Configuración del Arduino //////////////////////////////////////////////////////////
//////////////////////////////////////////
void setup(){
Serial.begin(9600); // Configuración del puerto serie
pinMode(encoder_pin, INPUT); // Configuración del pin nº2
attachInterrupt(0, counter, FALLING); // Configuración de la interrupción 0, donde esta conectado el encoder HC-020K. FALLING = la interrupción actua cuando la señal del pin cae : pasa de HIGH a LOW.
// Inicialización de los parametros
n = 0;
N = 0;
timeold = 0;
Serial.println("");
Serial.print(" Wheel ");Serial.print("Wheel ");Serial.println("Wheel");
Serial.print(" Seconds ");Serial.print("RPM ");Serial.print("Pulses "); Serial.println("Velocity [Km/h]");
}
//// Programa principal ////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////
void loop(){
if (millis() - timeold >= 1000){ // Se actualiza cada segundo, [t] es el tiempo de muestreo igual a 1000 milisegundos, 1 segundo.
detachInterrupt(0); // Desconectamos la interrupción para que no actué en esta parte del programa.
N = ( n * 60 ) / (( millis() - timeold )/ 1000 * S ); // N= n x 60 / (t x S) Calculamos las revoluciones por minuto [RPM]. El valor 1000 es para pasar los milisegundos a segundos 
velocity = N * 3.1416 * wheel_diameter * 60 / 1000000; // Cálculo de la velocidad en [Km/h]
Serial.print(" ");
Serial.print(millis()/1000);Serial.print(" ");
Serial.print(N,DEC);Serial.print(" ");
Serial.print(n,DEC);Serial.print(" ");
Serial.println(velocity,2);
n = 0; // Inicializamos los pulsos.
timeold = millis(); // Almacenamos el tiempo actual.
attachInterrupt(0, counter, FALLING); // Reiniciamos la interrupción
} }
//// Final del programa principal ////
