/*
* �v���C���̑̃N���X
*/

#pragma once
#include "Game/Player/PlayerPartsBase.h"


//�O���錾
namespace WataLib
{
	class Animation;
}

// �u�C���v�N���X���`����
class PlayerBody : public PlayerPartsBase
{

private:
	//static constexpr �R���p�C�����Ɍ��肷��@�N���X�O�ł̕ύX������K�v���Ȃ�����
	//static cons      �N���X�O�ŕύX����\��������ꍇ

	static constexpr const char PARTSNAME[] = "Body";


public:
	//�R���X�g���N�^
	PlayerBody(CommonResources* resources, 
		CharacterEntity* parent, 		                         //�e�N���X
		DirectX::SimpleMath::Vector3 scale,                  //�����̑傫��
		DirectX::SimpleMath::Vector3 position,               //�e�̍��W����ǂꂾ������Ă��邩
		DirectX::SimpleMath::Quaternion rotation);           //+Z�Ɍ����Ă���Ƃ��̉�]���
	//�f�X�g���N�^
	~PlayerBody() override;

	//IObject
	//������
	void Initialize() override;



};

