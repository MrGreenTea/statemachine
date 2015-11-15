#include "register_types.h"
#include "object_type_db.h"

#include "statemachine.h"
#include "state.h"

void register_statemachine_types() {
    ObjectTypeDB::register_type<StateMachine>();
    ObjectTypeDB::register_type<State>();
}



void unregister_statemachine_types() {


}
