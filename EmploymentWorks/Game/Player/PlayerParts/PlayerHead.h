/*
* �v���C���̓��N���X
*/
#pragma once
#include "Game/Player/PlayerPartsBase.h"

namespace WataLib
{
	class Animation;
}
// �u�C���v�N���X���`����
class PlayerHead : public PlayerPartsBase
{
private:
	//�p�[�c��
	static constexpr const char PARTSNAME[] = "Head";

public:
	//�R���X�g���N�^
	PlayerHead(CommonResources* resources, 
		CharacterEntity* parent
		, const DirectX::SimpleMath::Vector3& scale
		, const DirectX::SimpleMath::Vector3& position
		, const DirectX::SimpleMath::Quaternion& rotation);
	//�f�X�g���N�^
	~PlayerHead() override;



	//������
	void Initialize() override;

};

