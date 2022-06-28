#ifndef GODOT_MUJOCO_H
#define GODOT_MUJOCO_H

#include "core/reference.h"

class Mujoco : public Reference {
	GDCLASS(Mujoco, Reference);

protected:
	static void _bind_methods();

public:
	bool say_text(String p_txt);

	Mujoco();
};

#endif // GODOT_MUJOCO_H
