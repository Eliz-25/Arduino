void TestAT()
{
  wifi.println("AT");
  delay(1500);
  Respuesta();
  /*if(Respuesta("OK")){ Serial.println("Test AT completo");}
  else {Serial.println("Fallo test AT");}*/
}
void ActivationEcho(bool echoOnOff)
{
  if(!echoOnOff){wifi.println("ATE0");}
  else{wifi.println("ATE1"); Serial.println("Echo activo");}
  delay(1500);
  Respuesta();  
  /*if(Respuesta("OK")){Serial.println("Establecimiento modo Echo satisfactorio");}
  else{Serial.println("Hubo un problema con el modo Echo");}*/
}
void ActivationMode(int mode)
{
  wifi.println("AT+CWMODE="+ String(mode));
  delay(1500);
  Respuesta();
  /*if(Respuesta("OK")){Serial.println("Modo de activacion exitoso");}
  else{Serial.println("Hubo un error con el modo de activacion");}*/  
}
void ListAvailableAP()
{
  wifi.println("AT+CWLAP");
  delay(10000);
  Respuesta();
  /*if(Respuesta(Red)){Serial.println("Red "+ String(Red) +" encontrada");}
  else{Serial.println("Red no encontrada");}*/
}
void ConnectToAP(String ssid, String pswrd)
{
  wifi.println("AT+CWJAP=\""+ssid+"\",\""+pswrd+"\"");
  delay(15000);
  Respuesta();
  /*if(Respuesta("OK")){Serial.println("Conexion a "+Red+" exitosa");}
  else{Serial.println("Ha fallado la conexion");}*/
}
void ConnectionMode(int modeMux)
{
  wifi.println("AT+CIPMUX="+String(modeMux));
  delay(1500);
  Respuesta();
  /*if(Respuesta("OK"))
  {
    if(modeMux == 1){Serial.println("Single connection establecido");} 
    if(modeMux == 2){Serial.println("Multiple conection establecido");}
  }
  else{Serial.println("Error modo de conexion");}*/
}
void GetLocalIP()
{
  wifi.println("AT+CIFSR");
  delay(1500);
  Serial.println(RespuestaIP());
  if(LocalIP == "0.0.0.0"){return "No fue posible obtener la IP local";}     
}
void StartConection(int connection, String type, String ip, String portService, String localPort)
{
  wifi.println("AT+CIPSTART="+String(connection)+",\""+type+"\",\""+ip+"\","+portService+","+localPort+"");
  delay(10000);
  Respuesta();  
  /*if(Respuesta("1,CONNECT")){Serial.println("Start Connection succes");}
  else{Serial.println("Fallo la conexion");}*/
}
void CloseConection(int connection)
{
  wifi.println("AT+CIPCLOSE="+String(connection));
  delay(1500);
  /*if(Respuesta("OK")){Serial.println("Conexion cerrada");}
  else{Serial.println("No pudo cerrarse la conexion");}  */
  Respuesta();            
}
void ReceivedMessage()
{
    if(stringRX.startsWith("192."))
    {
      Serial.println("ggg");
      if(Serial.find("168")){Serial.println("okis");}
    }  
}
void SendMessage(String message, String connection)
{
  int lengthDatos = message.length();
  wifi.println("AT+CIPSEND="+connection+","+lengthDatos);
  delay(50);
  Respuesta();
  delay(2000);    
  wifi.println(message);
  delay(2000);
  Respuesta();  
  /*if(Respuesta("OK"))
  {

  }
  else{Serial.println("No pudo enviarse el mensaje");}*/  
}
void ServerMode(String connection, String puerto)
{
  wifi.println("AT+CIPSERVER="+connection+","+puerto);
  delay(1000);
  /*if(Respuesta("OK")){Serial.println("Server Establecido");}
  else{Serial.println("Fallo el comando Server");}*/  
  Respuesta();
}