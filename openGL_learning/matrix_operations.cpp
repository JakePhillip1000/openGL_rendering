#include <iostream>
#include <cmath>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>
#include <vector>

using namespace std;

// --------------------------------------------------------------
// Create matrix transformation (this is just for testing purpose)
static void MatrixTransformation() {
	glm::vec4 vec(1.0f, 0.0f, 0.0f, 1.0f); // 4d vec (x=1, y=0, z=0, w=1)
	glm::mat4 trans = glm::mat4(1.0f); // creating identity matrix
	trans = glm::translate(trans, glm::vec3(1.0f, 1.0f, 0.0f));
	vec = trans * vec;

	cout << "Testing matrix transformation: "
		<< vec.x << " " << vec.y << " " << vec.z << endl;
}

static void MatrixScaling_and_Rotation() {
	glm::vec4 vec(1.0f, 0.0f, 0.0f, 1.0f);
	glm::mat4 trans = glm::mat4(1.0f);

	trans = glm::rotate(trans, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	trans = glm::scale(trans, glm::vec3(0.5f, 0.5f, 0.5f));

	cout << "Testing matrix Rotating and Scaling: "
		<< vec.x << " " << vec.y << " " << vec.z << endl;
}

static void IdentityMatrixTest() {
	glm::vec4 position(1.0f, 0.0f, 0.0f, 1.0f);
	glm::mat4 identity_matrix(1.0f);
	cout << "Position: (" << position.x << ", " << position.y << ", " << position.z << ", " << position.w << ")" << endl;
}

static void DotProd_CrossProd() {
	glm::vec3 a(1, 0, 1);
	glm::vec3 b(0, 1, 0);

	float dotProd = glm::dot(a, b);
	glm::vec3 cross = glm::cross(a, b);

	cout << "Dot Product: " << dotProd << endl;
	cout << "Cross: " << cross.x << ", " << cross.y << ", " << cross.z << endl;
}

static void TransformMatrix() {
	glm::mat4 model = glm::mat4(1.0f);

	model = glm::translate(model, glm::vec3(2.0f, 3.0f, 4.0f));
	model = glm::rotate(model, glm::radians(45.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	model = glm::scale(model, glm::vec3(1.5f, 1.5f, 1.5f));
}

static void ProjectionMatrix() {
	// perspective projection
	float fov = 45.0f;
	float aspect = 16.0f / 9.0f;
	float nearPlane = 0.1f;
	float farPlane = 100.0f;

	glm::mat4 projection = glm::perspective(
		glm::radians(fov),
		aspect,
		nearPlane,
		farPlane
	);

	cout << "Projection Matrix:\n" << glm::to_string(projection) << endl;
}
// --------------------------------------------------------------


/*
int main() {
	cout << "===== Matrix Operations =====" << endl;
	MatrixTransformation();	
	MatrixScaling_and_Rotation();
	IdentityMatrixTest();
	DotProd_CrossProd();
	TransformMatrix();
	ProjectionMatrix();
}
*/