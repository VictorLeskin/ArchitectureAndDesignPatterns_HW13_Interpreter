cmake_minimum_required(VERSION 3.14)
project(ArchitectureAndDesignPatterns_HW13_Interpreter)

# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)


enable_testing()

add_executable(
  Interpreter

  source/ArchitectureAndDesignPatterns_HW13_Interpreter.hpp
  source/ArchitectureAndDesignPatterns_HW13_Interpreter.cpp

  source/nlohmann/json.hpp
  source/nlohmann/json_fwd.hpp

  source/aMessageBroker.hpp
  source/aMessageBroker.cpp
  source/cMessage.hpp
  source/cMessage.cpp
  source/cEndPoint.hpp
  source/cEndPoint.cpp
  source/cIoC.hpp
  source/cIoC.cpp
  source/iCommand.hpp
  source/iCommand.cpp
  source/cCommandsDeque.hpp
  source/cCommandsDeque.cpp
  source/cThreadSafeDeque.hpp
  source/cThreadSafeDeque.cpp
  source/cMessagesDeque.hpp
  source/cMessagesDeque.cpp
  source/cGame.hpp
  source/cGame.cpp
  source/cGameId.hpp
  source/cGameId.cpp
  source/cObject.hpp
  source/cObject.cpp
  source/cJsonString.hpp
  source/cJsonString.cpp
  source/cInterpretCommand.hpp
  source/cInterpretCommand.cpp
  source/cException.hpp
  source/cException.cpp
  source/cExceptionsHandler.hpp 
  source/cExceptionsHandler.cpp
  source/cSpaceShip.hpp
  source/cSpaceShip.cpp
  source/cStopCommand.cpp
  source/cStopCommand.hpp
#add source file here
  source/tests/test_ArchitectureAndDesignPatterns_HW13_Interpreter.cpp
  source/tests/test_aMessageBroker.cpp
  source/tests/test_cMessage.cpp
  source/tests/test_cEndPoint.cpp
  source/tests/test_cIoC.cpp
  source/tests/test_cCommandsDeque.cpp
  source/tests/test_iCommand.cpp
  source/tests/test_cThreadSafeDeque.cpp
  source/tests/test_cMessagesDeque.cpp
  source/tests/test_cGame.cpp
  source/tests/test_cGameId.cpp
  source/tests/test_cObject.cpp
  source/tests/test_cJsonString.cpp
  source/tests/test_cInterpretCommand.cpp
  source/tests/test_cException.cpp
  source/tests/test_cExceptionsHandler.cpp
  source/tests/test_cSpaceShip.cpp
  source/tests/test_cStopCommand.cpp
  source/tests/test_cFactory.cpp
  source/tests/test_cFactory.hpp
#add test file here
)

target_include_directories(
   Interpreter PRIVATE 
   source
)

target_link_libraries(
  Interpreter
  GTest::gtest_main
  GTest::gmock_main
)

include(GoogleTest GoogleMock)
gtest_discover_tests(Interpreter)