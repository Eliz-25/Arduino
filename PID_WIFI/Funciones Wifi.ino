void WifiStart()
{
  delay(3000);
  Serial.println("Iniciando WIFI");
  TestAT();
  ActivationEcho(true);
  ActivationMode(1);
  //ListAvailableAP();
  ConnectToAP(Red, Password);
  ConnectionMode(1);
  GetLocalIP();
  StartConection(1, "UDP", LocalIP, PuertoServicio, PuertoTemporal); 
  Serial.println("Inicio Wifi finalizado");
}

void Respuesta()
{
  String almacenRX[10];
  int pos = 0;
  String Mensaje = "";

  while(wifi.available())
  {
    stringRX = wifi.readStringUntil('\n');  
    almacenRX[pos] = stringRX;
    pos++;    
    Serial.println(stringRX);
    if(almacenRX[1].startsWith("+IPD"))
    {
      int pos_comando = almacenRX[1].indexOf(':');
      if(pos_comando >= 0)
      {
        String mensajeMaestro = ""; 
        int pos_ini = 0;  
        int pos_fin = 0;                            
        String arrayComandos[5];
        int indiceString = 0;
        mensajeMaestro = almacenRX[1].substring(pos_comando+1);
        Serial.println(mensajeMaestro);

        while(indiceString <= 5)
        {  
          pos_fin = mensajeMaestro.indexOf('/', pos_ini);
          arrayComandos[indiceString] = mensajeMaestro.substring(pos_ini, pos_fin);
          pos_ini = pos_fin+1;             
          indiceString++;          
        }
        if(arrayComandos[0] == UNIDAD || arrayComandos[0] == BROADCAST)
        {
          if(arrayComandos[1] == "25")
          {
            Serial.println("comando 25");            
            String IPMaestro = arrayComandos[2];
            String PuertoMaestro = arrayComandos[3];              
            CloseConection(1);            
            StartConection(2, "UDP", IPMaestro, PuertoServicio, PuertoMaestro);
            Mensaje = UNIDAD+"/"+arrayComandos[1]+"/"+LocalIP+"/"+PuertoLocal;
            delay(2000);
            SendMessage(Mensaje, "2");
            ServerMode("1", PuertoLocal);                                            
          }
          if(arrayComandos[1] == "27")
          {
            
          }
          if(arrayComandos[1] == "28")
          {

          }
          if(arrayComandos[1] == "29")
          {
            
          }
          if(arrayComandos[1] == "30")
          {

          }
          if(arrayComandos[1] == "31")
          {

          }                         
        }        
      }
    } 
  }
}

bool Respuesta(String palabraClave)
{
  String cadenaRX = "";
  while(wifi.available())
  {
    char caracterRX = char(wifi.read());
    cadenaRX += String(caracterRX);
  }
  int posicion = cadenaRX.indexOf(palabraClave,0);
  if( posicion > 0 ) {return true;}
  else {return false;}    
}
String RespuestaIP()
{
  while(wifi.available())
  {
    stringIP = wifi.readString();
    //cadenaRX += stringRX;
  }
  String local_ip = "";
  int pos_ini = stringIP.indexOf('"',0);
  int pos_fin = stringIP.indexOf('"', pos_ini+1);
  LocalIP = stringIP.substring(pos_ini+1, pos_fin);
  return LocalIP;
}



