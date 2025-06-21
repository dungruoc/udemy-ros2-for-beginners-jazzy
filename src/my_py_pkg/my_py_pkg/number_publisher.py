import rclpy
from rclpy.node import Node

from example_interfaces.msg import Int64

class NumberPublisherNode(Node):
    def __init__(self):
        super().__init__("nubmer_publisher")
        self.number = 5
        self.publisher = self.create_publisher(Int64, "number", 10)
        self.timer = self.create_timer(1.0, self.publish_number)
        self.get_logger().info("Number Publisher started")
    
    def publish_number(self):
        msg = Int64()
        msg.data = self.number
        self.get_logger().info(f"sending {msg.data}")
        self.publisher.publish(msg)


def main(args=None):
    rclpy.init(args=args)
    rclpy.spin(NumberPublisherNode())
    rclpy.shutdown()

if __name__ == "__main__":
    main()