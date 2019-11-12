// Week 1 - Implementing Game Agents.cpp: A program using the TL-Engine

#include <TL-Engine.h>	// TL-Engine include file and namespace
using namespace tle;

class Vec3D {
public:
	float x;
	float y;
	float z;
	Vec3D() {
		x = 0;
		y = 0;
		z = 0;
	}
	Vec3D(float arg_x, float arg_y, float arg_z) {
		x = arg_x;
		y = arg_y;
		z = arg_z;
	}
	Vec3D(Vec3D* arg_vector) {
		x = arg_vector->x;
		y = arg_vector->y;
		z = arg_vector->z;
	}
	Vec3D* operator+(Vec3D* arg_vector) {
		float new_x = x + arg_vector->x;
		float new_y = y + arg_vector->y;
		float new_z = z + arg_vector->z;
		Vec3D* new_vector = new Vec3D(new_x, new_y, new_z);
		return new_vector;
	}
	Vec3D* operator-(Vec3D* arg_vector) {
		float new_x = x - arg_vector->x;
		float new_y = y - arg_vector->y;
		float new_z = z - arg_vector->z;
		Vec3D* new_vector = new Vec3D(new_x, new_y, new_z);
		return new_vector;
	}
	Vec3D* operator*(float arg_float) {
		float new_x = x * arg_float;
		float new_y = y * arg_float;
		float new_z = z * arg_float;
		Vec3D* new_vector = new Vec3D(new_x, new_y, new_z);
		return new_vector;
	}
	void operator+=(Vec3D* arg_vector) {
		x += arg_vector->x;
		y += arg_vector->y;
		z += arg_vector->z;
	}
	void operator-=(Vec3D* arg_vector) {
		x -= arg_vector->x;
		y -= arg_vector->y;
		z -= arg_vector->z;
	}
	float get_distance() {
		return sqrt(x * y * z);
	}
	void normalise() {
		x /= get_distance();
		y /= get_distance();
		z /= get_distance();
	}
	Vec3D* cross_product(Vec3D* arg_target) {
		Vec3D* cross_vector;
		cross_vector->x = y * arg_target->z - arg_target->y * z;
		cross_vector->y = z * arg_target->x - arg_target->z * x;
		cross_vector->z = x * arg_target->y - arg_target->x * y;
		return cross_vector;
	}
};

class Vec2D {
public:
	float x;
	float y;
	float z;
	Vec2D() {
		x = 0;
		y = 0;
	}
	Vec2D(float arg_x, float arg_y) {
		x = arg_x;
		y = arg_y;
	}
	Vec2D(Vec2D* arg_vector) {
		x = arg_vector->x;
		y = arg_vector->y;
	}
	Vec2D* operator+(Vec2D* arg_vector) {
		float new_x = x + arg_vector->x;
		float new_y = y + arg_vector->y;
		Vec2D* new_vector = new Vec2D(new_x, new_y);
		return new_vector;
	}
	Vec2D* operator-(Vec2D* arg_vector) {
		float new_x = x - arg_vector->x;
		float new_y = y - arg_vector->y;
		Vec2D* new_vector = new Vec2D(new_x, new_y);
		return new_vector;
	}
	Vec2D* operator*(float arg_float) {
		float new_x = x * arg_float;
		float new_y = y * arg_float;
		Vec2D* new_vector = new Vec2D(new_x, new_y);
		return new_vector;
	}
	void operator+=(Vec2D* arg_vector) {
		x += arg_vector->x;
		y += arg_vector->y;
	}
	void operator-=(Vec2D* arg_vector) {
		x -= arg_vector->x;
		y -= arg_vector->y;
	}
	float get_distance() {
		return sqrt(x * y);
	}
	void normalise() {
		x /= get_distance();
		y /= get_distance();
	}
	float dot_product(Vec2D* arg_target) {
		return (x * arg_target->x) + (y * arg_target->y);
	}
	float angle_in_radians() {
		return atan2(x, y);
	}
	float angle_in_degrees() {
		return angle_in_radians() * 180 / 3.14159265359;
	}
};

class GameObject {
public:
	I3DEngine* engine;
	IMesh* mesh;
	IModel* model;
	Vec2D* position;
	Vec2D* movement;
	float rotation;
	EKeyCode key_turn_cw;
	EKeyCode key_turn_ccw;
	EKeyCode key_forward;
	EKeyCode key_backward;
	EKeyCode key_left;
	EKeyCode key_right;
	float move_speed = 0.0000015f;
	float drag = 0.001f;
	string state = "idle";
	int state_timer = 0;
	GameObject() {
		position = new Vec2D();
		movement = new Vec2D();
	}
	GameObject(IMesh* arg_mesh, Vec2D* arg_position, Vec2D* arg_movement) {
		position = arg_position;
		movement = arg_movement;
		model = arg_mesh->CreateModel();
	}
	Vec2D* GetPosition() {
		return position;
	}
	void SetPosition(Vec2D* arg_vector) {
		position->x = arg_vector->x;
		position->y = arg_vector->x;
		position->z = arg_vector->x;
	}
	Vec2D* GetMovement() {
		return movement;
	}
	void SetMovement(Vec2D* arg_vector) {
		movement->x = arg_vector->x;
		movement->y = arg_vector->x;
		movement->z = arg_vector->x;
	}
	void MovePosition(Vec2D* arg_position) {
		position = *position + arg_position;
	}
	void RotateToDirection() {
		rotation = movement->angle_in_degrees();
	}
	void RotateToTarget(GameObject* arg_target) {
		Vec2D* target_vector = *arg_target->position - position;
		rotation = target_vector->angle_in_degrees();
	}
	void UpdateModel() {
		model->SetPosition(position->x, 0, position->y);
		model->ResetOrientation();
		model->RotateLocalY(rotation);
	}
	void SetKeys(EKeyCode arg_key_left, EKeyCode arg_key_right, EKeyCode arg_key_forward, EKeyCode arg_key_backward) {
		key_left = arg_key_left;
		key_right = arg_key_right;
		key_forward = arg_key_forward;
		key_backward = arg_key_backward;
	}
	void apply_input() {
		if (engine->KeyHeld(key_forward)) {
			*movement += new Vec2D(0, move_speed);
		}
		if (engine->KeyHeld(key_backward)) {
			*movement += new Vec2D(0, -move_speed);
		}
		if (engine->KeyHeld(key_left)) {
			*movement += new Vec2D(-move_speed, 0);
		}
		if (engine->KeyHeld(key_right)) {
			*movement += new Vec2D(move_speed, 0);
		}
	}
	void apply_movement() {
		*position += movement;
	}
	void reset_movement() {
		*movement = Vec2D(0, 0);
	}
	void apply_drag() {
		movement = *movement - (*movement * drag);
	}
	void set_engine(I3DEngine* arg_engine) {
		engine = arg_engine;
	}
	int distance_from_object(GameObject* arg_object) {
		Vec2D* difference_vector = *position - arg_object->position;
		return difference_vector->get_distance();
	}
	void change_state(string arg_state) {
		state = arg_state;
		state_timer = 0;
	}
	void look_at(GameObject* arg_target) {
		Vec2D* target_direction = *arg_target->position - position;
		target_direction->normalise();
		float target_angle = target_direction->angle_in_degrees();
	}
};

class StateBox : public GameObject {
public:
	using GameObject::GameObject;
	void run_state() {
		if (state == "idle") {
			idle();
		}
		if (state == "alert") {
			alert();
		}
		if (state == "dead") {
			dead();
		}
	}
	void idle() {
		if (state_timer = 0) {
			model->SetSkin("");
		}
	}
	void alert() {

	}
	void dead() {

	}
};

class Guard : public GameObject {
public:
	using GameObject :: GameObject;
	StateBox* state_box;
	GameObject* target;
	string idle_skin;
	string alert_skin;
	string dead_skin;
	void run_state() {
		if (state == "idle") {
			idle();
		}
		if (state == "alert") {
			alert();
		}
		if (state == "dead") {
			dead();
		}
		state_timer++;
	}
	void set_target(GameObject* arg_target) {
		target = arg_target;
	}
	void idle() {
		if (state_timer == 0) {
			model->SetSkin(alert_skin);
		}
	}
	void alert() {

	}
	void dead() {

	}
	void set_skins(string arg_idle_skin, string arg_alert_skin, string arg_dead_skin) {
		idle_skin = arg_idle_skin;
		alert_skin = arg_alert_skin;
		dead_skin = arg_dead_skin;
	}
};

void main()
{
	// Create a 3D engine (using TLX engine here) and open a window for it
	I3DEngine* myEngine = New3DEngine(kTLX);
	myEngine->StartWindowed();

	// Add default folder for meshes and other media
	myEngine->AddMediaFolder("C:\\ProgramData\\TL-Engine\\Media");
	myEngine->AddMediaFolder("./models");

	// Load meshes
	IMesh* mesh_guard = myEngine->LoadMesh("Casual_A.x");
	IMesh* mesh_thief = myEngine->LoadMesh("sierra.x");
	IMesh* mesh_state = myEngine->LoadMesh("state.x");

	// Create thief
	GameObject* thief = new GameObject(mesh_thief, new Vec2D(0, 0), new Vec2D(0, 0));
	thief->set_engine(myEngine);
	thief->SetKeys(Key_Left,Key_Right,Key_Up,Key_Down);

	// Create guard
	GameObject* guard = new GameObject(mesh_guard, new Vec2D(0, 0), new Vec2D(0, 0));

	// Create state
	StateBox* state = new StateBox(mesh_state, new Vec2D(0, 0), new Vec2D(0, 0));

	// Create camera
	ICamera* camera = myEngine->CreateCamera(kManual,0,10,-10);
	camera->RotateX(45);


	// The main game loop, repeat until engine is stopped
	while (myEngine->IsRunning())
	{
		// Draw the scene
		myEngine->DrawScene();

		/**** Update your scene each frame here ****/

		// Thief input
		thief->apply_input();

		// Apply thief movement
		thief->apply_movement();

		// Apply rotation
		thief->RotateToDirection();
		guard->RotateToTarget(thief);

		// Reset thief movement
		thief->apply_drag();

		// Run
		//guard->run_state();
		//guard->state_box->run_state();

		// Update models
		thief->UpdateModel();
		guard->UpdateModel();
		//guard->state_box->UpdateModel();
		//state->UpdateModel();

		// Get distance


		// Close engine
		if (myEngine->KeyHit(Key_Escape)) {
			myEngine->Stop();
		}
	}

	// Delete the 3D engine now we are finished with it
	myEngine->Delete();
}
