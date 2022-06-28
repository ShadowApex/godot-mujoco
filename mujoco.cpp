#include "mujoco.h"
#include <mujoco/mujoco.h>

bool Mujoco::say_text(String p_txt) {
	// convert Godot String to Godot CharString to C string
	//return festival_say_text(p_txt.ascii().get_data());
	char error[1000] = "Could not load binary model";
	mj_loadXML(p_txt.ascii().get_data(), 0, error, 1000);
	return false;
}

void Mujoco::_bind_methods() {
	ClassDB::bind_method(D_METHOD("say_text", "txt"), &Mujoco::say_text);
}

Mujoco::Mujoco() {
	// festival_initialize(true, 210000); //not the best way to do it as this
	// should only ever be called once.
}
