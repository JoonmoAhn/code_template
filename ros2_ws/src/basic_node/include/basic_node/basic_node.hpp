#pragma once

#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/int8.hpp>

class BasicNode : public rclcpp::Node {
public:
  BasicNode();
  ~BasicNode();

private:
  rclcpp::TimerBase::SharedPtr update_timer_;

  // Publisher
  rclcpp::Publisher<std_msgs::msg::Int8>::SharedPtr int8_pub_;

  // Subscriber
  rclcpp::Subscription<std_msgs::msg::Int8>::SharedPtr int8_sub_;

  // Callback
  void int8_callback(std_msgs::msg::Int8::SharedPtr msg);
  void timer_callback();
};
