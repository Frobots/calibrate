# cmake needs this line
cmake_minimum_required(VERSION 3.1.0)

# Define project name
project(calibrate)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

# Find OpenCV, you may need to set OpenCV_DIR variable
# to the absolute path to the directory containing OpenCVConfig.cmake file
# via the command line or GUI
find_package(OpenCV REQUIRED)

# If the package has been found, several variables will
# be set, you can find the full list with descriptions
# in the OpenCVConfig.cmake file.
# Print some message showing some of them
message(STATUS "OpenCV library status:")
message(STATUS "    version: ${OpenCV_VERSION}")
message(STATUS "    libraries: ${OpenCV_LIBS}")
message(STATUS "    include path: ${OpenCV_INCLUDE_DIRS}")

# Add headers location to your include paths
include_directories(${OpenCV_INCLUDE_DIRS} ./depends/include)

link_directories(/home/paul/work/calibrate/depends/lib)

# Declare the executable target built from your sources
add_executable(calibrate ./Camera.cpp ./InternalParamCalibrate.cpp ./ExternalParamCalibrate.cpp ./Main.cpp)

# Link your application with libraries
target_link_libraries(calibrate ${OpenCV_LIBS} libMvCameraControl.so -lpthread -lOpennrif libmodbus.so)

target_link_libraries (calibrate ${_GRPC_GRPCPP_REFLECTION} ${_PROTOBUF_LIBPROTOBUF})
