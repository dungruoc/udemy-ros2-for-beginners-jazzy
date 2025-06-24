#include "rclcpp/rclcpp.hpp"

#include "my_robot_interfaces/msg/led_panel_state.hpp"
#include "my_robot_interfaces/srv/set_led.hpp"


class LedPanelNode : public rclcpp::Node {
    public:
        LedPanelNode() : rclcpp::Node("led_panel"), led_panel{0, 0, 0} {
            publisher = this->create_publisher<my_robot_interfaces::msg::LedPanelState>("led_panel", 10);
            server = this->
                create_service<my_robot_interfaces::srv::SetLed>(
                    "set_led",
                    std::bind(&LedPanelNode::callbackSetLed, this, std::placeholders::_1, std::placeholders::_2)
                );

            this->_timer = this->
                create_wall_timer(std::chrono::seconds(5),
                                 std::bind(&LedPanelNode::publishPanel, this));

            RCLCPP_INFO(this->get_logger(), "Led Panel has started");
        }
    
    private:
        void publishPanel() {
            auto message = my_robot_interfaces::msg::LedPanelState();
            message.led_states = led_panel;
            RCLCPP_INFO(this->get_logger(), "Sending [%d, %d, %d]", (int)led_panel.at(0), (int)led_panel.at(1), (int)led_panel.at(2));
            this->publisher->publish(message);
        }

        void callbackSetLed(
            const my_robot_interfaces::srv::SetLed::Request::SharedPtr request,
            my_robot_interfaces::srv::SetLed::Response::SharedPtr response
        ) {
            RCLCPP_INFO(this->get_logger(), "Reset service received %ld", request->led_number);
            if (request->led_number >= 0 and request->led_number < (int64_t)led_panel.size()) {
                led_panel[request->led_number] = request->state;
                RCLCPP_INFO(this->get_logger(), "Led state at %ld is set to %d", request->led_number, request->state);
                response->success = true;
            } else {
                response->success = false;
            }
        }

        rclcpp::Publisher<my_robot_interfaces::msg::LedPanelState>::SharedPtr publisher;
        rclcpp::Service<my_robot_interfaces::srv::SetLed>::SharedPtr server;

        std::vector<bool> led_panel;
        rclcpp::TimerBase::SharedPtr _timer;
};


int main(int argc, char **argv) {
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<LedPanelNode>());
    rclcpp::shutdown();
    return 0;
}