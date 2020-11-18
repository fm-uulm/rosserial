#include <nodelet/nodelet.h>
#include <pluginlib/class_list_macros.h>

#include "rosserial_server/serial_session.h"

namespace rosserial_server {

class SerialNodelet : public nodelet::Nodelet {
  virtual void onInit() {
    try {
      std::string port;
      int baud;
      ros::param::param<std::string>("~port", port, "/dev/ttyACM0");
      ros::param::param<int>("~baud", baud, 57600);
      boost::asio::io_service io_service;
      serial_session_ = std::make_shared<SerialSession>(io_service, port, baud);
      io_service.run();
    } catch (std::runtime_error e) {
      ROS_ERROR("%s", e.what());
    }
  }

  std::shared_ptr<SerialSession> serial_session_;
};

} // namespace rosserial_server

PLUGINLIB_EXPORT_CLASS(rosserial_server::SerialNodelet, nodelet::Nodelet)
