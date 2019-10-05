cmake_minimum_required(VERSION 3.5)
project(faketimer VERSION 1.0.0 LANGUAGES CXX)

list(INSERT CMAKE_MODULE_PATH 0 ${CMAKE_SOURCE_DIR}/cmake)

add_library(faketimer
    src/faketimer.cpp
)

add_library(FakeTimer::faketimer ALIAS faketimer)

target_compile_features(faketimer PRIVATE cxx_auto_type)
target_compile_options(faketimer PRIVATE $<$<CXX_COMPILER_ID:GNU>:-Wall>)

# find opendb package
find_package(FakeDB 1.0 REQUIRED)

target_include_directories(faketimer
    PUBLIC
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        ${PROJECT_BINARY_DIR}/include
        /usr/local/include
)

target_link_libraries(faketimer
    PRIVATE
        fakedb
)

include(GNUInstallDirs)
set(INSTALL_CONFIGDIR ${CMAKE_INSTALL_LIBDIR}/cmake/FakeTimer)

install(TARGETS faketimer
    EXPORT faketimer-targets
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

set_target_properties(faketimer PROPERTIES EXPORT_NAME FakeTimer)

install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

install(EXPORT faketimer-targets
  FILE
    FakeTimerTargets.cmake
  NAMESPACE
    FakeTimer::
  DESTINATION
    ${INSTALL_CONFIGDIR}
)

include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    ${CMAKE_CURRENT_BINARY_DIR}/FakeTimerConfigVersion.cmake
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY AnyNewerVersion
)

configure_package_config_file(${CMAKE_CURRENT_LIST_DIR}/cmake/FakeTimerConfig.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/FakeTimerConfig.cmake
    INSTALL_DESTINATION ${INSTALL_CONFIGDIR}
)

install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/FakeTimerConfig.cmake
    ${CMAKE_CURRENT_BINARY_DIR}/FakeTimerConfigVersion.cmake
    DESTINATION ${INSTALL_CONFIGDIR}
)

export(EXPORT faketimer-targets FILE ${CMAKE_CURRENT_BINARY_DIR}/FakeTimerTargets.cmake NAMESPACE FakeTimer::)

export(PACKAGE FakeTimer)