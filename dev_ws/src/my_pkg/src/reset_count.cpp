#include <rclcpp/rclcpp.hpp>
#include <example_interfaces/srv/set_bool.hpp>

class ResetCount : public rclcpp::Node{

    public:

        ResetCount(const char* name) : Node(name){
            m_thread = std::thread(std::bind(&ResetCount::reset, this));
        }

        void reset(){

            std::shared_ptr<rclcpp::Client<example_interfaces::srv::SetBool>> client 
                = this->create_client<example_interfaces::srv::SetBool>("reset_count");

            while(!client->wait_for_service(std::chrono::seconds(2))){
                RCLCPP_INFO(this->get_logger(), "Waiting for the server response");
            }

            std::shared_ptr<example_interfaces::srv::SetBool::Request> req
                = std::make_shared<example_interfaces::srv::SetBool::Request>();

            req->data = true;

            rclcpp::Client<example_interfaces::srv::SetBool>::FutureAndRequestId future
                = client->async_send_request(req);

            try{
                std::shared_ptr<example_interfaces::srv::SetBool_Response> res = future.get();
                RCLCPP_INFO(this->get_logger(), "request send to the server");
            } catch(const std::exception& e){
                RCLCPP_ERROR(this->get_logger(), "Message has not send to server");
            }
        }

    private:

        std::thread m_thread;

};

int main(int argc, char* argv[]){

    rclcpp::init(argc, argv);

    std::shared_ptr<ResetCount> node = std::make_shared<ResetCount>("reset_node");

    rclcpp::spin(node);
    rclcpp::shutdown();

    return 0;
}