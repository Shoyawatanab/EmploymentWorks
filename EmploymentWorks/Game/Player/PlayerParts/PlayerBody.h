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
	//�p�[�c��
	static constexpr const char PARTSNAME[] = "Body";


public:
	//�R���X�g���N�^
	PlayerBody(CommonResources* resources 
		, CharacterEntity* parent 		                         //�e�N���X
		, const DirectX::SimpleMath::Vector3& scale                  //�����̑傫��
		, const DirectX::SimpleMath::Vector3& position               //�e�̍��W����ǂꂾ������Ă��邩
		, const DirectX::SimpleMath::Quaternion& rotation);           //+Z�Ɍ����Ă���Ƃ��̉�]���
	//�f�X�g���N�^
	~PlayerBody() override;

	//IObject
	//������
	void Initialize() override;



};

