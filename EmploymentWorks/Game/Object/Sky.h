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
	void Update(float elapsedTime);
	void Render(DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix projection);
	void Finalize();


private:
};
