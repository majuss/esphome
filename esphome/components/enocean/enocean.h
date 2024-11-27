#pragma once

#include "esphome/core/component.h"
#include "esphome/core/automation.h"
#include "esphome/components/binary_sensor/binary_sensor.h"
#include "esphome/components/uart/uart.h"
#include <enocean.h>

namespace esphome {
namespace enocean {



class Enocean : public PollingComponent, public uart::UARTDevice {
 public:
  float get_setup_priority() const override { return setup_priority::HARDWARE; }

  void setup() override;
  void update() override;
  // void dump_config() override;

  void loop() override;


  void set_sensor(binary_sensor::BinarySensor *window_handle) { window_handle_ = window_handle;}
  
  // void set_temperature_sensor(sensor::Sensor *temperature_sensor) { temperature_sensor_ = temperature_sensor; }
  // void set_co2_sensor(sensor::Sensor *co2_sensor) { co2_sensor_ = co2_sensor; }
  // void set_abc_enabled(bool abc_enabled) { abc_boot_logic_ = abc_enabled ? MHZ19_ABC_ENABLED : MHZ19_ABC_DISABLED; }

 protected:
  bool window_state_ = false;

  binary_sensor::BinarySensor *window_handle_{nullptr};
  Packet packet;
  // sensor::Sensor *temperature_sensor_{nullptr};
  // sensor::Sensor *co2_sensor_{nullptr};
  // MHZ19ABCLogic abc_boot_logic_{MHZ19_ABC_NONE};
};

// template<typename... Ts> class MHZ19CalibrateZeroAction : public Action<Ts...> {
//  public:
//   MHZ19CalibrateZeroAction(MHZ19Component *mhz19) : mhz19_(mhz19) {}

//   void play(Ts... x) override { this->mhz19_->calibrate_zero(); }

//  protected:
//   MHZ19Component *mhz19_;
// };

// template<typename... Ts> class MHZ19ABCEnableAction : public Action<Ts...> {
//  public:
//   MHZ19ABCEnableAction(MHZ19Component *mhz19) : mhz19_(mhz19) {}

//   void play(Ts... x) override { this->mhz19_->abc_enable(); }

//  protected:
//   MHZ19Component *mhz19_;
// };

// template<typename... Ts> class MHZ19ABCDisableAction : public Action<Ts...> {
//  public:
//   MHZ19ABCDisableAction(MHZ19Component *mhz19) : mhz19_(mhz19) {}

//   void play(Ts... x) override { this->mhz19_->abc_disable(); }

//  protected:
//   MHZ19Component *mhz19_;
// };

}  // namespace mhz19
}  // namespace esphome
