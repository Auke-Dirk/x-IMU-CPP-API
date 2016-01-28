cmake_minimum_required(VERSION 2.8)
project(X-IMU-API)

# Policy for using X::Y
if(POLICY CMP0020)
  cmake_policy(SET CMP0020 NEW)
endif()

enable_testing()

set(X_IMU_API_MAJOR_VERION 0)
set(X_IMU_API_MINOR_VERION 1)
set(X_IMU_API_PATCH_VERION 0)


# set compiler flags
set(CMAKE_CXX_FLAGS "${CAMKE_CXX_FLAGS} -std=c++11")


# set main include directory
include_directories(
  include # main include directory
)

# For arm locate Threads
string ( TOLOWER "${CMAKE_SYSTEM_PROCESSOR}" CMAKE_SYSTEM_PROCESSOR_LOWERCASE)
if ("${CMAKE_SYSTEM_PROCESSOR_LOWERCASE}$" MATCHES ".*arm.*") 
    find_package (Threads)
endif()



# As moc files are generated in the binary dir, tell CMake
# to always look for includes there:
set(CMAKE_INCLUDE_CURRENT_DIR ON)
if (NOT QTDIR)
    set(QTDIR "" CACHE PATH "Qt root dir")
endif()


find_package(Qt5SerialPort)
find_package(Qt5Widgets)
find_package(Qt5OpenGL)
find_package(Qt5LinguistTools)

set(X_IMU_GUI_UI)
set(X_IMU_GUI_H)
set(X_IMU_GUI_SRC)

if (Qt5Widgets_FOUND)
    include_directories(${Qt5Widgets_INCLUDE_DIRS})
    add_definitions(${Qt5Widgets_DEFINITIONS})
    set(CMAKE_CXX_FLAGS "${CAMKE_CXX_FLAGS} -std=c++11 ${Qt5Widgets_EXECUTABLE_COMPILE_FLAGS}")
endif(Qt5Widgets_FOUND)


# add a target to generate API documentation with Doxygen
find_package(Doxygen)
if(DOXYGEN_FOUND)
    set(doxyfile_in ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in)
    set(doxyfile ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)

    configure_file(${doxyfile_in} ${doxyfile} @ONLY)

    add_custom_target(doc
        COMMAND ${DOXYGEN_EXECUTABLE} ${doxyfile}
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        COMMENT "Generating API documentation with Doxygen"
        VERBATIM)

    install(DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/html DESTINATION share/doc)
endif(DOXYGEN_FOUND)

###################
# source listings #
###################

# ximu api
set(X_IMU_API_SRC
  src/ximuapi/packet/packet_encoding.cpp
  src/ximuapi/utils/fixed_float.cpp
  src/ximuapi/data/register_data.cpp
  src/ximuapi/data/datetime_data.cpp
  src/ximuapi/data/digital_port_bits.cpp
  src/ximuapi/data/digital_io_data.cpp
  src/ximuapi/data/cal_inertial_and_magnetic_data.cpp
  src/ximuapi/data/raw_inertial_and_magnetic_data.cpp
  src/ximuapi/data/raw_battery_and_thermometer_data.cpp
  src/ximuapi/data/cal_battery_and_thermometer_data.cpp
  src/ximuapi/serialization/reader_base.cpp
  src/ximuapi/serialization/packet_reader.cpp
  src/ximuapi/serialization/writer_base.cpp
)

######
# Qt #
######

# ximu QT-serialport support
if (Qt5SerialPort_FOUND)
      qt5_wrap_cpp(MOC_SERIAL include/ximuapi/io/serial_port.h)
    set(X_IMU_API_SERIAL src/ximuapi/io/serial_port.cpp)
endif (Qt5SerialPort_FOUND)


# if widgets add simple window to src
if (Qt5Widgets_FOUND)
    set(SIMPLEWINDOW_MOC_HDRS include/ximugui/widgets/simplewindow.h)
    set(LANGUAGE_SELECTION_MOC_HDRS include/ximugui/widgets/lanuageselectionwidget.h)

    list(APPEND X_IMU_GUI_SRC src/ximugui/widgets/simplewindow.cpp)
    list(APPEND X_IMU_GUI_SRC src/ximugui/widgets/lanuageselectionwidget.cpp)

    list(APPEND X_IMU_GUI_UI src/ximugui/widgets/simplewindow.ui)
    list(APPEND X_IMU_GUI_UI src/ximugui/widgets/lanuageselectionwidget.ui)

    list(APPEND X_IMU_GUI_H ${SIMPLEWINDOW_MOC_HDRS})
    list(APPEND X_IMU_GUI_H ${LANGUAGE_SELECTION_MOC_HDRS})
endif (Qt5Widgets_FOUND)

if (Qt5SerialPort_FOUND AND Qt5Widgets_FOUND)
    set(SERIALVIEW_MOC_HDRS include/ximugui/widgets/serialview.h)
    list(APPEND X_IMU_GUI_SRC src/ximugui/widgets/serialview.cpp)
    list(APPEND X_IMU_GUI_UI src/ximugui/widgets/serialview.ui)
    list(APPEND X_IMU_GUI_H ${SERIALVIEW_MOC_HDRS})
endif (Qt5SerialPort_FOUND AND Qt5Widgets_FOUND)


if (Qt5OpenGL_FOUND)
    string(REGEX MATCHALL "([0-9])" QT_OPENGL_VERSION ${Qt5OpenGL_VERSION})
    list (GET QT_OPENGL_VERSION 1 MINOR)
    if (NOT MINOR LESS 4)
         set(Qt5OpenGL_MINOR_5_FOUND "TRUE")
    endif()
endif()


if(Qt5OpenGL_MINOR_5_FOUND AND Qt5Widgets_FOUND)
    set(ORIENTATIONVIEW_MOC_HDRS include/ximugui/widgets/orientationview.h)
    list(APPEND X_IMU_GUI_SRC src/ximugui/widgets/orientationview.cpp)
    list(APPEND X_IMU_GUI_UI src/ximugui/widgets/orientationview.ui)
    list(APPEND X_IMU_GUI_H ${ORIENTATIONVIEW_MOC_HDRS})
endif()


# add functionality to the library
add_library(X-IMU-API STATIC ${X_IMU_API_SRC} ${X_IMU_API_SERIAL} ${MOC_SERIAL})


if (Qt5SerialPort_FOUND)
    qt5_use_modules(X-IMU-API SerialPort)
endif (Qt5SerialPort_FOUND)

if (Qt5Widgets_FOUND)
    qt5_wrap_cpp(SIMPLEWINDOW_MOC_SRCS ${SIMPLEWINDOW_MOC_HDRS})
    qt5_wrap_cpp(LANGUAGE_SELECTION_MOC_SRCS ${LANGUAGE_SELECTION_MOC_HDRS})
    qt5_use_modules(X-IMU-API Core)
endif (Qt5Widgets_FOUND)

if (Qt5Widgets_FOUND AND Qt5OpenGL_FOUND)
    qt5_wrap_cpp(ORIENTATIONVIEW_MOC_SRCS ${ORIENTATIONVIEW_MOC_HDRS})
    qt5_use_modules(X-IMU-API Core OpenGL)
endif()

if (Qt5SerialPort_FOUND OR Qt5Widgets_FOUND)
    qt5_wrap_cpp(SERIALVIEW_MOC_SRCS ${SERIALVIEW_MOC_HDRS})
    qt5_wrap_ui(UI_HEADERS  ${X_IMU_GUI_UI})
endif (Qt5SerialPort_FOUND OR Qt5Widgets_FOUND)

# setup testing

# add c++ program
add_executable (PKT_ENC_TEST tests/packet_encoding_test.cpp)
add_executable (PKT_CNST_TEST tests/packet_construction_test.cpp)
add_executable (FXD_FLT_TEST tests/fixed_float_test.cpp)
add_executable (DATA_TYPES_TEST tests/data_types_test.cpp)
add_executable (DATA_SERIZ_READ tests/data_serialization_test.cpp)
add_executable (DATA_SERIZ_WRITE tests/data_serial_writer_test.cpp)

# if QT found build the tests/apps
if (Qt5Widgets_FOUND)
    # add the simple main window
    add_executable (QT_WINDOW_TEST tests/qt_window_test.cpp src/ximugui/widgets/simplewindow.cpp ${UI_HEADERS} ${SIMPLEWINDOW_MOC_SRCS})
    target_link_libraries(QT_WINDOW_TEST X-IMU-API Qt5::Widgets ${CMAKE_THREAD_LIBS_INIT})

    # add the language selection
    add_executable (QT_LANAGUAGE_SELECTION apps/language_selection.cpp src/ximugui/widgets/lanuageselectionwidget.cpp ${UI_HEADERS} ${LANGUAGE_SELECTION_MOC_SRCS})
    target_link_libraries(QT_LANAGUAGE_SELECTION Qt5::Widgets ${CMAKE_THREAD_LIBS_INIT})

endif (Qt5Widgets_FOUND)

if (Qt5SerialPort_FOUND AND Qt5Widgets_FOUND)
    qt5_add_resources(SERIALVIEW_RCC_SRCS src/ximugui/rc/serialview.qrc)
    add_executable (SERIAL_PORT tests/serial_port.cpp src/ximugui/widgets/serialview.cpp
    ${UI_HEADERS} ${SERIALVIEW_MOC_SRCS} ${SERIALVIEW_RCC_SRCS} ${QM} ${LANGUAGE_SELECTION_MOC_SRCS}
    src/ximugui/widgets/lanuageselectionwidget.cpp
    )
    target_link_libraries(SERIAL_PORT X-IMU-API ${CMAKE_THREAD_LIBS_INIT} Qt5::Widgets Qt5::SerialPort)
endif (Qt5SerialPort_FOUND AND Qt5Widgets_FOUND)

# If both Widget and Opengl add the Opengl (cube)
# widge. (Simple Quaternions that rotate cube )
if (Qt5Widgets_FOUND AND Qt5OpenGL_FOUND AND Qt5OpenGL_MINOR_5_FOUND)
    qt5_add_resources(ORIENTATIONVIEW_RCC_SRCS src/ximugui/rc/orientationview.qrc)    
    add_executable (QT_OPENGL_TEST tests/qt_opengl_test.cpp src/ximugui/widgets/orientationview.cpp src/ximugui/widgets/geometryengine.cpp
${UI_HEADERS} ${ORIENTATIONVIEW_MOC_SRCS} ${ORIENTATIONVIEW_RCC_SRCS})
    target_link_libraries(QT_OPENGL_TEST X-IMU-API Qt5::Widgets Qt5::OpenGL ${CMAKE_THREAD_LIBS_INIT})
endif ()


# link the x-IMU-API with the programs
target_link_libraries(PKT_ENC_TEST X-IMU-API)
target_link_libraries(PKT_CNST_TEST X-IMU-API)
target_link_libraries(FXD_FLT_TEST X-IMU-API)
target_link_libraries(DATA_TYPES_TEST X-IMU-API)
target_link_libraries(DATA_SERIZ_READ X-IMU-API)
target_link_libraries(DATA_SERIZ_WRITE X-IMU-API)

# add ximu port dump for as test data
configure_file(data/ximu.dmp ximu.dmp COPYONLY)

# perform the test
add_test(PACKET_ENCODING_DECODING PKT_ENC_TEST)
add_test(PACKET_CONSTRUCTION PKT_CNST_TEST)
add_test(FIXED_FLOAT FXD_FLT_TEST)
add_test(DATA_TYPES DATA_TYPES_TEST)
add_test(DATA_DESERIALIZER_RECIEVER DATA_SERIZ_READ)
add_test(DATA_DESERIALIZER_SENDER DATA_SERIZ_WRITE)

if (Qt5Widgets_FOUND)
    add_test(QT_WINDOW QT_WINDOW_TEST)
endif (Qt5Widgets_FOUND)

if (Qt5Widgets_FOUND AND QtOpenGL_FOUND)
    add_test(QT_OPENGL QT_OPENGL_TEST)
endif ()

################################
# Qt's lupdate for translation #
################################
set(TRANSLATIONS TRUE)
MACRO(update_translations sources translation_files)
    if (QTDIR AND TRANSLATIONS)
        find_program(lupdate lupdate ${QTDIR})
        if(NOT ${lupdate}-NOTFOUND)
            execute_process(
                COMMAND ${lupdate}
                -silent
                ${sources}
                 -ts ${translation_files}
                WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
                )
        endif()
    endif()
ENDMACRO(update_translations)

list (APPEND FILES_TO_TRANSLATE ${X_IMU_GUI_SRC} ${X_IMU_GUI_UI} ${X_IMU_GUI_H})
file (GLOB TRANSLATION_FILES translations/*.ts)
update_translations("${FILES_TO_TRANSLATE}" "${TRANSLATION_FILES}")

############################################
# Qt's  lrelease for building the qm files #
############################################
if (QTDIR AND TRANSLATIONS)
    find_program(lrelease lrelease ${QTDIR})
    if(NOT ${lrelease}-NOTFOUND)
        add_custom_command(OUTPUT output
            COMMAND ${lrelease} ${TRANSLATION_FILES}
            WORKING_DIRECTORY  ${CMAKE_SOURCE_DIR}
            DEPENDS ${TRANSLATION_FILES}
            COMMENT "Generating qm files")
        add_custom_target(build_qm ALL DEPENDS output WORKING_DIRECTORY  ${CMAKE_SOURCE_DIR})

        file (GLOB TRANSLATIONS_QM translations/*.qm)
        file(COPY ${TRANSLATIONS_QM} DESTINATION "${CMAKE_BINARY_DIR}/translations")
    endif()
endif()

