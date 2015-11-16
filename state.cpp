#include "state.h"

void State::enter(const Node* fromState) {
    emit_signal( "enter_state", fromState);
}

void State::exit(const Node* toState) {
    emit_signal( "exit_state", toState);
}

void State::execute(float deltaTime) {
    emit_signal("execute_state", deltaTime);
}

void State::_bind_methods() {
    ADD_SIGNAL( MethodInfo( "enter_state", PropertyInfo(Variant::OBJECT, "from_state") ) );
    ADD_SIGNAL( MethodInfo( "exit_state", PropertyInfo(Variant::OBJECT, "to_state") ) );
    ADD_SIGNAL( MethodInfo( "execute_state", PropertyInfo(Variant::REAL,"delta")) );
}

State::State() {

}
