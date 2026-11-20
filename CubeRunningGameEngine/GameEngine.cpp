// GameEngine.cpp : Defines the entry point for the console application.
//
#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

#include "GameLoader.h"
#include <chrono>
#include <thread>

int main()
{
	
	LoadConfiguration();
	StartOpenGl();
	Window window("Cube Running Game", ScreenWidth, ScreenHeight, fullscreen);

	float vertecies[]{
		// Front
		-0.5f, -0.5f,  0.5f, 0.0f, 1.0f, 0.0f,  0.0f, -1.0f,
		 0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 0.0f,  0.0f, -1.0f,
		-0.5f,  0.5f,  0.5f, 0.0f, 0.0f, 0.0f,  0.0f, -1.0f,
		 0.5f,  0.5f,  0.5f, 1.0f, 0.0f, 0.0f,  0.0f, -1.0f,

		 // Back
		 -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.0f,  0.0f, 1.0f,
		  0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 0.0f,  0.0f, 1.0f,
		 -0.5f,  0.5f, -0.5f, 0.0f, 0.0f, 0.0f,  0.0f, 1.0f,
		  0.5f,  0.5f, -0.5f, 1.0f, 0.0f, 0.0f,  0.0f, 1.0f,

		 // Right
		  0.5f, -0.5f, -0.5f, 0.0f, 1.0f, -1.0f,  0.0f,  0.0f,
		  0.5f,  0.5f, -0.5f, 1.0f, 1.0f, -1.0f,  0.0f,  0.0f,
		  0.5f, -0.5f,  0.5f, 0.0f, 0.0f, -1.0f,  0.0f,  0.0f,
		  0.5f,  0.5f,  0.5f, 1.0f, 0.0f, -1.0f,  0.0f,  0.0f,

		 // Left
		 -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 1.0f,  0.0f,  0.0f,
		 -0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f,  0.0f,  0.0f,
		 -0.5f, -0.5f,  0.5f, 0.0f, 0.0f, 1.0f,  0.0f,  0.0f,
		 -0.5f,  0.5f,  0.5f, 1.0f, 0.0f, 1.0f,  0.0f,  0.0f,

		 // Up
		 -0.5f,  0.5f, -0.5f, 0.0f, 1.0f, 0.0f, -1.0f,  0.0f,
		  0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 0.0f, -1.0f,  0.0f,
		 -0.5f,  0.5f,  0.5f, 0.0f, 0.0f, 0.0f, -1.0f,  0.0f,
		  0.5f,  0.5f,  0.5f, 1.0f, 0.0f, 0.0f, -1.0f,  0.0f,

		 // Down
		 -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.0f,  1.0f,  0.0f,
		  0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 0.0f,  1.0f,  0.0f,
		 -0.5f, -0.5f,  0.5f, 0.0f, 0.0f, 0.0f,  1.0f,  0.0f,
		  0.5f, -0.5f,  0.5f, 1.0f, 0.0f, 0.0f,  1.0f,  0.0f,
	};

	unsigned short indicies[]{
		0 + 4 * 0, 1 + 4 * 0, 2 + 4 * 0,
		3 + 4 * 0, 1 + 4 * 0, 2 + 4 * 0,

		0 + 4 * 1, 1 + 4 * 1, 2 + 4 * 1,
		3 + 4 * 1, 1 + 4 * 1, 2 + 4 * 1,

		0 + 4 * 2, 1 + 4 * 2, 2 + 4 * 2,
		3 + 4 * 2, 1 + 4 * 2, 2 + 4 * 2,

		0 + 4 * 3, 1 + 4 * 3, 2 + 4 * 3,
		3 + 4 * 3, 1 + 4 * 3, 2 + 4 * 3,

		0 + 4 * 4, 1 + 4 * 4, 2 + 4 * 4,
		3 + 4 * 4, 1 + 4 * 4, 2 + 4 * 4,

		0 + 4 * 5, 1 + 4 * 5, 2 + 4 * 5,
		3 + 4 * 5, 1 + 4 * 5, 2 + 4 * 5,
	};

	VBO VB(sizeof(vertecies), vertecies);
	EBO EB(sizeof(indicies), indicies);

	VAO VA;
	VA.Attach_VBO(VB);
	VA.Attach_EBO(EB);
	VA.Setup(3, 8, 0, 0);
	VA.Setup(2, 8, 3, 1);
	VA.Setup(3, 8, 5, 2);

	// Loading Shaders and Textures
	Shader boxShader("Shaders\\box.vert", "Shaders\\box.frag");
	Shader sunShader("Shaders\\sun.vert", "Shaders\\sun.frag");
	Shader playerShader("Shaders\\player.vert", "Shaders\\player.frag");
	Shader UIShader("Shaders\\UI.vert", "Shaders\\UI.frag");
	Shader DescriptionShader("Shaders\\UI.vert", "Shaders\\UI.frag");

	Texture2D container_texture("Textures\\container2.png", GL_RGBA, GL_RGBA);
	Texture2D Level_texture("Textures\\Level.png", GL_RGBA, GL_RGBA);
	Texture2D Complete_texture("Textures\\Complete.png", GL_RGBA, GL_RGBA);
	Texture2D Failed_texture("Textures\\Failed.png", GL_RGBA, GL_RGBA);
	Texture2D _0_texture("Textures\\0.png", GL_RGBA, GL_RGBA);
	Texture2D _1_texture("Textures\\1.png", GL_RGBA, GL_RGBA);
	Texture2D _2_texture("Textures\\2.png", GL_RGBA, GL_RGBA);
	Texture2D _3_texture("Textures\\3.png", GL_RGBA, GL_RGBA);
	Texture2D _4_texture("Textures\\4.png", GL_RGBA, GL_RGBA);
	Texture2D _5_texture("Textures\\5.png", GL_RGBA, GL_RGBA);
	Texture2D _6_texture("Textures\\6.png", GL_RGBA, GL_RGBA);
	Texture2D _7_texture("Textures\\7.png", GL_RGBA, GL_RGBA);
	Texture2D _8_texture("Textures\\8.png", GL_RGBA, GL_RGBA);
	Texture2D _9_texture("Textures\\9.png", GL_RGBA, GL_RGBA);

	Texture2D Description1("Textures\\Description1.png", GL_RGBA, GL_RGBA);
	Texture2D Description2("Textures\\Description2.png", GL_RGBA, GL_RGBA);
	Texture2D Description3("Textures\\Description3.png", GL_RGBA, GL_RGBA);
	Texture2D Description4("Textures\\Description4.png", GL_RGBA, GL_RGBA);
	Texture2D Description5("Textures\\Description5.png", GL_RGBA, GL_RGBA);
	Texture2D Description6("Textures\\Description6.png", GL_RGBA, GL_RGBA);
	Texture2D Description7("Textures\\Description7.png", GL_RGBA, GL_RGBA);
	Texture2D Description8("Textures\\Description8.png", GL_RGBA, GL_RGBA);
	Texture2D Description9("Textures\\Description9.png", GL_RGBA, GL_RGBA);
	Texture2D Description10("Textures\\Description10.png", GL_RGBA, GL_RGBA);
	Texture2D EndScreen("Textures\\end.png", GL_RGBA, GL_RGBA);
	

	Texture2D* const Digits[] = { &_0_texture, &_1_texture, &_2_texture, &_3_texture, &_4_texture, &_5_texture, &_6_texture, &_7_texture, &_8_texture, &_9_texture};
	Texture2D* const Description[] = { &Description1, &Description2, &Description3, &Description4, &Description5, &Description6, &Description7, &Description8, &Description9, &Description10 };

	container_texture.Minimizing_filter(GL_LINEAR_MIPMAP_NEAREST);
	container_texture.Maximizing_filter(GL_NEAREST);

	container_texture.GenerateMipmaps();
	Level_texture.GenerateMipmaps();
	Complete_texture.GenerateMipmaps();
	Failed_texture.GenerateMipmaps();
	_0_texture.GenerateMipmaps();
	_1_texture.GenerateMipmaps();
	_2_texture.GenerateMipmaps();
	_3_texture.GenerateMipmaps();
	_4_texture.GenerateMipmaps();
	_5_texture.GenerateMipmaps();
	_6_texture.GenerateMipmaps();
	_7_texture.GenerateMipmaps();
	_8_texture.GenerateMipmaps();
	_9_texture.GenerateMipmaps();
	Description1.GenerateMipmaps();
	Description2.GenerateMipmaps();
	Description3.GenerateMipmaps();
	Description4.GenerateMipmaps();
	Description5.GenerateMipmaps();
	Description6.GenerateMipmaps();
	Description7.GenerateMipmaps();
	Description8.GenerateMipmaps();
	Description9.GenerateMipmaps();
	Description10.GenerateMipmaps();
	EndScreen.GenerateMipmaps();



	// Creating the necessary Objects
	Object Player;
	Object plane;
	plane.position.y -= 0.75f;
	plane.scale = vec3(20.0f, 0.5f, 5000.0f);


	List<Object> Boxes;
	
	Material boxMat;

	Light light1;
	Camera camera(PERSPECTIVE, ScreenWidth, ScreenHeight, 0.1f, 100.0f, 90.0f);
	
	// Ui Objects
	Object UiBackground;
	UiBackground.scale = vec3(10.0f, 10.0f, 1.0f);
	Object UiLevelText;
	UiLevelText.position.x -= 0.3f;
	UiLevelText.position.y += 0.2f;

	Object UiFirstDigit;
	UiFirstDigit.position.y += 0.275f;
	UiFirstDigit.position.x += 0.55f;
	UiFirstDigit.scale *= 0.5f;
	UiFirstDigit.scale.x *= 0.6f;
	Object UiSecondDigit;
	UiSecondDigit.position.y += 0.275f;
	UiSecondDigit.position.x += 0.35f;
	UiSecondDigit.scale *= 0.5f;
	UiSecondDigit.scale.x *= 0.6f;

	Object UiLevelLevelState;
	UiLevelLevelState.position.x -= 0.0f;
	UiLevelLevelState.position.y -= 0.3f;
	
	Object UiLevelDescription;
	UiLevelDescription.position.x -= 0.375f;
	UiLevelDescription.position.y += 0.925f;
	UiLevelDescription.scale *= 0.1f;
	UiLevelDescription.scale.x *= 12.0f;

	Object UiEnd;
	UiEnd.scale.x *= 1.5f;
	UiEnd.scale.y *= 1.0f;

	// Application settings
	SetMouseCursorMode(window, !fullscreen);
	float SlidingBorder = 10.5f;
	float SlidingSpeed = 6.0f;
	float MovingSpeed = 5.0f;
	float CameraSpeed = 5.0f;
	float FinishLine = MovingSpeed * 60.0f;

	boxMat.shininess = 16.0f;

	// Light 1 settings
	light1.constant = 1.0f;
	light1.linear = 0.05f;
	light1.quadratic = 0.00f;
	light1.intensity = 1.0f;

	light1.color = Vector3(1.0f);
	light1.thetaSpotLight = 360.0f;
	light1.epsilon = 0.0f;

	light1.position = Vector3(0, 3, 0);
	light1.rotation = Vector3(90.0f, 0.0f, 0.0f);

	light1.ambient = Vector3(1.0f);
	light1.diffuse = Vector3(1.0f);
	light1.specular = Vector3(10.0f);

	// Shader preparations
	boxShader.setSampler("container_texture", container_texture);
	boxShader.setMaterial("material", boxMat);
	sunShader.setFloat("transparency", 0.0f);

	// Game State
	float GameStartCounter = 3.0f;
	float GameEndCounter = -1.0f;
	int GameState = 0;
	
	vec3 PlayerSpeed = vec3(0.0f, 0.0f, 0.0f);

	Vector2 LastCursorPosition = getCursorPosition();
	LoadLevel(Level);
	createLevel(Boxes);
	glfwSwapInterval(vsync);

	const double targetFPS = 120.0;
	const double targetFrameTime = 1.0 / targetFPS;
	double lastFrameTime = glfwGetTime();
	double nextFrameTime = lastFrameTime;

	int deltaIndex = 0;
	float deltaTimeStored[240];
	for (int i = 0; i < 240; i++) {
		deltaTimeStored[i] = 0;
	}
	float deltaTimeAVG = 0;

	while (!glfwWindowShouldClose(window.getID())) {
		double currentTime = glfwGetTime();
		float deltaTime = currentTime - lastFrameTime;
		lastFrameTime = currentTime;

		if (deltaTime > 0.1) {
			deltaTime = 0.1;
		}

		deltaTimeStored[deltaIndex] = deltaTime;
		deltaIndex++;
		if (deltaIndex == 240) {
			deltaIndex = 0;
		}
		for (int i = 0; i < 240; i++) {
			deltaTimeAVG += deltaTimeStored[i];
		}
		deltaTimeAVG /= 240.0f;

		// Game Logic
		// Collision Detection
		
		for (int i = 0; i < Boxes.get_size(); i++) {
			if ((Player.position.z + 1.5f > Boxes.get(i).position.z) && (Player.position.z - 1.5f < Boxes.get(i).position.z)) {
				if ((Player.position.x > Boxes.get(i).position.x - 1.5f) && (Player.position.x < Boxes.get(i).position.x + 1.5f)) {
					if (Player.position.y <= 2.75f) {
						PlayerSpeed = (Player.position - Boxes.get(i).position);
						PlayerSpeed.y = 3.0f;
						PlayerSpeed *= 5;
						GameState = -1;
					}
				}
			}
		}

		// Game Logic - Camera Offset Control
		if (GameState == 0) {
			light1.position = Player.position + vec3(0.0f, 15.0f, -5.0f);

			camera.position.y = Player.position.y + 3.0f;
			camera.position.z = Player.position.z - 5.0f;

			if (camera.position.x != Player.position.x)
			{
				CameraSpeed = 0.85f * (MovingSpeed + 0.5 * (Level - 1));
				if (abs(camera.position.x - Player.position.x) > CameraSpeed * deltaTimeAVG) {
					(camera.position.x > Player.position.x) ? camera.position.x -= CameraSpeed * deltaTimeAVG : camera.position.x += CameraSpeed * deltaTimeAVG;
				}
				else {
					camera.position.x = Player.position.x;
				}
			}
		}
		
		// Game Logic - Player Movement
		if (Player.position.x > SlidingBorder || Player.position.x < -SlidingBorder || Player.position.y < -1.0f) {
			PlayerSpeed.y = -9.0f;
			Player.rotation.x += PlayerSpeed.y * 6.0f * deltaTimeAVG;
			Player.rotation.y += PlayerSpeed.y * 12.0f * deltaTimeAVG;
		}
		if (GameState != -1 && GameStartCounter <= 0.0f) {
			Player.position.z += (MovingSpeed + 0.5 * (Level - 1)) * deltaTimeAVG;
			Player.position += PlayerSpeed * deltaTimeAVG;
			if (Player.position.y < -5.0f) {
				GameState = -1;
			}
			if (Player.position.z > FinishLine) {
				GameState = 1;
			}
		}
		else if (GameState == -1) {
			Player.position += PlayerSpeed * deltaTimeAVG;
			Player.rotation += PlayerSpeed * 6.0f * deltaTimeAVG;
			PlayerSpeed.y -= 60.0f * deltaTimeAVG;
			if (Player.position.y < 0.0f) {
				PlayerSpeed = vec3(0.0f);
			}
		}

		// Game Logic - Player Controls
		if (GameState == 0 && GameStartCounter <= 0.0f) {
			if (glfwGetKey(window.getID(), GLFW_KEY_D) || glfwGetKey(window.getID(), GLFW_KEY_RIGHT)) {
				if (Player.position.x > -SlidingBorder) {
					Player.position.x -= (SlidingSpeed + 0.5 * (Level - 1)) * deltaTimeAVG;
				}
			}
			if (glfwGetKey(window.getID(), GLFW_KEY_A) || glfwGetKey(window.getID(), GLFW_KEY_LEFT)) {
				if (Player.position.x < SlidingBorder) {
					Player.position.x += (SlidingSpeed + 0.5 * (Level - 1)) * deltaTimeAVG;
				}
			}
		}

		if (glfwGetKey(window.getID(), GLFW_KEY_ESCAPE)) {
			window.ShouldClose(true);
		}

		// GameManager

		// Restart
		if (GameStartCounter > 0.0f) {
			GameStartCounter -= deltaTimeAVG;
		}
		if (GameEndCounter > 3.0f) {
			if (GameState == -1) {
				GameEndCounter = -1.0f;
				Player.position = vec3(0.0f);
				Player.rotation = vec3(0.0f);
				PlayerSpeed = vec3(0.0f);
				camera.position.x = Player.position.x;
				GameState = 0;
			}
			if (GameState == 1) {
				LevelData.clear();
				Level++;
				if (Level <= 10) {
					if (Level > maxLevel) {
						setMaxLevel(Level);
					}
					LoadLevel(Level);
					createLevel(Boxes);

					GameEndCounter = -1.0f;
					Player.position = vec3(0.0f);
					Player.rotation = vec3(0.0f);
					PlayerSpeed = vec3(0.0f);
					camera.position.x = Player.position.x;
					GameState = 0;
				}
				else {
					GameEndCounter = -100000.0f;
				}
			}
		}

		// Updatting Shaders Uniforms
		boxShader.setVec3("CameraPosition", camera.position);
		playerShader.setVec3("CameraPosition", camera.position);
		boxShader.setLight("lights[0]", light1);
		playerShader.setLight("lights[0]", light1);

		sunShader.setCamera(camera);
		boxShader.setCamera(camera);
		playerShader.setCamera(camera);

		sunShader.setModel(light1);
		playerShader.setVec3("ObjectColor", 1.0f, 0.3f, 0.3f);
		playerShader.setModel(Player);

		// Drawing on the screen
		window.Draw(VA, sunShader);
		window.Draw(VA, playerShader);

		for (int i = 0; i < Boxes.get_size(); i++) {
			boxShader.setModel(Boxes.get(i));
			window.Draw(VA, boxShader);
		}
		
		// Plane custom settings
		playerShader.setModel(plane);
		playerShader.setVec3("ObjectColor", 0.5f, 1.0f, 0.5f);
		window.Draw(VA, playerShader);

		if (GameState == 0) {
			DescriptionShader.setFloat("transparency", 1.0f);
			DescriptionShader.setModel(UiLevelDescription);
			DescriptionShader.setSampler("UI_texture", *Description[Level - 1]);
			window.Draw(VA, DescriptionShader);
		}

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		if (GameState != 0) {
			GameEndCounter += 1.0f * deltaTimeAVG;
		}
		if (GameEndCounter > 0.0f) {
			// Drawing Background
			UiBackground.position = camera.position;
			sunShader.setFloat("transparency", GameEndCounter / 6);
			sunShader.setModel(UiBackground);
			window.Draw(VA, sunShader);


			// Drawing Level
			UIShader.setFloat("transparency", GameEndCounter / 4);
			UIShader.setModel(UiLevelText);
			UIShader.setSampler("UI_texture", Level_texture);
			window.Draw(VA, UIShader);

			// Drawing Level Number
			UIShader.setModel(UiFirstDigit);
			UIShader.setSampler("UI_texture", *Digits[Level % 10]);
			window.Draw(VA, UIShader);
			UIShader.setModel(UiSecondDigit);
			UIShader.setSampler("UI_texture", *Digits[Level / 10]);
			window.Draw(VA, UIShader);

			// Drawing Complete / Failed
			UIShader.setModel(UiLevelLevelState);
			if (GameState == 1) {
				UIShader.setSampler("UI_texture", Complete_texture);
			}
			else if (GameState == -1) {
				UIShader.setSampler("UI_texture", Failed_texture);
			}

			window.Draw(VA, UIShader);
		}
		if (GameEndCounter < -10.0f && GameState == 1) {
			// Drawing Background
			UiBackground.position = camera.position;
			sunShader.setFloat("transparency", 1.0f);
			sunShader.setModel(UiBackground);
			window.Draw(VA, sunShader);

			// Drawing the end screen
			UIShader.setFloat("transparency", 1.0f);
			UIShader.setModel(UiEnd);
			UIShader.setSampler("UI_texture", EndScreen);
			window.Draw(VA, UIShader);
		}

		window.setBackgroundColor(0.9f, 0.9f, 0.9f, 1.0f);
		window.update();

		// 4. Frame limiting (Sleep + Spin-wait)
		nextFrameTime += targetFrameTime;

		// Prevent catch-up burst if a frame took longer than targetFrameTime
		if (nextFrameTime < glfwGetTime()) {
			nextFrameTime = glfwGetTime();
		}

		double sleepTime = nextFrameTime - glfwGetTime();

		if (sleepTime > 0.002) {
			std::this_thread::sleep_for(
				std::chrono::duration<double>(sleepTime - 0.002)
			);
		}
	}

    return 0;
}

