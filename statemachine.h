#ifndef STATEMACHINE_H
#define STATEMACHINE_H

#include "scene/main/node.h"
#include "core/map.h"
#include "core/list.h"
#include "state.h"

class StateMachine : public Node
{
    OBJ_TYPE(StateMachine, Node);
private:
    Map<StringName, State*> stateMap;
    List<State*> stateStack;

    void add_child_nodes_as_states();
    void change_state(State *toState, State *fromState);

protected:
    static void _bind_methods();
    void _notification(int p_notification);
public:
    StateMachine();

    void add_new_state(Node* newState);
    StringArray get_all_state_names();
    int get_state_amount();

    State* get_active_state();
    void change_active_state_with_name(const StringName toStateName);
    void change_active_state_with_node(Node* toState);
    void step_back_state();

    void execute_active_state(float deltaTime);

};

#endif // STATEMACHINE_H
