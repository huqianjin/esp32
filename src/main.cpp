#include <Wire.h>
#include <ADXL345.h>
 
ADXL345 accelerometer;
 
int RedPin = 4;
int GreenPin = 3;
int BluePin = 2;
 
long RedTime;
long GreenTime;
long BlueTime;
long DTTime;
 
void setup(void)
{
Serial.begin(115200);
 
pinMode(RedPin, OUTPUT);
pinMode(BluePin, OUTPUT);
pinMode(GreenPin, OUTPUT);
digitalWrite(RedPin, LOW);
digitalWrite(BluePin, LOW);
digitalWrite(GreenPin, LOW);
 
  // Inicjalizacja ADXL345
Serial.println("Inicjalizacja ADXL345");
  while (!accelerometer.begin())
  {
Serial.println("Nie odnaleziono ADXL345, sprawdz podlaczenie!");
delay(500);
  }
 Serial.println("ADXL345 OK");
  // Wartosci dla wykrycia swobodnego spadania
accelerometer.setFreeFallThreshold(0.35); // 0.35 g
accelerometer.setFreeFallDuration(0.1); // 0.10 s
 
  // Wartosci dla wykrycia aktywnosci i jego braku
accelerometer.setActivityThreshold(1.2); // 1.20 g
accelerometer.setInactivityThreshold(1.2); // 1.20 g
accelerometer.setTimeInactivity(5); // 5.00 s
 
  // Badanie aktywnosci i jego braku we wszystkich osiach
accelerometer.setActivityXYZ(1);
accelerometer.setInactivityXYZ(1);
 
  // Badanie stukniec tylko dla osi Z
accelerometer.setTapDetectionX(0); // Nie sprawdzamy osi X
accelerometer.setTapDetectionY(0); // Nie sprawdzamy osi Y
accelerometer.setTapDetectionZ(1); // Uwzgledniamy jedynie os Z
 
  // Wartosci dla wykrywania stukniec
accelerometer.setTapThreshold(2.5); // 2.50 g
accelerometer.setTapDuration(0.02); // 0.02 s
accelerometer.setDoubleTapLatency(0.10); // 0.10 s
accelerometer.setDoubleTapWindow(0.30); // 0.30 s
 
  // Wybieramy przerwanie INT1
accelerometer.useInterrupt(ADXL345_INT1);
}
 
void loop(void)
{
  long time = micros();
 
  // Gaszenie zapalonych diod po uplywie danego czasu od zapalenia
  if ((time - RedTime) > 300000) digitalWrite(RedPin, LOW);
  if ((time - BlueTime) > 300000) digitalWrite(BluePin, LOW);
 
  // Opoznienie przed odczytem (poprawia wyniki) i odczytanie pomiaru
delay(50);
 
Vector norm = accelerometer.readNormalize();
 
  // Odczytanie aktywnosci
Activites activ = accelerometer.readActivites();
 
  // Jesli wykryto swobodne spdanie - mrugaj dioda
  if (activ.isFreeFall)
  {
    for (int i = 0; i <= 4; i++)
    {
digitalWrite(RedPin, HIGH);
digitalWrite(BluePin, HIGH);
delay(100);
digitalWrite(RedPin, LOW);
digitalWrite(BluePin, LOW);
delay(100);
    }
 
delay(200);
 
    return;
  }
 
  // Jesli wykryto podwojne stykniecie zapal czerowna
  if (activ.isDoubleTap)
  {
digitalWrite(RedPin, HIGH);
RedTime = micros();
  } else
  if (activ.isTap) // Jesli pojedyncze stukniecie zapal niebieska
  {
digitalWrite(BluePin, HIGH);
BlueTime = micros();
  }
 
  // Jesli nieaktywny zapal zielona diode
  if (activ.isInactivity)
  {
digitalWrite(GreenPin, HIGH);
GreenTime = micros();
  }
 
  // Jesli aktywny zgas zielona diode
  if (activ.isActivity)
  {
digitalWrite(GreenPin, LOW);
  }
}