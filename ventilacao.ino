const int high_setpoint = 2900;
const int low_setpoint = 2700;
const int tempo_espera_ventilacao = 5;

void funcao_ventilacao() {
  if (temperatura_atual >= high_setpoint) {
    if (!contador_ativo) {
      t0_ventilacao = millis();
      contador_ativo = true;
      digitalWrite(rele_ventilacao, HIGH);
    }
  }
  if (contador_ativo) {
    if (((millis() - t0_ventilacao) / ms_p_m) > tempo_espera_ventilacao) {
      if (temperatura_atual <= low_setpoint) {
        digitalWrite(rele_ventilacao, LOW);
        contador_ativo = false;
      }
    }
  }
}
