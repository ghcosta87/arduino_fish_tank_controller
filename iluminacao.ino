const int esta_claro = 18;//25;28
const int esta_escuro = 19; //20;27
const int tempo_lig_luz_p = 1;
const int tempo_desl_luz_p = 5;

bool condicao_do_dia = false;
bool desl_ativo = false;
bool lig_ativo = false;
long int espera_p_ligar = 0;
long int espera_p_desligar = 0;


bool funcao_iluminacao(int valor_ldr, int iluminacao, bool condicao_do_dia, int estado_luz_p, int requisicao) {  

  bool ligar_luz_p = !estado_luz_p;

  if (iluminacao > esta_claro)ligar_luz_p = ligar_luz(estado_luz_p, 0);
  if (iluminacao < esta_escuro)ligar_luz_p = desligar_luz(estado_luz_p, 0);

  if (iluminacao > esta_escuro && iluminacao < esta_claro) {
    lig_ativo = false;
    desl_ativo = false;
  }

  if (requisicao == 1)return ligar_luz_p;

  if (ligar_luz_p) {
    digitalWrite(rele_luz_principal, LOW);
    digitalWrite(rele_circulacao, LOW);
    led_noturno_fade(false, iluminacao);
  }

  if (!ligar_luz_p) {
    digitalWrite(rele_luz_principal, HIGH);
    digitalWrite(rele_circulacao, HIGH);
    led_noturno_fade(true, iluminacao);
  }

  //Serial.println((String)condicao_do_dia+"|"+(String)iluminacao+"|"+(String)espera_p_ligar+"|"+(String)((millis() - espera_p_ligar) / ms_p_m)+"|"+(String)espera_p_desligar+"|"+(String)((millis() - espera_p_desligar) / ms_p_m));
}

float desligar_luz(bool estado_luz_p, int requisicao) {

  float serial_t_off = ((millis() - espera_p_desligar) / ms_p_m);

  if (requisicao == 1)return serial_t_off;

  lig_ativo = false;

  if (!estado_luz_p) { //se a luz estiver ligada
    if (!desl_ativo) { //timer nao estiver rorando
      desl_ativo = true; //ativa o timer de desligar
      espera_p_desligar = millis(); // seta o timer
    } else {
      if (desl_ativo && ((millis() - espera_p_desligar) / ms_p_m > tempo_desl_luz_p)) {
        desl_ativo = false;
        return 0;
      } else {
        return !estado_luz_p;
      }
    }
  }
  return !estado_luz_p;
}

void led_noturno_fade(bool ativar, int iluminacao) {
  if (ativar) {
    int intensidade = map(iluminacao, 0, esta_escuro, 20, 255);
    if (intensidade > 255)intensidade = 255;
    analogWrite(led_noturno, intensidade);
  } else {
    digitalWrite(led_noturno, 0);
  }
}


float ligar_luz(bool estado_luz_p, int requisicao) {

  float serial_t_on = ((millis() - espera_p_ligar) / ms_p_m);

  if (requisicao == 1)return serial_t_on;

  desl_ativo = false;

  if (estado_luz_p) { //se a luz estiver desligado
    if (!lig_ativo) { //timer nao estiver rorando
      lig_ativo = true; //ativa o timer de desligar
      espera_p_ligar = millis(); // seta o timer
    } else {
      if (lig_ativo && ((millis() - espera_p_ligar) / ms_p_m > tempo_lig_luz_p)) {
        lig_ativo = false;
        return 1;
      } else {
        return !estado_luz_p;
      }
    }
  }
  return !estado_luz_p;
}
