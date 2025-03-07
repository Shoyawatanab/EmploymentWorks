/*
* オブジェクトのインターフェース
*/
#pragma once
#include "pch.h"

class CommonResources;


class IObject
{
public:
	//デストラクタ
	virtual ~IObject() = default;
	//初期化
	virtual void Initialize(CommonResources* resources) = 0;
	//座標の取得
	virtual const DirectX::SimpleMath::Vector3& GetPosition() = 0;
	//座標の設定
	virtual void SetPosition(const DirectX::SimpleMath::Vector3& position) = 0;
	//大きさの取得
	virtual const DirectX::SimpleMath::Vector3& GetScale() = 0;
	//大きさの設定
	virtual void SetScale(const DirectX::SimpleMath::Vector3& scale) = 0;
	//回転の取得
	virtual const DirectX::SimpleMath::Quaternion& GetRotation() = 0;
	//回転の設定
	virtual void SetRotation(const DirectX::SimpleMath::Quaternion& rotation) = 0;
	//描画
	virtual void Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection) = 0;
	//行列の取得
	virtual DirectX::SimpleMath::Matrix& GetMatrix() = 0;
	//親子関係があるかどうかの取得
	virtual bool& GetIsParentActive() = 0;
	//親子関係をやるかどうかの設定
	virtual void SetIsParentActive(const bool& isActive) = 0;
};
