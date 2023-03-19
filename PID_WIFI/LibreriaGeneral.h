#include <SoftwareSerial.h>
SoftwareSerial wifi(4,5);//RX, TX

String UNIDAD = "100";
String BROADCAST = "255";

//String Red ="INFINITUM08EF_2.4";
//String Password = "ForaneosDelTec";
String Red ="ARRIS-4E02";
String Password = "CF02CDD69FDF77D9";
String LocalIP = "";
String cadenaRX = "";
String stringRX ="";
String stringIP="";
String cadenaIP = "";

String PuertoTemporal = "9000";
String PuertoServicio = "9000";
String PuertoLocal = "9010";

int sPoint = 900, error1 = 0, error2 = 0, error3 = 0;
double PID, tiempoMuestreo = 0.1,  P = 0, I = 0, D = 0;
double kp = 5.4555555,  ki = 0.5, kd = 0.1;
bool tomaMuestra = false; 
int numeroMuestra = 1;

double vol1 = 0, vol2 = 0, vol3 = 0, volumen1 = 0, volumen2 = 0, volumen3 = 0;
int Distancia1, Distancia2, Distancia3;
long alturaTinaco = 30, radioTinaco = 126.156478;
int retardo = 4, numero_pasos = 0;   // Valor en grados donde se encuentra el motor

#include <TFT.h>

#define cs 10
#define dc 9
#define rst 8

TFT TFTpantalla = TFT(cs, dc, rst);
double puntoYVol = 0;
double puntoYSP = 0;
/*int x[140]; 
int y[140]; */

int x =30;
