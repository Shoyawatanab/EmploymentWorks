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

	//���s���̃A�j���[�V�����̎��
	const std::string& GetCurrentAnimationType() { return m_currentAnimationType; }
	//���s����A�j���[�V�����̓o�^
	void SetCurrentAnimationType(const std::string& type) { m_currentAnimationType = type; }
	//�A�j���[�V�����̎擾
	WataLib::Animation* GetAnimation() { return m_animation.get(); }

public:
	//�R���X�g���N
	CharacterEntity(CommonResources* resources
		,const DirectX::SimpleMath::Vector3& scale
		, const DirectX::SimpleMath::Vector3& position
		, const DirectX::SimpleMath::Quaternion& rotation);
	//�f�X�g���N�^
	~CharacterEntity() override;

//BaseEntity
	//������
	void Initialize();
	//�X�V����
	void  Update(const float& elapsedTime)  override;
	//�`�揈��
	void Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection);
//CollisionEntity
	//�����������ɌĂяo�����
	void OnCollisionEnter(CollisionEntity* object, CollisionTag tag) override;


	//�A�j���[�V�����̓o�^
	virtual void SetAnimationData(const std::string& animationType
		, std::unordered_map<std::string, std::unordered_map<std::string, WataLib::Json::AnimationData>> datas
		, const std::string& partsName = ""
		, bool isNormalAnimation = false);
	//�A�j���[�V�����̕ύX
	virtual	void ChangeAnimation(const std::string& animationType);

private:

	//���s�A�j���[�V������
	std::string m_currentAnimationType;
	//�A�j���[�V����
	std::unique_ptr<WataLib::Animation> m_animation;


};


