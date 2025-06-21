import rclpy
from rclpy.node import Node

from example_interfaces.msg import String


class SmartphoneNode(Node):
    def __init__(self):
        super().__init__("smartphone")
        self.subscriber = self.create_subscription(String, "robot_news", self.callback_robot_news, 10)
        self.get_logger().info("Smartphone started")

    def callback_robot_news(self, msg: String):
        self.get_logger().info(f"Received data: {msg.data}")


def main(args=None):
    rclpy.init(args=args)
    rclpy.spin(SmartphoneNode())
    rclpy.shutdown()

if __name__ == "__main__":
    main()