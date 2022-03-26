// → BIBLIOTECAS
#include "temperatura.h"
#define versao "v1c"

// → DEFINIÇÕES DOS PINOS
const int rele_ventilacao = 2;
const int rele_circulacao = 3;
const int led_noturno = 5;
const int rele_luz_principal = 4;
const int ldr = A6;
const int botao_apaga_eeprom = A3;
const int botao_abre_alimentador = A4;
const int botao_alimentacao_manual = A5;

// → CONSTANTES DE CONVERSAO
const float ms_p_h = 3600000.00;
const float ms_p_m = 60000.00;


// → DEFINIÇAO DOS TEMPORIZADOS
long medir_temp = 0;
bool medir_hab = false;
const int tempo_leitura_temperatura = 1;

// → VARIAVEIS GLOBAIS
int temperatura_atual = 0;
int tempo_para_gravar = 0;

// → VARIAVEIS DO ALIMENTADOR
bool alimentar = false;
int contagem = 0;
int tempo_gravado = 0;
long int tempo_inicial = 0;

// → CONTROLE DE LEITURA DA TEMPERATURA
long int intervalo_de_leitura_inicial;
bool reiniciar_tempo_leitura = false;
int temperatura = 0;
int temperaturaMin = 0;
int temperaturaMax = 0;

// → CONTROLE DA VENTILACAO
bool contador_ativo = false;
long int tempo_de_espera = 0;
long int t0_ventilacao = 0;

/*==============================================================
   ÁREA DE TESTES
  =============================================================
*/
unsigned int voltas = 0;
long tempo_d_envio = 0;

int ledTest = A0;
int fade = 0;

void setup() {
  Serial.begin(9600);
  Serial.println(versao);
  Serial.println("25/02/2022");

  //  Configura a pinagem de entrada e saída
  //  ============================================================
  pinMode(rele_ventilacao, OUTPUT);
  pinMode(rele_circulacao, OUTPUT);
  pinMode(led_noturno, OUTPUT);
  pinMode(ledTest, OUTPUT);
  pinMode(rele_luz_principal, OUTPUT);
  pinMode(botao_apaga_eeprom, INPUT_PULLUP);
  pinMode(botao_abre_alimentador, INPUT_PULLUP);
  pinMode(botao_alimentacao_manual, INPUT_PULLUP);

  //  Configura o padrão das saídas
  //  ============================================================
  digitalWrite(rele_ventilacao, LOW);
  digitalWrite(rele_circulacao, LOW);
  digitalWrite(rele_luz_principal, LOW);
  digitalWrite(led_noturno, 0);

  inicializar_eeprom();

  inicializar_onewire();

  inicializar_servo();

  inicializar_radio();

  temperatura_atual = ler_one_wire();
}

void loop() {
  digitalWrite(ledTest, !digitalRead(ledTest));
  delay(200);

  funcao_iluminacao(analogRead(ldr), map(analogRead(ldr), 0, 1000, 0, 100), false, digitalRead(rele_luz_principal), 0);

  funcao_temporizada();

  funcao_alimentador(0);

  funcao_gravar_dados();

  funcao_ler_botoes();

  //Serial.println((String)(millis() - tempo_d_envio) + "|" + (String)millis() + "|" + (String)tempo_d_envio);
  if (millis() - tempo_d_envio > 2000)funcao_enviar_dados();

  funcao_ventilacao();

  gravar_hora();

  Serial.println((String)ler_one_wire());
}

void funcao_temporizada() {
  if (!medir_hab) {
    medir_temp = millis();
    medir_hab = true;
  }
  if (medir_hab && ((millis() - medir_temp) / ms_p_m) > tempo_leitura_temperatura) {
    temperatura_atual = ler_one_wire();
    medir_hab = false;
  }
}
