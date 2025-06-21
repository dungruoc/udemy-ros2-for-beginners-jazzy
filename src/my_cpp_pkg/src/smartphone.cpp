#include "rclcpp/rclcpp.hpp"
#include "example_interfaces/msg/string.hpp"


class SmartphoneNode : public rclcpp::Node {
    public:
        SmartphoneNode() : rclcpp::Node("smartphone") {
            subscriber = this->
                create_subscription<example_interfaces::msg::String>(
                    "robot_news",
                    10,
                    std::bind(&SmartphoneNode::callbackRobotNews, this, std::placeholders::_1)
                );
            RCLCPP_INFO(this->get_logger(), "Smartphone started");
        }
    
    private:
        void callbackRobotNews(const example_interfaces::msg::String::SharedPtr msg) {
            RCLCPP_INFO(this->get_logger(), "Received: %s", msg->data.c_str());
        }

        rclcpp::Subscription<example_interfaces::msg::String>::SharedPtr subscriber;
};


int main(int argc, char **argv) {
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<SmartphoneNode>());
    rclcpp::shutdown();
    return 0;
}