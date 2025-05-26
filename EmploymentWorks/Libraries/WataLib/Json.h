#pragma once
#include <unordered_map>
#include <optional>

namespace WataLib
{
	class Json
	{

	public:

//�X�e�[�W����Json�ǂݍ��ݐ�p�\����

		struct ObjectData
		{
			std::string ModelName;
			DirectX::SimpleMath::Vector3 Position;
			DirectX::SimpleMath::Vector3 Scale;
			DirectX::SimpleMath::Vector3 Rotation;
			float BoundingSphereRadius;
		};

		struct StageData
		{
			int BoomerangCount;
			std::vector<ObjectData> ObjectDatas;
		};



//�A�j���[�V������Json�ǂݍ��ݐ�p�\����

		struct AnimationKeyFram
		{
			float Time;                                //�o�ߎ���
			std::optional<DirectX::SimpleMath::Vector3>  Scale ;
			std::optional< DirectX::SimpleMath::Vector3> Position;	    //�o�ߎ��Ԃɑ΂��Ă̍��W
			std::optional< DirectX::SimpleMath::Vector3> Rotation; 		//�o�ߎ��Ԃɑ΂��Ẳ�]

		};

		struct AnimationData
		{
			float TotalTime;                              //�A�j���[�V�����S�̂̎���
			float Speed;								  //�A�j���[�V�����̐i�s�X�s�[�h
			bool IsLoop;								  //1�A�j���[�V���������[�v�����邩
			std::vector<AnimationKeyFram> FramDatas;	  //�L�[�t���[���̏��@���ԏ��ɕ���ł�����̂Ƃ���

		};

//

	public:
		//�R���X�g���N�^
		Json();
		//�f�X�g���N�^
		~Json();
		//�X�e�[�W���̓ǂݍ���
		StageData LoadStageDatas(const std::wstring& fileName);
		//�A�j���[�V�����f�[�^�̓ǂݍ���
		std::unordered_map<std::string, AnimationData> LoadAnimationData(const std::wstring& fileName);

	private:
		//�X�e�[�W���̃p�����[�^�[
		std::vector<StageData> m_stageParamter;

		

	};
}

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