#pragma once



class Json
{

public:


	struct StageData
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



	std::vector<StageData> LoadStageDatas(const std::wstring& fileName);

private:

	std::vector<StageData> m_stageParamter;

};


/*Jsonファイルについて

	"A" : [
		"B" : "Name",
		"C" : : {
			"D" : 0,
			"E" : 1
		}
	]
	
	Aの要素 BとC
	Bの要素 Name
	Cの要素 DとE
	Dの要素 0
	Eの要素 1

	{}中のものが要素となり要素を参照して代入したりしている
	要素を参照することで改行してもしなくてもどっちでもよくなる


*/