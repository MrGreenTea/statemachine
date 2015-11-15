#ifndef STATEMACHINE_H
#define STATEMACHINE_H

#include "scene/main/node.h"
#include "core/hash_map.h"
#include "core/dictionary.h"
#include "core/map.h"
#include "state.h"

class StateMachine : public Node
{
    OBJ_TYPE(StateMachine, Node);
private:
    Map<StringName, State*> stateMap;
    State* currentState;
    State* previousState;

    void add_child_nodes_as_states();

protected:
    static void _bind_methods();
    void _notification(int p_notification);
public:
    StateMachine();

    StringArray get_all_states();
    int get_state_amount();

    void execute(float deltaTime);
    void change_with_name(const StringName toStateName);
    void change_with_node(Node* toState);
    void add(Node* newState);

};

#endif // STATEMACHINE_H
