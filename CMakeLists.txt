cmake_minimum_required(VERSION 3.8)
project(py_topic_cpp)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)

# C++ソースから実行可能ファイル（ノード）を作成します。
add_executable(py_talker src/py_talker.cpp)
# ノードが利用するROS 2のライブラリを指定します。
ament_target_dependencies(py_talker rclcpp std_msgs)

# C++ソースからサブスクライブノードの実行ファイルを作成します。
add_executable(py_listener src/py_listener.cpp)
# サブスクライブノードが利用するROS 2のライブラリを指定します。
ament_target_dependencies(py_listener rclcpp std_msgs)

# ros2 runで実行できるよう、パッケージの実行ファイル用フォルダへインストールします。
install(TARGETS
  py_talker
  py_listener
  DESTINATION lib/${PROJECT_NAME}
)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the linter which checks for copyrights
  # comment the line when a copyright and license is added to all source files
  set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # comment the line when this package is in a git repo and when
  # a copyright and license is added to all source files
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()
