#include <memory>
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include <iostream>
#define be RMW_QOS_POLICY_RELIABILITY_BEST_EFFORT

class MinimalSubscriber : public rclcpp::Node
{
public:
  MinimalSubscriber()
  : Node("int_sub"),
    best_effort(rclcpp::KeepLast(10))
    {
    subscription_ = this->create_subscription<std_msgs::msg::String>(
      "lvbool",best_effort.reliability(be),
      [this](const std_msgs::msg::String::SharedPtr msg){
      RCLCPP_INFO(this->get_logger(), "I heard: %s", msg->data.c_str());
      std::cout<<"callback received\n";
    });
  }

private:
  rclcpp::Subscription<std_msgs::msg::String>::SharedPtr subscription_;
  rclcpp::QoS best_effort;


};


int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<MinimalSubscriber>());
  rclcpp::shutdown();
  return 0;
}
