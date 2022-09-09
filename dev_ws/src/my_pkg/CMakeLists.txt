cmake_minimum_required(VERSION 3.8)
project(my_pkg)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(example_interfaces REQUIRED)

add_executable(node src/first_node.cpp)
ament_target_dependencies(node rclcpp std_msgs)

add_executable(oop_node src/oop_node.cpp)
ament_target_dependencies(oop_node rclcpp std_msgs)

add_executable(pub_node src/publisher.cpp)
ament_target_dependencies(pub_node rclcpp std_msgs example_interfaces)

add_executable(sub_node src/subscriber.cpp)
ament_target_dependencies(sub_node rclcpp std_msgs example_interfaces)

add_executable(num_pub src/num_pub.cpp)
ament_target_dependencies(num_pub rclcpp std_msgs)

add_executable(num_sub_count_pub src/num_sub_and_count_pub.cpp)
ament_target_dependencies(num_sub_count_pub rclcpp std_msgs example_interfaces)

add_executable(sum_server src/add2int_server.cpp)
ament_target_dependencies(sum_server rclcpp std_msgs example_interfaces)

add_executable(sum_client src/add2int_client.cpp)
ament_target_dependencies(sum_client rclcpp std_msgs example_interfaces)

add_executable(sum_client2 src/numsclient.cpp)
ament_target_dependencies(sum_client2 rclcpp std_msgs example_interfaces)

add_executable(reset_count src/reset_count.cpp)
ament_target_dependencies(reset_count rclcpp std_msgs example_interfaces)

install(TARGETS
  node
  oop_node
  pub_node
  sub_node
  num_pub
  num_sub_count_pub
  sum_server
  sum_client
  sum_client2
  reset_count
  DESTINATION lib/${PROJECT_NAME}
)

ament_package()
