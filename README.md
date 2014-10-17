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
[Cmake](http://www.cmake.org) is used as the main build tool.

For linux:
1. create a build directory inside "x-IMU-CPP-API"
2. from this build directory run: cmake ..
3. from this build directory run: make