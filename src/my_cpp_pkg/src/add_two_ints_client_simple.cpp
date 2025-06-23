#include "rclcpp/rclcpp.hpp"

#include "example_interfaces/srv/add_two_ints.hpp"

int main(int argc, const char **argv) {
    rclcpp::init(argc, argv);

    auto node = std::make_shared<rclcpp::Node>("add_two_ints_client_simple");
    auto client = node->create_client<example_interfaces::srv::AddTwoInts>("add_two_ints");

    while (not client->wait_for_service(std::chrono::seconds(1))) {
        RCLCPP_WARN(node->get_logger(), "waiting for the server ...");
    }

    auto request = std::make_shared<example_interfaces::srv::AddTwoInts::Request>();
    request->a = 5;
    request->b = 8;

    auto future = client->async_send_request(request);
    rclcpp::spin_until_future_complete(node, future);
    auto response = future.get();

    RCLCPP_INFO(node->get_logger(), "%ld + %ld = %ld", request->a, request->b, response->sum);

    rclcpp::shutdown();
    
    return 0;
}