cmake_minimum_required(VERSION 3.16)

project(ProtocolLib LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 REQUIRED COMPONENTS Core Network Xml)

add_library(protocol SHARED
  src/Protocol_global.h
  src/protocol.cpp  src/protocol.h
  src/protocoljson.cpp  src/protocoljson.h
  src/protocolxml.cpp  src/protocolxml.h
  src/command.cpp src/command.h)

target_include_directories(protocol PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)
target_link_libraries(protocol PUBLIC Qt5::Core Qt5::Network Qt5::Xml)
