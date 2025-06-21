#include "rclcpp/rclcpp.hpp"

class MyNode : public rclcpp::Node {
    public:
        MyNode() : rclcpp::Node("cpp_test"), _counter(0) {
            RCLCPP_INFO(this->get_logger(), "Hello world");
            this->_timer = this->create_wall_timer(std::chrono::seconds(1),
                                                   std::bind(&MyNode::timerCallback, this));
        }
    
    private:
        int _counter;
        rclcpp::TimerBase::SharedPtr _timer;

        void timerCallback() {
            RCLCPP_INFO(this->get_logger(), "Hello %d", this->_counter++);
        }

};


int main(int argc, char **argv) {
    rclcpp::init(argc, argv);

    auto node = std::make_shared<MyNode>();
    rclcpp::spin(node);
    
    rclcpp::shutdown();
    return 0;
}