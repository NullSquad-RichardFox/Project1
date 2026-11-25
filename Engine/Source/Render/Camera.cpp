#include "pch.h"
#include "Camera.h"
#include "Utility/Time.h"

#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/quaternion.hpp"


Camera::Camera(float aspectRatio, float zoomLevel, ECameraMode cameraMode)
	:AspectRatio(aspectRatio), ZoomLevel(zoomLevel), Rotation(0.0f), Position(0.0f), ProjectionMat(1.0f), ViewMat(1.0f), ViewProjectionMat(1.0f), CameraMode(cameraMode)
{
	RecalculateMatrices();
}

Camera::~Camera()
{

}

void Camera::OnUpdate(float deltaTime)
{
	if (bUpdateMatrices) RecalculateMatrices();
}

void Camera::SetZoomLevel(float zoomLevel)
{
	ZoomLevel = zoomLevel;
	bUpdateMatrices = true;
}

void Camera::SetRotation(glm::vec3 rotation)
{
	Rotation = rotation;
	bUpdateMatrices = true;
}

void Camera::SetPosition(glm::vec3 position)
{
	Position = position;
	bUpdateMatrices = true;
}

void Camera::RecalculateMatrices()
{
	switch (CameraMode)
	{
	case ECameraMode::Orthographic:
		ProjectionMat = glm::ortho<float>(-AspectRatio * ZoomLevel, AspectRatio * ZoomLevel, -ZoomLevel, ZoomLevel, -1, 1);
		break;
	
	case ECameraMode::Perspective:
		ProjectionMat = glm::perspective(90.f, AspectRatio, 0.1f, 1000.f);
		break;
	}
	
	glm::quat q(Rotation);
	ViewMat = glm::inverse(glm::translate(glm::mat4(1.0f), Position) * glm::toMat4(q));
	ViewProjectionMat = ProjectionMat * ViewMat;

	bUpdateMatrices = false;
}

void Camera::OnWindowResize(int32 width, int32 height)
{
	AspectRatio = (float)width / (float)height;
	bUpdateMatrices = true;
}