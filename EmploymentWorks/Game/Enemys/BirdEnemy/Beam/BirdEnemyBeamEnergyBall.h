/*
	@file	BirdEnemyBeamEnergyBall.h
	@brief　鳥の敵のビームのエネルギー弾
*/
#pragma once
#include "Game/Entities/MoveEntity.h"

// 前方宣言
class CommonResources;
class BirdEnemyBeam;

namespace mylib
{
	class DebugCamera;
	class GridFloor;
}
namespace WataLib
{
	class Bounding;
}


class BirdEnemyBeamEnergyBall : public CollisionEntity
{


public:

	static const std::vector<D3D11_INPUT_ELEMENT_DESC> INPUT_LAYOUT;


	struct ConstBuffer
	{
		DirectX::SimpleMath::Matrix		matWorld;
		DirectX::SimpleMath::Matrix		matView;
		DirectX::SimpleMath::Matrix		matProj;
	};


public:



	DirectX::SimpleMath::Vector3 GetTarget() { return m_target; }
 
	void SetTarget(DirectX::SimpleMath::Vector3 target) { m_target = target; }




	DirectX::SimpleMath::Vector3 GetInitialScale() { return m_initialScale; }
	
	DirectX::SimpleMath::Vector3 GetMaxScale() { return m_maxScale; }

	float GetMaxSizeTime() { return m_maxSizeTime; }


public :
	BirdEnemyBeamEnergyBall(CommonResources* resources, BaseEntity* parent, BirdEnemyBeam* beam);

	//デストラクタ
	~BirdEnemyBeamEnergyBall() override;

	//IObject
		//初期化
	void Initialize() override;
	//描画
	void Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection) override;
	//更新処理
	void  Update(const float& elapsedTime) override;

	//ICollisionObject
		//タグの取得
	CollisionTag GetCollisionTag() override { return CollisionEntity::CollisionTag::Beam; };
	//当たり判定クラスに登録
	void  AddCollision(CollisionManager* collsionManager) override;

	//当たった時に呼び出される
	void OnCollisionEnter(CollisionEntity* object, CollisionTag tag) override;
	//当たり判定の種類の取得
	const CollisionType GetCollisionType() override { return CollisionType::AABB; }
	//押し出しをするかどうか
	const bool GetIsExtrusion() override { return true; };
	//当たり判定を行わないタグ
	const std::vector<CollisionTag> GetNoHitDetectionTag() {
		return  {
			{CollisionTag::Enemy}
		};
	}




private:


	//	頂点シェーダ
	Microsoft::WRL::ComPtr<ID3D11VertexShader> m_vertexShader;
	//	ピクセルシェーダ
	Microsoft::WRL::ComPtr<ID3D11PixelShader> m_pixelShader;

	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;
	Microsoft::WRL::ComPtr<ID3D11Buffer>	m_CBuffer;

	// モデル
	std::unique_ptr<DirectX::Model> m_model;

	DirectX::SimpleMath::Vector3 m_iniialPosition;
	DirectX::SimpleMath::Quaternion m_initialRotate;
	DirectX::SimpleMath::Vector3 m_target;
	DirectX::SimpleMath::Vector3 m_initialScale;
	DirectX::SimpleMath::Vector3 m_maxScale;
	DirectX::SimpleMath::Vector3 m_wordlPosition;

	BirdEnemyBeam* m_beam;

	float m_maxSizeTime;
	float m_time;



};
