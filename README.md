x-IMU-CPP-API
=============

C++11 port of xioTechnologies API ( c++ ximu ).
This xioTechnologies project is also hosted on github and can be found [here](https://github.com/xioTechnologies/x-IMU-GUI).
The latest version of x-IMU-API has build in support for Qt.

**QtSerialPort (>= Qt 5.1.x)**

If the requirements are met, the library is extended --"ximu::SerialPort" with Qt's serialport functionality.
Next to this a serialport **(Qt)** programm with gui is added for the testing pruposes.

**QOpenGLWidget (>=Qt 5.4.x)**

When then requirements for the QOpenGLWidget are met, a test is added showing a rotating cube.

Code Snippet: *how to use the library*
------------------------------------
``` cpp
// Whenever the Qt::SerialPort is available
class MyClass {
    ximu::SerialPort _sp;
    void onQuaternionRecieved(const ximu::QuaternionData& q){...}
};
...
// registering for data is based on signals/slots from Qt
connect(&_sp, &ximu::SerialPort::quaternion, this, &MyClass::onQuaternionRecieved);
...
// Create your own Ximu class by extending the two available
// bases. ReaderBase for reading data from the ximu and WriterBase
// for writing to the ximu device. 
class XimuIO : public ximu::ReaderBase, public ximu::WriterBase {
    ..
    IOPort port; // os specific not included  (Except if Qt5::SerialPort 5.1.x) is found
    
    // often a callback is presented from the IO port
    void IOPortCallback(char* data, int length) {
        // two template methods are provided, see reader_base.h        
        fill(data, length);
        read();
    }
    
    // forward encoded data to the IOPort
    virtual void sendSerialBuffer(std::vector<unsigned char>& data) {
        ..
        port.write(data..
    }
    
    // implement reciever functions for those datatypes that you are interested in
    virtual void recievedQuaternionData(ximu::QuaternionData& q) {
        ..  
    }
    virtual void recievedCalInertialAndMagneticData(
    ximu::CalInertialAndMagneticData& data){
        ..        
    }
};

XimuIO xio;

// writing 
xio.sendCommandPacket(ximu::CommandCodes::ALGORITHM_CLEAR_TARE);
xio.sendCommandPacket(ximu::CommandCodes::ALGORITHM_INITIALISE_THEN_TARE);
..

ximu::DateTimeData dt(..,..);
xio.sendWriteDateTimePacket(dt);
```


Coding Style
------------
This project holds the [Google code style](http://google-styleguide.googlecode.com/svn/trunk/cppguide.html) guidelines.
Make sure that you test your code for code-style before you push, tools/scripts/plugins such as:

+ [cpplint](http://google-styleguide.googlecode.com/svn/trunk/cpplint/cpplint.py)
+ [google-c-style.el](http://google-styleguide.googlecode.com/svn/trunk/google-c-style.el)

can be of great confiniance.

Build Tool
------------
[CMake](http://www.cmake.org) is used as the main build tool.

For linux:
   1. create a build directory inside "x-IMU-CPP-API"
   2. from this build directory run: cmake ..
   3. from this build directory run: make
   
Windows:
   1. use cmake gui and generate the source for you visual studio version

Test Tool
-----------
[CTest](http://www.cmake.org/cmake/help/v2.8.8/ctest.html) can be used for testing.
CMake has been configured to provide automated testing.

For linux: make test 

Documentation
--------------
All functionality should come with a unit test, this test should be written such that it
serves as an example/documenation for the developer. The **Ported File List** section lists/links
what functionality already has been ported alongside its test/documentation.

Ported File List
----------------
| Orignal | Ported | Test/Documentation |
| ------- | ------ | ------------------ |
| [FixedFloat.cs](https://github.com/xioTechnologies/x-IMU-GUI/blob/master/x-IMU%20API/FixedFloat.cs) | [fixed_float.h](https://github.com/Auke-Dirk/x-IMU-CPP-API/blob/master/include/ximuapi/utils/fixed_float.h) | [fixed_float_test.cpp](https://github.com/Auke-Dirk/x-IMU-CPP-API/blob/master/tests/fixed_float_test.cpp)
| [PacketEncoding.cs](https://github.com/xioTechnologies/x-IMU-GUI/blob/master/x-IMU%20API/PacketEncoding.cs) | [packet_encoding.h](https://github.com/Auke-Dirk/x-IMU-CPP-API/blob/master/include/ximuapi/packet/packet_encoding.h)| [packet_encoding_test.cpp](https://github.com/Auke-Dirk/x-IMU-CPP-API/blob/master/tests/packet_encoding_test.cpp)
| [RegisterData.cs](https://github.com/xioTechnologies/x-IMU-GUI/blob/master/x-IMU%20API/RegisterData.cs) | [register_data.h](https://github.com/Auke-Dirk/x-IMU-CPP-API/blob/master/include/ximuapi/data/register_data.h) | [data_types_test.cpp](https://github.com/Auke-Dirk/x-IMU-CPP-API/blob/master/tests/data_types_test.cpp) |
| [DateTimeData.cs](https://github.com/xioTechnologies/x-IMU-GUI/blob/master/x-IMU%20API/DateTimeData.cs) | [datetime_data.h](https://github.com/Auke-Dirk/x-IMU-CPP-API/blob/master/include/ximuapi/data/datetime_data.h) | [data_types_test.cpp](https://github.com/Auke-Dirk/x-IMU-CPP-API/blob/master/tests/data_types_test.cpp) |
| [QuaternionData.cs](https://github.com/xioTechnologies/x-IMU-GUI/blob/master/x-IMU%20API/QuaternionData.cs) | [quaternion_data.h](https://github.com/Auke-Dirk/x-IMU-CPP-API/blob/master/include/ximuapi/data/quaternion_data.h) | [data_types_test.cpp](https://github.com/Auke-Dirk/x-IMU-CPP-API/blob/master/tests/data_types_test.cpp) |
| [PacketConstruction.cs](https://github.com/xioTechnologies/x-IMU-GUI/blob/master/x-IMU%20API/PacketConstruction.cs) | [packet_construction.h](https://github.com/Auke-Dirk/x-IMU-CPP-API/blob/master/include/ximuapi/packet/packet_construction.h) | [packet_construction_test.cpp](https://github.com/Auke-Dirk/x-IMU-CPP-API/blob/master/tests/packet_construction_test.cpp) |
| |[packet_deconstruction.h](https://github.com/Auke-Dirk/x-IMU-CPP-API/blob/master/include/ximuapi/packet/packet_deconstruction.h)  | [data_serialization_test.cpp](https://github.com/Auke-Dirk/x-IMU-CPP-API/blob/master/tests/data_serialization_test.cpp) |
| |[packet_reader.h](https://github.com/Auke-Dirk/x-IMU-CPP-API/blob/master/include/ximuapi/serialization/packet_reader.h)  | [data_serialization_test.cpp](https://github.com/Auke-Dirk/x-IMU-CPP-API/blob/master/tests/data_serialization_test.cpp) |
| [xIMUSerial.cs](https://github.com/xioTechnologies/x-IMU-GUI/blob/master/x-IMU%20API/xIMUserial.cs) | [reader_base.h](https://github.com/Auke-Dirk/x-IMU-CPP-API/blob/master/include/ximuapi/serialization/reader_base.h) | [data_serialization_test.cpp](https://github.com/Auke-Dirk/x-IMU-CPP-API/blob/master/tests/data_serialization_test.cpp) |
||[writer_base.h](https://github.com/Auke-Dirk/x-IMU-CPP-API/blob/master/include/ximuapi/serialization/writer_base.h)| [data_serial_writer_test.cpp](https://github.com/Auke-Dirk/x-IMU-CPP-API/blob/master/tests/data_serial_writer_test.cpp)|
|[CalInertialAndMagneticData.cs](https://github.com/xioTechnologies/x-IMU-GUI/blob/master/x-IMU%20API/CalInertialAndMagneticData.cs)| [cal_iner .. magnetic_data.h](https://github.com/Auke-Dirk/x-IMU-CPP-API/blob/master/include/ximuapi/data/cal_inertial_and_magnetic_data.h) |  [data_types_test.cpp](https://github.com/Auke-Dirk/x-IMU-CPP-API/blob/master/tests/data_types_test.cpp) |
|[DigitalPortBits.cs](https://github.com/xioTechnologies/x-IMU-GUI/blob/master/x-IMU%20API/DigitalPortBits.cs) |[digital_port_bits.h](https://github.com/Auke-Dirk/x-IMU-CPP-API/blob/master/include/ximuapi/data/digital_port_bits.h) | [data_types_test.cpp](https://github.com/Auke-Dirk/x-IMU-CPP-API/blob/master/tests/data_types_test.cpp) |
| [DigitalIOdata.cs](https://github.com/xioTechnologies/x-IMU-GUI/blob/master/x-IMU%20API/DigitalIOdata.cs) | [digital_io_data.h](https://github.com/Auke-Dirk/x-IMU-CPP-API/blob/master/include/ximuapi/data/digital_io_data.h) | [data_types_test.cpp](https://github.com/Auke-Dirk/x-IMU-CPP-API/blob/master/tests/data_types_test.cpp) |
|[PWMOutputData.cs](https://github.com/xioTechnologies/x-IMU-GUI/blob/master/x-IMU%20API/PWMoutputData.cs) | [pwm_output_data.h](https://github.com/Auke-Dirk/x-IMU-CPP-API/blob/master/include/ximuapi/data/pwm_output_data.h)| | 
|[CalADXL345busData.cs](https://github.com/xioTechnologies/x-IMU-GUI/blob/master/x-IMU%20API/CalADXL345busData.cs)|[adxl_345_bus_data.h](https://github.com/Auke-Dirk/x-IMU-CPP-API/blob/master/include/ximuapi/data/adxl_345_bus_data.h) ||
|[RawADXL345busData.cs](https://github.com/xioTechnologies/x-IMU-GUI/blob/master/x-IMU%20API/RawADXL345busData.cs) |[adxl_345_bus_data.h](https://github.com/Auke-Dirk/x-IMU-CPP-API/blob/master/include/ximuapi/data/adxl_345_bus_data.h) |
|[CalAnalogueInputData.cs](https://github.com/xioTechnologies/x-IMU-GUI/blob/master/x-IMU%20API/CalAnalogueInputData.cs) | [analogue_input_data.h](https://github.com/Auke-Dirk/x-IMU-CPP-API/blob/master/include/ximuapi/data/analogue_input_data.h) ||
|[RawAnalogueInputData.cs](https://github.com/xioTechnologies/x-IMU-GUI/blob/master/x-IMU%20API/RawAnalogueInputData.cs) | [analogue_input_data.h](https://github.com/Auke-Dirk/x-IMU-CPP-API/blob/master/include/ximuapi/data/analogue_input_data.h) ||
