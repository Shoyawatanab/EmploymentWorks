/*
	@file	BeamEnergyBall.h
	@brief	プレイシーンクラス
*/
#pragma once
#include "Game/Entities/MoveEntity.h"

// 前方宣言
class CommonResources;
class Beam;


namespace mylib
{
	class DebugCamera;
	class GridFloor;
}

namespace WataLib
{
	class Bounding;

}

class BeamEnergyBall : public MoveEntity
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

	static constexpr DirectX::SimpleMath::Vector3 INITALPOSITION { 100, 100, 0 };


public:
	//コンストラク
	BeamEnergyBall(CommonResources* resources,BaseEntity* parent);
	
	//デストラクタ
	~BeamEnergyBall() override;

	
	//初期化
	void Initialize() override;
	//描画処理
	void Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection) override;
	//更新処理
	void  Update(const float& elapsedTime) override;

	//タグの取得
	CollisionTag GetCollisionTag() override { return CollisionEntity::CollisionTag::BEAM; };
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
			,{CollisionTag::BOOMERANG}
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
	//初期回転
	DirectX::SimpleMath::Quaternion m_initialRotate;
	//ターゲット
	DirectX::SimpleMath::Vector3 m_target;
	//初期サイズ
	DirectX::SimpleMath::Vector3 m_initialScale;
	//最大サイズ
	DirectX::SimpleMath::Vector3 m_maxScale;
	//ビーム
	Beam* m_beam;
	//最大サイズになる時間
	float m_maxSizeTime;
	//時間
	float m_time;




};
