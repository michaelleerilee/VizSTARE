cmake_minimum_required (VERSION 3.0)

project (VizSTARE)

find_package(Coin REQUIRED)
message( "test: COIN_NAME  ${COIN_NAME}" )
message( "test: COIN_VERSION  ${COIN_VERSION}" )

find_package(SoQt REQUIRED)
message( "test: SOQT_VERSION  ${SOQT_VERSION}" )

find_package(Qt5 REQUIRED COMPONENTS Widgets Core OpenGL Gui )

if( NOT Coin_FOUND )

if( NOT DEFINED ENV{COIN3D_CONFIG_COMMAND} )
  include(FindCoin3D)
  if( NOT ${COIN3D_FOUND} )
    set( COIN3D_CONFIG_COMMAND_TEST "soqt-config")
    find_file( COIN3D_CONFIG_COMMAND "${COIN3D_CONFIG_COMMAND_TEST}" )
    if( NOT EXISTS "${COIN3D_CONFIG_COMMAND}" )
      message("COIN3D NOT FOUND\nSET ENVIRONMENT VARIABLE COIN3D_CONFIG_COMMAND TO soqt-config etc.\n")
    endif()
  endif()
else()
  find_file( COIN3D_CONFIG_COMMAND "$ENV{COIN3D_CONFIG_COMMAND}" )
  if( NOT EXISTS "${COIN3D_CONFIG_COMMAND}" )
      message("COIN3D NOT FOUND\nSET ENVIRONMENT VARIABLE COIN3D_CONFIG_COMMAND TO soqt-config etc.\n")
  endif()
endif()  

if( ${COIN3D_FOUND} )
  set( COIN3D_CPPFLAGS   "${COIN3D_INCLUDE_DIRS}" )
  set( COIN3D_LINKFLAGS  "${COIN3D_LIBRARIES}"    )
else()
  set( COIN3D_CONFIG_COMMAND_CPPFLAG "--cppflags" )
  execute_process(
    COMMAND         "${COIN3D_CONFIG_COMMAND}" "${COIN3D_CONFIG_COMMAND_CPPFLAG}"
    OUTPUT_VARIABLE COIN3D_CPPFLAGS
  )
  
  set( COIN3D_CONFIG_COMMAND_LINKFLAGS "--ldflags" )
  execute_process(
    COMMAND         "${COIN3D_CONFIG_COMMAND}" "${COIN3D_CONFIG_COMMAND_LINKFLAGS}"
    OUTPUT_VARIABLE COIN3D_LINKFLAGS
  )
  
  set( COIN3D_CONFIG_COMMAND_LIBS "--libs" )
  execute_process(
    COMMAND         "${COIN3D_CONFIG_COMMAND}" "${COIN3D_CONFIG_COMMAND_LIBS}"
    OUTPUT_VARIABLE COIN3D_LINKLIBS
  ) 

  # message( "COMMAND:   ${COIN3D_CONFIG_COMMAND} ${COIN3D_CONFIG_COMMAND_CPPFLAG}" )
  message( "CPPFLAGS:  ${COIN3D_CPPFLAGS}"  )
  message( "LINKFLAGS: ${COIN3D_LINKFLAGS}" )
  message( "LINKLIBS:  ${COIN3D_LINKLIBS}"  )  
  
endif()

set( COIN3D_CFLAGS "" )

else()
# Coin_FOUND

endif()

if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
  set( STARE_CPPFLAGS  "-std=c++11 -g -Wall -D_BOOL_EXISTS -D__macosx -UDIAGNOSE -fPIC -I/home/mrilee/workspace/STARE-CMAKE/include/" )
  set( STARE_CFLAGS    "-g -Wall -D_BOOL_EXISTS -D__macosx -UDIAGNOSE -fPIC -I/home/mrilee/workspace/STARE-CMAKE/include/" )
  set( STARE_LINKFLAGS "-L/home/mrilee/workspace/STARE-CMAKE/build/default/src/" )  
  set( STARE_LINKLIBS "-lSTARE" )
elseif(UNIX)
  set( STARE_CPPFLAGS  "-std=c++11 -g -Wall -D_BOOL_EXISTS -D__unix -UDIAGNOSE -fPIC -I/home/mrilee/workspace/STARE-CMAKE/include/" )
  set( STARE_CFLAGS    "-g -Wall -D_BOOL_EXISTS -D__unix -UDIAGNOSE -fPIC -I/home/mrilee/workspace/STARE-CMAKE/include/" )
  set( STARE_LINKFLAGS "-L/home/mrilee/workspace/STARE-CMAKE/build/default/src/" )
  set( STARE_LINKLIBS "-lSTARE" )
else()
  message(FATAL_ERROR "Platform ${CMAKE_SYSTEM_NAME} not handled.")
endif()

set( CMAKE_CXX_FLAGS " ${STARE_CPPFLAGS} ${COIN3D_CPPFLAGS} ${CMAKE_CXX_FLAGS} "  )
set( CMAKE_C_FLAGS   " ${STARE_CFLAGS}   ${COIN3D_CFLAGS}   ${CMAKE_C_FLAGS} "  )
message( "CMAKE_CXX_FLAGS = ${CMAKE_CXX_FLAGS}" )
message( "CMAKE_C_FLAGS   = ${CMAKE_C_FLAGS}"   )

set( CMAKE_EXE_LINKER_FLAGS "${STARE_LINKFLAGS} ${COIN3D_LINKFLAGS} ${CMAKE_EXE_LINKER_FLAGS} ${COIN3D_LINKLIBS} ${STARE_LINKLIBS}" )
message( "CMAKE_EXE_LINKER_FLAGS = ${CMAKE_EXE_LINKER_FLAGS}" )

# add_executable(VizSTARE VizSTARE.cpp)
# add_library( VizSTARE STATIC ${STARE_SrcFiles} )
add_library( VizSTARE STATIC VizSTARE.cpp )
target_include_directories( VizSTARE PUBLIC VizSTARE /usr/include /usr/include/qt5 /usr/include/qt5/QtCore /usr/include/qt5/QtGui /usr/local/Coin3D/include )

add_executable(      VizSTARE_TestIntervals VizSTARE_TestIntervals.cpp )
target_link_libraries( VizSTARE_TestIntervals VizSTARE SoQt::SoQt )
# target_link_libraries(VizHTM_main SoQt::SoQt VizHTM_LIB ${STARE_LINK_LIB} ${GEOMPACK_LIBRARY_LIB} ${HDF_LIBRARIES} shp gfortran erfa )
target_include_directories( VizSTARE_TestIntervals PUBLIC VizSTARE /usr/include /usr/include/qt5 /usr/include/qt5/QtCore /usr/include/qt5/QtGui /usr/local/Coin3D/include )


