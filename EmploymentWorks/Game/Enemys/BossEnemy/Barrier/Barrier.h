/*
	@file	Barrier.h
	@brief	プレイシーンクラス
*/
#pragma once
#include "Game/Entities/MoveEntity.h"

// 前方宣言
class CommonResources;
class Beam;
class BarrierStateMachine;

namespace mylib
{
	class DebugCamera;
	class GridFloor;
}

namespace WataLib
{
	class Bounding;

}

class Barrier : public MoveEntity
{
public:

	//コンスタントバッファ
	struct ConstBuffer
	{
		DirectX::SimpleMath::Matrix		matWorld;
		DirectX::SimpleMath::Matrix		matView;
		DirectX::SimpleMath::Matrix		matProj;
		DirectX::SimpleMath::Vector4    Color;

	};

	static constexpr DirectX::SimpleMath::Vector3 SCALE { 1.5f, 2.0f, 1.0f };

public:

	BarrierStateMachine* GetBarrierStateMachine() { return m_stateMachine.get(); }

public:
	//コンストラク
	Barrier(CommonResources* resources,BaseEntity* parent);
	//デストラクタ
	~Barrier() override;

	//初期化
	void Initialize() override;
	//描画処理
	void Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection) override;
	//更新処理
	void  Update(const float& elapsedTime) override;

	//有効になったら
	void OnEnable() override;
	//無効になったら
	void OnDisable()override;

	//ICollisionObject
		//タグの取得
	CollisionTag GetCollisionTag() override { return CollisionEntity::CollisionTag::BARRIER; };
	//当たり判定クラスに登録
	void  AddCollision(CollisionManager* collsionManager) override;

	//当たった時に呼び出される
	void OnCollisionEnter(CollisionEntity* object, CollisionTag tag) override;
	//当たり判定の種類の取得
	const CollisionType GetCollisionType() override { return CollisionType::AABB; }
	//押し出しをするかどうか
	const bool GetIsExtrusion() override { return false; };
	//当たり判定を行わないタグ
	const std::vector<CollisionTag> GetNoHitDetectionTag() {
		return  {
			{CollisionTag::PLAYERPARTS}
			,{CollisionTag::ENEMY}
			,{CollisionTag::ENEYPARTS}
		};
	}
	//押し出しを行わないタグ
	const std::vector<CollisionTag> GetNoExtrusionTag() {
		return  {
		};
	};



	//クラスに必要な情報（ポインタ）の登録
	void AddPointer(Beam* beam);
	//リセット
	void ReSet();

private:

	static const std::vector<D3D11_INPUT_ELEMENT_DESC> INPUT_LAYOUT;

	//	頂点シェーダ
	Microsoft::WRL::ComPtr<ID3D11VertexShader> m_vertexShader;
	//	ピクセルシェーダ
	Microsoft::WRL::ComPtr<ID3D11PixelShader> m_pixelShader;
	//インプットレイアウト
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;
	//定数バッファ
	Microsoft::WRL::ComPtr<ID3D11Buffer>	m_CBuffer;

	// モデル
	DirectX::Model* m_model;
	//ステートマシーン
	std::unique_ptr<BarrierStateMachine> m_stateMachine;
	//初期回転
	DirectX::SimpleMath::Quaternion m_initialRotate;
	//初期の大きさ
	DirectX::SimpleMath::Vector3 m_initialScale;
	//最大の大きさ
	DirectX::SimpleMath::Vector3 m_maxScale;
	//ビーム
	Beam* m_beam;
	//最大サイズになる時間
	float m_maxSizeTime;
	//時間
	float m_time;




};
