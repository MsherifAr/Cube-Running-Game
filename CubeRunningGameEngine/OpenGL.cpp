#pragma once

#define STB_IMAGE_IMPLEMENTATION
#include "OpenGL.h"

void PrintVector3(const char* name, Vector3 vector) {
	std::cout << name << " : (" << vector.x << ", " << vector.y << ", " << vector.z << ")\n";
}

std::string ReadFile(const char* directory) {
	std::ifstream file(directory);
	if (!file.is_open()) {
		std::cout << "Error :: Loading " << directory << "Failed !!" << endl;
		assert(0);
	}

	std::string temp;
	std::string result;

	int SharedStructsHeaderIgnore = 0;
	while (std::getline(file, temp)) {
		result += temp + endl;
	}

	return result;
}

void StartOpenGl(int major, int minor) {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, major);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minor);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

}

int PrintShaderCompilationStatus(OpenID Shader, std::string name) {
	int success;
	char infoLog[512];
	glGetShaderiv(Shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(Shader, 512, NULL, infoLog);
		std::cout << "ERROR :: " << name << " SHADER COMPILATION FAILED\n" << infoLog << endl;
		assert(0);
	}
	else {
		std::cout << name << " Shader has been compiled successfully" << endl;
	}
	return success;
}


	VBO::VBO(uint16_t size, float* data) {
		glGenBuffers(1, &ID);
		glBindBuffer(GL_ARRAY_BUFFER, ID);
		glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void VBO::Use() {
		glBindBuffer(GL_ARRAY_BUFFER, ID);
	}

	void VBO::UnUse() {
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	OpenID VBO::getID() {
		return ID;
	}



	EBO::EBO(uint16_t size, unsigned short* data) {
		glGenBuffers(1, &ID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
		nIndices = size / sizeof(unsigned short);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	void EBO::Use() {
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
	}
	void EBO::UnUse() {
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	OpenID EBO::getID() {
		return ID;
	}

	uint16_t EBO::get_nIndices() {
		return nIndices;
	}



	VAO::VAO() {
		glGenVertexArrays(1, &ID);
	}

	void VAO::Attach_VBO(VBO object) {
		glBindVertexArray(ID);
		glBindBuffer(GL_ARRAY_BUFFER, object.getID());
		glBindVertexArray(0);
	}

	void VAO::Attach_EBO(EBO object) {
		glBindVertexArray(ID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, object.getID());
		nIndices = object.get_nIndices();
		glBindVertexArray(0);
	}

	void VAO::Setup(short nSize, short nStride, short nBeginning_Index, short location) {
		glBindVertexArray(ID);
		glVertexAttribPointer(location, nSize, GL_FLOAT, GL_FALSE, nStride * sizeof(float), ((void*)(nBeginning_Index * sizeof(float))));
		glEnableVertexAttribArray(location);
		glBindVertexArray(0);
	}

	void VAO::Use() {
		glBindVertexArray(ID);
	}

	void VAO::UnUse() {
		glBindVertexArray(0);
	}

	uint16_t VAO::get_nIndices() {
		return nIndices;
	}

	OpenID VAO::getID() {
		return ID;
	}

	Texture2D::Texture2D() = default;

	Texture2D::Texture2D(const std::string& directory, OpenID input, OpenID output) {
		int width, height, nrChannels;
		unsigned char* data = stbi_load(directory.c_str(), &width, &height, &nrChannels, 0);
		if (!data) {
			std::cout << "ERROR :: FAILED TO LOAD TEXTURE FROM " << directory << endl;
			assert(0);
		}

		glGenTextures(1, &ID);
		glBindTexture(GL_TEXTURE_2D, ID);

		glTexImage2D(GL_TEXTURE_2D, 0, output, width, height, 0, input, GL_UNSIGNED_BYTE, data);
		Wraping_x();
		Wraping_y();
		Minimizing_filter();
		Maximizing_filter();

		stbi_image_free(data);

		glBindTexture(GL_TEXTURE_2D, 0);
	}

	void Texture2D::Wraping_x(OpenID setting) {
		glBindTexture(GL_TEXTURE_2D, ID);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, setting);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	void Texture2D::Wraping_y(OpenID setting) {
		glBindTexture(GL_TEXTURE_2D, ID);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, setting);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	void Texture2D::Minimizing_filter(OpenID setting) {
		glBindTexture(GL_TEXTURE_2D, ID);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, setting);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	void Texture2D::Maximizing_filter(OpenID setting) {
		glBindTexture(GL_TEXTURE_2D, ID);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, setting);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	void Texture2D::GenerateMipmaps() {
		glBindTexture(GL_TEXTURE_2D, ID);
		glGenerateMipmap(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	void Texture2D::Load(const std::string& directory, OpenID input, OpenID output) {
		Texture2D(directory, input, output);
	}

	void Texture2D::unLoad() {
		if (ID != 0) {
			glDeleteTextures(1, &ID);
		}
		else {
			std::cout << "WARNING :: TEXTURE IS ALREADY UNLOADED" << endl;
		}
	}

	void Texture2D::Use() {
		glBindTexture(GL_TEXTURE_2D, ID);
	}
	void Texture2D::UnUse() {
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	OpenID Texture2D::getID() {
		return ID;
	}



	Shader::Shader(const char* Vertex_Shader_Directory, const char* Fragment_Shader_Directory) {
		OpenID VS, FS;
		VS = glCreateShader(GL_VERTEX_SHADER);
		FS = glCreateShader(GL_FRAGMENT_SHADER);

		std::string VertexSourceString = ReadFile(Vertex_Shader_Directory);
		const char* VertexSourceChar = VertexSourceString.c_str();
		glShaderSource(VS, 1, &VertexSourceChar, NULL);
		glCompileShader(VS);
		PrintShaderCompilationStatus(VS, "Vertex");

		std::string FragementSourceString = ReadFile(Fragment_Shader_Directory);
		const char* FragementSourceChar = FragementSourceString.c_str();
		glShaderSource(FS, 1, &FragementSourceChar, NULL);
		glCompileShader(FS);
		PrintShaderCompilationStatus(FS, "Fragment");

		ID = glCreateProgram();
		glAttachShader(ID, VS);
		glAttachShader(ID, FS);
		glLinkProgram(ID);
		glDeleteShader(VS);
		glDeleteShader(FS);

		for (uint16_t x = 0; x < 16; x++) {
			slots[x] = 0;
		}
	}

	void Shader::setFloat(std::string name, float value) {
		Use();
		OpenID UniAddress = glGetUniformLocation(ID, name.c_str());
		glUniform1f(UniAddress, value);
		UnUse();
	}

	void Shader::setVec2(std::string name, float x, float y) {
		Use();
		OpenID UniAddress = glGetUniformLocation(ID, name.c_str());
		glUniform2f(UniAddress, x, y);
		UnUse();
	}
	void Shader::setVec2(std::string name, Vector2 value) {
		Use();
		OpenID UniAddress = glGetUniformLocation(ID, name.c_str());
		glUniform2f(UniAddress, value.x, value.y);
		UnUse();
	}

	void Shader::setVec3(std::string name, float x, float y, float z) {
		Use();
		OpenID UniAddress = glGetUniformLocation(ID, name.c_str());
		glUniform3f(UniAddress, x, y, z);
		UnUse();
	}
	void Shader::setVec3(std::string name, Vector3 value) {
		Use();
		OpenID UniAddress = glGetUniformLocation(ID, name.c_str());
		glUniform3f(UniAddress, value.x, value.y, value.z);
		UnUse();
	}
	
	void Shader::setVec4(std::string name, float x, float y, float z, float a) {
		Use();
		OpenID UniAddress = glGetUniformLocation(ID, name.c_str());
		glUniform4f(UniAddress, x, y, z, a);
		UnUse();
	}

	void Shader::setVec4(std::string name, Vector4 value) {
		Use();
		OpenID UniAddress = glGetUniformLocation(ID, name.c_str());
		glUniform4f(UniAddress, value.x, value.y, value.z, value.w);
		UnUse();
	}

	void Shader::setInt(std::string name, int value) {
		Use();
		OpenID UniAddress = glGetUniformLocation(ID, name.c_str());
		glUniform1i(UniAddress, value);
		UnUse();
	}

	void Shader::setMat4(std::string name, const Mat4& value) {
		Use();
		OpenID UniAddress = glGetUniformLocation(ID, name.c_str());
		glUniformMatrix4fv(UniAddress, 1, GL_FALSE, glm::value_ptr(value));
		UnUse();
	}
	void Shader::setMaterial(std::string name, Material& material) {
		Use();
		std::string ambient = name + ".ambient";
		std::string diffuse = name + ".diffuse";
		std::string specular = name + ".specular";
		std::string shininess = name + ".shininess";

		
		setSampler(ambient, material.ambient);
		setSampler(diffuse, material.diffuse);
		setSampler(specular, material.specular);
		setFloat(shininess, material.shininess);
		
		UnUse();
	}

	void Shader::setLight(std::string name, const Light light) {
		Use();

		// Address names.

		std::string intensity = name + ".intensity";
		std::string constant = name + ".constant";
		std::string linear = name + ".linear";
		std::string quadratic = name + ".quadratic";

		std::string color = name + ".color";
		std::string thetaSpotLight = name + ".thetaSpotLight";
		std::string epsilon = name + ".epsilon";

		std::string position = name + ".position";
		std::string direction = name + ".direction";

		std::string ambient = name + ".ambient";
		std::string diffuse = name + ".diffuse";
		std::string specular = name + ".specular";

		// Transforming the rotations xyz format to directional vector.
		float x_dir = sin(glm::radians(light.rotation.y)) * cos(glm::radians(light.rotation.x));
		float y_dir = -sin(glm::radians(light.rotation.x));
		float z_dir = cos(glm::radians(light.rotation.y)) * cos(glm::radians(light.rotation.x));

		// Using the names, we finally set the values into place.
		setFloat(intensity, light.intensity);
		setFloat(constant, light.constant);
		setFloat(linear, light.linear);
		setFloat(quadratic, light.quadratic);

		setVec3(color, light.color);
		setFloat(thetaSpotLight, cos(glm::radians(light.thetaSpotLight / 2.0f)));
		setFloat(epsilon, light.epsilon);

		setVec3(position, light.position);
		vec3 Lightdirection = vec3(x_dir, y_dir, z_dir);
		setVec3(direction, Lightdirection);

		setVec3(ambient, light.ambient);
		setVec3(diffuse, light.diffuse);
		setVec3(specular, light.specular);

		UnUse();
	}

	void Shader::setSampler(const std::string& name, Texture2D& texture) {
		bool used = false;
		if (texture.TextureID == -1) {
			for (uint16_t x = 0; x < 16; x++) {
				if (slots[x] == 0) {
					texture.TextureID = x;
					slots[x] = texture.getID();
					used = true;
					break;
				}
			}
			if (used == false) {
				std::cout << "ERROR :: OUT TEXTURE SLOTS, ONLY " << 16 << " SLOTS ARE AVAILABLE." << endl;
				assert(0);
			}
		}

		setInt(name, texture.TextureID);
		glActiveTexture(GL_TEXTURE0 + texture.TextureID);
		glBindTexture(GL_TEXTURE_2D, texture.getID());
	}

	void Shader::setModel(Object& object) {
		setMat4("model", object.getTransform());
	}

	void Shader::setCamera(Camera& camera) {
		setMat4("view", camera.getView());
		setMat4("perspective", camera.getPerspective());
	}

	inline void Shader::Use() {
		glUseProgram(ID);

		for (uint16_t x = 0; x < 16; x++) {
			
			glActiveTexture(GL_TEXTURE0 + x);
			glBindTexture(GL_TEXTURE_2D, slots[x]);
			
		}
	}

	inline void Shader::UnUse() {
		glUseProgram(0);
		for (uint16_t x = 0; x < 16; x++) {
			glBindTexture(GL_TEXTURE_2D, 0);
		}
	}

	OpenID Shader::getID() {
		return ID;
	}

	Vector2 CursorPosition = Vector2(0.0f, 0.0f);

	void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
		CursorPosition.x = xpos;
		CursorPosition.y = ypos;
	}

	void SetMouseCursorMode(Window& window, bool mode) {
		if (mode == false) {
			glfwSetInputMode(window.getID(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		}
		else if (mode == true) {
			glfwSetInputMode(window.getID(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		}
	}

	Vector2 getCursorPosition() {
		return CursorPosition;
	}

	void glfw_error_callback(int error, const char* description)
	{
		std::cerr << "GLFW Error " << error
			<< ": " << description << '\n';
	}


	Window::Window(std::string name, int width, int height, bool fullscreen) {
		glfwSetErrorCallback(glfw_error_callback);

		GLFWmonitor* monitor = glfwGetPrimaryMonitor();
		ID = glfwCreateWindow(width, height, name.c_str(), NULL, NULL);

		if (fullscreen) {
			glfwSetWindowMonitor(ID, monitor, 0, 0, width, height, GLFW_DONT_CARE);
		}

		if (ID == NULL) {
			std::cout << "ERROR :: FAILED TO CREATE GLFW WINDOW !!" << endl;
			throw(0);
		}
		glfwMakeContextCurrent(ID);
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
			std::cout << "ERROR :: FAILED TO START GLAD !!" << endl;
			throw(0);
		}

		glViewport(0, 0, width, height);
		glEnable(GL_BLEND);
		glEnable(GL_DEPTH_TEST);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glfwSetCursorPosCallback(getID(), mouse_callback);
	}

	void Window::change_Resolution(int width, int height) {
		glfwSetWindowSize(ID, width, height);
		glViewport(0, 0, width, height);
	}

	void Window::update() {
		glfwPollEvents();
		glfwSwapBuffers(ID);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void Window::setBackgroundColor(float red, float green, float blue, float alpha) {
		glClearColor(red, green, blue, alpha);
	}

	void Window::Draw(VAO VertexArrayObject, Shader shader) {
		shader.Use();
		VertexArrayObject.Use();
		glDrawElements(GL_TRIANGLES, VertexArrayObject.get_nIndices(), GL_UNSIGNED_SHORT, 0);
		shader.UnUse();
		VertexArrayObject.UnUse();
	}

	void Window::ShouldClose(bool mode) {
		glfwSetWindowShouldClose(ID, mode);
	}

	GLFWwindow* Window::getID() {
		return ID;
	}


	Mat4 Object::getTransform() {
		Mat4 Transform = Mat4(1.0f);
		Transform = glm::translate(Transform, position);
		Transform = glm::rotate(Transform, glm::radians(rotation.x), Vector3(1.0f, 0.0f, 0.0f));
		Transform = glm::rotate(Transform, glm::radians(rotation.y), Vector3(0.0f, 1.0f, 0.0f));
		Transform = glm::rotate(Transform, glm::radians(rotation.z), Vector3(0.0f, 0.0f, 1.0f));
		Transform = glm::scale(Transform, scale);
		return Transform;
	}

	Vector3 Object::RelativeForward() {
		const float pitch = glm::radians(rotation.x);
		const float yaw = glm::radians(rotation.y);

		Vector3 forward{
			-sin(yaw) * cos(pitch),
			sin(pitch),
			cos(yaw) * cos(pitch)
		};
		forward = glm::normalize(forward);
		return forward;
	}
	Vector3 Object::RelativeRight() {
		const float pitch = glm::radians(rotation.x);
		const float yaw = glm::radians(rotation.y);

		Vector3 forward{
			-sin(yaw) * cos(pitch),
			sin(pitch),
			cos(yaw) * cos(pitch)
		};
		Vector3 right = glm::cross(forward, Vector3(0.0f, 1.0f, 0.0f));

		return right;
	}
	Vector3 Object::RelativeUp() {
		const float pitch = glm::radians(rotation.x);
		const float yaw = glm::radians(rotation.y);

		Vector3 forward{
			-sin(yaw) * cos(pitch),
			sin(pitch),
			cos(yaw) * cos(pitch)
		};
		Vector3 right = glm::cross(forward, Vector3(0.0f, 1.0f, 0.0f));
		Vector3 Up = glm::cross(right, forward);

		return Up;
	}

	Camera::Camera(Camera_Settings view_type, float width, float height, float near, float far, float fov) {
		near_clipping = near;
		far_clipping = far;
		if (view_type == PERSPECTIVE) {
			FOV = fov;
			Perspective = glm::perspective(glm::radians(FOV), width / height, near_clipping, far_clipping);
		}
		else if (view_type == ORTHO) {
			FOV = fov;
			Perspective = glm::ortho(0.0f, width, 0.0f, height, near_clipping, far_clipping);
		}
		else {
			std::cout << "ERROR :: INVALID CAMERA SETTINGS" << endl;
			assert(0);
		}

	}

	void Camera::setup(Camera_Settings view_type, float width, float height, float near, float far, float fov) {
		Camera(view_type, width, height, near, far, fov);
	}

	Mat4& Camera::getView() {
		const float pitch = glm::radians(rotation.x);
		const float yaw = glm::radians(-rotation.y);

		Vector3 forward{
			sin(yaw) * cos(pitch),
			sin(pitch),
			cos(yaw) * cos(pitch)
		};

		forward = glm::normalize(forward);

		const Vector3 worldUp{ 0.0f, 1.0f, 0.0f };

		View = glm::lookAt(position, position + forward, worldUp);
		return View;
	}

	Mat4& Camera::getPerspective() {
		return Perspective;
	}
	
	void Camera::LookAt(Vector3 target) {
		Vector3 direction = glm::normalize(target - position);
		rotation.y = glm::degrees(glm::atan(direction.x / -direction.z));
		if (direction.z < 0) {
			rotation.y += 180;
		}
		rotation.x = glm::degrees(glm::asin(direction.y));
	}

	void Update() {

	}