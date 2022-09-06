#include "rclcpp/rclcpp.hpp"


int main(int argc, char* argv[]){

    rclcpp::init(argc, argv);

    std::shared_ptr<rclcpp::Node> node = std::make_shared<rclcpp::Node>("node");
    
    RCLCPP_INFO(node->get_logger(), "Hello from node");

    rclcpp::spin(node);

    rclcpp::shutdown();

    return 0;
}