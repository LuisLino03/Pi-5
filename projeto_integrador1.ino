#include <LiquidCrystal.h>

float setUmidade = 50;
float umidade = 0;
bool teclaA, teclaB, teclaC, IM;
int menu = 0;


LiquidCrystal tela(A1, A2, A3, A4, A5, 2);

void setup(){
  pinMode(5, OUTPUT);
  pinMode(6, INPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
  tela.begin(16, 2);
}

void loop(){
  
  if(umidade < setUmidade){digitalWrite(5, HIGH);}else{digitalWrite(5, LOW);}
  
  //Menu inicial das opções
    tela.clear();
    tela.setCursor(0, 0);
    tela.print("(A)Enter (B)Next");
    tela.setCursor(0, 1);
  
  switch (menu) {
    case 0: tela.print("> Ver Umidade    "); break;
    case 1: tela.print("> Set Umidade    "); break;
    case 2: tela.print("> Irrigar Manual "); break;
  }
   
  while(!teclaA){
    //Verifica se a tecla B foi apertada e troca para a proxima opção do menu
    digitalWrite(12, HIGH);
    if(digitalRead(6)== HIGH){menu++;delay(250);if(menu > 2){menu =0;}}
    digitalWrite(12, LOW);
    
    //Atualiza as opsções no menu
    tela.setCursor(0, 1);
  	 switch (menu) {
      case 0: tela.print("> Ver Umidade    "); break;
      case 1: tela.print("> Set Umidade    "); break;
      case 2: tela.print("> Irrigar Manual "); break;
    }
     
    // Verifica se a tecla A foi apertada
    digitalWrite(13, HIGH);
    if(digitalRead(6)== HIGH){teclaA = true;}
    digitalWrite(13, LOW);
  }           
  
  tela.clear();
 
  	//Primeira opção do menu para vizualizar a umidade
  	while(teclaA && !teclaC && menu == 0){
   
      umidade = analogRead(A0)*0.11415525114155251141552511415525;
      tela.setCursor(0, 0);
  	  tela.print("(C)Back");
      tela.setCursor(0, 1);
      tela.print("Umidade:");
      tela.setCursor(8, 1);
      tela.print(umidade);
     
      digitalWrite(11, HIGH);
      if(digitalRead(6)== HIGH){teclaC = true; teclaA = false;}
      digitalWrite(11, LOW);
    }
   
  teclaC = false;
  
  //Segunda opção do menu para selelcionam em qual valor de umidade a irrigação será ativada
   while(teclaA && !teclaC && menu == 1){
   	  
      delay(150);
     
      tela.setCursor(0, 0);
  	  tela.print("(A)+(B)- (C)Back");
      tela.setCursor(0, 1);
      tela.print("Atual:");
      tela.setCursor(10, 1);
      tela.print(setUmidade);
     
      //Atualiza o valor da umidade setada
     
      //Aumentar o valor setado
      digitalWrite(13, HIGH);
      if(digitalRead(6)== HIGH && setUmidade<100){++setUmidade;delay(250);}
      digitalWrite(13, LOW);
      
      //diminui o valor setado
      digitalWrite(12, HIGH);
   	  if(digitalRead(6)== HIGH && setUmidade > 0){--setUmidade;delay(250);}
      digitalWrite(12, LOW);
     
     
      //Retorna para tela de menu inical
      digitalWrite(11, HIGH);
      if(digitalRead(6)== HIGH){teclaC = true; teclaA = false;}
      digitalWrite(11, LOW);
    }
  
  teclaC = false;
  
  //Terceira opção do menu para ligar a irrigação manualmente, independente do valor lido no sensor de umidade
  while(teclaA && !teclaC && menu == 2){
   
      delay(150);
      tela.setCursor(0, 0);
  	  tela.print("(A)Start (C)Back");
     
      //Ativa a opção para iniciar a irrigação manual
      digitalWrite(13, HIGH);
      if(digitalRead(6)== HIGH){IM = true; digitalWrite(5, HIGH);}
      digitalWrite(13, LOW);
    
      //Retorna para tela de menu inical
      digitalWrite(11, HIGH);
      if(digitalRead(6)== HIGH){teclaC = true; teclaA = false;}
      digitalWrite(11, LOW);
    
    
    if(IM){tela.clear();}
                                                         
    while(IM){
      tela.setCursor(0, 0);
  	  tela.print("(C)Back");
      tela.setCursor(0, 1);
      tela.print("Irrig ativa");
    
      digitalWrite(11, HIGH);
      if(digitalRead(6)== HIGH){IM = false; digitalWrite(5, LOW);tela.clear();}
      digitalWrite(11, LOW);
    }
  }
  
  teclaC = false;
}
