cmake_minimum_required(VERSION 3.5)
project(labview_ros)

# Default to C99
if(NOT CMAKE_C_STANDARD)
  set(CMAKE_C_STANDARD 99)
endif()

# Default to C++14
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 14)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the linter which checks for copyrights
  # uncomment the line when a copyright and license is not present in all source files
  #set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # uncomment the line when this package is not in a git repo
  #set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

find_package(rosidl_default_generators REQUIRED)

rosidl_generate_interfaces(${PROJECT_NAME}
  "msg/Myint.msg"
  "msg/Clusterdemo.msg"
  "msg/Intarray.msg"
 )


ament_package()

add_executable(sub_float64 src/sub_float64.cpp)
add_executable(pub_int32 src/pub_int32.cpp)
add_executable(pub_stri src/pub_stri.cpp)
add_executable(sub_str src/sub_str.cpp)
add_executable(sub_int32 src/sub_int32.cpp)
add_executable(sub_bool src/sub_bool.cpp)
add_executable(pub_cluster src/pub_cluster.cpp)
add_executable(sub_cluster src/sub_cluster.cpp)

                
ament_target_dependencies(sub_float64 rclcpp)
ament_target_dependencies(pub_int32 rclcpp)
ament_target_dependencies(pub_stri rclcpp)
ament_target_dependencies(sub_str rclcpp)
ament_target_dependencies(sub_int32 rclcpp)
ament_target_dependencies(sub_bool rclcpp)
ament_target_dependencies(pub_cluster rclcpp std_msgs)
ament_target_dependencies(sub_cluster rclcpp std_msgs )

rosidl_target_interfaces(pub_cluster ${PROJECT_NAME} "rosidl_typesupport_cpp")
rosidl_target_interfaces(sub_cluster ${PROJECT_NAME} "rosidl_typesupport_cpp")



install(TARGETS 
      sub_float64
      pub_int32
      pub_stri
      sub_str
      sub_int32
      sub_bool
      pub_cluster
      sub_cluster
      DESTINATION lib/${PROJECT_NAME}
      )

