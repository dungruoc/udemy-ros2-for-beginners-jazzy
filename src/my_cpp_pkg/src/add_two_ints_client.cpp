#include "rclcpp/rclcpp.hpp"

#include "example_interfaces/srv/add_two_ints.hpp"

class AddTwoIntsClientNode : public rclcpp::Node {
public:
    AddTwoIntsClientNode() : rclcpp::Node("add_two_ints_client") {
        client = this->create_client<example_interfaces::srv::AddTwoInts>("add_two_ints");
        this->addTwoInts(6, 9);
    }

private:
    void addTwoInts(int64_t a, int64_t b) {
        while (not client->wait_for_service(std::chrono::seconds(1))) {
            RCLCPP_WARN(this->get_logger(), "waiting for the server ...");
        }

        auto request = std::make_shared<example_interfaces::srv::AddTwoInts::Request>();
        request->a = a;
        request->b = b;

        auto future = client
            ->async_send_request(
                request,
                std::bind(&AddTwoIntsClientNode::callbackAddTwoIntsRequested, this, std::placeholders::_1)
            );
    }

    void callbackAddTwoIntsRequested(rclcpp::Client<example_interfaces::srv::AddTwoInts>::SharedFuture future) {
        auto response = future.get();
        RCLCPP_INFO(this->get_logger(), "Sum: %ld", response->sum);
    }


    rclcpp::Client<example_interfaces::srv::AddTwoInts>::SharedPtr client;
};


int main(int argc, const char **argv) {
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<AddTwoIntsClientNode>());
    rclcpp::shutdown();
    
    return 0;
}