cmake_minimum_required(VERSION 3.20)

# 1. Project Metadata
project(ulsp 
    VERSION 1.0.0 
    DESCRIPTION "Ultra Low-latency Systems Profiler"
    LANGUAGES CXX
)

# 2. Options
option(ULSP_BUILD_SHARED "Build ulsp as a shared library" OFF)
option(ULSP_BUILD_EXAMPLES "Build example applications" ON)

# 3. Define the Library Target
add_library(ulsp_benchmark) # Implementation type decided by sources/options

# create a namespaced alias (ulsp::benchmark) for internal usage matches external usage
add_library(ulsp::benchmark ALIAS ulsp_benchmark)

# 4. Sources
target_sources(ulsp_benchmark
    PRIVATE
        src/benchmark/registry.cpp
        src/benchmark/runner.cpp
        src/core/timer.cpp
        src/core/stats.cpp
)

# 5. Compiler Settings (C++20 Strict)
target_compile_features(ulsp_benchmark PUBLIC cxx_std_20)
set_target_properties(ulsp_benchmark PROPERTIES
    CXX_EXTENSIONS OFF
    VISIBILITY_INLINES_HIDDEN ON
    CXX_VISIBILITY_PRESET hidden
)

# 6. Include Directories (The critical part for installation)
# --- Include Directories ---
target_include_directories(ulsp_benchmark
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include>  # <--- ADD THIS LINE
        $<INSTALL_INTERFACE:include>
    PRIVATE
        src
)
# 7. Symbol Visibility (Windows DLL Support)
include(GenerateExportHeader)
generate_export_header(ulsp_benchmark
    BASE_NAME ulsp
    EXPORT_FILE_NAME include/ulsp/ulsp_export.h
)

# 8. Version Header
configure_file(cmake/version.h.in include/ulsp/version.h @ONLY)

# 9. Installation Rules (Production Packaging)
include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

# Install the Binary (lib/dll)
install(TARGETS ulsp_benchmark
    EXPORT ulspTargets
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

# Install the Headers
install(DIRECTORY include/ulsp
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

# 10. Generate CMake Config Files (so find_package works)
set(ULSP_CONFIG_FILE "${CMAKE_CURRENT_BINARY_DIR}/ulspConfig.cmake")
set(ULSP_VERSION_FILE "${CMAKE_CURRENT_BINARY_DIR}/ulspConfigVersion.cmake")

write_basic_package_version_file(
    "${ULSP_VERSION_FILE}"
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY SameMajorVersion
)

configure_package_config_file(
    cmake/ulspConfig.cmake.in
    "${ULSP_CONFIG_FILE}"
    INSTALL_DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/ulsp"
)

# Install the CMake Configs
install(EXPORT ulspTargets
    FILE ulspTargets.cmake
    NAMESPACE ulsp::
    DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/ulsp"
)

install(FILES
    "${ULSP_CONFIG_FILE}"
    "${ULSP_VERSION_FILE}"
    DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/ulsp"
)

# 11. Examples
if(ULSP_BUILD_EXAMPLES)
    add_executable(ulsp_basic examples/basic_usage.cpp)
    target_link_libraries(ulsp_basic PRIVATE ulsp::benchmark)
endif()