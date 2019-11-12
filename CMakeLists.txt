cmake_minimum_required(VERSION 3.15)
project(TMRG)

set(CMAKE_CXX_STANDARD 17)

add_executable(TMRG main.cpp tasks/min_period.cpp tasks/min_period.h tasks/min_period_alt.cpp tasks/min_period_alt.h structures/linked_list.cpp structures/linked_list.h global/console_coloring.cpp global/console_coloring.h math/operation.cpp math/operation.h)