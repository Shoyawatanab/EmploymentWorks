/*
* �L�����N�^�[�̃C���^�[�t�F�[�X
*/
#pragma once
#include <unordered_map>
#include "Game/Interface/IMoveObject.h"
#include "Libraries/WataLib/Json.h"

class ICharacter : public IMoveObject
{
public:

	using ANIMATIONDATAS = std::unordered_map<std::string, std::unordered_map<std::string, WataLib::Json::AnimationData>>;

public:
	//�f�X�g���N�^
	virtual ~ICharacter() = default;
	//�A�j���[�V�����̓o�^
	virtual void SetAnimationData(std::string animationType, ANIMATIONDATAS datas ,bool isNormalAnimation) = 0;
	//�A�j���[�V�����̕ύX
	virtual void ChangeAnimation(std::string animationType) = 0;
	//HP�֌W



};



