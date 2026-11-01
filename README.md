# py_topic_cpp

`py_topic_cpp`は、ROS 2のトピック通信を学ぶためのC++サンプルパッケージです。文字列メッセージを定期的に送信するノードと、受信して表示するノードを使って、PublisherとSubscriberの基本を確認できます。

## ノードの説明

| 実行コマンド | ノード名 | 説明 |
| --- | --- | --- |
| `ros2 run py_topic_cpp py_talker` | `py_talker` | 0.1秒ごとに`Hello world`を送信し、送信内容と回数をログに表示します。 |
| `ros2 run py_topic_cpp py_listener` | `py_listener` | 受信した文字列をROS 2のログに表示します。 |

## トピックの説明

| ノード | トピック | 型 | 通信 |
| --- | --- | --- | --- |
| `py_talker` | `py_chatter` | `std_msgs/msg/String` | パブリッシュ |
| `py_listener` | `py_chatter` | `std_msgs/msg/String` | サブスクライブ |

両ノードはキュー深度10で通信します。`py_talker`が送信するメッセージを`py_listener`が受信して表示します。

## 実行方法

以下は、ワークスペースが`~/ros2_ws`にあり、ROS 2がインストール済みの場合の手順です。`<ros2ディストリビューション>`は、利用環境に合わせて`humble`や`jazzy`などに置き換えてください。

### 1. ビルド

```bash
cd ~/ros2_ws
source /opt/ros/<ros2ディストリビューション>/setup.bash
colcon build --packages-select py_topic_cpp
source install/setup.bash
```

### 2. ノードの起動

端末を2つ開き、それぞれでROS 2とワークスペースの環境を読み込んでください。

**端末1（受信ノード）**

```bash
cd ~/ros2_ws
source /opt/ros/<ros2ディストリビューション>/setup.bash
source install/setup.bash
ros2 run py_topic_cpp py_listener
```

**端末2（送信ノード）**

```bash
cd ~/ros2_ws
source /opt/ros/<ros2ディストリビューション>/setup.bash
source install/setup.bash
ros2 run py_topic_cpp py_talker
```

受信ノードを起動した端末に`Hello world`が表示されます。終了するには各端末で`Ctrl+C`を押してください。

## ROS 2 C++パッケージの作成手順

以下は、`ament_cmake`を使ってC++パッケージを作成し、ノードを実行するまでの基本的な流れです。ここではパッケージ名を`sample_cpp_pkg`とします。作成するノードに合わせてパッケージ名や依存パッケージを変更してください。

### 1. ワークスペースの`src`に移動

```bash
source /opt/ros/<ros2ディストリビューション>/setup.bash
mkdir -p ~/ros2_ws/src
cd ~/ros2_ws/src
```

### 2. C++パッケージを作成

```bash
ros2 pkg create --build-type ament_cmake --dependencies rclcpp std_msgs sample_cpp_pkg
```

`--build-type ament_cmake`でCMakeを使うC++パッケージを作成します。`--dependencies`には、ノードが利用するROS 2パッケージを指定します。作成後、主に次のファイルやディレクトリが用意されます。

| ファイル・ディレクトリ | 役割 |
| --- | --- |
| `sample_cpp_pkg/src/` | C++ノードのソースファイルを置く場所 |
| `CMakeLists.txt` | C++ソースのビルド方法、依存関係、インストール先を定義 |
| `package.xml` | パッケージ情報と依存関係を定義 |

### 3. C++ノードを作成

`sample_cpp_pkg/src/`にノードのソースファイル（例：`sample_node.cpp`）を作成します。ノードの処理を実装し、`main`関数でROS 2を初期化してノードを実行します。

### 4. ビルドして実行

`CMakeLists.txt`に実行ファイルと依存関係、インストール先を記載した後、ワークスペースをビルドします。

```bash
cd ~/ros2_ws
colcon build --packages-select sample_cpp_pkg
source install/setup.bash
ros2 run sample_cpp_pkg sample_node
```

## CMakeLists.txtの記載方法

C++ノードをビルドして`ros2 run`で起動するには、`CMakeLists.txt`に主に次の設定を記載します。`sample_node`は実行ファイル名、`src/sample_node.cpp`はソースファイルのパスです。

```cmake
# ノードが利用するROS 2パッケージを見つけます。
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)

# C++ソースから実行ファイルを作成します。
add_executable(sample_node src/sample_node.cpp)

# 実行ファイルが利用するROS 2パッケージを指定します。
ament_target_dependencies(sample_node rclcpp std_msgs)

# ros2 runで起動できるよう、パッケージの実行ファイル用フォルダへインストールします。
install(TARGETS
  sample_node
  DESTINATION lib/${PROJECT_NAME}
)
```

`find_package`で見つけた依存パッケージは`ament_target_dependencies`にも指定します。ソースファイルを追加した場合は、そのノードごとに`add_executable`、依存関係の指定、`install`への登録が必要です。また、同じ依存関係を`package.xml`にも記載します。`ament_package()`は`CMakeLists.txt`の末尾に置き、パッケージ情報をamentに登録します。