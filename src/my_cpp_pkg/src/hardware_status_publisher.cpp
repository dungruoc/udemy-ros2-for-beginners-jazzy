#include "rclcpp/rclcpp.hpp"
#include "my_robot_interfaces/msg/hardware_status.hpp"

const char *TIMER_SECOND_PARAM = "timer_seconds";

class HardwareStatusPublisherNode : public rclcpp::Node {
    public:
        HardwareStatusPublisherNode() : rclcpp::Node("hardware_status_publisher") {
            this->declare_parameter(TIMER_SECOND_PARAM, 1);
            this->publisher = this->create_publisher<my_robot_interfaces::msg::HardwareStatus>("hardware_status", 10);
            this->_timer = this->create_wall_timer(std::chrono::seconds(this->get_parameter(TIMER_SECOND_PARAM).as_int()),
                                                   std::bind(&HardwareStatusPublisherNode::publishHardwareStatus, this));

            RCLCPP_INFO(this->get_logger(), "Hardware Status Publisher has started");
        }
    
    private:

        void publishHardwareStatus() {
            auto message = my_robot_interfaces::msg::HardwareStatus();
            message.temperature = 20.3;
            message.are_motors_ready = true;
            message.debug_message = "status ok";
            RCLCPP_INFO(this->get_logger(), "Sending status, temperature %f", message.temperature);
            this->publisher->publish(message);
        }

        rclcpp::Publisher<my_robot_interfaces::msg::HardwareStatus>::SharedPtr publisher;
        rclcpp::TimerBase::SharedPtr _timer;
};


int main(int argc, char **argv) {
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<HardwareStatusPublisherNode>());    
    rclcpp::shutdown();
    return 0;
}