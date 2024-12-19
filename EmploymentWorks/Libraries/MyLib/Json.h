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


/*Json�t�@�C���ɂ���

	"A" : [
		"B" : "Name",
		"C" : : {
			"D" : 0,
			"E" : 1
		}
	]
	
	A�̗v�f B��C
	B�̗v�f Name
	C�̗v�f D��E
	D�̗v�f 0
	E�̗v�f 1

	{}���̂��̂��v�f�ƂȂ�v�f���Q�Ƃ��đ�������肵�Ă���
	�v�f���Q�Ƃ��邱�Ƃŉ��s���Ă����Ȃ��Ă��ǂ����ł��悭�Ȃ�


*/