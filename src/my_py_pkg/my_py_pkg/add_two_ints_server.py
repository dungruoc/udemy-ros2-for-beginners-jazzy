import rclpy
from rclpy.node import Node

from example_interfaces.srv import AddTwoInts

class AddTwoIntsNode(Node):
    def __init__(self):
        super().__init__("add_two_ints_server")
        self.server = self.create_service(AddTwoInts, "add_two_ints", self.callback_add_two_ints)

        self.get_logger().info("Add Two Ints has started")

    def callback_add_two_ints(self, request: AddTwoInts.Request, response: AddTwoInts.Response):
        response.sum = request.a + request.b
        self.get_logger().info(f"{request.a} + {request.b} = {response.sum}")
        return response

def main(args=None):
    rclpy.init(args=args)
    rclpy.spin(AddTwoIntsNode())
    rclpy.shutdown()

if __name__ == "__main__":
    main()