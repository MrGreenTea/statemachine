#include "statemachine.h"
void StateMachine::_notification(int p_notification) {
    switch (p_notification) {
        case NOTIFICATION_ENTER_TREE: {
            this->add_child_nodes_as_states();
        }
    }
}

void StateMachine::add_child_nodes_as_states() {
    for (int i = 0; i < get_child_count(); i++) {
        this->add(get_child(i));
    }
}

void StateMachine::add(Node* newState) {
    ERR_FAIL_NULL(newState);
    ERR_FAIL_COND(newState->get_type() != "State");
    String stateName = newState->get_name();
    ERR_FAIL_COND(this->stateMap.has(stateName));
    this->stateMap[stateName] = dynamic_cast<State*>(newState);
}

StringArray StateMachine::get_all_states() {
    StringArray state_name_list;
    Map<StringName, State*>::Element *iterator = stateMap.front();
     while (iterator) {
        state_name_list.append(iterator->key());
        iterator = iterator->next();
    }
    return state_name_list;
}

void StateMachine::get_state_amount() {
    return this->stateMap.size();
}

void StateMachine::execute(const float deltaTime) {
    ERR_FAIL_NULL(this->currentState);
    this->currentState->execute(deltaTime);
}

void StateMachine::change_with_name(const StringName toStateName) {
    ERR_FAIL_COND(this->stateMap.size() == 0);
    ERR_FAIL_COND(!this->stateMap.has(toStateName));
    this->change_with_node(this->stateMap[toStateName]);
}

void StateMachine::change_with_node(Node* toStateNode) {
    ERR_FAIL_COND(toStateNode->get_type() != "State");
    State* castedStateNode = dynamic_cast<State*>(toStateNode);
    if (this->currentState == castedStateNode) {
        WARN_PRINT("Tried changing to currently active state. This will exit and immediatlely enter that state and can lead to unpredicted behaviour");
    }
    if (this->currentState) {
        this->currentState->exit(castedStateNode);
        this->previousState = this->currentState;
    }
    this->currentState = castedStateNode;
    this->currentState->enter(this->previousState);
}

void StateMachine::_bind_methods() {
    ObjectTypeDB::bind_method(_MD("get_all_state_names"), &StateMachine::get_all_states);
    ObjectTypeDB::bind_method(_MD("get_state_amount"), &StateMachine::get_state_amount);
    ObjectTypeDB::bind_method(_MD("add_state", "name:String", "state:State"), &StateMachine::add);
    ObjectTypeDB::bind_method(_MD("execute_current_state", "delta:float"), &StateMachine::execute);
    ObjectTypeDB::bind_method(_MD("change_state_with_name", "name:String"), &StateMachine::change_with_name);
    ObjectTypeDB::bind_method(_MD("change_state_with_node", "state:State"), &StateMachine::change_with_node);

}

StateMachine::StateMachine()
{

}

