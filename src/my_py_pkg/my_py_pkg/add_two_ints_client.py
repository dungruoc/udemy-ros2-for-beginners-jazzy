import rclpy
from rclpy.node import Node

from example_interfaces.srv import AddTwoInts

class AddTwoIntClientNode(Node):
    def __init__(self):
        super().__init__("add_two_ints_client")
        self.client = self.create_client(AddTwoInts, "add_two_ints")
        self.call_service(3, 8)

    def call_service(self, a: int, b:int):
        while not self.client.wait_for_service(1.0):
            self.get_logger().warn("waiting for Add Two Ints server ...")

        request = AddTwoInts.Request(a=a, b=b)
        future = self.client.call_async(request)
        future.add_done_callback(self.callback_response)

    def callback_response(self, future):
        response = future.result()
        self.get_logger().info(f"Received: {response.sum}")


def main(args=None):
    rclpy.init(args=args)
    rclpy.spin(AddTwoIntClientNode())
    rclpy.shutdown()
