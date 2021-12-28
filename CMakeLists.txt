# cmake needs this line
cmake_minimum_required(VERSION 3.1.0)

# Define project name
project(rvision)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

# Find Protobuf
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")
find_package(Protobuf REQUIRED)
set(_PROTOBUF_LIBPROTOBUF protobuf::libprotobuf)
message(STATUS "Using protobuf ${protobuf_VERSION}")

# Find gRPC
find_package(GRPC REQUIRED)
set(_GRPC_GRPCPP_REFLECTION gRPC::grpc++_reflection)
message(STATUS "Using gRPC ${gRPC_VERSION}")

# Proto file
message(STATUS "CMAKE_CURRENT_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}")
set(hw_proto ${CMAKE_CURRENT_SOURCE_DIR}/user/Grpc.proto)

set(PROTO_SRC_DIR ${CMAKE_CURRENT_BINARY_DIR}/proto-src)
file(MAKE_DIRECTORY ${PROTO_SRC_DIR})

# Include generated *.pb.h files
include_directories(${PROTO_SRC_DIR})

# Generated sources
protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS ${PROTO_SRC_DIR} ${hw_proto})
grpc_generate_cpp(GRPC_SRCS GRPC_HDRS ${PROTO_SRC_DIR} ${hw_proto})



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

link_directories(/home/paul/work/rvision/depends/lib)

# Declare the executable target built from your sources
add_executable(rvision ./driver/Robot.cpp ./driver/Hand.cpp ./driver/Camera.cpp ./driver/ExternalParamCalibrate.cpp ./driver/InternalParamCalibrate.cpp ./user/GeometricalDetector.cpp 
${PROTO_SRCS} ${GRPC_SRCS} ./user/GrpcClient.cpp ./user/Main.cpp)

# Link your application with libraries
target_link_libraries(rvision ${OpenCV_LIBS} libMvCameraControl.so -lpthread -lOpennrif libmodbus.so)

target_link_libraries (rvision ${_GRPC_GRPCPP_REFLECTION} ${_PROTOBUF_LIBPROTOBUF})
