#pragma once
/*
	@file	Sky.h.h
	@brief	プレイシーンクラス
*/
#pragma once
#include "pch.h"
#include "Game/Entities/BaseEntity.h"

// 前方宣言
class CommonResources;




class Sky : public BaseEntity
{


public:
	Sky(CommonResources* resources
		, DirectX::SimpleMath::Vector3 scale,
		DirectX::SimpleMath::Vector3 position,
		DirectX::SimpleMath::Quaternion rotation);


	//デストラクタ
	~Sky() override;

	//IObject
		//初期化
	void Initialize() override;
	//描画
	void Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection) override;
	//更新処理
	void  Update(const float& elapsedTime) override;

private:

	// モデル
	DirectX::Model* m_model;
};
