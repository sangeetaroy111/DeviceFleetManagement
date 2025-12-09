#include "device_fleet_management.h"
#include <grpcpp/grpcpp.h>
#include "devicefleetmanagement.grpc.pb.h"


int InitiateDeviceAction (int device_id, int action_type, string action_param){
    return DevicePool::getInstance()->Initiate(device_id,action_type,action_param);
}

class DeviceFleetManagementImpl final : public devicefleetmanagement::DeviceFleetManagement ::Service {
  
grpc::Status RegisterDevice(grpc::ServerContext* context, const devicefleetmanagement::Device * request, devicefleetmanagement::noParam* reply) override {
    DevicePool::getInstance()->RegisterDevice(request->device_id(), request->state());
    return grpc::Status::OK;
  }

grpc::Status SetDeviceStatus (grpc::ServerContext* context, const devicefleetmanagement::Device * request, devicefleetmanagement::noParam* reply) override {
    DevicePool::getInstance()->SetDeviceStatus (request->device_id(), request->state());
    return grpc::Status::OK;
  }

grpc::Status GetDeviceInfo (grpc::ServerContext* context, const devicefleetmanagement::GetDeviceInfoRequest * request, devicefleetmanagement::GetDeviceInfoReply * reply) override {
    Device* app = DevicePool::getInstance()->GetDevice (request->device_id());
    reply->set_currentl_state(app->get_state());
    reply->set_info(app->get_info());
    return grpc::Status::OK;
  }

grpc::Status InitiateDeviceAction (grpc::ServerContext* context, const devicefleetmanagement::InitiateDeviceActionRequest* request, devicefleetmanagement::InitiateDeviceActionReply* reply) override {
     reply->set_state(DevicePool::getInstance()->getDevice (request->device_id())->state());
     std::future<int> future_result = std::async(std::launch::async, dummy , 1001, SOFTWARE_UPDATE, "http2");
     int action_id = future_result.get(); 
     reply->set_action_id(action_id); 
    return grpc::Status::OK;
  }

grpc::Status GetDeviceAction (grpc::ServerContext* context, const devicefleetmanagement::GetDeviceActionRequest * request, devicefleetmanagement::GetDeviceActionReply * reply) override {
    reply->set_action_status(DevicePool::getInstance()->GetDeviceAction (request->device_id(),request->action_id()));
    return grpc::Status::OK;
  }

  };

void RunServer() {
  std::string server_address("0.0.0.0:50051");
  DeviceFleetManagementImpl service;

  grpc::ServerBuilder builder;
  builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
  builder.RegisterService(&service);
  std::unique_ptr<grpc::Server> server(builder.BuildAndStart());
  server->Wait();
}

int main() {
  RunServer();
  return 0;
}
