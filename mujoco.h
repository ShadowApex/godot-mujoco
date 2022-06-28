#ifndef GODOT_MUJOCO_H
#define GODOT_MUJOCO_H

#include "core/reference.h"
#include <mujoco/mujoco.h>

// mjModel
class MujocoModel : public Reference {
	GDCLASS(MujocoModel, Reference);
	mjModel *model;
	mjData *data;

protected:
	static void _bind_methods();

public:
	void setModel(mjModel *m);
	void step();

	MujocoModel();
	~MujocoModel();
};

// Mujoco singleton
class Mujoco : public Reference {
	GDCLASS(Mujoco, Reference);

protected:
	static void _bind_methods();

public:
	Ref<MujocoModel> load_xml(String p_txt);

	Mujoco();
};

#endif // GODOT_MUJOCO_H
