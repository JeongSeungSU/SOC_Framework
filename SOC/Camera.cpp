#include "Camera.h"
#include "Scene.h"

using namespace Common;
using namespace std;
using namespace Rendering::Light;
using namespace Device;

namespace Rendering
{
	Camera::Camera() : Component()
	{

	}

	Camera::~Camera(void)
	{
	
	}

	void Camera::Initialize()
	{
		FOV = 60;
		clippingNear = 0.01f;
		clippingFar = 1000.0f;
		normalizedViewPortRect = Rect<float>(0, 0, 1, 1);

		Size<int> windowSize = DeviceDirector::GetInstance()->GetApplication()->GetSize();
		aspect = (float)windowSize.w / (float)windowSize.h;

		camType    = Type::Perspective;
		clearColor = Color(0.5f, 0.5f, 1.0f,1.0f);

		frustum = new Frustum(0.0f);		
		this->skybox = nullptr;

		clearFlag = ClearFlag::FlagSolidColor;
	}

	void Camera::Destroy()
	{
		Utility::SAFE_DELETE(frustum);
	}

	void Camera::Clear()
	{
		//defulat is 'target clear option'.
//		Graphics flag = Graphics::FlagTarget;
		Graphics::GraphicsForm::ClearFlag flag = Graphics::GraphicsForm::FlagTarget;

		if( clearFlag == ClearFlag::FlagDontClear )
			return;

		if( clearFlag == ClearFlag::FlagSkybox )
		{
			//skybox Rendering
			skybox->Render();
			return;
		}

		else if( clearFlag == ClearFlag::FlagSolidColor )
			flag |= Graphics::GraphicsForm::FlagZBuffer;

		DeviceDirector::GetInstance()->GetGraphics()->Clear( 0, NULL, flag, clearColor, 1.0f, 0);
	}

	void Camera::CalcAspect()
	{
		float w = normalizedViewPortRect.size.w - normalizedViewPortRect.x;
		float h = normalizedViewPortRect.size.h - normalizedViewPortRect.y;

		Size<int> windowSize =  Device::DeviceDirector::GetInstance()->GetSize();
		
		aspect = ((float)windowSize.w * w) / ((float)windowSize.h * h);
	}

	void Camera::GetPerspectiveMatrix(SOC_Matrix *outMatrix, float farGap)
	{
		float radian = FOV * SOCM_PI / 180.0f;
		SOCMatrixPerspectiveFovLH(outMatrix, radian, aspect, clippingNear, clippingFar + farGap);
	}
	void Camera::GetOrthoGraphicMatrix(SOC_Matrix *outMatrix)
	{
		Size<int> windowSize = Device::DeviceDirector::GetInstance()->GetSize();;
		SOCMatrixOrthoLH(outMatrix, 
			(float)(windowSize.w * normalizedViewPortRect.size.w),
			(float)(windowSize.h * normalizedViewPortRect.size.h),
			clippingNear, clippingFar);
	}
	void Camera::GetProjectionMatrix(SOC_Matrix *outMatrix, float farGap /* =0 */)
	{
		if(camType == Type::Perspective)
		{
			GetPerspectiveMatrix(outMatrix, farGap);
			return;
		}

		GetOrthoGraphicMatrix(outMatrix);
	}

	void Camera::SetViewPort(Common::Rect<float> rect)
	{
		normalizedViewPortRect = rect;
		CalcAspect();
	}

	void Camera::SceneUpdate(float dt, std::vector<Object*> *sceneObjects)
	{
		for(vector<Object*>::iterator iter = sceneObjects->begin(); iter != sceneObjects->end(); ++iter)
			(*iter)->Update(dt);
	}

	void Camera::SceneRender(Camera *cam, std::vector<Object*>::iterator& objectBegin,
			std::vector<Object*>::iterator& objectEnd, Light::LightManager* sceneLights)
	{
		SOC_Matrix projMat, viewMat, viewProjMat;
		cam->GetProjectionMatrix(&projMat);
		cam->GetViewMatrix(&viewMat);

		viewProjMat = viewMat * projMat;

		cam->Clear();		
		cam->frustum->Make(&(viewMat * projMat));

		//���� �۾�.	

		vector<LightForm*> lights;
		sceneLights->Intersect(cam->frustum, &lights);
		//���� ���� ������ ����ü�� ��ġ�°� ��� ã��.

		for(vector<Object*>::iterator iter = objectBegin; iter != objectEnd; ++iter)
		{
			(*iter)->Culling(cam->frustum);
			(*iter)->Render(&lights, &viewMat, &projMat, &viewProjMat);
		}
	}

	void Camera::GetViewMatrix(SOC_Matrix *outMatrix)
	{
		ownerTransform->GetWorldMatrix(outMatrix);
		//ownerTransform->GetMatrix(outMatrix);

		SOC_Vector3 worldPos = ownerTransform->GetWorldPosition();

		SOC_Vector3 p = SOC_Vector3(
			-SOCVec3Dot(&ownerTransform->GetRight(), &worldPos),
			-SOCVec3Dot(&ownerTransform->GetUp(), &worldPos),
			-SOCVec3Dot(&ownerTransform->GetForward(), &worldPos));

		outMatrix->_41 = p.x;
		outMatrix->_42 = p.y;
		outMatrix->_43 = p.z;
		outMatrix->_44 = 1.0f;
	}

	void Camera::GetViewProjectionMatrix(SOC_Matrix *outMatrix, float farGap)
	{
		SOC_Matrix proj;

		ownerTransform->GetWorldMatrix(outMatrix); // view Matrix
		GetProjectionMatrix(&proj, farGap);

		SOCMatrixMultiply(outMatrix, outMatrix, &proj);
	}

	//Component::Type Camera::GetComponentType()
	//{
	//	return Component::Type::Camera;
	//}
}