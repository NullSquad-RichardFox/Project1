#pragma once


enum class ECameraMode
{
	Orthographic,
	Perspective
};

class Camera
{
public:
	Camera(float aspectRatio, float zoomLevel, ECameraMode cameraMode);
	~Camera();

	void OnUpdate(float deltaTime);

	void SetZoomLevel(float zoomLevel);
	void SetRotation(glm::vec3 rotation);
	void SetPosition(glm::vec3 position);

	inline float GetZoomLevel() const { return ZoomLevel; }
	inline glm::vec3 GetRotation() const { return Rotation; }
	inline glm::vec3 GetPosition() const { return Position; }

	inline const glm::mat4& GetProjectionMatrix() const { return ProjectionMat; }
	inline const glm::mat4& GetViewMatrix() const { return ViewMat; }
	inline const glm::mat4& GetViewProjectionMatrix() const { return ViewProjectionMat; }

private:
	void RecalculateMatrices();

	void OnWindowResize(int32 width, int32 height);

	glm::mat4 ProjectionMat;
	glm::mat4 ViewMat;
	glm::mat4 ViewProjectionMat;

	float AspectRatio;
	float ZoomLevel;

	glm::vec3 Rotation;
	glm::vec3 Position;

	bool bUpdateMatrices;
	ECameraMode CameraMode;
};