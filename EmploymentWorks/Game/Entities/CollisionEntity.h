/*
* プレイヤクラス　
*/

#pragma once

#include "BaseEntity.h"

class CollisionManager;

namespace WataLib
{

	class Bounding;
}


class CollisionEntity : public BaseEntity
{
public:

	//当たり判定の種類
	enum  class CollisionType
	{
		AABB = 1 << 0
		, OBB = 1 << 1
		, SPHERE = 1 << 2
	};

	//当たり判定のタグ
	enum class CollisionTag
	{
		NONE = 0
		, PLAYER = 1 << 0
		, PLAYERPARTS = 1 << 1
		, STAGE = 1 << 2
		, ENEMY = 1 << 3
		, ENEYPARTS = 1 << 4
		, BOOMERANG = 1 << 5
		, BEAM = 1 << 6
		, BARRIER = 1 << 7
	};

public:
	//当たり判定が有効かどうか
	bool GetIsCollisionActive() { return m_isCollisionActive; }
	//当たり判定の有効かどうかの登録
	void SetIsCollisionActive(bool isActive) { m_isCollisionActive = isActive; }

public:

	//コンストラクタ
	CollisionEntity(CommonResources* resources
		, const DirectX::SimpleMath::Vector3& scale
		, const DirectX::SimpleMath::Vector3& position
		, const DirectX::SimpleMath::Quaternion& rotation) ;


	//初期化
	void Initialize() override;
	//更新処理
	void  Update(const float& elapsedTime) override ;
	//描画処理
	void Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection) override ;


	//タグの取得
	virtual CollisionTag GetCollisionTag() = 0;
	//当たった時に呼び出される
	virtual void OnCollisionEnter(CollisionEntity* object, CollisionTag tag) { UNREFERENCED_PARAMETER(object); UNREFERENCED_PARAMETER(tag); };
	//当たり続けているときの呼び出される
	virtual void OnCollisionStay(CollisionEntity* object, CollisionTag tag) { UNREFERENCED_PARAMETER(object); UNREFERENCED_PARAMETER(tag); };
	//衝突が終了したときに呼び出される
	virtual void OnCollisionExit(CollisionEntity* object, CollisionTag tag) { UNREFERENCED_PARAMETER(object); UNREFERENCED_PARAMETER(tag); };
	//当たり判定クラスに登録
	virtual void  AddCollision(CollisionManager* collsionManager);
	//当たり判定の取得
	WataLib::Bounding* GetBounding() { return m_bounding.get(); };
	//当たり判定の種類の取得
	virtual const CollisionType GetCollisionType() = 0;
	//押し出しをするかどうか
	virtual const bool GetIsExtrusion() = 0;
	//当たり判定を行わないタグ
	virtual const std::vector<CollisionTag> GetNoHitDetectionTag() = 0;
	//当たったオブジェクトの取得
	const std::vector<CollisionEntity*> GetHitObject() { return m_hitObject; };
	//当たったオブジェクトの登録
	void SetHitObject(CollisionEntity* object) { m_hitObject.push_back(object); };
	//当たったオブジェクトの削除
	void DleteHitObject(CollisionEntity* object, bool& isDelete) {
		size_t initialSize = m_hitObject.size();
		//オブジェクトがあれば削除
		m_hitObject.erase(std::remove(m_hitObject.begin(), m_hitObject.end(), object), m_hitObject.end());
		//削除できたかどうか
		if (m_hitObject.size() < initialSize)
		{
			//削除できたら
			isDelete = true;
		}
	};

	//押し出しを行わないタグ
	virtual const std::vector<CollisionTag> GetNoExtrusionTag()  = 0;

private:
	//当たり判定
	std::unique_ptr<WataLib::Bounding> m_bounding;
	//当たったオブジェクトの格納変数
	std::vector<CollisionEntity*> m_hitObject;
	//当たり判定の有無
	bool m_isCollisionActive;

};


