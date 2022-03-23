set(SRC_PATH ${CMAKE_SOURCE_DIR}/src/app)

enable_testing()

add_executable(
  lexer_tests
  lexer_tests.cpp
  
)

target_include_directories(
  lexer_tests
  PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
  PRIVATE
    ${SRC_PATH}
    
)

target_link_libraries(
  lexer_tests
    antlr4_cpp_runtime
    lexerlib
    gtest_main
    
)

include(GoogleTest)
gtest_discover_tests(lexer_tests)
