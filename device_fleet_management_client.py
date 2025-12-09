#!/usr/bin/python3
import grpc
import devicefleetmanagement_pb2
import devicefleetmanagement_pb2_grpc

def run_client():
    with grpc.insecure_channel('localhost:50051') as channel:
        stub = devicefleetmanagement_pb2_grpc.DeviceFleetManagementStub(channel)
while True:
    try:
        
        print("""Please select (1-5) from below choice:
        1. RegisterDevice
        2. SetDeviceStatus
        3. GetDeviceInfo
        4. InitiateDeviceActionRequest
        5. GetDeviceAction
        Please select any other number to exit
        """)
        choice=int(input('please enter your choice (1-5): '))
        match choice:
            case 1:            
                # Call RegisterDevice
                d_id=int(input('please enter any Device ID: '))
                print("""Please enter any state (0-6):
                    IDLE - 0
                    BUSY - 1
                    OFFLINE - 2
                    MAINTENANCE - 3
                    UPDATING - 4
                    RECOVERING - 5 
                    ERROR - 6
                """)
                st=int(input('please enter any state: '))
                device= devicefleetmanagement_pb2.RegisterDevice(DeviceId=d_id, state=st)       
                print(f"Server says: {RegisterDevice}")
            case 2:        
                # Call SetDeviceStatus 
                d_id=int(input('please enter any Device ID: '))
                print("""Please enter any state (0-6):
                    IDLE - 0
                    BUSY - 1
                    OFFLINE - 2
                    MAINTENANCE - 3
                    UPDATING - 4
                    RECOVERING - 5 
                    ERROR - 6
                """)
                st=int(input('please enter any state: '))
                device= devicefleetmanagement_pb2.SetDeviceStatus(DeviceId=d_id, state=st)       
                print(f"Server says: {SetDeviceStatus }")
            case 3:
                # Call GetDeviceInfo 
                d_id=int(input('please enter any Device ID: '))
                data_request = devicefleetmanagement_pb2.GetDeviceInfo (DeviceId=d_id)
                data_reply = stub.GetDeviceInfo (data_request)
                print(f"State: {data_reply.current_state} info: {data_reply.info} ")
             case 4:
                # Call InitiateDeviceActionRequest
                d_id=int(input('please enter any Device ID: '))
                print("""Select ActionType :
                    SOFTWARE_UPDATE - 0
                    """)
                a_type=int(input('please enter ActionType: '))
                a_param=input('please enter Action Param, say software verion: '))    
                data_request = devicefleetmanagement_pb2.InitiateDeviceActionRequest(DeviceId=d_id, action_type=a_type, action_param=a_param)
                data_reply = stub.InitiateDeviceActionRequest(data_request)
                print(f"State: {data_reply.state} info: {data_reply.action_id} ")
             case 5:
                # Call GetDeviceAction 
                a_id=int(input('please enter any Action ID: '))
                data_request = devicefleetmanagement_pb2.GetDeviceAction (action_id=a_id)
                data_reply = stub.GetDeviceAction (data_request)
                print(f"State: {data_reply.action_status} ")
            case _:
                break
            except:
                print('error')
                continue

if __name__ == '__main__':
    run_client()

