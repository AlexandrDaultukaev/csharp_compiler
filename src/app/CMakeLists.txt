set(target_name app)
set(SRC_PATH {CMAKE_SOURCE_DIR}/src/app)

add_executable(
  ${target_name}
  main.cpp
)

add_library(lexerlib STATIC lexer/lexer.hpp lexer/lexer.cpp grammar/CsharpLexer.h grammar/CsharpLexer.cpp)

include(CompileOptions)
set_compile_options(${target_name})
set_compile_options(lexerlib)

target_include_directories(
  ${target_name}
  PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
  PRIVATE
    ${SRC_PATH}
)

target_include_directories(
    lexerlib
    PRIVATE
      ${CMAKE_CURRENT_LIST_DIR}
    PUBLIC
      ${SRC_PATH}
)

target_link_libraries(lexerlib antlr4_cpp_runtime)
target_link_libraries(lexerlib CLI11)

target_link_libraries(${target_name} antlr4_cpp_runtime)
target_link_libraries(${target_name} CLI11)
target_link_libraries(${target_name} lexerlib)



