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
	Vec3D* operator+=(Vec3D* param_vector) {
		x += param_vector->x;
		y += param_vector->y;
		z += param_vector->z;
	}
};

class GameObject {
public:
	IMesh* mesh;
	IModel* model;
	Vec3D* position; 
	Vec3D* movement;
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
		model->SetPosition(position->x,position->y,position->z);
	}
};

void main()
{
	// Create a 3D engine (using TLX engine here) and open a window for it
	I3DEngine* myEngine = New3DEngine( kTLX );
	myEngine->StartWindowed();

	// Add default folder for meshes and other media
	myEngine->AddMediaFolder("C:\\ProgramData\\TL-Engine\\Media");
	myEngine->AddMediaFolder("./models");

	// Load meshes
	IMesh* mesh_guard = myEngine->LoadMesh("Casual_A.x");
	IMesh* mesh_thief = myEngine->LoadMesh("sierra.x");
	IMesh* mesh_state = myEngine->LoadMesh("state.x");

	// Create models
	IModel* model_guard = mesh_guard->CreateModel(0,0,0);
	IModel* model_thief = mesh_thief->CreateModel(0,0,10);
	IModel* model_state = mesh_state->CreateModel(0,2,0);

	// Create gameobject
	GameObject* guard = new GameObject(mesh_guard, new Vec3D(0,0,0), new Vec3D(0,0,0));
	guard->SetPosition(new Vec3D(1, 1, 1));


	// The main game loop, repeat until engine is stopped
	while (myEngine->IsRunning())
	{
		// Draw the scene
		myEngine->DrawScene();

		/**** Update your scene each frame here ****/
		guard->position += new Vec3D(1, 1, 1);
		guard->MovePosition(guard->movement);
		guard->UpdateModel();

	}

	// Delete the 3D engine now we are finished with it
	myEngine->Delete();
}
