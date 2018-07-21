add_library(fringetree STATIC "")

target_sources(
  fringetree
  PRIVATE
  fringetree.cpp)

include(GNUInstallDirs)

target_include_directories(fringetree PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
  $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/${CMAKE_LOWER_PROJECT_NAME}>  # <prefix>/include/fringetree
  )

install(
  TARGETS fringetree
  EXPORT ${TARGETS_EXPORT_NAME}
  DESTINATION ${CMAKE_INSTALL_LIBDIR}
  )

string(TOLOWER ${CMAKE_PROJECT_NAME} CMAKE_LOWER_PROJECT_NAME)

install(
  DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/
  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${CMAKE_LOWER_PROJECT_NAME}
  FILES_MATCHING PATTERN "*.h"
  )


## Tests
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
