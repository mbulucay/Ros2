#include <rclcpp/rclcpp.hpp>
#include <example_interfaces/srv/add_two_ints.hpp>

int main(int argc, char* argv[]){

    rclcpp::init(argc, argv);

    std::shared_ptr<rclcpp::Node> node = std::make_shared<rclcpp::Node>("Sum2Client");

    std::shared_ptr<rclcpp::Client<example_interfaces::srv::AddTwoInts>> client = node->create_client<example_interfaces::srv::AddTwoInts>("add2int");
    while(!client->wait_for_service(std::chrono::seconds(2))){
        RCLCPP_WARN(node->get_logger(), "Waiting for the server");
    }

    std::shared_ptr<example_interfaces::srv::AddTwoInts::Request> req = std::make_shared<example_interfaces::srv::AddTwoInts::Request>(); 
    req->a = 4;
    req->b = 4;

    rclcpp::Client<example_interfaces::srv::AddTwoInts>::FutureAndRequestId res =  client->async_send_request(req);

    if(rclcpp::spin_until_future_complete(node, res) == rclcpp::FutureReturnCode::SUCCESS)
        RCLCPP_INFO(node->get_logger(), "%ld + %ld = %ld", req->a, req->b, res.get()->sum);
    else
        RCLCPP_ERROR(node->get_logger(), "Serve not response the request");
    
    rclcpp::shutdown();

    return 0;
}