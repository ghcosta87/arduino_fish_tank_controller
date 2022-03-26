

void funcao_ler_botoes() {
  if (!digitalRead(botao_apaga_eeprom)) {
    delay(1000);
    limpar_eeprom();
  }

  if (!digitalRead(botao_abre_alimentador)) {
    Serial.println(F("################## Abrindo alimentador ################"));
    abrir_tampa();
  }

  if (!digitalRead(botao_alimentacao_manual)) {
    delay(1000);
    alimentar_agora();
    Serial.println(F("################## Alimentando manualmente ################"));
  }
}
