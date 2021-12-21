#ifndef CLOSURE_HPP
#define CLOSURE_HPP

#include "../value.hpp"

namespace LLVMToy {
  class ClosureContainer {
    public:
      inline unsigned int get_slot_for(string var_name) {
        if (indexes.count(var_name) > 0) {
          return indexes[var_name];
        } else {
          values.push_back(Value::make_undefined());
          unsigned int new_index = values.size() - 1;
          indexes[var_name] = new_index;
          return new_index;
        }
      }
      inline unsigned int initialize_slot(string var_name, Value initial_value) {
        unsigned int index = get_slot_for(var_name);
        set_slot_value(index, initial_value);
        return index;
      }
      inline void set_slot_value(unsigned int index, Value val){
        values[index] = val;
      }
      inline Value get_slot_value(unsigned int index){
        return values[index];
      }
    private:
      vector<Value> values;
      map<string, unsigned int> indexes;
  };
}

#endif