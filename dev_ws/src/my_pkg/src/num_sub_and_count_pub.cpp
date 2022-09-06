#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/int64.hpp>

class NumSubAndCountPub : public rclcpp::Node {

    public:

        NumSubAndCountPub(const char* name) : Node(name){

            RCLCPP_INFO(this->get_logger(), "Number receiver has started");
            m_msg.data = 0;

            m_sub = this->create_subscription<std_msgs::msg::Int64>
            ("number", 10, std::bind(&NumSubAndCountPub::numReceiver, this, std::placeholders::_1));

            m_pub = this->create_publisher<std_msgs::msg::Int64>("number_count", 10);
            m_timer = this->create_wall_timer(std::chrono::seconds(1), std::bind(&NumSubAndCountPub::countPublisher, this));

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

        std_msgs::msg::Int64 m_msg;
        std::shared_ptr<rclcpp::Publisher<std_msgs::msg::Int64>> m_pub;
        std::shared_ptr<rclcpp::TimerBase> m_timer;

        std::shared_ptr<rclcpp::Subscription<std_msgs::msg::Int64>> m_sub;

};

int main(int argc, char* argv[]){

    rclcpp::init(argc, argv);

    std::shared_ptr<NumSubAndCountPub> node = std::make_shared<NumSubAndCountPub>("sub_pub_node");

    rclcpp::spin(node);
    rclcpp::shutdown();

    return 0;
}
