#include "Scene.h"

using namespace Rendering;
using namespace Texture;
using namespace Shader;
using namespace Light;
using namespace std;

//static Scene* nowScene = nullptr;

Scene::Scene(void) : BaseScene()
{
	destroyMgr = true;
}

Scene::~Scene(void)
{
	Destroy();
}

void Scene::Initialize()
{
	lightMgr		= new LightManager;
	textureMgr		= new TextureManager;
	graphics		= Device::DeviceDirector::GetInstance()->GetGraphics();
	shaderMgr		= new ShaderManager(graphics);
	cameraMgr		= new CameraManager;
	rootObjects		= new Container<Object>;
	meshDataMgr		= new MeshDataManager;
	materialMgr		= new MaterialManager;

	NextState();
	OnInitialize();
}

void Scene::Update(float dt)
{
	OnUpdate(dt);
	vector<Object*>::iterator end = rootObjects->GetEndIter();

	for(vector<Object*>::iterator iter = rootObjects->GetBeginIter(); iter != end; ++iter)
		(*iter)->Update(dt);
}

void Scene::Render()
{
	Camera *mainCam = cameraMgr->GetMainCamera();

	if(mainCam == nullptr)
		return;

	graphics->BeginScene();
	{
		OnRenderPreview();

		//for(vector<Camera*>::iterator iter = cameraMgr->GetIteratorBegin(); iter != cameraMgr->GetIteratorEnd(); ++iter)
		//	(*iter)->Run(dt);
		
		Camera::SceneRender(mainCam, rootObjects->GetBeginIter(), rootObjects->GetEndIter(), lightMgr);
		//�ϴ���, �̷��� ó���ϰ� ���Ŀ� �� ī�޶󸶴� Render to texture �������ص�, �װ� ó���ϵ��� �ؾ��ҵ�.
		//���� ������ �ʿ���.

		OnRenderPost();
	}
	graphics->EndScene();
	graphics->Present();
}

void Scene::Destroy()
{
	if(destroyMgr == false)
		return;

	lightMgr->DeleteAll(true);
	shaderMgr->DeleteAll();
	textureMgr->DeleteAll();
	meshDataMgr->DeleteAll();
	materialMgr->DeleteAll();

	Utility::SAFE_DELETE(lightMgr);
	Utility::SAFE_DELETE(shaderMgr);
	Utility::SAFE_DELETE(textureMgr);
	Utility::SAFE_DELETE(cameraMgr);
	Utility::SAFE_DELETE(meshDataMgr);
	Utility::SAFE_DELETE(materialMgr);

	OnDestroy();
}

LightManager* Scene::GetLightManager()
{
	return lightMgr;
}

TextureManager* Scene::GetTextureManager()
{
	return textureMgr;
}

ShaderManager* Scene::GetShaderManager()
{
	return shaderMgr;
}

CameraManager* Scene::GetCameraManager()
{
	return cameraMgr;
}

Rendering::MeshDataManager* Scene::GetMeshDataMgr()
{
	return meshDataMgr;
}

Rendering::MaterialManager* Scene::GetMaterialMgr()
{
	return materialMgr;
}