#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/int64.hpp>

class NumPublisher : public rclcpp::Node{

    public:

        NumPublisher(const char* name) : Node(name){
            RCLCPP_INFO(this->get_logger(), "Num Publisher has started");
            
            m_msg.data = 0;
            m_pub = this->create_publisher<std_msgs::msg::Int64>("number", 10);
            m_timer = this->create_wall_timer(std::chrono::seconds(1), std::bind(&NumPublisher::callback, this));
        }

    private:

        void callback(){
            m_pub->publish(m_msg);
            m_msg.data += 1;
        }

        std_msgs::msg::Int64 m_msg;
        std::shared_ptr<rclcpp::Publisher<std_msgs::msg::Int64>> m_pub;
        std::shared_ptr<rclcpp::TimerBase> m_timer;

};

int main(int argc, char* argv[]){

    rclcpp::init(argc, argv);

    std::shared_ptr<NumPublisher> nPub = std::make_shared<NumPublisher>("num_publisher");

    rclcpp::spin(nPub);
    rclcpp::shutdown();

    return 0;
}