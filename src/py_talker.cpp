#include <chrono>
#include <functional>
#include <memory>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

using namespace std::chrono_literals;

// ROS 2のノードを表すクラスです。
class PyTalker : public rclcpp::Node
{
public:
  PyTalker()
  : Node("py_talker"), count_(0)
  {
    // String型のメッセージをpy_chatterトピックへ送るPublisherを作ります。
    // 「10」は、送信待ちメッセージを保持するキューの深さです。
    publisher_ = create_publisher<std_msgs::msg::String>("py_chatter", 10);

    // 0.1秒ごとにpublish_message()を呼び出すタイマーを作ります。
    timer_ = create_wall_timer(
      100ms, std::bind(&PyTalker::publish_message, this));
  }

private:
  void publish_message()
  {
    // 送信する文字列メッセージを作成します。
    auto message = std_msgs::msg::String();
    message.data = "Hello world";

    // メッセージを送信し、送信内容と回数をROS 2のログに表示します。
    ++count_;
    RCLCPP_INFO(get_logger(), "Publishing: '%s' %d", message.data.c_str(), count_);
    publisher_->publish(message);
  }

  // Publisherとタイマーをメンバー変数にして、ノードが動作している間保持します。
  rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher_;
  rclcpp::TimerBase::SharedPtr timer_;
  int count_;
};

int main(int argc, char * argv[])
{
  // ROS 2を初期化し、コマンドライン引数をROS 2に渡します。
  rclcpp::init(argc, argv);

  // ノードを実行し、タイマーなどのイベントを待ち受けます。
  rclcpp::spin(std::make_shared<PyTalker>());

  // ノードの終了後にROS 2を終了します。
  rclcpp::shutdown();
  return 0;
}