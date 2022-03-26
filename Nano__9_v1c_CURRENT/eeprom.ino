#include <EEPROM.h>

//  EEPROM
//  ============================================================
const float format_float = 0.00f;
int tempMin_eeprom = 99;
int tempMax_eeprom = 0;
int contagem_eeprom = 0;
int backup_tempo_alimentacao = 0;
int pos_mem1 = 0;
int pos_mem2 = 4;
int pos_mem3 = 8;
int pos_mem4 = 12;
int pos_mem5 = 16;

void inicializar_eeprom() {
  Serial.println(F("##################EEPROM INICIALIZADA################"));
  tempMin_eeprom = (int)(100 * (EEPROM.get(pos_mem1, format_float)));
  temperaturaMin = tempMin_eeprom;
  tempMax_eeprom = (int)(100 * (EEPROM.get(pos_mem2, format_float)));
  temperaturaMax = tempMax_eeprom;
  contagem_eeprom = (int)(100 * (EEPROM.get(pos_mem3, format_float)));
  contagem = contagem_eeprom;
  backup_tempo_alimentacao = (int)(100 * (EEPROM.get(pos_mem4, format_float)));
  tempo_gravado = backup_tempo_alimentacao;
  Serial.println("temp min: " + (String)temperaturaMin);
  Serial.println("temp max: " + (String)temperaturaMax);
  Serial.println("contagem: " + (String)contagem);
  Serial.println("t gravado: " + (String)tempo_gravado);
}

void funcao_gravar_dados() { 
  
  if (temperatura_atual < tempMin_eeprom)
  {
    temperaturaMin = temperatura_atual; //temperatura minima
    tempMin_eeprom=temperaturaMin;
    EEPROM.put(pos_mem1, ((float)temperaturaMin) / 100);    
  }
  if (temperatura_atual > tempMax_eeprom)
  {
    temperaturaMax = temperatura_atual; //temperatura maxima
    tempMax_eeprom=temperaturaMax;
    EEPROM.put(pos_mem2, ((float)temperaturaMax) / 100);    
  }

  //  if (temperatura < 0 || temperatura > 40) {
  //    alarme[4] = true;
  //  }

  contagem_eeprom = contagem;
  EEPROM.put(pos_mem3, ((float)contagem_eeprom) / 100);

  EEPROM.put(pos_mem4, backup_tempo_alimentacao);
}

void limpar_eeprom() {
  Serial.println(F("##################MEMORIA APAGADA################"));
  EEPROM.put(pos_mem1, 99.0);
  EEPROM.put(pos_mem2, 0.0);
  EEPROM.put(pos_mem3, 0.0);
  EEPROM.put(pos_mem4, 0.0);
  contagem = EEPROM.get(pos_mem3, format_float);

  inicializar_eeprom();
  temperatura_atual = ler_one_wire();
}
