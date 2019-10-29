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
	Vec3D(float param_x, float param_y, float param_z) {
		x = param_x;
		y = param_y;
		z = param_z;
	}
	Vec3D* operator+(Vec3D* param_vector) {
		float new_x = x + param_vector->x;
		float new_y = y + param_vector->y;
		float new_z = z + param_vector->z;
		Vec3D* new_vector = new Vec3D(new_x, new_y, new_z);
		return new_vector;
	}
	Vec3D* operator-(Vec3D* param_vector) {
		float new_x = x - param_vector->x;
		float new_y = y - param_vector->y;
		float new_z = z - param_vector->z;
		Vec3D* new_vector = new Vec3D(new_x, new_y, new_z);
		return new_vector;
	}
	Vec3D* operator*(float param_float) {
		float new_x = x * param_float;
		float new_y = y * param_float;
		float new_z = z * param_float;
		Vec3D* new_vector = new Vec3D(new_x, new_y, new_z);
		return new_vector;
	}
	void operator+=(Vec3D* param_vector) {
		x += param_vector->x;
		y += param_vector->y;
		z += param_vector->z;
	}
	void operator-=(Vec3D* param_vector) {
		x -= param_vector->x;
		y -= param_vector->y;
		z -= param_vector->z;
	}
	float get_distance() {
		return sqrt(x * y * z);
	}
};

class GameObject {
public:
	GameObject* child_object;
	I3DEngine* engine;
	IMesh* mesh;
	IModel* model;
	Vec3D* position;
	Vec3D* movement;
	EKeyCode key_turn_cw;
	EKeyCode key_turn_ccw;
	EKeyCode key_forward;
	EKeyCode key_backward;
	EKeyCode key_left;
	EKeyCode key_right;
	float move_speed = 0.0000015f;
	float drag = 0.001f;
	string state = "idle";
	GameObject() {
		position = new Vec3D();
		movement = new Vec3D();
	}
	GameObject(IMesh* param_mesh, Vec3D* param_position, Vec3D* param_movement) {
		position = param_position;
		movement = param_movement;
		model = param_mesh->CreateModel();
	}
	Vec3D* GetPosition() {
		return position;
	}
	void SetPosition(Vec3D* param_vector) {
		position->x = param_vector->x;
		position->y = param_vector->x;
		position->z = param_vector->x;
	}
	Vec3D* GetMovement() {
		return movement;
	}
	void SetMovement(Vec3D* param_vector) {
		movement->x = param_vector->x;
		movement->y = param_vector->x;
		movement->z = param_vector->x;
	}
	void MovePosition(Vec3D* param_position) {
		position = *position + param_position;
	}
	void UpdateModel() {
		model->SetPosition(position->x, position->y, position->z);
	}
	void SetKeys(EKeyCode param_key_left, EKeyCode param_key_right, EKeyCode param_key_forward, EKeyCode param_key_backward) {
		key_left = param_key_left;
		key_right = param_key_right;
		key_forward = param_key_forward;
		key_backward = param_key_backward;
	}
	void apply_input() {
		if (engine->KeyHeld(key_forward)) {
			*movement += new Vec3D(0, 0, move_speed);
		}
		if (engine->KeyHeld(key_backward)) {
			*movement += new Vec3D(0, 0, -move_speed);
		}
		if (engine->KeyHeld(key_left)) {
			*movement += new Vec3D(-move_speed, 0, 0);
		}
		if (engine->KeyHeld(key_right)) {
			*movement += new Vec3D(move_speed, 0, 0);
		}
	}
	void apply_movement() {
		*position += movement;
	}
	void reset_movement() {
		*movement = Vec3D(0, 0, 0);
	}
	void apply_drag() {
		movement = *movement - (*movement * drag);
	}
	void set_engine(I3DEngine* param_engine) {
		engine = param_engine;
	}
	void idle() {
		
	}
	void alert() {

	}
	void dead() {

	}
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
	int distance_from_object(GameObject* param_object) {
		Vec3D* difference_vector = *position - param_object->position;
		return difference_vector->get_distance();
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
	GameObject* thief = new GameObject(mesh_thief, new Vec3D(0, 1, 10), new Vec3D(0, 0, 0));
	thief->set_engine(myEngine);
	thief->SetKeys(Key_Left,Key_Right,Key_Up,Key_Down);

	// Create guard
	GameObject* guard = new GameObject(mesh_guard, new Vec3D(0, 0, 0), new Vec3D(0, 0, 0));

	// Create state
	GameObject* state = new GameObject(mesh_state, new Vec3D(0, 2, 0), new Vec3D(0, 0, 0));

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

		// Reset thief movement
		thief->apply_drag();

		// Update models
		thief->UpdateModel();
		guard->UpdateModel();
		state->UpdateModel();

		// Close engine
		if (myEngine->KeyHit(Key_Escape)) {
			myEngine->Stop();
		}
	}

	// Delete the 3D engine now we are finished with it
	myEngine->Delete();
}
