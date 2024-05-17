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
