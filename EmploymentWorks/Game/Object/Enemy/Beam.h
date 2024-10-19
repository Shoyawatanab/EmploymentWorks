#pragma once
/*
	@file	Beam.h.h
	@brief	�r�[���N���X
*/
#include "pch.h"
#include "Libraries/MyLib/Bounding.h"


// �O���錾
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
		float Life;  //�r�[���̎���

	};

private:
	// ���ʃ��\�[�X
	CommonResources* m_commonResources;



	DirectX::SimpleMath::Vector3 m_position;
	DirectX::SimpleMath::Quaternion m_initialRotate;
	DirectX::SimpleMath::Quaternion m_rotate;

	std::vector<std::unique_ptr<Bounding>> m_bounding;

	Player* m_player;
	Enemy* m_enemy;

	//bounding�̐����Ԋu
	float m_generationInterval;
	//�\������̎���
	float m_preliminaryActionTime;

	DirectX::SimpleMath::Vector3 m_startPos;
	DirectX::SimpleMath::Vector3 m_endPos;

	//bounding�̐���������W�̊i�[�ϐ�
	std::vector<BoundingParameter> m_boundingParameter;

	//��������Boundint�̍��W�̈ꎞ�ۊ�
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
