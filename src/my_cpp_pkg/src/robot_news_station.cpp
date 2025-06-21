#include "rclcpp/rclcpp.hpp"
#include "example_interfaces/msg/string.hpp"


class RobotNewsStationNode : public rclcpp::Node {
    public:
        RobotNewsStationNode() : rclcpp::Node("robot_news_station"), robot_name("R2D2") {
            this->publisher = this->create_publisher<example_interfaces::msg::String>("robot_news", 10);
            this->_timer = this->create_wall_timer(std::chrono::seconds(1),
                                                   std::bind(&RobotNewsStationNode::publishNews, this));

            RCLCPP_INFO(this->get_logger(), "Robot News Station %s started", robot_name.c_str());
        }
    
    private:

        void publishNews() {
            auto message = example_interfaces::msg::String();
            message.data = std::string("Hi, this is from ") + robot_name + std::string(" - the Robot News Station");
            RCLCPP_INFO(this->get_logger(), "Sending %s", message.data.c_str());
            this->publisher->publish(message);
        }


        std::string robot_name;
        rclcpp::Publisher<example_interfaces::msg::String>::SharedPtr publisher;
        rclcpp::TimerBase::SharedPtr _timer;
};


int main(int argc, char **argv) {
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<RobotNewsStationNode>());    
    rclcpp::shutdown();
    return 0;
}