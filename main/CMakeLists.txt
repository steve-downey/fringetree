add_executable(fringe "")

target_sources(
  fringe
  PRIVATE
  main.cpp)

target_link_libraries(fringe fringetree)

install(TARGETS fringe DESTINATION bin)
