#pragma once
#ifndef ICollisionObject_DEFINED
#define ICollisionObject_DEFINED

class CollisionManager;
class Bounding;


enum  class CollsionObjectTag
{
	Player = 0,
	Enemy,
	NotMoveObject,
	Boomerang,


};

// ICollisionObject�C���^�t�F�[�X���`����(GOF State�p�^�[��)
class ICollisionObject
{
public:
	/// <summary>
	/// �����蔻��N���X�ɓo�^����
	/// </summary>
	/// <param name="collsionManager">�����蔻��N���X</param>
	virtual void RegistrationCollionManager(CollisionManager* collsionManager) = 0;


	/// <summary>
	/// �o�E���f�B���O�N���X�̎擾
	/// </summary>
	/// <returns>�o�E���f�B���O�N���X</returns>
	virtual Bounding* GetBounding() const = 0;


	/// <summary>
	/// �^�O�̎擾
	/// </summary>
	/// <returns>�^�O</returns>
	virtual CollsionObjectTag GetCollsionTag() const = 0;

	virtual void OnCollision() = 0; 

	virtual void SetPos(DirectX::SimpleMath::Vector3& Pos) = 0;

	virtual DirectX::SimpleMath::Vector3 GetPos() = 0;
};

#endif		// ICollisionObject_DEFINED
