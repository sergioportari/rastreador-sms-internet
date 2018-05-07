#include <SoftwareSerial.h> //Incluimos a livraria SoftwareSerial
//#defina os pinos TX e RX utilizados com softserial
#define SIM800_TX D5
#define SIM800_RX D6
SoftwareSerial SIM800L(SIM800_TX,SIM800_RX);
int contador=0;
String Comando; //Declaramos uma variavel de tipo String para armazenar o texto do SMS recebido
int LED = LED_BUILTIN; //Definimos o led interno como led de testes. Pode ser colocado qualquer pino Dn (ex: D8)
 
void setup(){
Serial.begin(115200); //Iniciamos a comunicação serie

SIM800L.begin(9600); //Iniciamos una instância da livraria SoftwareSerial
SIM800L.println("AT+CFUN=1");
delay(1000);
SIM800L.println("AT+CMGF=1\r\n"); //Configuramos o módulo para trabalhar com os SMS em modo texto
delay(1000); //Pausa de 1 segundo
SIM800L.println("AT+CNMI=1,2,0,0,0"); //Configuramos o módulo para que nos mostre os SMS recebidos por comunicação serie
pinMode(LED, OUTPUT); //Definimos o pino onde esta ligado o LED como saida
}
 
void loop(){
if (SIM800L.available()){ //Se há dados disponiveis
Comando = SIM800L.readString(); //Armazenamo-los na variavel Comandos
Serial.println("NOVO SMS ENTRADA: " + Comando); //Obtemo-los por comunicação série
}
 
if(Comando.indexOf("On")>=0){ //Se a variável Comando contem a palavra ON
Serial.println("Acender o LED"); //Avisamos por comunicação serie
digitalWrite(LED, LOW); //Activamos o LED
Comando = ""; //Esvaziamos a variavel
//SIM800L.println("AT+CMGDA=1");
}
 
if(Comando.indexOf("Off")>=0){ //Se a variavel Comando contem a palavra OFF
Serial.println("Apagar o LED"); //Avisamos por comunicação serie
digitalWrite(LED, HIGH); //Desactivamos o LED
Comando = ""; //Esvaziamos a variavel
//SIM800L.println("AT+CMGDA=1");
}
if(Comando.indexOf("Esta online")>=0){ //Se a variavel Comando contem a palavra OFF
Serial.println("Retornar está online"); //Avisamos por comunicação serie
  SIM800L.write("AT+CMGS=\"+5534991089514\"\r\n");
  delay(1000);
   
  SIM800L.write("Estou ativo na rede celular");
  delay(1000);
   
  SIM800L.write((char)26);
  delay(1000);
     
  Serial.println("Feito");
Comando = ""; //Esvaziamos a variavel
//SIM800L.println("AT+CMGDA=1");
}
if(Comando.indexOf("Local")>=0){ //Se a variavel Comando contem a palavra Local
  {
    Comando="";
    SIM800L.println("AT+CMGDA=1 ");
    
    delay(500);  
    Serial.println("Retornar Localização"); 
     SIM800L.write("AT+CMGS=\"+5534991089514\"\r\n");
  delay(1000);
   
  SIM800L.write("Obter Localização do módulo GPS");
  delay(1000);
   
  SIM800L.write((char)26);
  delay(1000);


  //mandar para o MQTT
    SIM800L.println("AT+SAPBR=3,1,\"CONTYPE\",\"GPRS\""); //seta modo GPRS, deasabilitando sms e ligações
    delay(500);
    SIM800L.println("AT+SAPBR=3,1,\"APN\",\"algar.br\""); //setar APN CTBC, abaixo usuário e senha
    delay(500);
    SIM800L.println("AT+SAPBR=3,1,\"USER\",\"algar\"");
    delay(500);
    SIM800L.println("AT+SAPBR=3,1,\"PWD\",\"1212\"");
    delay(500);
    SIM800L.println("AT+SAPBR=1,1");
    delay(1000);
    SIM800L.println("AT+SAPBR=2,1");
    delay(2000);
    SIM800L.println("AT+HTTPINIT");
    delay(1000);
    SIM800L.println("AT+HTTPPARA=\"CID\",1");
    delay(1000);
    SIM800L.println("AT+HTTPPARA=\"URL\",\"http://www.portari.com.br/phpMQTT/exemplos/sim800l.php?posicaoatual=Obter_do_modulo_gps\"");
    delay(500);
    SIM800L.println("AT+HTTPACTION=0");
    delay(4500);
    SIM800L.println("AT+HTTPREAD");
    delay(1000);
    SIM800L.println("AT+HTTPTERM");
    delay(1000);
    SIM800L.println("AT+CFUN=0");
    delay(7000);
    SIM800L.println("AT+CFUN=1");
    delay(7000);
    
    SIM800L.println("AT+CMGF=1\r\n"); //Configuramos o módulo para trabalhar com os SMS em modo texto
    delay(1000); //Pausa de 1 segundo
    SIM800L.println("AT+CNMI=1,2,0,0,0"); //Configuramos o módulo para que nos mostre os SMS recebidos por comunicação serie
    delay(1000);
    
    Serial.println("Feito");
  }
}
 contador++;
 /*
 if(contador==1000000)
 {
  Serial.println("Resetando!");
  contador=0;
   SIM800L.println("AT+CFUN=0");
    delay(7000);
    SIM800L.println("AT+CFUN=1");
    delay(7000);
    
  } */
  
}
