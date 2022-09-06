#include <rclcpp/rclcpp.hpp>
#include <string>
#include <iostream>

class MyNode : public rclcpp::Node {

    public:
        MyNode(std::string node_name) : Node(node_name), m_counter(0) {
            RCLCPP_INFO(get_logger(), "Hello OOP");

            m_timer = this->create_wall_timer(std::chrono::seconds(1),
                                                std::bind(&MyNode::call_back, this));
        }

        std::string get_node_name() { return m_node_name; }

    private:

        void call_back(){
            RCLCPP_INFO(get_logger(), "TIMER %d", m_counter);
            m_counter++;
        }

        int m_counter; 
        std::string m_node_name;
        std::shared_ptr<rclcpp::TimerBase> m_timer;

};


int main(int argc, char* argv[]){

    rclcpp::init(argc, argv);
    
    std::shared_ptr<MyNode> node = std::make_shared<MyNode>("oop_node");

    rclcpp::spin(node);
    rclcpp::shutdown();

    return 0;
}