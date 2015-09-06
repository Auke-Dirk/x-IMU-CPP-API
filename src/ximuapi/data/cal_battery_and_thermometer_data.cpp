#include "ximuapi/data/cal_battery_and_thermometer_data.h"

namespace ximu {

	CalBatteryAndThermometerData::CalBatteryAndThermometerData()
		: 
		_batteryVoltage(0),
		_thermometer(0){
	}

	CalBatteryAndThermometerData::CalBatteryAndThermometerData(
		const float &batVolt,
		const float &thermo)
		:
		_batteryVoltage(batVolt),
		_thermometer(thermo){

	}

	CalBatteryAndThermometerData::~CalBatteryAndThermometerData(){
	}

	float CalBatteryAndThermometerData::batteryVoltage() const
	{
		return _batteryVoltage;
	}

	void CalBatteryAndThermometerData::batteryVoltage(const float & batVolt)
	{
		_batteryVoltage = batVolt;
	}

	float CalBatteryAndThermometerData::thermometer() const
	{
		return _thermometer;
	}

	void CalBatteryAndThermometerData::thermometer(const float& thermo)
	{
		_thermometer = thermo;
	}

}