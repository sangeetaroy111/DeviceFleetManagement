Deliverables:
1.	GitHub Link
2.	README.md
  i.	Instruction to run both C++ backend service and Python CLI app on Linux
        a. run below binary created after compiling device_fleet_managemet_server.cc, to start the server.
          ./device_fleet_managemet_server
        b. run below command to start python CLI
          ./device_fleet_managemet_client.py
  ii.	.proto service definition file
            protoc --grpc_out=. --cpp_out=. device_fleet_management.proto
  iii.	Architecture overview on how backend and CLI interact
      
  iv.	Detailed example on how to use CLI to interact with the services for all API function
    This will every time will ask whiich service to call with user input (1-5), any other number is exit condition.
    each service will ask related input from user to continue.
  v.	Assumptions/simplifications/improvements
      a. Exception handler need to be added, also need to add checks for negative scenarios.
      b. GetDeviceAction API call is currently based only on Action ID, Device ID can be added for better design amd maintenance.
      c. Client CLI can be more user friendly with infinite loop for different API call by users. 
