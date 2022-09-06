#include <rclcpp/rclcpp.hpp>
#include <example_interfaces/msg/string.hpp>

class PublisherNode : public rclcpp::Node{


    public:
        PublisherNode(const char* name) : Node(name){

            m_publisher = this->create_publisher<example_interfaces::msg::String>("my_topic", 10);
            m_timer = this->create_wall_timer(std::chrono::seconds(1),
                                                    std::bind(&PublisherNode::callback, this));

            RCLCPP_INFO(get_logger(), "Started Node");
        }

    private:

    void callback(){
        
        example_interfaces::msg::String msg;
        msg.data = "This is a message from Publisher " + std::to_string(a);
        m_publisher->publish(msg);
        a *= 2;
    }

    int a = 1;
    std::shared_ptr<rclcpp::TimerBase> m_timer;
    std::shared_ptr<rclcpp::Publisher<example_interfaces::msg::String>> m_publisher;

};


int main(int argc, char* argv[]){

    rclcpp::init(argc, argv);

    std::shared_ptr<PublisherNode> pN = std::make_shared<PublisherNode>("pub_node");

    rclcpp::spin(pN);
    rclcpp::shutdown();

    return 0;
}