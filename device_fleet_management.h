#include <string>
#include <map>
#include <iostream>
#include <mutex>
#include <thread>
#include <future>

using namespace std;

std::mutex mtx;

enum State{
    IDLE,
    BUSY,
    OFFLINE,
    MAINTENANCE,
    UPDATING,
    RECOVERING,
    ERROR
};
enum ActionType{
    SOFTWARE_UPDATE
  };

enum ActionStatus{
   PENDING,
   RUNNING,
   COMPLETED,
   FAILED
  };
  
class Action{
  ActionType _action_type;   
  ActionStatus _action_status;
  string _action_param; 
  int _action_id;
  static int _id_gen;
  public:
    Action(){}
    Action(int action_type, string action_param):_action_type(static_cast<ActionType>(action_type)),_action_param(action_param){
	    _action_id=_id_gen++;
	    _action_status=RUNNING;
	    }
    int get_action_id(){
	    return _action_id;
	    }
    int get_action_status(){
	    return _action_status;
	    }
};
int Action::_id_gen=1;

class Device{
  string _device_info;
  State _device_state;
  map<int, Action> _actions;
  public:
  Device(int st):_device_state(static_cast<State>(st)){}
  void set_state(int st){
  _device_state=static_cast<State>(st);
  }
  void set_action(Action& ac){
    _actions[ ac.get_action_id()]=ac;
  }
  Action get_action(int id){
    return _actions.find(id)->second;
  }
  int get_state(){
  return _device_state;
  }
  string get_info(){
  return _device_info;
  }
};

class DevicePool{
    map<int, Device*> _pool;
    static DevicePool* _self;
    
    DevicePool(){}
    DevicePool(const DevicePool&)=delete;
    DevicePool& operator=(const DevicePool&)=delete;
    
    public:
    static DevicePool* getInstance(){
	    if(_self==nullptr)
		    _self=new DevicePool();
	    return _self;
	    }
    void RegisterDevice(int device_id, int state){
	    Device* app = new Device(state);
	    _pool[device_id]=app;
	    }
    void SetDeviceStatus (int device_id, int state){
	    Device *app =_pool.find(device_id)->second;
	    app->set_state(state);
	    }
    Device *GetDevice(int device_id){
	    return _pool.find(device_id)->second;
	    }
    int Initiate(int device_id, int action_type, string action_param){
	    std::lock_guard<std::mutex> lock(mtx);
	    Device* app=_pool.find(device_id)->second;
	    app->set_state(UPDATING);
	    std::this_thread::sleep_for(std::chrono::seconds(3));
	    Action ac( action_type, action_param);
	    app->set_action(ac);
	    app->set_state(IDLE);
	    return ac.get_action_id();
	    }
    int GetDeviceAction (int device_id, int action_id){
      Device* app=_pool.find(device_id)->second;
      int a_id=app->get_action(action_id).get_action_status();
      return a_id;
	    }
};

DevicePool* DevicePool::_self=nullptr;



