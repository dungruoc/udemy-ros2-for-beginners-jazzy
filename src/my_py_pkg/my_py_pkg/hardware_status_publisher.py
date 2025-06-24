import rclpy
from rclpy.node import Node

from my_robot_interfaces.msg import HardwareStatus

class HardwareStatusPublisherNode(Node):
    def __init__(self):
        super().__init__("hardware_status_publisher")
        self.number = 5
        self.publisher = self.create_publisher(HardwareStatus, "hardware_status", 10)
        self.timer = self.create_timer(1.0, self.publish_status)
        self.get_logger().info("Hardware Status Publisher started")
    
    def publish_status(self):
        msg = HardwareStatus(temperature=50.0, are_motors_ready=True, debug_message="OK")
        self.get_logger().info(f"sending {msg}")
        self.publisher.publish(msg)


def main(args=None):
    rclpy.init(args=args)
    rclpy.spin(HardwareStatusPublisherNode())
    rclpy.shutdown()

if __name__ == "__main__":
    main()