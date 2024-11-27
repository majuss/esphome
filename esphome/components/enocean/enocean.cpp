// problem is that mhz19 integration writes values to uart and getting stuff back. we need to listen 24/7
// a good integration to look at is the gps integration. gps integration does all uart in esphome nothing in library.
// maybe haier is better

#include "enocean.h"
#include "esphome/core/log.h"

#define ENOCEAN_HEADER 4
#define ENOCEAN_MAX_DATA 40

namespace esphome {
namespace enocean {

static const char *const TAG = "enocean";
static const uint8_t ENOCEAN_PACKET_LENGTH = 8;

void Enocean::setup() { ESP_LOGD(TAG, "setup called:"); }

void Enocean::update() {
  ESP_LOGD(TAG, "update called:");

  if (this->window_handle_ != nullptr)
    this->window_handle_->publish_state(this->window_state_);
}

void Enocean::loop() {
  ESP_LOGD(TAG, "Loop started:");
  ESP_LOGD(TAG, "foobar:");

  ESP_LOGD(TAG, this->available());

  while (this->available()) {
    // int const b{this->read()};
    uint8_t c;
    this->read_byte(&c);

    // if (b == 0x55) {
    //   do {
    //     yield();
    //   } while (this->available() < ENOCEAN_HEADER + 1);

    //   Packet packet;

    //   this->read_array(packet.getHeader(), ENOCEAN_HEADER);
    //   byte const CRC8H{this->read()};

    //   if (packet.checkHeaderCRC8(CRC8H)) {
    //     ESP_LOGD(TAG, "Header CRC8 is valid.");
    //   } else {
    //     ESP_LOGD(TAG, "Header CRC8 is invalid.");
    //     return;
    //   }
    //   byte waitCounter;
    //   byte available;
    //   do {
    //     yield();
    //     available = this->available();

    //   } while (available < packet.payloadLength + 1 || waitCounter++ > 50);

    //   if (packet.payloadLength + 1 <= available) {
    //     Serial.println("read data");

    //     this->read_array(packet.enocean_data, packet.dataLength);
    //     this->read_array(packet.enocean_optional, packet.optionalLength);
    //     byte const CRC8D = this->read();

    //     if (packet.checkDataCRC8(CRC8D)) {
    //       ESP_LOGD(TAG, "Data CRC8 is valid.");
    //     } else {
    //       ESP_LOGD(TAG, "Data CRC8 is invalid.");
    //       return;
    //     };
    //     packet.handleTelegram();
    //   }
    //   if (packet.getState() == "open") {
    //     this->window_state_ = true;
    //   } else if (packet.getState() == "closed") {
    //     this->window_state_ = false;
    //   }
    //   ESP_LOGD(TAG, "%s", packet.getState().c_str());
    //   // for (int i = 0; i < 4; i++)
    //   // {
    //   //     Serial.print("senderAddress[");
    //   //     Serial.print(i);
    //   //     Serial.print("]: ");
    //   //     Serial.println(packet.getSenderAddress()[i], HEX);
    //   // }

    // }  // magic byte 0x55
    // byte const b{this->read()};

    // if (b == 0x55)
    // {
    //     do
    //     {
    //         yield();
    //     } while (this->available() < ENOCEAN_HEADER + 1);

    //     Packet packet;
    //

    // Serial.println(packet.state);
    // for (int i = 0; i < 4; i++)
    // {
    //     Serial.print("senderAddress[");
    //     Serial.print(i);
    //     Serial.print("]: ");
    //     Serial.println(packet.senderAddress[i], HEX);
    // }

  }  // magic byte 0x55
}  // whileserial available
}  // namespace enocean
}  // namespace esphome

// void setup()
// {
//     Serial.begin(115200);
//     Serial.println("Setup starting");
//     Serial2.begin(57600, SERIAL_8N1, 16, 17);

// }

// void loop()
// {

//     while (Serial2.available())
//     {

//     } // while
// }