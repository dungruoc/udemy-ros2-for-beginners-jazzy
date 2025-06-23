#include "rclcpp/rclcpp.hpp"

#include "example_interfaces/msg/int64.hpp"
#include "example_interfaces/srv/set_bool.hpp"


class NumberCounterNode : public rclcpp::Node {
    public:
        NumberCounterNode() : rclcpp::Node("number_counter"), counter(0) {
            publisher = this->create_publisher<example_interfaces::msg::Int64>("number_count", 10);
            server = this->
                create_service<example_interfaces::srv::SetBool>(
                    "reset_counter",
                    std::bind(&NumberCounterNode::callbackResetCounter, this, std::placeholders::_1, std::placeholders::_2)
                );

            subscriber = this->
                create_subscription<example_interfaces::msg::Int64>(
                    "number",
                    10,
                    std::bind(&NumberCounterNode::callbackNumberReceived, this, std::placeholders::_1)
                );
            RCLCPP_INFO(this->get_logger(), "Number Counter started");
        }
    
    private:
        void callbackNumberReceived(const example_interfaces::msg::Int64::SharedPtr msg) {
            RCLCPP_INFO(this->get_logger(), "Received: %ld", msg->data);
            counter++;
            auto message = example_interfaces::msg::Int64();
            message.data = counter;
            RCLCPP_INFO(this->get_logger(), "Sending %ld", message.data);
            this->publisher->publish(message);

        }

        void callbackResetCounter(
            const example_interfaces::srv::SetBool::Request::SharedPtr request,
            example_interfaces::srv::SetBool::Response::SharedPtr response
        ) {
            RCLCPP_INFO(this->get_logger(), "Reset service received %d", request->data);
            if (request->data) {
                this->counter = 0;
                RCLCPP_INFO(this->get_logger(), "counter reset");
                response->success = true;
                response->message = "counter reset successfully";
            } else {
                response->success = false;
                response->message = "counter not reset";
            }
        }

        rclcpp::Subscription<example_interfaces::msg::Int64>::SharedPtr subscriber;
        rclcpp::Publisher<example_interfaces::msg::Int64>::SharedPtr publisher;
        int64_t counter;

        rclcpp::Service<example_interfaces::srv::SetBool>::SharedPtr server;

};


int main(int argc, char **argv) {
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<NumberCounterNode>());
    rclcpp::shutdown();
    return 0;
}