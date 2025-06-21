#include "rclcpp/rclcpp.hpp"
#include "example_interfaces/msg/int64.hpp"


class NumberCounterNode : public rclcpp::Node {
    public:
        NumberCounterNode() : rclcpp::Node("number_counter"), counter(0) {
            publisher = this->create_publisher<example_interfaces::msg::Int64>("number_count", 10);

            subscriber = this->
                create_subscription<example_interfaces::msg::Int64>(
                    "number",
                    10,
                    std::bind(&NumberCounterNode::callbackRobotNews, this, std::placeholders::_1)
                );
            RCLCPP_INFO(this->get_logger(), "Number Counter started");
        }
    
    private:
        void callbackRobotNews(const example_interfaces::msg::Int64::SharedPtr msg) {
            RCLCPP_INFO(this->get_logger(), "Received: %ld", msg->data);
            counter++;
            auto message = example_interfaces::msg::Int64();
            message.data = counter;
            RCLCPP_INFO(this->get_logger(), "Sending %ld", message.data);
            this->publisher->publish(message);

        }

        rclcpp::Subscription<example_interfaces::msg::Int64>::SharedPtr subscriber;
        rclcpp::Publisher<example_interfaces::msg::Int64>::SharedPtr publisher;
        int64_t counter;
};


int main(int argc, char **argv) {
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<NumberCounterNode>());
    rclcpp::shutdown();
    return 0;
}