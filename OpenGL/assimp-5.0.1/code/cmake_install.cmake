# Install script for directory: /Users/ihorfarion/Developer/OpenGL/assimp-5.0.1/code

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

# Set default install directory permissions.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/objdump")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES
    "/Users/ihorfarion/Developer/OpenGL/assimp-5.0.1/lib/libassimp.5.0.0.dylib"
    "/Users/ihorfarion/Developer/OpenGL/assimp-5.0.1/lib/libassimp.5.dylib"
    )
  foreach(file
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libassimp.5.0.0.dylib"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libassimp.5.dylib"
      )
    if(EXISTS "${file}" AND
       NOT IS_SYMLINK "${file}")
      execute_process(COMMAND "/usr/bin/install_name_tool"
        -id "/usr/local/lib/libassimp.5.dylib"
        "${file}")
      execute_process(COMMAND /usr/bin/install_name_tool
        -delete_rpath "/Users/ihorfarion/Developer/OpenGL/assimp-5.0.1/lib"
        "${file}")
      if(CMAKE_INSTALL_DO_STRIP)
        execute_process(COMMAND "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/strip" -x "${file}")
      endif()
    endif()
  endforeach()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES "/Users/ihorfarion/Developer/OpenGL/assimp-5.0.1/lib/libassimp.dylib")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libassimp.dylib" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libassimp.dylib")
    execute_process(COMMAND "/usr/bin/install_name_tool"
      -id "/usr/local/lib/libassimp.5.dylib"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libassimp.dylib")
    execute_process(COMMAND /usr/bin/install_name_tool
      -delete_rpath "/Users/ihorfarion/Developer/OpenGL/assimp-5.0.1/lib"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libassimp.dylib")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/strip" -x "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libassimp.dylib")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xassimp-devx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/assimp" TYPE FILE FILES
    "/Users/ihorfarion/Developer/OpenGL/assimp-5.0.1/code/../include/assimp/anim.h"
    "/Users/ihorfarion/Developer/OpenGL/assimp-5.0.1/code/../include/assimp/aabb.h"
    "/Users/ihorfarion/Developer/OpenGL/assimp-5.0.1/code/../include/assimp/ai_assert.h"
    "/Users/ihorfarion/Developer/OpenGL/assimp-5.0.1/code/../include/assimp/camera.h"
    "/Users/ihorfarion/Developer/OpenGL/assimp-5.0.1/code/../include/assimp/color4.h"
    "/Users/ihorfarion/Developer/OpenGL/assimp-5.0.1/code/../include/assimp/color4.inl"
    "/Users/ihorfarion/Developer/OpenGL/assimp-5.0.1/code/../include/assimp/config.h"
    "/Users/ihorfarion/Developer/OpenGL/assimp-5.0.1/code/../include/assimp/defs.h"
    "/Users/ihorfarion/Developer/OpenGL/assimp-5.0.1/code/../include/assimp/Defines.h"
    "/Users/ihorfarion/Developer/OpenGL/assimp-5.0.1/code/../include/assimp/cfileio.h"
    "/Users/ihorfarion/Developer/OpenGL/assimp-5.0.1/code/../include/assimp/light.h"
    "/Users/ihorfarion/Developer/OpenGL/assimp-5.0.1/code/../include/assimp/material.h"
    "/Users/ihorfarion/Developer/OpenGL/assimp-5.0.1/code/../include/assimp/material.inl"
    "/Users/ihorfarion/Developer/OpenGL/assimp-5.0.1/code/../include/assimp/matrix3x3.h"
    "/Users/ihorfarion/Developer/OpenGL/assimp-5.0.1/code/../include/assimp/matrix3x3.inl"
    "/Users/ihorfarion/Developer/OpenGL/assimp-5.0.1/code/../include/assimp/matrix4x4.h"
    "/Users/ihorfarion/Developer/OpenGL/assimp-5.0.1/code/../include/assimp/matrix4x4.inl"
    "/Users/ihorfarion/Developer/OpenGL/assimp-5.0.1/code/../include/assimp/mesh.h"
    "/Users/ihorfarion/Developer/OpenGL/assimp-5.0.1/code/../include/assimp/pbrmaterial.h"
    "/Users/ihorfarion/Developer/OpenGL/assimp-5.0.1/code/../include/assimp/postprocess.h"
    "/Users/ihorfarion/Developer/OpenGL/assimp-5.0.1/code/../include/assimp/quaternion.h"
    "/Users/ihorfarion/Developer/OpenGL/assimp-5.0.1/code/../include/assimp/quaternion.inl"
    "/Users/ihorfarion/Developer/OpenGL/assimp-5.0.1/code/../include/assimp/scene.h"
    "/Users/ihorfarion/Developer/OpenGL/assimp-5.0.1/code/../include/assimp/metadata.h"
    "/Users/ihorfarion/Developer/OpenGL/assimp-5.0.1/code/../include/assimp/texture.h"
    "/Users/ihorfarion/Developer/OpenGL/assimp-5.0.1/code/../include/assimp/types.h"
    "/Users/ihorfarion/Developer/OpenGL/assimp-5.0.1/code/../include/assimp/vector2.h"
    "/Users/ihorfarion/Developer/OpenGL/assimp-5.0.1/code/../include/assimp/vector2.inl"
    "/Users/ihorfarion/Developer/OpenGL/assimp-5.0.1/code/../include/assimp/vector3.h"
    "/Users/ihorfarion/Developer/OpenGL/assimp-5.0.1/code/../include/assimp/vector3.inl"
    "/Users/ihorfarion/Developer/OpenGL/assimp-5.0.1/code/../include/assimp/version.h"
    "/Users/ihorfarion/Developer/OpenGL/assimp-5.0.1/code/../include/assimp/cimport.h"
    "/Users/ihorfarion/Developer/OpenGL/assimp-5.0.1/code/../include/assimp/importerdesc.h"
    "/Users/ihorfarion/Developer/OpenGL/assimp-5.0.1/code/../include/assimp/Importer.hpp"
    "/Users/ihorfarion/Developer/OpenGL/assimp-5.0.1/code/../include/assimp/DefaultLogger.hpp"
    "/Users/ihorfarion/Developer/OpenGL/assimp-5.0.1/code/../include/assimp/ProgressHandler.hpp"
    "/Users/ihorfarion/Developer/OpenGL/assimp-5.0.1/code/../include/assimp/IOStream.hpp"
    "/Users/ihorfarion/Developer/OpenGL/assimp-5.0.1/code/../include/assimp/IOSystem.hpp"
    "/Users/ihorfarion/Developer/OpenGL/assimp-5.0.1/code/../include/assimp/Logger.hpp"
    "/Users/ihorfarion/Developer/OpenGL/assimp-5.0.1/code/../include/assimp/LogStream.hpp"
    "/Users/ihorfarion/Developer/OpenGL/assimp-5.0.1/code/../include/assimp/NullLogger.hpp"
    "/Users/ihorfarion/Developer/OpenGL/assimp-5.0.1/code/../include/assimp/cexport.h"
    "/Users/ihorfarion/Developer/OpenGL/assimp-5.0.1/code/../include/assimp/Exporter.hpp"
    "/Users/ihorfarion/Developer/OpenGL/assimp-5.0.1/code/../include/assimp/DefaultIOStream.h"
    "/Users/ihorfarion/Developer/OpenGL/assimp-5.0.1/code/../include/assimp/DefaultIOSystem.h"
    "/Users/ihorfarion/Developer/OpenGL/assimp-5.0.1/code/../include/assimp/ZipArchiveIOSystem.h"
    "/Users/ihorfarion/Developer/OpenGL/assimp-5.0.1/code/../include/assimp/SceneCombiner.h"
    "/Users/ihorfarion/Developer/OpenGL/assimp-5.0.1/code/../include/assimp/fast_atof.h"
    "/Users/ihorfarion/Developer/OpenGL/assimp-5.0.1/code/../include/assimp/qnan.h"
    "/Users/ihorfarion/Developer/OpenGL/assimp-5.0.1/code/../include/assimp/BaseImporter.h"
    "/Users/ihorfarion/Developer/OpenGL/assimp-5.0.1/code/../include/assimp/Hash.h"
    "/Users/ihorfarion/Developer/OpenGL/assimp-5.0.1/code/../include/assimp/MemoryIOWrapper.h"
    "/Users/ihorfarion/Developer/OpenGL/assimp-5.0.1/code/../include/assimp/ParsingUtils.h"
    "/Users/ihorfarion/Developer/OpenGL/assimp-5.0.1/code/../include/assimp/StreamReader.h"
    "/Users/ihorfarion/Developer/OpenGL/assimp-5.0.1/code/../include/assimp/StreamWriter.h"
    "/Users/ihorfarion/Developer/OpenGL/assimp-5.0.1/code/../include/assimp/StringComparison.h"
    "/Users/ihorfarion/Developer/OpenGL/assimp-5.0.1/code/../include/assimp/StringUtils.h"
    "/Users/ihorfarion/Developer/OpenGL/assimp-5.0.1/code/../include/assimp/SGSpatialSort.h"
    "/Users/ihorfarion/Developer/OpenGL/assimp-5.0.1/code/../include/assimp/GenericProperty.h"
    "/Users/ihorfarion/Developer/OpenGL/assimp-5.0.1/code/../include/assimp/SpatialSort.h"
    "/Users/ihorfarion/Developer/OpenGL/assimp-5.0.1/code/../include/assimp/SkeletonMeshBuilder.h"
    "/Users/ihorfarion/Developer/OpenGL/assimp-5.0.1/code/../include/assimp/SmoothingGroups.h"
    "/Users/ihorfarion/Developer/OpenGL/assimp-5.0.1/code/../include/assimp/SmoothingGroups.inl"
    "/Users/ihorfarion/Developer/OpenGL/assimp-5.0.1/code/../include/assimp/StandardShapes.h"
    "/Users/ihorfarion/Developer/OpenGL/assimp-5.0.1/code/../include/assimp/RemoveComments.h"
    "/Users/ihorfarion/Developer/OpenGL/assimp-5.0.1/code/../include/assimp/Subdivision.h"
    "/Users/ihorfarion/Developer/OpenGL/assimp-5.0.1/code/../include/assimp/Vertex.h"
    "/Users/ihorfarion/Developer/OpenGL/assimp-5.0.1/code/../include/assimp/LineSplitter.h"
    "/Users/ihorfarion/Developer/OpenGL/assimp-5.0.1/code/../include/assimp/TinyFormatter.h"
    "/Users/ihorfarion/Developer/OpenGL/assimp-5.0.1/code/../include/assimp/Profiler.h"
    "/Users/ihorfarion/Developer/OpenGL/assimp-5.0.1/code/../include/assimp/LogAux.h"
    "/Users/ihorfarion/Developer/OpenGL/assimp-5.0.1/code/../include/assimp/Bitmap.h"
    "/Users/ihorfarion/Developer/OpenGL/assimp-5.0.1/code/../include/assimp/XMLTools.h"
    "/Users/ihorfarion/Developer/OpenGL/assimp-5.0.1/code/../include/assimp/IOStreamBuffer.h"
    "/Users/ihorfarion/Developer/OpenGL/assimp-5.0.1/code/../include/assimp/CreateAnimMesh.h"
    "/Users/ihorfarion/Developer/OpenGL/assimp-5.0.1/code/../include/assimp/irrXMLWrapper.h"
    "/Users/ihorfarion/Developer/OpenGL/assimp-5.0.1/code/../include/assimp/BlobIOSystem.h"
    "/Users/ihorfarion/Developer/OpenGL/assimp-5.0.1/code/../include/assimp/MathFunctions.h"
    "/Users/ihorfarion/Developer/OpenGL/assimp-5.0.1/code/../include/assimp/Macros.h"
    "/Users/ihorfarion/Developer/OpenGL/assimp-5.0.1/code/../include/assimp/Exceptional.h"
    "/Users/ihorfarion/Developer/OpenGL/assimp-5.0.1/code/../include/assimp/ByteSwapper.h"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xassimp-devx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/assimp/Compiler" TYPE FILE FILES
    "/Users/ihorfarion/Developer/OpenGL/assimp-5.0.1/code/../include/assimp/Compiler/pushpack1.h"
    "/Users/ihorfarion/Developer/OpenGL/assimp-5.0.1/code/../include/assimp/Compiler/poppack1.h"
    "/Users/ihorfarion/Developer/OpenGL/assimp-5.0.1/code/../include/assimp/Compiler/pstdint.h"
    )
endif()

