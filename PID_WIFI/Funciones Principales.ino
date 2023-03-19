/*
      Pestaña que contiene las funciones principales del programa,
      muestreo de volumen en el Tinaco, cálculo de PID y de control del movimiento de la servo válvula.  
*/
//=====================================================================================================//
//    FUNCION SETUP
//=====================================================================================================//
void Inicializacion(){
  Serial.begin(9600);
  wifi.begin(9600);
  
  pinMode(4, OUTPUT);     // IN1
  pinMode(5, OUTPUT);     // IN2
  pinMode(6, OUTPUT);    // IN3
  pinMode(7, OUTPUT);    // IN4
  
  pinMode(6, INPUT);  //Ec
  pinMode(7, OUTPUT); //Trig
  PantallaPrincipal();
  WifiStart();
 
}

//=====================================================================================================//
//    FUNCIONES LOOP
//=====================================================================================================//
void Comunicacion()
{
  if(Serial.available()) 
  {
    wifi.write(Serial.read());
  }
  if (wifi.available())
  {
    Respuesta();
  }
}
void muestreo(){ 
  unsigned long tiempoTranscurrido = millis();
  static unsigned long tiempoAnterior;
//CADA 100ms TOMA MUESTRA  
  if (tiempoTranscurrido - tiempoAnterior >= 100){ 
    tomaMuestra = true;

    //Primera muestra
    if (tomaMuestra == true && numeroMuestra == 1){
      float Distancia1 = CalculaDistancia();
      vol1 = CalculaVolumen(Distancia1);
      numeroMuestra = 2;
      tomaMuestra = false;
    }
    //Segunda muestra    
      if (tomaMuestra == true && numeroMuestra ==2){
      float Distancia2 = CalculaDistancia();
      vol2 = CalculaVolumen(Distancia2);

      volumen1 = volumen3;
      volumen3 = vol2;
      volumen2 = vol1;
      vol3=volumen3;      
      //Serial.println(String(volumen3));    
      
      //Calcula PID cada 200ms
      error1 = sPoint - volumen1;
      error2 = sPoint - volumen2;
      error3 = sPoint - volumen3;
      P = kp * error3;
      I = (ki * tiempoMuestreo * (error1 + 2*(error2) + error3))/2;
      D = kd * ((error1 - error3) / tiempoMuestreo);
      PID = P + I + D;
      if (PID <0){PID = 0;}
      if (PID >4500){PID = 4500;}
      
      numeroMuestra = 1;
      tomaMuestra = false;
    }
    
    tiempoAnterior = tiempoTranscurrido;
  }
}
void MovValvula(){
  float grados = map(PID,0,4500,0,360);       
  float pasos = grados * 1.4583333333;
  while (pasos>numero_pasos)
  { 
    izquierda();  
    numero_pasos = numero_pasos + 1;
  }
  while (pasos<numero_pasos)
  { 
    derecha();  
    numero_pasos = numero_pasos -1;
  }
  apagado();
}