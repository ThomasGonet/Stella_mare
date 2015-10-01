
#include <SoftwareSerial.h>

#define LORA_RX 3
#define LORA_TX 2

int nbLoop = 0;

SoftwareSerial loraSS = SoftwareSerial(LORA_TX, LORA_RX);

// -----------------------------------------------------------------------------
// Fonction de communication basique (send msg, receive response)
void sendCmd(char *string, char *resp) {
  //char tmp[500]; int i = 0;
  loraSS.println(string);
  delay(300);
  readFromModem(resp);
  }

// -----------------------------------------------------------------------------
// Required for radio com
void launchTransceiverMode(char *tmp) {
  sendCmd("mac pause", tmp);
  // tmp != 0 ok
  }
  
// -----------------------------------------------------------------------------
// Get the device version (sys get ver)
void getDeviceVersion(char *tmp) {
  sendCmd("sys get ver",tmp);
  }

// -----------------------------------------------------------------------------
// <channelId> : decimal number representing the fequency.
// Response: decimal number representing the frequency, from 
// 863000000 to 870000000 or from 433050000 to 434790000, in Hz, depending on
// the frequency band selected
long getFreq(int freq) {
  char temp[100]; char cmd[50];
  sprintf(cmd, "radio get freq");
  sendCmd(cmd, temp);
  return atol( temp );
  }

void readFromModem(char *tmp) {
  //char tmp[500]; 
  memset(tmp, '\0', 100*sizeof(char));
  int i=0;
  //delay(100);
  while (loraSS.available()) {
    tmp[i] = loraSS.read();
    //if (tmp[i] == 0x0A) break;
    i++;
    delay(100);
  }
} 
  
// -----------------------------------------------------------------------------
void DeviceTEST(char* msg) {
  char temp[100];
  char msgId[270];
  memset(msgId, '\0', 270*sizeof(char));
  sprintf(msgId, "%s%d", msg, nbLoop);
  sendLoRa(msgId, temp);
  }

void sendLoRa(char *msg, char *tmp) {
  char trame[270]; char endTx[100];
  memset(trame, '\0', 270*sizeof(char));
  sprintf(trame, "radio tx %s", msg);
  Serial.println(trame);
  sendCmd(trame, tmp);
  // interprete result (à faire)
  Serial.println(tmp);
  delay(3000);
  readFromModem(endTx);
  Serial.println(endTx);
  }


//-------------------------------------------------------------------------------
// Main program
//-------------------------------------------------------------------------------

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  loraSS.begin(57600);
  Serial.println("Initialisation");
  char temp[100];
  
  delay(1000);
  getDeviceVersion(temp);
  Serial.println(temp);
  launchTransceiverMode(temp);
  Serial.println(temp);
  //delay(1000);
  
  }

void loop() {
  delay(2000);
  Serial.println("Test");
  
  char msg[270];
  memset(msg, '\0', 270*sizeof(char));
  sprintf(msg, "aaaa");
  
  DeviceTEST(msg);
  
  nbLoop++;
  }
  
