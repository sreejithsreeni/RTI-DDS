#include <memory>
#include "rclcpp/rclcpp.hpp"
#include "labview_ros/msg/clusterdemo.hpp"

#define be RMW_QOS_POLICY_RELIABILITY_BEST_EFFORT

class MinimalSubscriber : public rclcpp::Node
{
public:
  MinimalSubscriber()
  : Node("cluster_sub"),
    best_effort(rclcpp::KeepLast(10))
  {
    subscription_ = this->create_subscription<labview_ros::msg::Clusterdemo>(
      "lvcluster", best_effort.reliability(be), [this](const labview_ros::msg::Clusterdemo::SharedPtr msg){
      RCLCPP_INFO(this->get_logger(), "I heard: %d and %s", msg->x,msg->y.c_str());
      int size = (sizeof(*msg))/(sizeof(msg->z[0]))-2;
      printf("size\n%d",size);
      for(int i=0;i<size;i++)
      {
        printf("%lf\n",msg->z[i]);
      }
    });
  }

private:
  rclcpp::Subscription<labview_ros::msg::Clusterdemo>::SharedPtr subscription_;

  rclcpp::QoS best_effort;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<ba>());
  rclcpp::shutdown();
  return 0;
}
