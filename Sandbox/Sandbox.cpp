#include <core/ElenaApp.h>
#include <core/SceneManager.h>
#include <core/Scene.h>
#include <core/Node.h>
#include <camera/FPSCamera.h>
#include <camera/FPSCameraController.h>
#include <light/DirectionalLight.h>
#include <pipeline/Texture2DViewRenderPass.h>
#include <pipeline/DepthOnlyRenderPass.h>
#include <pipeline/BaseRenderPass.h>
#include <material/BlankMaterial.h>
#include <material/CheckerMaterial.h>
#include <material/PhongMaterial.h>
#include <primitive/Primitive.h>
#include <utils/MeshImporter.h>
#include <utils/AssetsPath.h>
#include <3rdparty/imgui/imgui.h>
#include <spdlog/spdlog.h>

int main()
{
	auto& App = Elena::CElenaApp::getInstance();
	App.setMainWindow(std::make_shared<Elena::CWindow>(800, 600, "Elena"));

	//const auto& pRootNode = std::make_shared<Elena::CNode>("Root");
	//const auto& pModelNode = Elena::CMeshImporter::import(Elena::CAssetsPath::getAssetsPath() + "models/nanosuit/nanosuit.obj", std::make_shared<Elena::CCheckerMaterial>());
	//pModelNode->getTransform().setScale(glm::vec3(0.1f, 0.1f, 0.1f));
	//pRootNode->addChild(pModelNode);

	//const auto& pPlane = Elena::CPrimitive::createPlane();
	//const auto& pCube = Elena::CPrimitive::createCube();
	//const auto& pMaterial = std::make_shared<Elena::CPhongMaterial>(
	//	std::make_shared<Elena::CTexture2D>(glm::vec3(1.0f, 0.5f, 0.31f)),
	//	std::make_shared<Elena::CTexture2D>(glm::vec3(0.5f, 0.5f, 0.5f)),
	//	32.0f
	//);
	//const auto& pPlaneNode = std::make_shared<Elena::CNode>("Plane");
	//pPlaneNode->addMesh(std::make_shared<Elena::CMesh>(pPlane, pMaterial));
	//pPlaneNode->getTransform().setScale(glm::vec3(10.0f, 10.0f, 10.0f));
	//const auto& pCubeNode = std::make_shared<Elena::CNode>("Cube");
	//pCubeNode->addMesh(std::make_shared<Elena::CMesh>(pCube, pMaterial));
	//pCubeNode->getTransform().setPosition(glm::vec3(1.0f, 0.6f, 1.0f));
	//pRootNode->addChild(pPlaneNode);
	//pRootNode->addChild(pCubeNode);

	auto pFPSCamera = std::make_shared<Elena::CFPSCamera>();
	auto pFPSCameraController = std::make_shared<Elena::CFPSCameraController>(pFPSCamera);
	auto pDirectionalLight = std::make_shared<Elena::CDirectionalLight>(glm::vec3(0.0f, 5.0f, 0.0f), glm::vec3(0.5f, -1.0f, 0.5f), 10.0f, 10.0f);
	//pDirectionalLight->setShadowType(Elena::CLight::EShadowType::NO_SHADOW);
	const auto& pScene = Elena::CSceneManager::getInstance().getActiveScene();
	//pScene->setRootNode(pRootNode);
	pScene->addCamera(pFPSCamera, pFPSCameraController);
	pScene->addLight(pDirectionalLight);
	Elena::CSceneManager::getInstance().addScene(pScene);

	Elena::CDepthOnlyRenderPass DepthOnlyPass;
	Elena::CTexture2DViewRenderPass TexViewPass(pDirectionalLight->getShadowMap());
	Elena::CBaseRenderPass BaseRenderPass;
	App.setRender([&]() {
		DepthOnlyPass.render(Elena::CSceneManager::getInstance().getActiveScene());
		//TexViewPass.render(Elena::CSceneManager::getInstance().getActiveScene());
		BaseRenderPass.render(Elena::CSceneManager::getInstance().getActiveScene());
	});
	App.run();
	return 0;
}

// Camera的Aspect以及FrameBuffer的width和height应该是Scene Panel
// Scene Panel 奇怪的width height
// WindowUI设置清屏导致的闪烁