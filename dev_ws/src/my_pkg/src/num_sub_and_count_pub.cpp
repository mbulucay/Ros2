#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/int64.hpp>
#include <example_interfaces/srv/set_bool.hpp>

class NumSubAndCountPub : public rclcpp::Node {

    public:

        NumSubAndCountPub(const char* name) : Node(name){

            RCLCPP_INFO(this->get_logger(), "Number receiver has started");
            m_msg.data = 0;

            m_sub = this->create_subscription<std_msgs::msg::Int64>
            ("number", 10, std::bind(&NumSubAndCountPub::numReceiver, this, std::placeholders::_1));

            m_pub = this->create_publisher<std_msgs::msg::Int64>("number_count", 10);
            m_timer = this->create_wall_timer(std::chrono::seconds(1), std::bind(&NumSubAndCountPub::countPublisher, this));

            m_serv = this->create_service<example_interfaces::srv::SetBool>
            ("reset_count", std::bind(&NumSubAndCountPub::resetCount, this, std::placeholders::_1, std::placeholders::_2));

        }

    private:

        void countPublisher(){

            RCLCPP_INFO(this->get_logger() ,"Published %ld", m_msg.data);
            m_pub->publish(m_msg);
        }
        

        void numReceiver(const std::shared_ptr<std_msgs::msg::Int64> msg){

            m_msg.data += 1;
            RCLCPP_INFO(this->get_logger() ,"Received  %ld", msg->data);
        }

        void resetCount(const std::shared_ptr<example_interfaces::srv::SetBool::Request> req,
                        const std::shared_ptr<example_interfaces::srv::SetBool::Response> res
                        ){
                            // RCLCPP_INFO(this->get_logger(), "")
                            res->success = true;
                            m_msg.data = 0;
        }

        // Publisher
        std_msgs::msg::Int64 m_msg;
        std::shared_ptr<rclcpp::Publisher<std_msgs::msg::Int64>> m_pub;
        std::shared_ptr<rclcpp::TimerBase> m_timer;

        //Subscriber
        std::shared_ptr<rclcpp::Subscription<std_msgs::msg::Int64>> m_sub;

        //Service Server
        std::shared_ptr<rclcpp::Service<example_interfaces::srv::SetBool>> m_serv;
};

int main(int argc, char* argv[]){

    rclcpp::init(argc, argv);

    std::shared_ptr<NumSubAndCountPub> node = std::make_shared<NumSubAndCountPub>("sub_pub_node");

    rclcpp::spin(node);
    rclcpp::shutdown();

    return 0;
}
