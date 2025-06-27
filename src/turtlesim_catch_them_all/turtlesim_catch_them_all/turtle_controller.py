import rclpy
from rclpy.node import Node
from turtlesim.msg import Pose
from geometry_msgs.msg import Twist
import math

class TurtleControllerNode(Node):
    def __init__(self):
        super().__init__("turtle_controller")
        self.pose_subscriber = self.create_subscription(
            Pose, "turtle1/pose",
            self.callback_turtle_pose, 10
        )
        self.pose = None
        self.target = {'x': 2.0, 'y': 8.0}
        self.cmd_vel_publisher = self.create_publisher(
            Twist,
            "turtle1/cmd_vel",
            10
        )
        self.control_timer = self.create_timer(
            0.01, self.control_loop
        )

    def callback_turtle_pose(self, pose: Pose):
        self.pose = pose

    def control_loop(self):
        self.get_logger().info(f"current pos: {self.pose}")
        if self.pose:
            dist_x = self.target.get('x') - self.pose.x
            dist_y = self.target.get('y') - self.pose.y
            dist = math.sqrt(dist_x**2 + dist_y**2)
            cmd = Twist()
            if dist > 0.5:
                cmd.linear.x = dist
                goal_theta = math.atan2(dist_y, dist_x)
                theta_diff = goal_theta - self.pose.theta
                if theta_diff > math.pi:
                    theta_diff -= 2*math.pi
                elif theta_diff < -math.pi:
                    theta_diff += 2*math.pi
                    
                cmd.angular.z = theta_diff
            else:
                cmd.linear.x = 0.0
                cmd.angular.z = 0.0
            
            self.cmd_vel_publisher.publish(cmd)


def main(args=None):
    rclpy.init(args=args)
    rclpy.spin(TurtleControllerNode())
    rclpy.shutdhow()