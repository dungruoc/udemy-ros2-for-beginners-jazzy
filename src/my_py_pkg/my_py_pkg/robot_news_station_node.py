import rclpy
from rclpy.node import Node

from example_interfaces.msg import String

class RobotNewsStationNode(Node):
    def __init__(self):
        super().__init__("robot_news_station")
        self.robot_name = "C3PO"
        self.publisher = self.create_publisher(String, "robot_news", 10)
        self.timer = self.create_timer(1.0, self.publish_news)
        self.get_logger().info("Robot News Station started")

    def publish_news(self):
        msg = String()
        msg.data = f"Hello, this is from {self.robot_name} - Robot News Stations"
        self.get_logger().info(f"sending {msg.data}")
        self.publisher.publish(msg)


def main(args=None):
    rclpy.init(args=args)
    rclpy.spin(RobotNewsStationNode())
    rclpy.shutdown()

if __name__ == "__main__":
    main()