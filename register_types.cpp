#include "register_types.h"

#include "core/class_db.h"
#include "mujoco.h"

void register_mujoco_types() {
	ClassDB::register_class<Mujoco>();
}

void unregister_mujoco_types() {
	// Nothing to do here in this example.
}
