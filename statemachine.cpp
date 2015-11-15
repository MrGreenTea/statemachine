#include "statemachine.h"
void StateMachine::_notification(int p_notification) {
    switch (p_notification) {
        case NOTIFICATION_ENTER_TREE: {
            add_child_nodes_as_states();
        }
    }
}

void StateMachine::add_child_nodes_as_states() {
    for (int i = 0; i < get_child_count(); i++) {
        add_new_state(get_child(i));
    }
}

void StateMachine::add_new_state(Node* newState) {
    ERR_FAIL_NULL(newState);
    ERR_FAIL_COND(newState->get_type() != "State");
    String stateName = newState->get_name();
    ERR_FAIL_COND(stateMap.has(stateName));
    stateMap[stateName] = dynamic_cast<State*>(newState);
}

StringArray StateMachine::get_all_state_names() {
    StringArray state_name_list;
    Map<StringName, State*>::Element *currentElement = stateMap.front();
     while (currentElement) {
        state_name_list.append(currentElement->key());
        currentElement = currentElement->next();
    }
    return state_name_list;
}

int StateMachine::get_state_amount() {
    return stateMap.size();
}

State* StateMachine::get_active_state() {
    if (stateStack.size() > 0) {
        return stateStack.back()->get();
    }
    return NULL;
}

void StateMachine::execute_active_state(const float deltaTime) {
    ERR_FAIL_NULL(get_active_state());
    get_active_state()->execute(deltaTime);
}

void StateMachine::change_active_state_with_name(const StringName toStateName) {
    ERR_FAIL_COND(stateMap.size() == 0);
    ERR_FAIL_COND(!stateMap.has(toStateName));
    change_active_state_with_node(stateMap[toStateName]);
}

void StateMachine::change_state(State* toState, State* fromState) {
    ERR_FAIL_NULL(toState);
    if (toState == fromState) {
        WARN_PRINT("Tried changing to the already active state. This will exit and immediatlely enter that same state and can lead to unpredicted behaviour");
    }
    if (fromState) {
        fromState->exit(toState);
    }
    toState->enter(fromState);
}

void StateMachine::change_active_state_with_node(Node* toStateNode) {
    ERR_FAIL_NULL(toStateNode);
    State* castedToState = dynamic_cast<State*>(toStateNode);
    State* castedFromState = get_active_state();
    change_state(castedToState, castedFromState);
    stateStack.push_back(castedToState);
}

void StateMachine::step_back_state() {
    ERR_FAIL_COND(stateStack.size() < 2);
    State* toState = stateStack.back()->prev()->get();
    State* fromState = get_active_state();
    change_state(toState, fromState);
    stateStack.pop_back();
}

void StateMachine::_bind_methods() {
    ObjectTypeDB::bind_method(_MD("get_all_state_names"), &StateMachine::get_all_state_names);
    ObjectTypeDB::bind_method(_MD("get_state_amount"), &StateMachine::get_state_amount);

    ObjectTypeDB::bind_method(_MD("add_state", "name:String", "state:State"), &StateMachine::add_new_state);

    ObjectTypeDB::bind_method(_MD("get_active_state"), &StateMachine::execute_active_state);
    ObjectTypeDB::bind_method(_MD("execute_current_state", "delta:float"), &StateMachine::execute_active_state);

    ObjectTypeDB::bind_method(_MD("change_active_state_with_name", "name:String"), &StateMachine::change_active_state_with_name);
    ObjectTypeDB::bind_method(_MD("change_active_state_with_node", "state:State"), &StateMachine::change_active_state_with_node);
    ObjectTypeDB::bind_method(_MD("step_back_state"), &StateMachine::step_back_state);
}

StateMachine::StateMachine()
{

}

