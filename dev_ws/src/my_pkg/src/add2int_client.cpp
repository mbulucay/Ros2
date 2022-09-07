#include <rclcpp/rclcpp.hpp>
#include <example_interfaces/srv/add_two_ints.hpp>


class Add2Int : public rclcpp::Node{

    public:

        Add2Int(const char* name) : Node(name){

            m_threads.push_back(std::thread(std::bind(&Add2Int::sum, this, 19, 43)));
            m_threads.push_back(std::thread(std::bind(&Add2Int::sum, this, 123, 323)));
            m_threads.push_back(std::thread(std::bind(&Add2Int::sum, this, 43289, 4332)));
            m_threads.push_back(std::thread(std::bind(&Add2Int::sum, this, 15, 532)));
            m_threads.push_back(std::thread(std::bind(&Add2Int::sum, this, 452, 653)));
            m_threads.push_back(std::thread(std::bind(&Add2Int::sum, this, 7655, 4523)));
        }

        void sum(long int a, long int b){
        
            std::shared_ptr<rclcpp::Client<example_interfaces::srv::AddTwoInts>> client = this->create_client<example_interfaces::srv::AddTwoInts>("add2int");
            while(!client->wait_for_service(std::chrono::seconds(2))){
                RCLCPP_WARN(this->get_logger(), "Waiting for the server");
            }

            std::shared_ptr<example_interfaces::srv::AddTwoInts::Request> req = std::make_shared<example_interfaces::srv::AddTwoInts::Request>(); 
            req->a = a;
            req->b = b;

            rclcpp::Client<example_interfaces::srv::AddTwoInts>::FutureAndRequestId future =  client->async_send_request(req);  

            try{

                std::shared_ptr<example_interfaces::srv::AddTwoInts_Response> res =  future.get();
                RCLCPP_INFO(this->get_logger(), "%ld + %ld = %ld ", a, b, res->sum);

            }catch(const std::exception& e){
                RCLCPP_ERROR(this->get_logger(), "Server call failed");
            }

        }

    private:
        std::vector<std::thread> m_threads;

};

int main(int argc, char* argv[]){

    rclcpp::init(argc, argv);

    std::shared_ptr<Add2Int> client = std::make_shared<Add2Int>("client");

    rclcpp::spin(client);
    rclcpp::shutdown();
    return 0;
}