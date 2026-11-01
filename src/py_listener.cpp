#include <memory>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

// ROS 2のメッセージを受信するノードを表すクラスです。
class PyListener : public rclcpp::Node
{
public:
  PyListener()
  : Node("py_listener")
  {
    // py_chatterトピックのStringメッセージを受信するSubscriptionを作ります。
    // メッセージを受信するたびにlisten()が呼び出されます。
    // 「10」は、受信待ちメッセージを保持するキューの深さです。
    subscription_ = create_subscription<std_msgs::msg::String>(
      "py_chatter", 10,
      std::bind(&PyListener::listen, this, std::placeholders::_1));
  }

private:
  void listen(const std_msgs::msg::String::SharedPtr message) const
  {
    // 受信したメッセージの内容をROS 2のログに表示します。
    RCLCPP_INFO(get_logger(), "%s", message->data.c_str());
  }

  // ノードが動作している間、Subscriptionを保持します。
  rclcpp::Subscription<std_msgs::msg::String>::SharedPtr subscription_;
};

int main(int argc, char * argv[])
{
  // ROS 2を初期化し、コマンドライン引数をROS 2に渡します。
  rclcpp::init(argc, argv);

  // ノードを実行し、メッセージ受信などのイベントを待ち受けます。
  rclcpp::spin(std::make_shared<PyListener>());

  // ノードの終了後にROS 2を終了します。
  rclcpp::shutdown();
  return 0;
}
