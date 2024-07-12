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

// ICollisionObjectインタフェースを定義する(GOF Stateパターン)
class ICollisionObject
{
public:
	/// <summary>
	/// 当たり判定クラスに登録する
	/// </summary>
	/// <param name="collsionManager">当たり判定クラス</param>
	virtual void RegistrationCollionManager(CollisionManager* collsionManager) = 0;


	/// <summary>
	/// バウンディングクラスの取得
	/// </summary>
	/// <returns>バウンディングクラス</returns>
	virtual Bounding* GetBounding() const = 0;


	/// <summary>
	/// タグの取得
	/// </summary>
	/// <returns>タグ</returns>
	virtual CollsionObjectTag GetCollsionTag() const = 0;

	virtual void OnCollision() = 0; 

	virtual void SetPos(DirectX::SimpleMath::Vector3& Pos) = 0;

	virtual DirectX::SimpleMath::Vector3 GetPos() = 0;
};

#endif		// ICollisionObject_DEFINED
