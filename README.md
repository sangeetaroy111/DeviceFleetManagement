Deliverables:
1.	GitHub Link
2.	README.md
  i.	Instruction to run both C++ backend service and Python CLI app on Linux
  ii.	.proto service definition file
            protoc --grpc_out=. --plugin=protoc-gen-grpc=`which grpc_cpp_plugin` --cpp_out=. devicefleetmanagement.proto
  iii.	Architecture overview on how backend and CLI interact
  iv.	Detailed example on how to use CLI to interact with the services for all API function
  v.	Assumptions/simplifications/improvements
