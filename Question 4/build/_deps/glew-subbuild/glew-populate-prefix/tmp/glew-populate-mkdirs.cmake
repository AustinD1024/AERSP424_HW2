# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "C:/Users/945au/OneDrive/Desktop/Penn_State/Senior Year School Work/Semester 2/AERSP 424/OpenGL Example/build/_deps/glew-src"
  "C:/Users/945au/OneDrive/Desktop/Penn_State/Senior Year School Work/Semester 2/AERSP 424/OpenGL Example/build/_deps/glew-build"
  "C:/Users/945au/OneDrive/Desktop/Penn_State/Senior Year School Work/Semester 2/AERSP 424/OpenGL Example/build/_deps/glew-subbuild/glew-populate-prefix"
  "C:/Users/945au/OneDrive/Desktop/Penn_State/Senior Year School Work/Semester 2/AERSP 424/OpenGL Example/build/_deps/glew-subbuild/glew-populate-prefix/tmp"
  "C:/Users/945au/OneDrive/Desktop/Penn_State/Senior Year School Work/Semester 2/AERSP 424/OpenGL Example/build/_deps/glew-subbuild/glew-populate-prefix/src/glew-populate-stamp"
  "C:/Users/945au/OneDrive/Desktop/Penn_State/Senior Year School Work/Semester 2/AERSP 424/OpenGL Example/build/_deps/glew-subbuild/glew-populate-prefix/src"
  "C:/Users/945au/OneDrive/Desktop/Penn_State/Senior Year School Work/Semester 2/AERSP 424/OpenGL Example/build/_deps/glew-subbuild/glew-populate-prefix/src/glew-populate-stamp"
)

set(configSubDirs Debug)
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "C:/Users/945au/OneDrive/Desktop/Penn_State/Senior Year School Work/Semester 2/AERSP 424/OpenGL Example/build/_deps/glew-subbuild/glew-populate-prefix/src/glew-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "C:/Users/945au/OneDrive/Desktop/Penn_State/Senior Year School Work/Semester 2/AERSP 424/OpenGL Example/build/_deps/glew-subbuild/glew-populate-prefix/src/glew-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()
