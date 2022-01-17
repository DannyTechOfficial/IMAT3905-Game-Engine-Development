/** \file application.cpp
*/

#include "engine_pch.h"

// Temp
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "core/application.h"
#include "platform/GLFW/GLFWCodes.h"


#ifdef NG_PLATFORM_WINDOWS
#include "platform/GLFW/GLFWSystem.h"
#endif

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "rendering/indexBuffer.h"
#include "rendering/vertexBuffer.h"
#include "rendering/vertexArray.h"
#include "rendering/subTexture.h"
#include "rendering/texture.h"
#include "rendering/shader.h"
#include "rendering/Renderer3D.h"
#include "rendering/Renderer2D.h"

namespace Engine {
	// Set static vars
	Application* Application::s_instance = nullptr;

	Application::Application()
	{
		if (s_instance == nullptr)
		{
			s_instance = this;
		}

		//Start systems

		//Start log
		m_logSystem.reset(new Log);
		m_logSystem->start();

		// Start the windows System
#ifdef NG_PLATFORM_WINDOWS
		m_windowSystem.reset(new GLFWSystem);
#endif
		m_windowSystem->start();

		// Start Timer
		m_timer.reset(new ChronoTimer);
		m_timer->start();
		WindowProperties props("Danny Tech Engine", 1024, 800, false);
		m_window.reset(Window::create(props));
		m_window->setVSync(false);
		InputPoller::setNative(m_window->getNativeWindow());
		//m_window->getEventHandler;

#pragma region setCallback
		m_window->getEventHandler().setOnCloseCallback(std::bind(&Application::onClose, this, std::placeholders::_1));
		m_window->getEventHandler().setOnResizeCallback(std::bind(&Application::onResize, this, std::placeholders::_1));
		m_window->getEventHandler().setOnFocusCallback(std::bind(&Application::onFocus, this, std::placeholders::_1));
		m_window->getEventHandler().setOnLostFocusCallback(std::bind(&Application::onLostFocus, this, std::placeholders::_1));
		m_window->getEventHandler().setOnWindowMovedCallback(std::bind(&Application::onMoved, this, std::placeholders::_1));

		m_window->getEventHandler().setOnKeyPressedCallback(std::bind(&Application::onKeyPressed, this, std::placeholders::_1));
		m_window->getEventHandler().setOnKeyReleasedCallback(std::bind(&Application::onKeyReleased, this, std::placeholders::_1));

		m_window->getEventHandler().setOnButtonPressedCallback(std::bind(&Application::onButtonPressed, this, std::placeholders::_1));
		m_window->getEventHandler().setOnButtonReleasedCallback(std::bind(&Application::onButtonReleased, this, std::placeholders::_1));
		m_window->getEventHandler().setOnMouseMovedCallback(std::bind(&Application::onMouseMoved, this, std::placeholders::_1));
		m_window->getEventHandler().setOnMouseWheelCallback(std::bind(&Application::onMouseWheel, this, std::placeholders::_1));
#pragma endregion
		m_timer->reset();
	}

	bool Application::onClose(WindowCloseEvent & e)
	{
		e.handle(true);
		//Log::info("Window Close Works!!");
		m_running = false;
		return e.handled();
	}

	bool Application::onResize(WindowResizeEvent &e)
	{
		e.handle(true);
		//Log::info("Resize Works!! {0} {1}", e.getWidth(), e.getHeight());
		return e.handled();
	}

	bool Application::onFocus(e_WindowFocus & e)
	{
		e.handle(true);
		Log::info("GAME RESUMED!");
		return e.handled();
	}

	bool Application::onLostFocus(e_WindowLostFocus & e)
	{
		e.handle(true);
		Log::info("GAME PAUSED!");
		return e.handled();
	}

	bool Application::onMoved(e_WindowMoved & e)
	{
		e.handle(true);
		Log::info("Window Moved! - {0} - {1}", e.getXPos(), e.getYPos());
		return e.handled();
	}

	bool Application::onKeyPressed(e_KeyPressed & e)
	{
		Log::info("Key Pressed" + e.getKeyCode());
		e.handle(true);
		if (e.getKeyCode() == NG_KEY_RIGHT)
		{
			Log::info("A Key Pressed!");
		}
		else if (e.getKeyCode() == int32_t(68))
		{
			Log::info("D is pressed");
		}
		else if (e.getKeyCode() == int32_t(87))
		{
			Log::info("W is pressed");
		}
		else if (e.getKeyCode() == int32_t(83))
		{
			Log::info("S is pressed");
		}
		return e.handled();
	}

	bool Application::onKeyReleased(e_KeyReleased & e)
	{
		e.handle(true);
		return e.handled();
	}

	bool Application::onButtonPressed(e_MouseButtonPressed & e)
	{
		e.handle(true);
		Log::info("Key Pressed" + e.getButton());
		return e.handled();
	}

	bool Application::onButtonReleased(e_MouseButtonReleased & e)
	{
		e.handle(true);
		return e.handled();
	}

	bool Application::onMouseMoved(e_MouseMoved & e)
	{
		e.handle(true);
		return e.handled();
	}

	bool Application::onMouseWheel(e_MouseScrolled & e)
	{
		e.handle(true);
		return e.handled();
	}

	Application::~Application()
	{
		//Stop systems.

		//Stop log
		m_logSystem->stop();

		m_windowSystem->stop();
	}


	void Application::run()
	{
#pragma region TEXTURES

		std::shared_ptr<Texture> letterTexture;
		letterTexture.reset(Texture::create("assets/textures/letterAndNumberCube2.png"));
		std::shared_ptr<Texture> numberTexture;
		numberTexture.reset(Texture::create("assets/textures/numberCube.png"));
		unsigned char whitePx[4] = { 255, 255, 255, 255 };
		std::shared_ptr<Texture> plainWhiteTexture;
		plainWhiteTexture.reset(Texture::create(1, 1, 4, whitePx)); // Check after fix

		SubTexture letterCube(letterTexture, { 0.f, 0.f }, { 1.0f, 0.5f });
		SubTexture numberCube(numberTexture, { 0.f, 0.5f }, { 1.0f, 1.0f });

#pragma endregion

#pragma region RAW_DATA

		float cubeVertices[8 * 24] = 
		{
			//	 <------ Pos ------>  <--- normal --->  <-- UV -->
				 0.5f,  1.5f, -0.5f,  0.f,  0.f, -1.f,  letterCube.transformU(0.f),   letterCube.transformV(0.f),
				 0.5f, 0.5f, -0.5f,  0.f,  0.f, -1.f,   letterCube.transformU(0.f),   letterCube.transformV(0.5f),
				 -0.5f, 0.5f, -0.5f,  0.f,  0.f, -1.f,   letterCube.transformU(0.33f), letterCube.transformV(0.5f),
				 -0.5f,  1.5f, -0.5f,  0.f,  0.f, -1.f,  letterCube.transformU(0.33f), letterCube.transformV(0.f),

				 -0.5f, -0.5f, 0.5f,   0.f,  0.f,  1.f,  letterCube.transformU(0.33f), letterCube.transformV(0.5f),
				 0.5f, -0.5f, 0.5f,   0.f,  0.f,  1.f,  letterCube.transformU(0.66f), letterCube.transformV(0.5f),
				 0.5f,  0.5f, 0.5f,   0.f,  0.f,  1.f,  letterCube.transformU(0.66f), letterCube.transformV(0.f),
				 -0.5f,  0.5f, 0.5f,   0.f,  0.f,  1.f,  letterCube.transformU(0.33),  letterCube.transformV(0.f),

				 -0.5f, -0.5f, -0.5f,  0.f, -1.f,  0.f,  letterCube.transformU(1.f),   letterCube.transformV(0.f),
				 0.5f, -0.5f, -0.5f,  0.f, -1.f,  0.f,  letterCube.transformU(0.66f), letterCube.transformV(0.f),
				 0.5f, -0.5f, 0.5f,   0.f, -1.f,  0.f,  letterCube.transformU(0.66f), letterCube.transformV(0.5f),
				 -0.5f, -0.5f, 0.5f,   0.f, -1.f,  0.f,  letterCube.transformU(1.0f),  letterCube.transformV(0.5f),

				 0.5f,  0.5f, 0.5f,   0.f,  1.f,  0.f,  numberCube.transformU(0.f),   numberCube.transformV(0.5f),
				 0.5f,  0.5f, -0.5f,  0.f,  1.f,  0.f,  numberCube.transformU(0.f),   numberCube.transformV(1.0f),
				 -0.5f,  0.5f, -0.5f,  0.f,  1.f,  0.f,  numberCube.transformU(0.33f), numberCube.transformV(1.0f),
				 -0.5f,  0.5f, 0.5f,   0.f,  1.f,  0.f,  numberCube.transformU(0.3f),  numberCube.transformV(0.5f),

				 -0.5f,  0.5f, 0.5f,  -1.f,  0.f,  0.f,  numberCube.transformU(0.66f), numberCube.transformV(0.5f),
				 -0.5f,  0.5f, -0.5f, -1.f,  0.f,  0.f,  numberCube.transformU(0.33f), numberCube.transformV(0.5f),
				 -0.5f, -0.5f, -0.5f, -1.f,  0.f,  0.f,  numberCube.transformU(0.33f), numberCube.transformV(1.0f),
				 -0.5f, -0.5f, 0.5f,  -1.f,  0.f,  0.f,  numberCube.transformU(0.66f), numberCube.transformV(1.0f),

				 0.5f, -0.5f, -0.5f,  1.f,  0.f,  0.f,  numberCube.transformU(1.0f),  numberCube.transformV(1.0f),
				 0.5f,  0.5f, -0.5f,  1.f,  0.f,  0.f,  numberCube.transformU(1.0f),  numberCube.transformV(0.5f),
				 0.5f,  0.5f, 0.5f,   1.f,  0.f,  0.f,  numberCube.transformU(0.66f), numberCube.transformV(0.5f),
				 0.5f, -0.5f, 0.5f,   1.f,  0.f,  0.f,  numberCube.transformU(0.66f), numberCube.transformV(1.0f)
		};

		float pyramidVertices[8 * 16] = 
		{
			//	 <------ Pos ------>  <--- normal --->  <-- UV -->
				-0.5f, -0.5f, -0.5f,  0.f, -1.f, 0.f,  0.f, 0.f, //  square Magneta
				 0.5f, -0.5f, -0.5f,  0.f, -1.f, 0.f,  0.f, 0.5f,
				 0.5f, -0.5f,  0.5f,  0.f, -1.f, 0.f,  0.33f, 0.5f,
				-0.5f, -0.5f,  0.5f,  0.f, -1.f, 0.f,  0.33f, 0.f,

				-0.5f, -0.5f, -0.5f,  -0.8944f, 0.4472f, 0.f,  0.33f, 1.f,  //triangle Green
				-0.5f, -0.5f,  0.5f,  -0.8944f, 0.4472f, 0.f,  0.66f, 1.f,
				 0.0f,  0.5f,  0.0f,  -0.8944f, 0.4472f, 0.f,  0.495, 0.f,

				-0.5f, -0.5f,  0.5f,  0.f, 0.4472f, 0.8944f,  0.f, 0.f, //triangle Red
				 0.5f, -0.5f,  0.5f,  0.f, 0.4472f, 0.8944f,  0.f, 0.f,
				 0.0f,  0.5f,  0.0f,  0.f, 0.4472f, 0.8944f,  0.f, 0.f,

				 0.5f, -0.5f,  0.5f,  0.8944f, 0.4472f, 0.f,  0.f, 0.f, //  triangle Yellow
				 0.5f, -0.5f, -0.5f,  0.8944f, 0.4472f,  0.f, 0.f, 0.f,
				 0.0f,  0.5f,  0.0f,  0.8944f, 0.4472f,  0.f, 0.f, 0.f,

				 0.5f, -0.5f, -0.5f,  0.f,  0.4472f, -0.8944f,   0.f, 0.f, //  triangle Blue
				-0.5f, -0.5f, -0.5f,  0.f, 0.4472f, -0.8944f,   0.f, 0.f,
				 0.0f,  0.5f,  0.0f,  0.f, 0.4472f, -0.8944f,  0.f, 0.f,
		};

		uint32_t pyramidIndices[3 * 6] =
		{
			0, 1, 2,
			2, 3, 0,
			4, 5, 6,
			7, 8, 9,
			10, 11, 12,
			13, 14, 15
		};

		uint32_t cubeIndices[3 * 12] = 
		{
			0, 1, 2,
			2, 3, 0,
			4, 5, 6,
			6, 7, 4,
			8, 9, 10,
			10, 11, 8,
			12, 13, 14,
			14, 15, 12,
			16, 17, 18,
			18, 19, 16,
			20, 21, 22,
			22, 23, 20
		};
#pragma endregion

#pragma region GL_BUFFERS
		std::shared_ptr<VertexArray> cubeVAO;
		std::shared_ptr<VertexBuffer> cubeVBO;
		std::shared_ptr<IndexBuffer> cubeIBO;

		std::shared_ptr<VertexArray> pyramidVAO;
		std::shared_ptr<VertexBuffer> pyramidVBO;
		std::shared_ptr<IndexBuffer> pyramidIBO;

		cubeVAO.reset(VertexArray::create());

		BufferLayout cubeLayout = { ShaderDataType::Float3, ShaderDataType::Float3, ShaderDataType::Float2 };
		cubeVBO.reset(VertexBuffer::create(cubeVertices, sizeof(cubeVertices), cubeLayout));

		cubeVAO->addVertextBuffer(cubeVBO);

		cubeIBO.reset(IndexBuffer::create(cubeIndices, 36));
		cubeVAO->setIndexBuffer(cubeIBO);

		pyramidVAO.reset(VertexArray::create());

		pyramidVBO.reset(VertexBuffer::create(pyramidVertices, sizeof(pyramidVertices), cubeLayout));

		pyramidIBO.reset(IndexBuffer::create(pyramidIndices, 18));

		pyramidVAO->addVertextBuffer(pyramidVBO);

		pyramidVAO->setIndexBuffer(pyramidIBO);

#pragma endregion

#pragma region SHADERS
		std::shared_ptr<Shader> TPShader;
		TPShader.reset(Shader::create("./assets/shaders/texturedPhong.glsl"));

#pragma endregion

#pragma region MATERIALS
		std::shared_ptr<Material> pyramidMat;
		std::shared_ptr<Material> letterCubeMat;
		std::shared_ptr<Material> numberCubeMat;

		pyramidMat.reset(new Material(TPShader, { 0.4f, 0.7f, 0.3f, 0.5f }));
		letterCubeMat.reset(new Material(TPShader, letterTexture));
		numberCubeMat.reset(new Material(TPShader, numberTexture));


#pragma endregion
		float timestep = 0.0f;

		Quad quads[6] = 
		{
			Quad::createCentreHalfExtents({ 400.f, 75.f }, { 100.f, 50.f }),
			Quad::createCentreHalfExtents({ 350.f, 300.f }, { 50.f, 100.f }),
			Quad::createCentreHalfExtents({ 400.f, 500.f }, { 75.f, 75.f }),

			Quad::createCentreHalfExtents({ 100.f, 200.f }, { 75.f, 50.f }),
			Quad::createCentreHalfExtents({ 700.f, 100.f }, { 50.f, 25.f }),
			Quad::createCentreHalfExtents({ 600.f, 450.f }, { 75.f, 15.f })
		};
		glClearColor(0.3f, 0.4f, 1.f, 1.0f);

		Renderer3D::init();
		Renderer2D::init();
		/*glm::mat4 view = glm::lookAt(
			glm::vec3(0.f, 0.f, 0.f),
			glm::vec3(0.f, 0.f, -1.f),
			glm::vec3(0.f, 1.f, 0.f)
		);*/
#pragma region CameraTest
		glm::mat4 view;
		float camX = 0.0f;
		float camY = 0.0f;
		float camZ = -6.0f;
		float camZZ= 3.0f;
		view = glm::lookAt(
			glm::vec3(0.0f, 0.0f, 3.0f),
			glm::vec3(camX, camY, camZ), 
			glm::vec3(0.0f, 1.0f, 0.0f)
		);
		
		const float radius = 10.f;
#pragma endregion
		glm::mat4 projection = glm::perspective(glm::radians(45.f), 1024.f / 800.f, 0.1f, 100.f);

		glm::mat4 models[3];
		models[0] = glm::translate(glm::mat4(1.0f), glm::vec3(-2.f, 0.f, -6.f));
		models[1] = glm::translate(glm::mat4(1.0f), glm::vec3(0.f, 0.f, -6.f));
		models[2] = glm::translate(glm::mat4(1.0f), glm::vec3(2.f, 0.f, -6.f));

		glm::mat4 view2D = glm::mat4(1.0f);
		glm::mat4 projection2D = glm::ortho(0.f, static_cast<float>(m_window->getWidth()), static_cast<float>(m_window->getHeight()), 0.f);


		SceneWideUniforms swu3D;

		glm::vec3 lightdata[3] = { { 1.0f, 1.0f, 1.0f }, { -2.f, 4.f, 6.f }, { 0.f, 0.f, 0.f } };

		swu3D["u_view"] = std::pair<ShaderDataType, void *>(ShaderDataType::Mat4, static_cast <void *>(glm::value_ptr(view)));
		swu3D["u_projection"] = std::pair<ShaderDataType, void *>(ShaderDataType::Mat4, static_cast <void *>(glm::value_ptr(projection)));

		swu3D["u_lightColour"] = std::pair<ShaderDataType, void *>(ShaderDataType::Float3, static_cast<void *>(glm::value_ptr(lightdata[0])));
		swu3D["u_lightPos"] = std::pair<ShaderDataType, void *>(ShaderDataType::Float3, static_cast<void *>(glm::value_ptr(lightdata[1])));
		swu3D["u_viewPos"] = std::pair<ShaderDataType, void *>(ShaderDataType::Float3, static_cast<void *>(glm::value_ptr(lightdata[2])));
		
		SceneWideUniforms swu2D;
		swu2D["u_view"] = std::pair<ShaderDataType, void*>(ShaderDataType::Mat4, static_cast <void*>(glm::value_ptr(view2D)));
		swu2D["u_projection"] = std::pair<ShaderDataType, void*>(ShaderDataType::Mat4, static_cast <void*>(glm::value_ptr(projection2D)));


		while (m_running)
		{
			if (InputPoller::isKeyPressed(NG_KEY_S)) //!< Camera Controls (BASIC)
			{
				view = glm::lookAt(
					glm::vec3(0.0f, 0.0f, 3.0f),
					glm::vec3(camX, camY - 0.002, camZ),
					glm::vec3(0.0f, 1.0f, 0.0f)
				);
				camY -= 0.002;
			}
			else if (InputPoller::isKeyPressed(NG_KEY_W)) 
			{
				view = glm::lookAt(
					glm::vec3(0.0f, 0.0f, 3.0f),
					glm::vec3(camX, camY + 0.002, camZ),
					glm::vec3(0.0f, 1.0f, 0.0f)
				);
				camY += 0.002;
			}
			else if (InputPoller::isKeyPressed(NG_KEY_A))
			{
				view = glm::lookAt(
					glm::vec3(0.0f, 0.0f, 3.0f),
					glm::vec3(camX - 0.002, camY, camZ),
					glm::vec3(0.0f, 1.0f, 0.0f)
				);
				camX -= 0.002;
			}
			else if (InputPoller::isKeyPressed(NG_KEY_D))
			{
				view = glm::lookAt(
					glm::vec3(0.0f, 0.0f, 3.0f),
					glm::vec3(camX + 0.002, camY, camZ),
					glm::vec3(0.0f, 1.0f, 0.0f)
				);
				camX += 0.002;
			}

			timestep = m_timer->getElapsedTime();
			m_timer->reset();
			//Log::trace("FPS {0}", 1.0f / timestep);

			// Do frame stuff
			for (auto& model : models) { model = glm::rotate(model, timestep, glm::vec3(0.f, 1.0f, 0.f)); }

			// Do frame stuff
#pragma region Render
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			plainWhiteTexture->bindToUnit(0);
			
			glEnable(GL_DEPTH_TEST);
			Renderer3D::begin(swu3D);

 			Renderer3D::submit(pyramidVAO, pyramidMat, models[0]);

			Renderer3D::submit(cubeVAO, letterCubeMat, models[1]);

			Renderer3D::submit(cubeVAO, letterCubeMat, models[2]);

			Renderer3D::end();
			
#pragma endregion
			glDisable(GL_DEPTH_TEST);
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

			Renderer2D::begin(swu2D);

			Renderer2D::submit(quads[0], { 0.f, 0.f, 1.f, 1.f });
			Renderer2D::submit(quads[1], letterTexture);
			Renderer2D::submit(quads[2], { 0.f, 1.f, 1.f, 1.f }, numberTexture);
			Renderer2D::submit(quads[3], { 0.f, 1.f, 1.f, 0.5f }, numberTexture, 45.f, true);
			Renderer2D::submit(quads[3], { 1.f, 0.f, 1.f, 0.5f }, numberTexture, glm::radians(-45.f));
			Renderer2D::submit(quads[4], { 1.f, 1.f, 0.f, 1.f }, 30.f, true);
			Renderer2D::submit(quads[5], { 1.f, 1.f, 0.f, 1.f }, letterTexture, 90.f, true);

			Renderer2D::end();

			glDisable(GL_BLEND);

			m_window->onUpdate(timestep);
		};

	}

}
