x-IMU-CPP-API
=============

C++ port of xioTechnologies/x-IMU-GUI and API.
This project is also hosted on github and can be found [here](https://github.com/xioTechnologies/x-IMU-GUI).

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

Test Tool
-----------
[CTest](http://www.cmake.org/cmake/help/v2.8.8/ctest.html) can be used for testing.
CMake has been configured to provide automated testing.

For linux: simply call: make test 

Documentation
--------------
All functionality should come with a unit test, this test should be written such that it
serves as an example/documenation for the developer. The **Ported File List** section lists/links
what functionality already has been ported alongside its test/documentation.

Ported File List
----------------
+ [PacketEncoding.cs](https://github.com/xioTechnologies/x-IMU-GUI/blob/master/x-IMU%20API/PacketEncoding.cs) ::  [packet_encoding.h](https://github.com/Auke-Dirk/x-IMU-CPP-API/blob/master/include/ximuapi/packet/packet_encoding.h) ::
[packet_encoding_test.cpp](https://github.com/Auke-Dirk/x-IMU-CPP-API/blob/master/tests/packet_encoding_test.cpp)
