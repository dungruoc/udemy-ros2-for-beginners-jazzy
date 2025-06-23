#include "rclcpp/rclcpp.hpp"

#include "example_interfaces/srv/add_two_ints.hpp"


class AddTwoIntsServerNode : public rclcpp::Node {

public:
    AddTwoIntsServerNode() : rclcpp::Node("add_two_ints_server") {
        server = this->
            create_service<example_interfaces::srv::AddTwoInts>(
                "add_two_ints",
                std::bind(&AddTwoIntsServerNode::callbackAddTwoInts, this, std::placeholders::_1, std::placeholders::_2)
            );
        
        RCLCPP_INFO(this->get_logger(), "Add Two Ints server has started");
    }

private:
    void callbackAddTwoInts(
        const example_interfaces::srv::AddTwoInts::Request::SharedPtr request,
        example_interfaces::srv::AddTwoInts::Response::SharedPtr response
    ) {
        response->sum = request->a + request->b;
        RCLCPP_INFO(this->get_logger(), "%ld + %ld = %ld", request->a, request->b, response->sum);
    }

    rclcpp::Service<example_interfaces::srv::AddTwoInts>::SharedPtr server;
};

int main(int argc, const char **argv) {
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<AddTwoIntsServerNode>());
    rclcpp::shutdown();

    return 0;
}