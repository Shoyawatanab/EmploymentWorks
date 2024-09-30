#pragma once
#ifndef RESOURCES_DEFINED
#define RESOURCES_DEFINED
#include "Model.h"
#include "Game/CommonResources.h"

// Resourcesクラスを定義する
class Resources
{
public:
	// 「プレイヤ」モデルを取得する
	DirectX::Model* GetPlayerModel() { return m_playerModel.get(); }
	// 「敵」モデルを取得する
	DirectX::Model* GetEnemyModel() { return m_enemyModel.get(); }
	// 「ブーメラン」モデルを取得する
	DirectX::Model* GetBoomerangModel() { return m_boomerangModel.get(); }
	// 「床」モデルを取得する
	DirectX::Model* GetFloorModel() { return m_floorModel.get(); }
	// 「岩」モデルを取得する
	DirectX::Model* GetRockModel() { return m_rockModel.get(); }
	// 「空」モデルを取得する
	DirectX::Model* GetSkyModel() { return m_skyModel.get(); }
	// 「木１」モデルを取得する
	DirectX::Model* GetTree1Model() { return m_tree1Model.get(); }



public:
	Resources(Resources&&) = default;
	Resources& operator= (Resources&&) = default;
	Resources& operator= (Resources const&) = delete;
	// デストラクタ
	~Resources() = default;
	// Resoucesクラスのインスタンスを取得する
	static Resources* const GetInstance();
	// リソースをロードする
	void LoadResource(CommonResources* resources);

private:
	// コンストラクタ
	Resources() noexcept
		:
		m_playerModel{},
		m_enemyModel{},
		m_boomerangModel{},
		m_floorModel{},
		m_rockModel{},
		m_skyModel{},
		m_tree1Model{}
	{
	}

private:
	// リソース
	static std::unique_ptr<Resources> m_resources;

	// 「プレイヤ」モデル
	std::unique_ptr<DirectX::Model> m_playerModel;
	// 「敵」モデル
	std::unique_ptr<DirectX::Model> m_enemyModel;
	// 「ブーメラン」モデル
	std::unique_ptr<DirectX::Model> m_boomerangModel;
	// 「床」モデル
	std::unique_ptr<DirectX::Model> m_floorModel;
	// 「岩」モデル
	std::unique_ptr<DirectX::Model> m_rockModel;
	// 「空」モデル
	std::unique_ptr<DirectX::Model> m_skyModel;
	// 「木１」モデル
	std::unique_ptr<DirectX::Model> m_tree1Model;


};

#endif		// RESOURCES_DEFINED
