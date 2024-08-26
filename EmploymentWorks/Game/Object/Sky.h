#pragma once
/*
	@file	Sky.h.h
	@brief	プレイシーンクラス
*/
#pragma once
#include "pch.h"

// 前方宣言
class CommonResources;




class Sky 

{
public:


private:
	// 共通リソース
	CommonResources* m_commonResources;

	// モデル
	std::unique_ptr<DirectX::Model> m_model;


public:
	Sky();
	~Sky();

	void Initialize(CommonResources* resources);
	void Update(float elapsedTime, DirectX::SimpleMath::Quaternion cameraRotation);
	void Render(DirectX::CXMMATRIX view, DirectX::CXMMATRIX projection);
	void Finalize();


private:
};
