#pragma once


class Time
{
public:
	static void Initialize();
	static void Shutdown();

	inline static float OnUpdate() { return sTimeInstance->OnUpdate_Int(); }
	inline static float GetDelatTime() { return sTimeInstance->DeltaTime; }

private:
	float OnUpdate_Int();

private:
	inline static Time* sTimeInstance = nullptr;

	float DeltaTime = 0.0f;
	float TimeLastFrame = 0.0f;
};

