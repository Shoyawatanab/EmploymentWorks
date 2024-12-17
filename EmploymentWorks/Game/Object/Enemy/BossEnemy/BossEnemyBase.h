#pragma once
#ifndef BossEnemyBase_DEFINED
#define BossEnemyBase_DEFINED
#include "Interface/IComponent.h"
#include <unordered_map>
#include "Libraries/MyLib/Animation.h"

class CommonResources;
class Bounding;


class BossEnemyBase : public IComponent
{
public:



public:
	// �e���擾����
	IComponent* GetParent() const { return m_parent; }
	//�����傫�����擾
	DirectX::SimpleMath::Vector3 GetInitialScale() const { return m_initialScale; }
	//������]�p���擾����
	DirectX::SimpleMath::Quaternion GetInitialAngle() const { return m_initialAngle; }
	//���f�����擾����
	DirectX::Model* GetModel() { return nullptr; }
	//���[���h�s����擾����
	DirectX::SimpleMath::Matrix& GetWorldMatrix() { return m_worldMatrix; }
	//�e���W����̋������擾
	DirectX::SimpleMath::Vector3 GetPositonFromParent() { return m_positonFromParent; }
	CommonResources* GetResources() { return m_commonResources; }

	//�A�j���[�V�����̓o�^ 
	void SetAnimations(std::unique_ptr<Animation> animations, std::string name) { m_animations[name] = std::move(animations); }

	//���s����A�j���[�V�����̖��O
	void SetRunnginAnimationName(std::string name) override;


	//�A�j���[�V�������W�̎擾
	DirectX::SimpleMath::Vector3 GetAnimationPosition() { return m_animationPosition; }
	//�A�j���[�V�����̉�]�̎擾
	DirectX::SimpleMath::Quaternion GetAnimationRotation() { return m_animationRotation; }



public:
	// �C�����i�ԍ������Z�b�g����(-1����J�n����)
	static int ResetPartsNumber() { s_partsNumber = -1;  return s_partsNumber; }
	// �C�����i�ԍ��̃C���N�������g��ɖC�����i�ԍ����擾����
	static int GetPartsNumberAfterIncrement() { return ++s_partsNumber; }

public:
	// �R���X�g���N�^
	BossEnemyBase(CommonResources* resources,BossEnemyBase* parent,
		const DirectX::SimpleMath::Vector3 initialScale, const DirectX::SimpleMath::Vector3& positonFromParent,
		const DirectX::SimpleMath::Quaternion& initialAngle,int partsHp);
	// �f�X�g���N�^
	virtual ~BossEnemyBase();
	// ����������
	virtual void Initialize();
	// ����������
	virtual void Initialize( std::unique_ptr<DirectX::Model> model);
	// �X�V����
	inline virtual void Update(const float& elapsdTime);
	// �C�����i��ǉ�����
	virtual void Attach(std::unique_ptr<IComponent> turretPart);
	// �C�����i���폜����
	virtual void Detach(std::unique_ptr<IComponent> turretPart);
	// �`�悷��
	virtual void Render(DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix projection);
	// �`�悷��
	inline virtual void Render(const DirectX::SimpleMath::Matrix& matrix,DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix projection);
	// ���f����`�悷��
	inline virtual void DrawModel(const DirectX::SimpleMath::Matrix& matrix, DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix projection);
	// ���E�{�b�N�X��`�悷��
	inline void DrawBoundingBox(const DirectX::SimpleMath::Matrix& matrix);
	// �㏈�����s��
	virtual void Finalize();

	virtual void RegistrationCollionManager(CollisionManager* collsionManager) override;

	virtual void Damage(const int  damage);

	virtual void PartsDamage(const int  damage);

	Bounding* GetBounding() const { return m_bounding.get(); }

	

public:

	//�o�E���f�B���O�̐���
	void CreateBounding(DirectX::SimpleMath::Vector3 position, DirectX::SimpleMath::Quaternion rotate , DirectX::SimpleMath::Vector3 boxExten,float SphereRadius);
	//�o�E���f�B���O�̍X�V�@���W
	void BoundingUdate(DirectX::SimpleMath::Vector3 position,DirectX::SimpleMath::Quaternion rotate);

	void BoundingRender(DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix projection);

	//�A�j���[�V�����̎��s
	Animation::AnimationState AnimationUdate(const float& elapsdTime)override ;


private:
	// �C�����i�J�E���g
	static int s_partsNumber;

private:
	// ���f��
	std::unique_ptr<DirectX::Model> m_model;

	std::unique_ptr<Bounding> m_bounding;

	// �e
	BossEnemyBase* m_parent;
	//�����傫��
	DirectX::SimpleMath::Vector3 m_initialScale;
	// ������]�p
	DirectX::SimpleMath::Quaternion m_initialAngle;
	// ���i�z��
	std::vector<std::unique_ptr<IComponent>> m_parts;
	//	���[���h�s��
	DirectX::SimpleMath::Matrix m_worldMatrix;

	//�e���W����̋���
	DirectX::SimpleMath::Vector3 m_positonFromParent;
	// ���ʃ��\�[�X
	CommonResources* m_commonResources;
	//���s����A�j���[�V�����̖��O
	std::string m_runningAnimationName;
	//�A�j���[�V�����̕ۑ��ϐ�
	std::unordered_map<std::string, std::unique_ptr<Animation>> m_animations;
	//�A�j���[�V�����̍��W
	DirectX::SimpleMath::Vector3 m_animationPosition;
	//�A�j���[�V�����̉�]
	DirectX::SimpleMath::Quaternion m_animationRotation;
	//�A�j���[�V�����̐؂�ւ���
	int  m_animationSwitchingCount;
	//�A�j���[�V�����̎��s������
	float m_animetionTime;

	//�o�[�c���Ƃ�HP
	int m_hp;

	//���d�q�b�g��h�����߂̕ϐ�
	bool m_isHit;

	float m_hitTime;



public:

	const int BOOMERANGDAMEGE = 2;

	//�r��HP
	const int ARMHP = 4;
	//���̂�HP
	const  int BODYHP = 10;
	//����HP
	const int LEGHP = 6;
};
#endif		// BossEnemyBase_DEFINED
