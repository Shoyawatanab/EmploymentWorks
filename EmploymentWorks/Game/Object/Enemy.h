#pragma once
/*
	@file	Enemy.h.h
	@brief	プレイシーンクラス
*/
#include "pch.h"
#include "Boomerang/Boomerang.h"

// 前方宣言
class CommonResources;

namespace mylib
{
	class DebugCamera;
	class GridFloor;
}


class Enemy final 

{
private:
	// 共通リソース
	CommonResources* m_commonResources;

	// モデル
	std::unique_ptr<DirectX::Model> m_model;

	DirectX::SimpleMath::Vector3 m_position;


public:
	Enemy();
	~Enemy() ;

	void Initialize(CommonResources* resources, DirectX::SimpleMath::Vector3 position) ;
	void Update(float elapsedTime);
	void Render(DirectX::CXMMATRIX view, DirectX::CXMMATRIX projection) ;
	void Finalize() ;


};
