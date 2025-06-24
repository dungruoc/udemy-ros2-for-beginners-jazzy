import rclpy
from rclpy.node import Node

from my_robot_interfaces.srv import SetLed

class BatteryNode(Node):
    def __init__(self):
        super().__init__("battery")
        self.clock = 0
        self.full_level = True
        self.led = 2
        self.client = self.create_client(SetLed, "set_led")
        self.timer = self.create_timer(1.0, self.update_level)
        self.get_logger().info("Battery has started")
    
    def update_level(self):
        self.get_logger().info(f"clock {self.clock}")
        self.clock += 1
        if self.clock % 10 == 4:
            self.full_level = False
            self.update_led(not self.full_level)
        elif self.clock % 10 == 0:
            self.full_level = True
            self.update_led(not self.full_level)
    
    def update_led(self, empty_battery):
        while not self.client.wait_for_service(1.0):
            self.get_logger().warn("waiting for SetLed server ...")

        request = SetLed.Request(led_number=self.led, state=empty_battery)
        self.get_logger().info(f"Update Led {request}")
        future = self.client.call_async(request)
        future.add_done_callback(self.callback_response)

    def callback_response(self, future):
        response = future.result()
        self.get_logger().info(f"Response.success: {response.success}")


def main(args=None):
    rclpy.init(args=args)
    rclpy.spin(BatteryNode())
    rclpy.shutdown()

if __name__ == "__main__":
    main()