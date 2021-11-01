/*==============================================================
   BIBLIOTECAS E DEFINIÇÕES
  =============================================================
*/

#include "RF24.h"

//byte addresses[][6] = {"pipe0","pipe1","pipe2","pipe3","pipe4","pipe5"};
byte addresses[][6] = {"0pipe","1pipe","2pipe","3pipe","4pipe","5pipe"};

RF24 radio (9, 10);

struct estrutura_envioRF
{
  byte inicio = 149;
  int iluminacao = 0;
  int contagem_alimentador = 0;
  int tempMin = 0;
  int tempMax = 0;
  int tempAtual = 0;
  int tempo_p_alimentar = 0;
  bool vent = false;
  bool ilum = false;
  bool circ = false;
  byte fim = 249;
};

typedef struct estrutura_envioRF tipoDadosRF;
tipoDadosRF envioRF;

void inicializar_radio() {
  radio.begin();
  radio.setPALevel(RF24_PA_MAX);
  radio.openWritingPipe(addresses[3]);
  //radio.setChannel(76);
}

void funcao_enviar_dados() {
  tempo_d_envio=millis();
  if (!radio.available()) {
    envioRF.iluminacao = map(analogRead(ldr), 0, 1000, 0, 100);
    envioRF.contagem_alimentador = contagem;
    envioRF.tempMin = temperaturaMin;
    envioRF.tempMax = temperaturaMax;
    envioRF.tempAtual = temperatura_atual;
    envioRF.tempo_p_alimentar = funcao_alimentador(1);
    envioRF.vent = digitalRead(rele_ventilacao);
    envioRF.ilum = !digitalRead(rele_luz_principal);
    envioRF.circ = !digitalRead(rele_circulacao);
    !radio.write(&envioRF, sizeof(envioRF));
  }
}
