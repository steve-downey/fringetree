add_executable(fringe "")

target_sources(
  fringe
  PRIVATE
  main.cpp)

target_link_libraries(fringe fringetree)

include(GNUInstallDirs)

install(
  TARGETS fringe
  DESTINATION ${CMAKE_INSTALL_BINDIR}
  )
