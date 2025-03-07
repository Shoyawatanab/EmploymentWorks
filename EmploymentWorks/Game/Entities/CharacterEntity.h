/*
* �v���C���N���X�@
*/

#pragma once

#include "MoveEntity.h"
#include <unordered_map>
#include "Libraries/WataLib/Json.h"

namespace WataLib
{
	class Animation;
}

class CharacterEntity : public MoveEntity
{
public:


	const std::string& GetCurrentAnimationType() { return m_currentAnimationType; }

	void SetCurrentAnimationType(const std::string& type) { m_currentAnimationType = type; }

	WataLib::Animation* GetAnimation() { return m_animation.get(); }

public:


	CharacterEntity(CommonResources* resources
		,const DirectX::SimpleMath::Vector3& scale
		, const DirectX::SimpleMath::Vector3& position
		, const DirectX::SimpleMath::Quaternion& rotation);

	~CharacterEntity() override;

//BaseEntity
	//������
	void Initialize();
	//�X�V����
	void  Update(const float& elapsedTime)  override;
	//�`��
	void Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection);
//CollisionEntity
	//�����������ɌĂяo�����
	void OnCollisionEnter(CollisionEntity* object, CollisionTag tag) override;




	//�A�j���[�V�����̓o�^
	virtual void SetAnimationData(std::string animationType
		, std::unordered_map<std::string, std::unordered_map<std::string, WataLib::Json::AnimationData>> datas
		, const std::string& partsName = ""
		, bool isNormalAnimation = false);
	//�A�j���[�V�����̕ύX
	virtual	void ChangeAnimation(std::string animationType);




private:

	//���s�A�j���[�V������
	std::string m_currentAnimationType;

	std::unique_ptr<WataLib::Animation> m_animation;


};


