#include "basic_node/basic_node.hpp"
using namespace std::chrono_literals;

BasicNode::BasicNode() : rclcpp::Node("basic_node") {
  std::cout << "Basic Node Constructor" << std::endl;

  int8_pub_ =
      this->create_publisher<std_msgs::msg::Int8>("/basic_node/int8", 10);

  int8_sub_ = this->create_subscription<std_msgs::msg::Int8>(
      "/basic_node/int8", 10,
      std::bind(&BasicNode::int8_callback, this, std::placeholders::_1));

  update_timer_ = this->create_wall_timer(
      1000ms, std::bind(&BasicNode::timer_callback, this));
}

BasicNode::~BasicNode() {}

void BasicNode::timer_callback() {
  static int cnt = 0;
  std_msgs::msg::Int8 msg;
  msg.data = cnt;
  // Publish
  int8_pub_->publish(msg);
  std::cout << "Publish int8 : " << (int)msg.data << std::endl;
  cnt++;
}

void BasicNode::int8_callback(std_msgs::msg::Int8::SharedPtr msg) {
  std::cout << "Subscribed int8 : " << (int)msg->data << std::endl;
}

int main(int argc, char *argv[]) {
  rclcpp::init(argc, argv);
  auto node = std::make_shared<BasicNode>();
  while (rclcpp::ok()) {
    rclcpp::spin_some(node);
  }
  return 0;
}
