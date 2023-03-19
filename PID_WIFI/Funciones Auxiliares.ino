/*
      Pestaña que contiene las funciones auxiliares del programa, funciones como la de cálculo de la distancia con 
      el sensor ultrasónico, cálculo de volumen del contenido del Tinaco y las funciones para el movimiento del 
      motor.
*/
//=====================================================================================================//
//    FUNCIONES PARA CÁLCULO DE DISANCIA Y VOLUMEN
//=====================================================================================================//

int CalculaDistancia(){
  digitalWrite(3, HIGH);  
  delayMicroseconds(10);
  digitalWrite(3, LOW);
  int tiempo = pulseIn(2, HIGH);
  int Distancia = (tiempo/59)-5;
  return (Distancia);
}
float CalculaVolumen(int distancia){
  float Vol;
  if(distancia > 30 || distancia < 0)
  {
    Vol = 0;
  }
  else if(distancia<30 && distancia>0)
  {
    Vol=(PI*(radioTinaco*radioTinaco)*(alturaTinaco-distancia))/1000;
  }
  return (Vol);
}

//=====================================================================================================//
//    FUNCIONES PARA MOVIMIENTO DE MOTOR
//=====================================================================================================//

void derecha(){
  digitalWrite(7, LOW);
  digitalWrite(6, LOW);
  digitalWrite(5, HIGH);
  digitalWrite(4, HIGH);
  delay(retardo);
  digitalWrite(7, LOW);
  digitalWrite(6, HIGH);
  digitalWrite(5, HIGH);
  digitalWrite(4, LOW);
  delay(retardo);
  digitalWrite(7, HIGH);
  digitalWrite(6, HIGH);
  digitalWrite(5, LOW);
  digitalWrite(4, LOW);
  delay(retardo);
  digitalWrite(7, HIGH);
  digitalWrite(6, LOW);
  digitalWrite(5, LOW);
  digitalWrite(4, HIGH);
  delay(retardo);
}
void izquierda() {
  digitalWrite(7, HIGH);
  digitalWrite(6, HIGH);
  digitalWrite(5, LOW);
  digitalWrite(4, LOW);
  delay(retardo);
  digitalWrite(7, LOW);
  digitalWrite(6, HIGH);
  digitalWrite(5, HIGH);
  digitalWrite(4, LOW);
  delay(retardo);
  digitalWrite(7, LOW);
  digitalWrite(6, LOW);
  digitalWrite(5, HIGH);
  digitalWrite(4, HIGH);
  delay(retardo);
  digitalWrite(7, HIGH);
  digitalWrite(6, LOW);
  digitalWrite(5, LOW);
  digitalWrite(4, HIGH);
  delay(retardo);
}        
void apagado() {
  digitalWrite(7, LOW); 
  digitalWrite(6, LOW);  
  digitalWrite(5, LOW);  
  digitalWrite(4, LOW);  
 }

//=====================================================================================================//
//    FUNCIONES PARA PANTALLA TFT
//=====================================================================================================//

void PantallaPrincipal(){
  TFTpantalla.begin();  
  TFTpantalla.setRotation (1);
  TFTpantalla.background(255,255,255);
  TFTpantalla.stroke(ST7735_WHITE);  
  TFTpantalla.setTextSize(1);
  TFTpantalla.fillRoundRect(15, 2, 126, 12,2, ST7735_MAGENTA);
  TFTpantalla.text(" PID", 60, 5);
  TFTpantalla.fillRect(28, 20, 2, 80, ST7735_BLACK);
  TFTpantalla.fillRect(26, 100, 120, 2, ST7735_BLACK);
  TFTpantalla.fillRect(25, 20, 4, 2, ST7735_BLACK);
  TFTpantalla.fillRect(25, 36, 4, 2, ST7735_BLACK);
  TFTpantalla.fillRect(25, 52, 4, 2, ST7735_BLACK);
  TFTpantalla.fillRect(25, 68, 4, 2, ST7735_BLACK);
  TFTpantalla.fillRect(25, 84, 4, 2, ST7735_BLACK);
  TFTpantalla.stroke(ST7735_MAGENTA);
  TFTpantalla.text("1500", 1, 17);
  TFTpantalla.text("1200", 1, 33);
  TFTpantalla.text("900", 6, 49);
  TFTpantalla.text("600", 6, 65);
  TFTpantalla.text("300", 6, 81);
  TFTpantalla.text("0", 18, 97);
  //TFTpantalla.fillRoundRect(25, 105, 120, 20,4, ST7735_BLACK);
  TFTpantalla.fillRect(30,20, 120,79, ST7735_YELLOW);
}
void Graficando(){
  static unsigned long   tiempoA;
  unsigned long tiempo = millis();
  if (tiempo - tiempoA >100)
  {
    puntoYSP = map(sPoint,0, 1500, 100, 20);
    TFTpantalla.fillRect(30, puntoYSP, 120, 2, ST7735_RED);

    puntoYVol = map(volumen3, 0, 1500, 100, 20);
    //x[140] = puntoYVol;  //asigna el valor escalado a el ultimo dato de la matriz
    TFTpantalla.drawPixel(x++, puntoYVol, ST7735_MAGENTA);
    if(x>120){
      TFTpantalla.fillRect(30,20, 120,79, ST7735_YELLOW);
      x=30;
    }   
    tiempoA = tiempo;
  }

}