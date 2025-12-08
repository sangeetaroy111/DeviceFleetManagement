
import grpc
import devicefleetmanagement_pb2
import devicefleetmanagement_pb2_grpc

def run_client():
    with grpc.insecure_channel('localhost:50051') as channel:
        stub = devicefleetmanagement_pb2_grpc.DeviceFleetManagementStub(channel)

        # Call RegisterDevice
        device= devicefleetmanagement_pb2.RegisterDevice(device_id=1001, state=0)       
        print(f"Server says: {RegisterDevice}")

        # Call SetDeviceStatus 
        device= devicefleetmanagement_pb2.SetDeviceStatus(device_id=1001, state=2)       
        print(f"Server says: {SetDeviceStatus }")


        # Call GetDeviceInfo 
        data_request = devicefleetmanagement_pb2.GetDeviceInfo (device_id=1001)
        data_reply = stub.GetDeviceInfo (data_request)
        print(f"State: {data_reply.current_state} info: [data_reply.info] ")

        # Call InitiateDeviceActionRequest
        data_request = devicefleetmanagement_pb2.InitiateDeviceActionRequest(device_id=1001, action_type=0, action_param='version2')
        data_reply = stub.InitiateDeviceActionRequest(data_request)
        print(f"State: {data_reply.state} info: [data_reply.action_id] ")

        # Call GetDeviceAction 
        data_request = devicefleetmanagement_pb2.GetDeviceAction (action_id=1)
        data_reply = stub.GetDeviceAction (data_request)
        print(f"State: {data_reply.action_status} ")


if __name__ == '__main__':
    run_client()

