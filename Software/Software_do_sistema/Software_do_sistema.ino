

/*
 * =====================================================================================================
 * Projeto: Função de medir temperatura
 * Autores: Elismar Silva Pereira, Bruna Cavalcanti
 * Professor: Moacy
 * =====================================================================================================
 * 
 * 
 * Logs:
 * 
 *  Versão 0.1a (07 de abril de 2019):
 *    -Principais Funções adicionadas;
 *    -Leitura de sensores e mapeamento de hardware;
 *    -Suporte para sensor de presença, monitor real de tempoe leitura de temperatura;
 *  
 *  
 *  Versão 0.2a(14 de abril de 2019):
 *    -Adicionado prototipo para sensores magnéticos;
 *  
 *  Versão 0.3a (20 de abril de 2019):
 *    -Adicionado testes para monitoramento Serial (comunicação serial);
 *  
 */


//==================== Bibliotecas ====================
#include <DS1307.h> 


//====================  Hardware ======================
#define internal A0
#define external A1
#define sensorPIR 2
#define janela_1 7
#define janela_2 8


//=============== Funções auxiliares ==================
void temperaturaInterna();
void temperaturaExterna();
void presencaAmbiente();
void verificacaodeTempo();
void sensorMagnetico1();
void sensorMagnetico2();


//=================== Variáveis ========================
float temperaturaint = 0.00;
float temperaturaext = 0.00;
boolean presenca;
boolean janela1 = false;
boolean janela2 = false;

//Função para chamar o módulo RTC com o objeto "rtc"
DS1307 rtc(A4,A5);  //SDA/SDL



//Setup
void setup() {
  //Para comunicação SERIAL  
  Serial.begin(9600);

  //Setagem de pinos 
  pinMode(internal, INPUT);
  pinMode(external, INPUT);
  pinMode(sensorPIR, INPUT);
  pinMode(janela_1, INPUT);
  pinMode(janela_2, INPUT);

  //Módulo DS-1307

  rtc.halt(false); //Aciona o relogio 
  rtc.setDOW(MONDAY); //Dia da semana 
  rtc.setTime(10,20,0); //Horário
  rtc.setDate(16,04,2019); //Data

  rtc.setSQWRate(SQW_RATE_1); 
  rtc.enableSQW(true);
}


// Loop infinito
void loop() {
  temperaturaInterna();
  delay(1);
  temperaturaExterna();
  delay(1);
  presencaAmbiente();
  delay(1);
  verificacaodeTempo();
  delay(1);
  sensorMagnetico1();
  delay(1);
  sensorMagnetico2();
  delay(1000);
}



//Função para medir temperatura
void temperaturaInterna()
{
  temperaturaint = (float(analogRead(A0))*5/1023)/0.01;   //Calculo da temperatura
  Serial.print("Temperatura Interna: ");                  //Printo a temperatura interna
  Serial.print(temperaturaint);                           
  Serial.println(" C");
}


//Função para medir temperatura
void temperaturaExterna()
{
  temperaturaext = (float(analogRead(A1))*5/1023)/0.01;   //Calculo da temperatura
  Serial.print("Temperatura Externa: ");                  //Printo a temperatura interna
  Serial.print(temperaturaext);
  Serial.println(" C");
}


//Função para conferir se existe pessoas no local
void presencaAmbiente()
{
  
  presenca = digitalRead(sensorPIR);
  if(presenca == true)
  {
    Serial.println("Tem alunos na sala.");
  }
  else
  {
    Serial.println("Nao tem alunos na sala."); 
  }

}


//Função para verificar e printar o tempo
void verificacaodeTempo()
{
  
  //Informações no Monitor Serial
  Serial.print("Hora: ");
  Serial.print(rtc.getTimeStr());                       //Função para printar a hora
  Serial.print(" ");
  Serial.print("Data: ");
  Serial.print(rtc.getDateStr(FORMAT_SHORT));           //Função para printar a data
  Serial.print(" ");
  Serial.println(rtc.getDOWStr(FORMAT_SHORT));
  
}


//Funções para leitura dos sensores magnéticos

void sensorMagnetico1()
{
  if(digitalRead(janela_1) == true){
    Serial.println("A janela 1 esta aberta.");
  }
  else{
    Serial.println("A janela 1 esta fechada.");
  }

}


void sensorMagnetico2()
{
  if(digitalRead(janela_2) == true){
    Serial.println("A janela 2 esta aberta.");
  }
  else{
    Serial.println("A janela 2 esta fechada.");
  }
  Serial.println("\n\n");
}
