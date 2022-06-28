#include "mujoco.h"
#include "core/os/memory.h"
#include "core/print_string.h"
#include "core/reference.h"
#include "mujoco/mjtnum.h"
#include <mujoco/mujoco.h>

#define CreateThenReturnRID(owner, ridData) \
	RID rid = owner.make_rid(ridData);      \
	ridData->set_self(rid);                 \
	ridData->_set_physics_server(this);     \
	return rid;

#define mujoconew(cl) \
	new cl

// Mujoco
Mujoco::Mujoco() {
	if (mjVERSION_HEADER != mj_version()) {
		print_error("Header version does not match library version!");
	}
}

Ref<MujocoModel> Mujoco::load_xml(String p_txt) {
	// convert Godot String to Godot CharString to C string
	char error[1000] = "Could not load binary model";
	mjModel *m = mj_loadXML(p_txt.ascii().get_data(), nullptr, error, 1000);
	if (!m) {
		ERR_PRINT(error);
	}

	// Create a Godot mjModel
	Ref<MujocoModel> model = memnew(MujocoModel);
	model->setModel(m);

	return model;
}

void Mujoco::_bind_methods() {
	ClassDB::bind_method(D_METHOD("load_xml", "txt"), &Mujoco::load_xml);
}

// Mujoco Model
MujocoModel::MujocoModel() {
}

MujocoModel::~MujocoModel() {
	mj_deleteModel(this->model);
	mj_deleteData(this->data);
}

void MujocoModel::setModel(mjModel *m) {
	this->model = m;
	this->data = mj_makeData(m);
}

void MujocoModel::step() {
	print_line("Start Stepping!");
	// advance interactive simulation for 1/60 sec
	//  Assuming MuJoCo can simulate faster than real-time, which it usually can,
	//  this loop will finish on time for the next frame to be rendered at 60 fps.
	//  Otherwise add a cpu timer and exit this loop when it is time to render.
	mjtNum sim_start = this->data->time;
	while (this->data->time - sim_start < 1.0 / 60.0) {
		print_line("Stepping!");
		mj_step(this->model, this->data);
	}
}

void MujocoModel::_bind_methods() {
	ClassDB::bind_method(D_METHOD("step"), &MujocoModel::step);
}
