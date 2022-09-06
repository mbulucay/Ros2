#include <rclcpp/rclcpp.hpp>
#include <example_interfaces/msg/string.hpp>

class SubscriberNode : public rclcpp::Node {

    public:
        SubscriberNode (const char* name) : Node(name){
            
            m_subscriber = this->create_subscription<example_interfaces::msg::String>
                ("my_topic", 10, std::bind(&SubscriberNode::callback, this, std::placeholders::_1));
           
           RCLCPP_INFO(get_logger(),"Subscriber Started"); 
        }

    private:

        void callback(const std::shared_ptr<example_interfaces::msg::String> msg){
           RCLCPP_INFO(get_logger(),"%s", msg->data.c_str()); 
           RCLCPP_INFO(get_logger(), "aksljdsa");
        }

    // std::shared_ptr<rclcpp::TimerBase> m_timer;
    std::shared_ptr<rclcpp::Subscription<example_interfaces::msg::String>> m_subscriber;

};

int main(int argc, char* argv[]){

    rclcpp::init(argc, argv);

    std::shared_ptr<SubscriberNode> sub = std::make_shared<SubscriberNode>("subscriber_node");

    rclcpp::spin(sub);
    rclcpp::shutdown();

    return 0;
}