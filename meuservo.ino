/*==============================================================
   BIBLIOTECAS E DEFINIÇÕES
  =============================================================
*/

#include <Servo.h>

#define SERVO 3

Servo servo;

// >>>> bloco: controle da alimentação
const int tempo_gravar_intervalo_alimentacao = 20;
const int tempo_de_alimentacao = 6;
const int abertura = 180;
const int intervalo_d_abertura = 50;
const int tempo_d_a_f=700;
const int tampa_aberta=180;

void inicializar_servo() {
  servo.attach(SERVO);
  servo.write(0);
  tempo_inicial = millis();
}

int funcao_alimentador(int requicisao) {
  float tempo_ate_alimentar = tempo_de_alimentacao - ((millis() - tempo_inicial) / ms_p_h) - (((float)tempo_gravado) / 100);
  if (requicisao == 1)return (int)(tempo_ate_alimentar * 100);

  if ((((millis() - tempo_inicial) / ms_p_h) + (((float)tempo_gravado) / 100)) > tempo_de_alimentacao) {
    alimentar_agora();
  }
}

void gravar_hora() {
  if ((((millis() - tempo_inicial) / ms_p_h)) * 100 >= (float)tempo_gravar_intervalo_alimentacao / 100) {
    float timer = ((millis() - tempo_inicial) / ms_p_h) + (((float)tempo_gravado) / 100);
    backup_tempo_alimentacao = (int)(100 * timer);
  }
}

void abrir_tampa() {
  servo.write(tampa_aberta);
}

void alimentar_agora() {
  int a = abertura;
  servo.write(abertura);
  delay(tempo_d_a_f);
  servo.write(0);
  delay(tempo_d_a_f); 
  while (a > 0) {
    servo.write(a);
    delay(200);
    servo.write(0);
    delay(200);
    Serial.print(a);
    a=a-intervalo_d_abertura;
  }

  contagem++;
  tempo_gravado = 0;
  tempo_inicial = millis();
}
