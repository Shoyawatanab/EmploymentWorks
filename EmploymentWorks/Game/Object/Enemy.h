#pragma once
/*
	@file	Enemy.h.h
	@brief	プレイシーンクラス
*/
#include "pch.h"
#include "Boomerang/Boomerang.h"

// 前方宣言
class CommonResources;
class Bounding;

namespace mylib
{
	class DebugCamera;
	class GridFloor;
}


class Enemy final 

{
public:
	DirectX::SimpleMath::Vector3 GetPosition() { return m_position; }
	DirectX::SimpleMath::Quaternion GetRotate() { return m_rotate; }

	Bounding* GetBounding() { return m_bounding.get(); }


private:
	// 共通リソース
	CommonResources* m_commonResources;

	// モデル
	std::unique_ptr<DirectX::Model> m_model;

	DirectX::SimpleMath::Vector3 m_position;
	DirectX::SimpleMath::Quaternion m_rotate;

	std::unique_ptr<Bounding> m_bounding;

public:
	Enemy();
	~Enemy() ;

	void Initialize(CommonResources* resources, DirectX::SimpleMath::Vector3 position) ;
	void Update(float elapsedTime);
	void Render(DirectX::CXMMATRIX view, DirectX::CXMMATRIX projection) ;
	void Finalize() ;


};
