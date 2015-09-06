#include "ximuapi/data/raw_battery_and_thermometer_data.h"

namespace ximu {

	RawBatteryAndThermometerData::RawBatteryAndThermometerData()
		:
		_batteryVoltage(0),
		_thermometer(0){
	}

	RawBatteryAndThermometerData::RawBatteryAndThermometerData(
		const short &batVolt,
		const short &thermo)
		:
		_batteryVoltage(batVolt),
		_thermometer(thermo){
	}

	RawBatteryAndThermometerData::~RawBatteryAndThermometerData(){
	}

	short RawBatteryAndThermometerData::batteryVoltage() const
	{
		return _batteryVoltage;
	}

	void RawBatteryAndThermometerData::batteryVoltage(const short & batVolt)
	{
		_batteryVoltage = batVolt;
	}

	short RawBatteryAndThermometerData::thermometer() const
	{
		return _thermometer;
	}

	void RawBatteryAndThermometerData::thermometer(const short& thermo)
	{
		_thermometer = thermo;
	}

}