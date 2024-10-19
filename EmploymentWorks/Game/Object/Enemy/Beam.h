#pragma once
/*
	@file	Beam.h.h
	@brief	ビームクラス
*/
#include "pch.h"
#include "Libraries/MyLib/Bounding.h"


// 前方宣言
class CommonResources;
class Bounding;
class Player;
class Enemy;
class BeamModel;


namespace mylib
{
	class DebugCamera;
	class GridFloor;
}


class Beam 

{
public:

	std::vector<std::unique_ptr<Bounding>>& GetBounding() { return m_bounding; }


public:

	struct  BoundingParameter
	{
		//std::unique_ptr<Bounding> Bounding;

		DirectX::SimpleMath::Vector3 Position;
		float Life;  //ビームの時間

	};

private:
	// 共通リソース
	CommonResources* m_commonResources;



	DirectX::SimpleMath::Vector3 m_position;
	DirectX::SimpleMath::Quaternion m_initialRotate;
	DirectX::SimpleMath::Quaternion m_rotate;

	std::vector<std::unique_ptr<Bounding>> m_bounding;

	Player* m_player;
	Enemy* m_enemy;

	//boundingの生成間隔
	float m_generationInterval;
	//予備動作の時間
	float m_preliminaryActionTime;

	DirectX::SimpleMath::Vector3 m_startPos;
	DirectX::SimpleMath::Vector3 m_endPos;

	//boundingの生成する座標の格納変数
	std::vector<BoundingParameter> m_boundingParameter;

	//生成するBoundintの座標の一時保管
	std::vector<BoundingParameter> m_keepBoundingParameter;

	std::unique_ptr<BeamModel> m_models;
	std::vector<std::unique_ptr<BeamModel>> m_drawModels;

public:
	Beam();
	~Beam() ;

	void Initialize(CommonResources* resources,Player* player, Enemy* enemy) ;
	void Update(float elapsedTime);
	void Render(DirectX::CXMMATRIX view, DirectX::CXMMATRIX projection) ;
	void Finalize() ;

	bool Attack(float elapsdTime);

	void CreateBounding(DirectX::SimpleMath::Vector3 Pos,float radius);


};
