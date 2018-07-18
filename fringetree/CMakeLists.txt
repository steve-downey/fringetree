add_library(fringetree STATIC "")

target_sources(
  fringetree
  PRIVATE
  fringetree.cpp)

target_include_directories(fringetree PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
  $<INSTALL_INTERFACE:include/fringetree>  # <prefix>/include/fringetree
  )

install(TARGETS fringetree DESTINATION lib)
install(FILES fringetree.h DESTINATION include/fringetree)

add_executable(fringetree_test "")

target_sources(
  fringetree_test
  PRIVATE
  fringetree.t.cpp)

target_link_libraries(fringetree_test fringetree)
target_link_libraries(fringetree_test gtest)
target_link_libraries(fringetree_test gtest_main)

include(GoogleTest)
gtest_discover_tests(fringetree_test)
