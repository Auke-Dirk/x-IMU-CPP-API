#ifndef INCLUDE_XIMUAPI_DATA_CAL_BATTERY_AND_THERMOMETER_DATA_H_
#define INCLUDE_XIMUAPI_DATA_CAL_BATTERY_AND_THERMOMETER_DATA_H_

namespace ximu {

	class CalBatteryAndThermometerData
	{
	
	private:
		float _batteryVoltage;
		float _thermometer;

	public:
		
		/// <summary>
		/// Initialises a new instance of the class.
		/// </summary>
		CalBatteryAndThermometerData();

		/// <summary>
		/// Initialises a new instance of the class.
		/// </summary>
		/// <param name="batVolt">
		/// Calibrated battery voltage data in volts.
		/// </param>
		/// <param name="thermo">
		/// Calibrated thermometer data degrees Celsius.
		/// </param>
		CalBatteryAndThermometerData(const float &batVolt, const float &thermo);
		~CalBatteryAndThermometerData();


		/// <summary>
		/// Gets or sets the calibrated battery voltage data in volts.
		/// </summary>
		float batteryVoltage() const;
		void batteryVoltage(const float& batVolt);

		/// <summary>
		/// Gets or sets the calibrated thermometer data degrees Celsius.
		/// </summary>
		float thermometer() const;
		void thermometer(const float& thermo);
	};

}
#endif  // INCLUDE_XIMUAPI_DATA_CAL_BATTERY_AND_THERMOMETER_DATA_H_