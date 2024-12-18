#pragma once



class Json
{

public:


	struct StageParamater
	{

		std::string ModelName;
		DirectX::SimpleMath::Vector3 Position;
		DirectX::SimpleMath::Vector3 Scale;
		DirectX::SimpleMath::Vector3 Rotation;
		float BoundingSphereRadius;


	};


public:

	Json();
	~Json();

public:

	void LoadJson();


	std::vector<StageParamater> LoadStageParameter(const std::wstring& fileName);

private:

	std::vector<StageParamater> m_stageParamter;

};