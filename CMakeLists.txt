cmake_minimum_required(VERSION 3.5)
project(bcu C CXX)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (CMAKE_HOST_WIN32)
        set(WINDOWS 1)
elseif (CMAKE_HOST_APPLE)
        set(MACOS 1)
elseif (CMAKE_HOST_UNIX)
        set(LINUX 1)
endif ()

find_package(PkgConfig REQUIRED)
pkg_check_modules(LIBFTDI REQUIRED libftdi1)
pkg_check_modules(LIBYAML REQUIRED yaml-0.1)
pkg_check_modules(LIBUSB REQUIRED libusb-1.0)

set(LIBBCU_CORE_SOURCES
        port.c
        chip.c
        board.c
        bcu_parser.c
        bcu_yaml.c
        bcu_ftdi_eeprom.c
)

include_directories(
        ${PROJECT_SOURCE_DIR}
        ${PROJECT_SOURCE_DIR}/libbcu
        ${LIBUSB_INCLUDE_DIRS}
        ${LIBFTDI_INCLUDE_DIRS}
        ${LIBYAML_INCLUDEDIR}
)
link_directories(${LIBUSB_LIBRARY_DIRS} ${LIBFTDI_LIBRARY_DIRS} ${LIBYAML_LIBRARY_DIRS})

if (LINUX)
        execute_process(COMMAND ${PROJECT_SOURCE_DIR}/create_version_h.sh ${PROJECT_SOURCE_DIR})
elseif (MACOS)
        execute_process(COMMAND sh ${PROJECT_SOURCE_DIR}/create_version_h.sh ${PROJECT_SOURCE_DIR})
endif ()

add_library(bcu_shared SHARED ${LIBBCU_CORE_SOURCES})
set_target_properties(bcu_shared PROPERTIES OUTPUT_NAME bcu)

add_library(bcu_static STATIC ${LIBBCU_CORE_SOURCES})
set_target_properties(bcu_static PROPERTIES OUTPUT_NAME bcu)
target_compile_definitions(bcu_shared PRIVATE LIBBCU_NO_PRINT=1)
target_compile_definitions(bcu_static PRIVATE LIBBCU_NO_PRINT=1)

if (LINUX)
        target_link_libraries(bcu_shared ${LIBUSB_LIBRARIES} ${LIBFTDI_LIBRARIES} ${LIBYAML_LIBRARIES} -lpthread -lm -ldl)
        target_link_libraries(bcu_static ${LIBUSB_LIBRARIES} ${LIBFTDI_LIBRARIES} ${LIBYAML_LIBRARIES} -lpthread -lm -ldl)
elseif (MACOS)
        target_link_libraries(bcu_shared ${LIBUSB_LIBDIR}/lib${LIBUSB_LIBRARIES}.dylib ${LIBFTDI_LIBDIR}/${LIBFTDI_MODULE_NAME}.dylib ${LIBYAML_LIBDIR}/lib${LIBYAML_LIBRARIES}.dylib -lpthread -lm)
        target_link_libraries(bcu_static ${LIBUSB_LIBDIR}/lib${LIBUSB_LIBRARIES}.dylib ${LIBFTDI_LIBDIR}/${LIBFTDI_MODULE_NAME}.dylib ${LIBYAML_LIBDIR}/lib${LIBYAML_LIBRARIES}.dylib -lpthread -lm)
endif ()

if (LINUX)
        add_executable(bcu bcu.c)
        target_link_libraries(bcu bcu_static)
        install(TARGETS bcu DESTINATION bin)
elseif (MACOS)
        add_executable(bcu_mac bcu.c)
        target_link_libraries(bcu_mac bcu_static)
        install(TARGETS bcu_mac DESTINATION bin)
endif ()

install(TARGETS bcu_shared bcu_static
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
        RUNTIME DESTINATION bin)
install(FILES libbcu/libbcu.h DESTINATION include)
