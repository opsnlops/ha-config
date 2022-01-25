/*!
 *  @file LC709203F.h
 *
 * 	I2C Driver for the  LC709203F LiPo Cell Monitor
 *
 *	BSD license (see license.txt)
 */

#ifndef _LC709203F_H
#define _LC709203F_H


#include "esphome/core/component.h"
#include "esphome/components/sensor/sensor.h"
#include "esphome/components/i2c/i2c.h"

namespace esphome {
namespace lc709203f {

#define LC709203F_I2C_ADDR              0x0B    // LC709203F default i2c address

// Registers per datasheet Table 6

#define LC709203F_WO_BEFORE_RSOC      0x04    // Executes RSOC initialization with sampled maximum voltage when 0xAA55 is set
#define LC709203F_RW_THERMISTORB      0x06    // Sets B−constant of the thermistor to be measured.
#define LC709203F_WO_INITRSOC 	      0x07    // Executes RSOC initialization when 0xAA55 is set.
#define LC709203F_RW_CELLTEMPERATURE  0x08    // Read or Write Cell Temperature  For ESP32-Bar-Rev2 must write temperature, no thermistor on board
#define LC709203F_RO_CELLVOLTAGE      0x09    // Read cell voltage
#define LC709203F_RW_CURRENTDIRECTION 0x0A    // Selects Auto/Charge/Discharge mode 0x0000: Auto mode, 0x0001: Charge mode, 0xFFFF: Discharge mode
#define LC709203F_RW_APA 	      0x0B    // APA Register, Table 7
#define LC709203F_RW_APTHERMISTOR     0x0C    // Sets a value to adjust temperature measurement delay timing. Defaults to0x001E
#define LC709203F_RW_RSOC             0x0D    // Read cell indicator to empty in 1% steps
#define LC709203F_RO_ITE     	      0x0F    // Read cell indicator to empty in 0.1% steps
#define LC709203F_RO_ICVERSION 	      0x11    // Contains the ID number of the IC
#define LC709203F_RW_PROFILE	      0x12    // Adjusts the battery profile for nominal and fully charged voltages, see Table 8
#define LC709203F_RW_ALARMRSOC 	      0x13    // Alarm on percent threshold
#define LC709203F_RW_ALARMVOLT 	      0x14    // Alarm on voltage threshold
#define LC709203F_RW_POWERMODE 	      0x15    // Sets sleep/power mode 0x0001: Operational mode 0x0002: Sleep mode
#define LC709203F_RW_STATUSBIT 	      0x16    // Temperature method, 0x0000: I2C mode, 0x0001: Thermistor mode 
#define LC709203F_RO_CELLPROFILE      0x1A    // Displays battery profile code

// to remove warning static uint8_t crc8(uint8_t *data, int len);

/*!  Approx cell capacity Table 7 */
typedef enum {
  LC709203F_APA_100MAH              = 0x08,
  LC709203F_APA_200MAH              = 0x0B,
  LC709203F_APA_500MAH              = 0x10,
  LC709203F_APA_1000MAH             = 0x19,
  LC709203F_APA_2000MAH             = 0x2D,
  LC709203F_APA_3000MAH             = 0x36,
} lc709203_adjustment_t;

/*!  Cell profile */
typedef enum {
  LC709203_NOM3p7_Charge4p2         = 1,
  LC709203_NOM3p8_Charge4p35        = 3,
  LC709203_NOM3p8_Charge4p35_Less500mAh = 6,
  LC709203_ICR18650_SAMSUNG         = 5,
  LC709203_ICR18650_PANASONIC       = 4
}lc709203_cell_profile_t ;

/*!  Cell temperature source */
typedef enum {
  LC709203F_TEMPERATURE_I2C         = 0x0000,
  LC709203F_TEMPERATURE_THERMISTOR  = 0x0001,
} lc709203_tempmode_t;

/*!  Chip power state */
typedef enum {
  LC709203F_POWER_OPERATE           = 0x0001,
  LC709203F_POWER_SLEEP             = 0x0002,
} lc709203_powermode_t;

/*!
 *    @brief  Class that stores state and functions for interacting with
 *            the LC709203F I2C LiPo monitor
 */
// class LC709203F {
class LC709203FComponent : public PollingComponent, public i2c::I2CDevice, public Sensor {
public:

  bool begin( void );
  void initRSOC(void);

  void setPowerMode(lc709203_powermode_t t);
  void setCellCapacity(lc709203_adjustment_t apa);
  void setCellProfile(lc709203_cell_profile_t t);
  
  uint16_t getICversion(void);
  uint16_t cellVoltage_mV(void);
  uint16_t cellRemainingPercent10(void);	// Remaining capacity in increments of 0.1% as integer
  uint16_t cellStateOfCharge(void);		// In increments of 1% as integer
	

  uint16_t getThermistorBeta(void);
  void setThermistorB(uint16_t beta);

  void setTemperatureMode(lc709203_tempmode_t t);
  uint16_t getCellTemperature(void);
  void setAlarmRSOC(uint8_t percent);
  void setAlarmVoltage(float voltage);


  //  added to align with esphome
  void set_cellVoltage_sensor( sensor::Sensor *cellVoltage)       { cellVoltage_    = cellVoltage; }
  void set_cellRemPercent_sensor( sensor::Sensor *cellRemPercent) { cellRemPercent_ = cellRemPercent; }
  void set_icversion_sensor( sensor::Sensor *icversion)           { icversion_      = icversion; }
  void set_cellCharge_sensor( sensor::Sensor *cellCharge)         { cellCharge_     = cellCharge; }
  void setup() override;
  void update() override;
  void dump_config() override;

protected:
  void write16( uint8_t regAddress, uint16_t data);
  int16_t read16(uint8_t regAddress);

  // added for esphome
  sensor::Sensor *cellVoltage_;
  sensor::Sensor *cellRemPercent_;
  sensor::Sensor *icversion_;
  sensor::Sensor *cellCharge_;

};

}   // namespace lc709203f
}   // namespace esphome

#endif
