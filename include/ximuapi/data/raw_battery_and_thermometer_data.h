#ifndef INCLUDE_XIMUAPI_DATA_RAW_BATTERY_AND_THERMOMETER_DATA_H_
#define INCLUDE_XIMUAPI_DATA_RAW_BATTERY_AND_THERMOMETER_DATA_H_
	    
namespace ximu {

	class RawBatteryAndThermometerData
	{

	private:
		short _batteryVoltage;
		short _thermometer;

	public:

		/// <summary>
		/// Initialises a new instance of the class.
		/// </summary>
		RawBatteryAndThermometerData();

		/// <summary>
		/// Initialises a new instance of the class.
		/// </summary>
		/// <param name="batVolt">
		/// Calibrated battery voltage data in volts.
		/// </param>
		/// <param name="thermo">
		/// Calibrated thermometer data degrees Celsius.
		/// </param>
		RawBatteryAndThermometerData(const short &batVolt, const short &thermo);
		~RawBatteryAndThermometerData();


		/// <summary>
		/// Gets or sets the calibrated battery voltage data in volts.
		/// </summary>
		short batteryVoltage() const;
		void batteryVoltage(const short& batVolt);

		/// <summary>
		/// Gets or sets the calibrated thermometer data degrees Celsius.
		/// </summary>
		short thermometer() const;
		void thermometer(const short& thermo);
	};

}

#endif // INCLUDE_XIMUAPI_DATA_RAW_BATTERY_AND_THERMOMETER_DATA_H_
