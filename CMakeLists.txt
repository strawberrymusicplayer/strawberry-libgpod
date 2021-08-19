project(libgpod)

cmake_minimum_required(VERSION 3.0)

include(CheckIncludeFiles)
include(FindPkgConfig)
include(GNUInstallDirs)

list(APPEND COMPILE_OPTIONS
  -std=c99
  -Wall
  -Wextra
  -Wpedantic
  -Wunused
  -Wshadow
  -Wuninitialized
  -Wredundant-decls
  -Winit-self
  -Wmissing-include-dirs
  -Wmissing-declarations
  -Wstrict-overflow=2
  -Wunused-parameter
  -Wformat=2
  -Wdisabled-optimization
)

if(CMAKE_C_COMPILER_ID MATCHES "GNU")
  list(APPEND COMPILE_OPTIONS -Wno-cast-function-type)
endif()

option(BUILD_WERROR "Build with -Werror" OFF)
if(BUILD_WERROR)
  list(APPEND COMPILE_OPTIONS -Werror)
endif(BUILD_WERROR)

add_compile_options(${COMPILE_OPTIONS})

set(SOURCES
  src/itdb_thumb.c
  src/itdb_track.c
  src/itdb_zlib.c
  src/pixmaps.c
  src/itdb_itunesdb.c
  src/db-parse-context.c
  src/db-artwork-parser.c
  src/db-artwork-writer.c
  src/itdb_artwork.c
  src/itdb_iphone.c
  src/itdb_playlist.c
  src/rijndael.c
  src/ithumb-writer.c
  src/itdb_tzinfo.c
  src/itdb_photoalbum.c
  src/itdb_hash58.c
  src/db-image-parser.c
  src/itdb_hash72.c
  src/itdb_sqlite.c
  src/itdb_device.c
  src/itdb_sysinfo_extended_parser.c
  src/itdb_chapterdata.c
  src/db-artwork-debug.c
  src/itdb_hashAB.c
  src/itdb_plist.c
)

pkg_check_modules(GLIB REQUIRED glib-2.0)
pkg_check_modules(GMODULE REQUIRED gmodule-2.0)
pkg_check_modules(GOBJECT REQUIRED gobject-2.0)
pkg_check_modules(GDK_PIXBUF gdk-pixbuf-2.0)
pkg_search_module(LIBPLIST REQUIRED libplist-2.0 libplist)
pkg_check_modules(LIBIMOBILEDEVICE libimobiledevice-1.0)
pkg_check_modules(SQLITE3 REQUIRED sqlite3)
pkg_check_modules(ZLIB REQUIRED zlib)
check_include_files(unistd.h HAVE_UNISTD_H)

option(ENABLE_GDKPIXBUF "Build with gdk-pixbuf support" ${GDK_PIXBUF_FOUND})
option(ENABLE_LIBIMOBILEDEVICE "Build with libimobiledevice support" ${LIBIMOBILEDEVICE_FOUND})

set(HAVE_GDKPIXBUF ${ENABLE_GDKPIXBUF})
set(HAVE_LIBIMOBILEDEVICE ${ENABLE_LIBIMOBILEDEVICE})

set(LIBGPOD_BLOB_DIR "${CMAKE_INSTALL_PREFIX}/libgpod")
set(VERSION 0.8.0)

if(HAVE_GDKPIXBUF)
  set(GDKPIXBUF_REQ "gdk-pixbuf-2.0")
endif()

if(HAVE_LIBIMOBILEDEVICE)
  set(LIBIMOBILEDEVICE_REQ "libimobiledevice-1.0")
endif()

if(GLIB_VERSION GREATER_EQUAL 2.68)
  set(HAVE_G_MEMDUP2 ON)
endif()

configure_file(config.h.in config.h)
configure_file(libgpod-1.0.pc.in libgpod-1.0.pc @ONLY)

add_definitions(-DGETTEXT_PACKAGE="\\"libgpod\\"")

if (${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
  add_definitions(-DHAVE_STRUCT_TM_TM_GMTOFF)
endif()
#add_definitions(-DHAVE_LOCALTIME_R)

add_library(gpod SHARED ${SOURCES})

target_include_directories(gpod SYSTEM PRIVATE
  ${GLIB_INCLUDE_DIRS}
  ${GMODULE_INCLUDE_DIRS}
  ${GOBJECT_INCLUDE_DIRS}
  ${LIBPLIST_INCLUDE_DIRS}
  ${SQLITE3_INCLUDE_DIRS}
  ${ZLIB_INCLUDE_DIRS}
)

target_include_directories(gpod PRIVATE
  ${CMAKE_CURRENT_BINARY_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_link_directories(gpod PRIVATE
  ${GLIB_LIBRARY_DIRS}
  ${GMODULE_LIBRARY_DIRS}
  ${GOBJECT_LIBRARY_DIRS}
  ${LIBPLIST_LIBRARY_DIRS}
  ${SQLITE3_LIBRARY_DIRS}
  ${ZLIB_LIBRARY_DIRS}
)

target_link_libraries(gpod PRIVATE
  ${GLIB_LIBRARIES}
  ${GMODULE_LIBRARIES}
  ${GOBJECT_LIBRARIES}
  ${LIBPLIST_LIBRARIES}
  ${SQLITE3_LIBRARIES}
  ${ZLIB_LIBRARIES}
)

if(ENABLE_GDKPIXBUF)
  target_include_directories(gpod SYSTEM PRIVATE ${GDK_PIXBUF_INCLUDE_DIRS})
  target_link_directories(gpod PRIVATE ${GDK_PIXBUF_LIBRARY_DIRS})
  target_link_libraries(gpod PRIVATE ${GDK_PIXBUF_LIBRARIES})
endif()

if(ENABLE_LIBIMOBILEDEVICE)
  target_include_directories(gpod SYSTEM PRIVATE ${LIBIMOBILEDEVICE_INCLUDE_DIRS})
  target_link_directories(gpod PRIVATE ${LIBIMOBILEDEVICE_LIBRARY_DIRS})
  target_link_libraries(gpod PRIVATE ${LIBIMOBILEDEVICE_LIBRARIES})
endif()

install(TARGETS gpod
  RUNTIME DESTINATION bin
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
)

install(
  DIRECTORY src/
  DESTINATION include/gpod-1.0/gpod
  FILES_MATCHING PATTERN itdb.h
)

install(
  FILES ${CMAKE_CURRENT_BINARY_DIR}/libgpod-1.0.pc
  DESTINATION lib/pkgconfig
)
