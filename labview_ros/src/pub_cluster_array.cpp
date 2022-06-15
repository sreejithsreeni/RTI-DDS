
// common stl includes
#include <chrono>
#include <memory>
#include "rclcpp/rclcpp.hpp"
#include "labview_ros/msg/clusterdemo.hpp"
#include <string>
using namespace std::chrono_literals;


class MinimalPublisher : public rclcpp::Node
{
public:

  MinimalPublisher()
  : Node("ros_publisher")
  {
    publisher_ = this->create_publisher<labview_ros::msg::Clusterdemo>("roscluster", 10);

    //init the timer ptr with a wall timer object.

    timer_ = this->create_wall_timer(
      500ms, [this](){
        // create string obj.
        auto message = labview_ros::msg::Clusterdemo();
        message.x = this->count;
        message.y= "test";
        message.z = {84,3,23,23.4,21.4,2};
        RCLCPP_INFO(this->get_logger(), "Publishing: %d , %s", message.x, message.y.c_str());
        int size=(sizeof(message))/sizeof(message.z[0])-2;
        printf("size%d\n",size);
        for(int i=0;i<size;i++)
        {
          printf("%lf\n",message.z[i]);
          printf("printintg number--%d\n",i);
        }

        //publish message
        publisher_->publish(message);
        this->count++;
      });
  }

private:
  int count=0;
  //shared ptr of a timer
  rclcpp::TimerBase::SharedPtr timer_;
  rclcpp::Publisher<labview_ros::msg::Clusterdemo>::SharedPtr publisher_;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<MinimalPublisher>());
  rclcpp::shutdown();
  return 0;
}
