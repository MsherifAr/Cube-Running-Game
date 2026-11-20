#pragma once

#include <cstdint>
#include <cmath>
#include <fstream>
#include <string>
#include <glad\glad.h>
#include <glfw\glfw3.h>
#include <ctime>
#include "LinkedLists.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <stb_image.h>

using OpenID = unsigned int;

using Vector2 = glm::vec2;
using Vector3 = glm::vec3;
using Vector4 = glm::vec4;
using Mat4 = glm::mat4;

using vec2 = glm::vec2;
using vec3 = glm::vec3;
using vec4 = glm::vec4;
using mat4 = glm::mat4;

const std::string endl = "\n";

void PrintVector3(const char* name, Vector3 vector);

class Texture2D {
	OpenID ID;
public:
	int TextureID = -1;
	Texture2D();
	Texture2D(const std::string& directory, OpenID input = GL_RGB, OpenID output = GL_RGB);
	void Wraping_x(OpenID setting = GL_REPEAT);
	void Wraping_y(OpenID setting = GL_REPEAT);
	void Minimizing_filter(OpenID setting = GL_LINEAR_MIPMAP_LINEAR);
	void Maximizing_filter(OpenID setting = GL_LINEAR);
	void GenerateMipmaps();
	void Load(const std::string& directory, OpenID input = GL_RGB, OpenID output = GL_RGB);
	void unLoad();
	void Use();
	void UnUse();
	OpenID getID();
};

class Object {
public:
	Vector3 position = { 0.0f, 0.0f, 0.0f };
	Vector3 rotation = { 0.0f, 0.0f, 0.0f };
	Vector3  scale   = { 1.0f, 1.0f, 1.0f };

	Vector3 RelativeForward();
	Vector3 RelativeRight();
	Vector3 RelativeUp();

	Mat4 getTransform();
};

enum Camera_Settings {
	PERSPECTIVE,
	ORTHO
};

struct Camera : Object {
private:
	float near_clipping = 0.1f;
	float far_clipping = 100.0f;
	float FOV = 45.0f;

	Mat4 Perspective = Mat4(1.0f);
	Mat4 View = Mat4(1.0f);

public:
	Camera(Camera_Settings view_type, float width, float height, float near = 0.1f, float far = 100.0f, float fov = 45.0f);
	void setup(Camera_Settings view_type, float width, float height, float near = 0.1f, float far = 100.0f, float fov = 45.0f);
	Mat4& getView();
	Mat4& getPerspective();
	void LookAt(Vector3 target);
};

struct Material {
	Texture2D ambient;
	Texture2D diffuse;
	Texture2D specular;
	float shininess;
};

struct Light : Object{
	float intensity = 1.0f;
	float constant = 0.0f;
	float linear = 0.0f;
	float quadratic = 1.0f;

	Vector3 color = vec3(1.0f, 1.0f, 1.0f);
	float thetaSpotLight = 360.0f;
	float epsilon = 0.0f;

	Vector3 ambient;
	Vector3 diffuse;
	Vector3 specular;
};

class Shader {
	OpenID ID;
	OpenID slots[16];

public:
	Shader(const char* Vertex_Shader_Directory, const char* Fragment_Shader_Directory);
	void setFloat(std::string name, float value);
	void setVec2(std::string name, float x, float y);
	void setVec2(std::string name, Vector2 value);
	void setVec3(std::string name, float x, float y, float z);
	void setVec3(std::string name, Vector3 value);
	void setVec4(std::string name, float x, float y, float z, float a);
	void setVec4(std::string name, Vector4 value);
	void setInt(std::string name, int value);
	void setMat4(std::string name, const Mat4& value);
	void setMaterial(std::string name, Material& material);
	void setLight(std::string name, const Light light);
	void setSampler(const std::string& name, Texture2D& texture);
	void setCamera(Camera& camera);
	void setModel(Object& object);
	inline void Use();
	inline void UnUse();
	OpenID getID();
};

std::string ReadFile(const char* directory);

void StartOpenGl(int major = 3, int minor = 3);

int PrintShaderCompilationStatus(OpenID Shader, std::string name = "");

class VBO {
	OpenID ID;
	
public:
	VBO(uint16_t size, float* data);
	void Use();
	void UnUse();
	OpenID getID();
};

class EBO {
	OpenID ID;
	uint16_t nIndices;
public:

	EBO(uint16_t size, unsigned short* data);
	void Use();
	void UnUse();
	OpenID getID();
	uint16_t get_nIndices();
};

class VAO {
	OpenID ID;
	uint16_t nIndices = 0; 
public:
	VAO();
	void Attach_VBO(VBO object);
	void Attach_EBO(EBO object);
	void Setup(short nSize, short nStride, short nBeginning_Index, short location = 0);
	void Use();
	void UnUse();
	uint16_t get_nIndices();
	OpenID getID();
};

void mouse_callback(GLFWwindow* window, double xpos, double ypos);

class Window {
	GLFWwindow* ID;

public:
	Window(std::string name, int width, int height, bool fullscreen);

	void change_Resolution(int width, int height);

	void update();

	void setBackgroundColor(float red, float green, float blue, float alpha);

	void Draw(VAO VertexArrayObject, Shader shader);

	void ShouldClose(bool mode);

	GLFWwindow* getID();
};

void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void SetMouseCursorMode(Window& window, bool mode);
Vector2 getCursorPosition();


void glfw_error_callback(int error, const char* description);


