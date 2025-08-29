# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "C:/Users/jan.kristel/Documents/Thesis/HardwareAPI/Project/HW_API_final/build/_deps/arm_cmsis_core-src"
  "C:/Users/jan.kristel/Documents/Thesis/HardwareAPI/Project/HW_API_final/build/_deps/arm_cmsis_core-build"
  "C:/Users/jan.kristel/Documents/Thesis/HardwareAPI/Project/HW_API_final/build/_deps/arm_cmsis_core-subbuild/arm_cmsis_core-populate-prefix"
  "C:/Users/jan.kristel/Documents/Thesis/HardwareAPI/Project/HW_API_final/build/_deps/arm_cmsis_core-subbuild/arm_cmsis_core-populate-prefix/tmp"
  "C:/Users/jan.kristel/Documents/Thesis/HardwareAPI/Project/HW_API_final/build/_deps/arm_cmsis_core-subbuild/arm_cmsis_core-populate-prefix/src/arm_cmsis_core-populate-stamp"
  "C:/Users/jan.kristel/Documents/Thesis/HardwareAPI/Project/HW_API_final/build/_deps/arm_cmsis_core-subbuild/arm_cmsis_core-populate-prefix/src"
  "C:/Users/jan.kristel/Documents/Thesis/HardwareAPI/Project/HW_API_final/build/_deps/arm_cmsis_core-subbuild/arm_cmsis_core-populate-prefix/src/arm_cmsis_core-populate-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "C:/Users/jan.kristel/Documents/Thesis/HardwareAPI/Project/HW_API_final/build/_deps/arm_cmsis_core-subbuild/arm_cmsis_core-populate-prefix/src/arm_cmsis_core-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "C:/Users/jan.kristel/Documents/Thesis/HardwareAPI/Project/HW_API_final/build/_deps/arm_cmsis_core-subbuild/arm_cmsis_core-populate-prefix/src/arm_cmsis_core-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()
