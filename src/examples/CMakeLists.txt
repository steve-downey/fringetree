
include(GNUInstallDirs)

add_executable(fringe "")

target_sources(
  fringe
  PRIVATE
  main.cpp)

target_link_libraries(fringe fringetree)

install(
  TARGETS fringe
  DESTINATION ${CMAKE_INSTALL_BINDIR}
  )

add_executable(prepend "")

target_sources(
  prepend
  PRIVATE
  prepend.cpp)

target_link_libraries(prepend fringetree)

install(
  TARGETS prepend
  DESTINATION ${CMAKE_INSTALL_BINDIR}
  )
