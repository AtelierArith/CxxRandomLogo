add_library(util util.cpp)
target_compile_features(myproject_compiler_flags INTERFACE cxx_std_17)
target_include_directories(util INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(util PUBLIC myproject_compiler_flags)

add_library(affine affine.cpp)
target_compile_features(myproject_compiler_flags INTERFACE cxx_std_17)
target_include_directories(affine INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(affine PUBLIC Eigen3::Eigen myproject_compiler_flags)

add_library(ifs_sigma_factor ifs_sigma_factor.cpp)
target_compile_features(myproject_compiler_flags INTERFACE cxx_std_17)
target_include_directories(ifs_sigma_factor INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(ifs_sigma_factor PUBLIC affine util myproject_compiler_flags)

add_library(ifs ifs.cpp)
target_compile_features(myproject_compiler_flags INTERFACE cxx_std_17)
target_include_directories(ifs INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(ifs PUBLIC util affine ifs_sigma_factor myproject_compiler_flags)

add_library(point_generation point_generation.cpp)
target_compile_features(myproject_compiler_flags INTERFACE cxx_std_17)
target_include_directories(point_generation INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(point_generation PUBLIC ifs ifs_sigma_factor myproject_compiler_flags)

# Julia interface
find_package(JlCxx)
get_target_property(JlCxx_location JlCxx::cxxwrap_julia LOCATION)
get_filename_component(JlCxx_location ${JlCxx_location} DIRECTORY)
message(STATUS "Found JlCxx at ${JlCxx_location}")
message(STATUS "Julia_LIBRARY at ${Julia_LIBRARY}")

add_library(jl_app SHARED jl_app.cpp)
target_link_libraries(jl_app point_generation JlCxx::cxxwrap_julia JlCxx::cxxwrap_julia_stl ${Julia_LIBRARY})

