//  ~~~ radio ~~~
//  settings
byte addresses[][6] = {"0pipe", "1pipe", "2pipe", "3pipe", "4pipe", "5pipe"};
struct rfOutputStructure
{
  byte pipeBegin = 149;
  int ambientLightnessValue = 0;
  int feederCounterFeedback = 0;
  int minTemperature = 0;
  int maxTemperature = 0;
  int currentTemperature = 0;
  int timeNextFeed = 0;
  bool fanFeedback = false;
  bool internalLightFeedback = false;
  bool airPmpFeedback = false;
  byte pipeEnd = 249;
};
typedef struct rfOutputStructure rfDataType;
rfDataType rfOutput;
//  timers
bool sendDataEnabled = true;
unsigned long sendDataInitializer = 0;

//  ~~~ eeprom ~~~
//  temperature storage
unsigned int m_minTemp;
unsigned int m_maxTemp;
//  feeder storage
unsigned int m_feederTimeRemaining;
int m_feederCounter;
//  timers
unsigned long recorderInititalTime;

//  ~~~ temperature ~~~
//  settings
byte sensorType;
byte sensorAdress[8];
//  sensor reading
unsigned int currentTemp;
unsigned int minTemp;
unsigned int maxTemp;
//  timers
bool readTimerEnabled = true;
unsigned long tempReadInitializer = 0;

//  ~~~ lighting ~~~
//  control
bool lightingCondition = false;
//  timers
bool turnOnOnline = false;
bool turnOffOnline = false;
unsigned long turnOnInitialTime = 0;
unsigned long turnOffInitialTime = 0;

//  ~~~ feeder ~~~
//  control
int feederCounter;
//  timers
bool feederTimerEnabled = true;
unsigned long feederInititalTime;

//  ~~~ fan ~~~
//  control
bool fanTimerEnabled = false;
//  timers
unsigned long fanInititalTime;

// → DEFINIÇAO DOS TEMPORIZADOS   ~~~~rever
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
