
#include <ESP8266WiFi.h>
#include "oui.h"

extern "C" {
  #include "user_interface.h"
}

byte channel;
byte t = 0;
String alfa = "1234567890qwertyuiopasdfghjkklzxcvbnm QWERTYUIOPASDFGHJKLZXCVBNM_";

uint8_t packet[128] = {

 /* ---- control frame */
 /* 0000 */   0x40, 0x00, 0x00, 0x00,               /* type/subtype: probe request */
 /* 0004 */   0xff, 0xff, 0xff, 0xff, 0xff, 0xff,   /* receiver address: broadcast */
 /* 000a */   0x12, 0x34, 0x56, 0x78, 0x9a, 0xbc,   /* transmitter address: STA */
 /* 0010 */   0xff, 0xff, 0xff, 0xff, 0xff, 0xff,   /* bss id: broadcast */
 /* 0016 */   0x40, 0x01,                           /* sequence/fragment number */

 /* ---- management frame ---- */
 /* 0018 */   0x00,                                 /* tag number: 0 (SSID parameter set) */
 /* 0019 */   0x08,                                 /* tag length: 8 */
 /* 001a */   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* SSID: */

 /* 0022 */   0x01,                                 /* tag number: 1 (Supported Rates) */
 /* 0023 */   0x04,                                 /* tag length: 4 */
 /* 0024 */   0x02, 0x04, 0x0b, 0x16,

 /* 0028 */   0x32,                                 /* tag number: 50 (Extended supported rates) */
 /* 0029 */   0x08,                                 /* tag length: 8 */
 /* 002a */   0x0c, 0x12, 0x18, 0x24, 0x30, 0x48, 0x60, 0x6c,

 /* 0032 */   0x03,                                 /* tag number: 3 (Current channel) */
 /* 0033 */   0x01,                                 /* tag length: 1 */
 /* 0034 */   0x09,                                 /* channel: 9 */

 /* 0035 */   0x2d,                                 /* tag number: 45 (HT Capabilities) */
 /* 0036 */   0x1a,                                 /* tag length: 26 */
 /* 0037 */   0x20, 0x00, 0x1a, 0xff, 0x00, 0x00, 0x00, 0x00,
 /* 003f */   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
 /* 0047 */   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
 /* 004f */   0x00, 0x00,

 /* 0051 */   0x7f,                                 /* tag number: 127 (Extended Capabilities) */
 /* 0052 */   0x04,                                 /* tag length: 4 */
 /* 0053 */   0x00, 0x00, 0x08, 0x04

};

void setup() {
  delay(500);
  pinMode(LED_BUILTIN, OUTPUT);
  wifi_set_opmode(STATION_MODE);
  wifi_promiscuous_enable(1);
}

void loop() {
  // randomize channel
  channel = random(1,12);
  wifi_set_channel(channel);

  // randomize SRC MAC
  int idx = random(sizeof(oui)/3);
  packet[10] = oui[idx][0];
  packet[11] = oui[idx][1];
  packet[12] = oui[idx][2];
  packet[13] = random(256);
  packet[14] = random(256);
  packet[15] = random(256);

  // randomize SSID
  packet[26] = alfa[random(65)];
  packet[27] = alfa[random(65)];
  packet[28] = alfa[random(65)];
  packet[29] = alfa[random(65)];
  packet[30] = alfa[random(65)];
  packet[31] = alfa[random(65)];
  packet[32] = alfa[random(65)];
  packet[33] = alfa[random(65)];

  // set channel accordingly
  packet[53] = channel;

  // send raw packet
  wifi_send_pkt_freedom(packet, 87, 0);
  wifi_send_pkt_freedom(packet, 87, 0);
  wifi_send_pkt_freedom(packet, 87, 0);
  delay(1);

  // do some blinking
  digitalWrite(LED_BUILTIN, t++ & 0x80);
}
