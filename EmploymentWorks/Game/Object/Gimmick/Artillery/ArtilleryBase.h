#pragma once
/*
	@file	ArtilleryBase.h.h
	@brief	プレイシーンクラス
*/
#pragma once
#include "pch.h"
#include "Game/Object/Boomerang/Boomerang.h"
#include "Interface/ICollisionObject.h"

// 前方宣言
class CommonResources;
class Bounding;



class ArtilleryBase

{
public:


private:
	// 共通リソース
	CommonResources* m_commonResources;

	std::unique_ptr<Bounding> m_bounding;

	// モデル
	std::unique_ptr<DirectX::Model> m_model;

	DirectX::SimpleMath::Vector3 m_position;
	DirectX::SimpleMath::Vector3 m_scale;
	DirectX::SimpleMath::Quaternion m_rotate;




public:
	ArtilleryBase();
	~ArtilleryBase() ;

	void Initialize(CommonResources* resources, DirectX::SimpleMath::Vector3 position, DirectX::SimpleMath::Vector3 Scale ,DirectX::SimpleMath::Quaternion Rotate);
	void Update(float elapsedTime);
	void Render(DirectX::CXMMATRIX view, DirectX::CXMMATRIX projection) ;
	void Finalize() ;


private:
};
