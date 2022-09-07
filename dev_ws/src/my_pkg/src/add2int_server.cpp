#include <rclcpp/rclcpp.hpp>
#include <example_interfaces/srv/add_two_ints.hpp>

class Add2Int: public rclcpp::Node {

    public:
        Add2Int(const char* name) : Node(name) {
            
            m_serv = this->create_service<example_interfaces::srv::AddTwoInts>
            ("add2int", std::bind(&Add2Int::callback, this, std::placeholders::_1, std::placeholders::_2));

            RCLCPP_INFO(this->get_logger(), "Add two number service server started");
        }

    private:

        // int64 a
        // int64 b
        // ---
        // int64 sum
        void callback(const std::shared_ptr<example_interfaces::srv::AddTwoInts::Request> req,
                      const std::shared_ptr<example_interfaces::srv::AddTwoInts::Response> res                
        ){
                res->sum = req->a + req->b;
                RCLCPP_INFO(this->get_logger(), "%ld + %ld = sum > %ld",req->a, req->b, res->sum);
        }


        std::shared_ptr<rclcpp::Service<example_interfaces::srv::AddTwoInts>> m_serv;


};


int main(int argc, char*argv[]){

    rclcpp::init(argc, argv);

    std::shared_ptr<Add2Int> node = std::make_shared<Add2Int>("summer");

    rclcpp::spin(node);
    rclcpp::shutdown();

    return 0;
}