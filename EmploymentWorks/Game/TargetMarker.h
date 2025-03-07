#pragma once
/*
	@file	TargetMarker.h.h
	@brief	�v���C�V�[���N���X
*/
#pragma once
#include "pch.h"
#include  "Game/Entities/EnemyEntity.h"
#include "Game/Interface/IObserver.h"
// �O���錾
class CommonResources;
namespace WataLib
{
	class TPS_Camera;
	class DrawTexture;

}



class TargetMarker : public IObserver

{
public:

	//�^�[�Q�b�g�̒��Sk��̋���
	static constexpr float RANGE{ 200.0f };

public:

	bool GetIsLockOn() { return m_isLockOn; }

	DirectX::SimpleMath::Vector3 GetTargetPosition() { return m_target; }


public:
	TargetMarker();
	~TargetMarker();

	void Initialize(CommonResources* resources);
	void Update(float elapsedTime);
	void Render();

	//�N���X�ɕK�v�ȏ��i�|�C���^�j��o�^����
	void AddPointer(WataLib::TPS_Camera* tpsCamera);




	DirectX::SimpleMath::Vector2 FilterWithinRange(const std::vector<DirectX::SimpleMath::Vector3>& points, const DirectX::SimpleMath::Vector2& center, float range);

	//void AddTargetObject(ICharacter* object) { m_targetObject.push_back(object); }

	void AddTargetObject(std::vector<std::unique_ptr<EnemyEntity>>& object)
	{ 
		for (auto& ob : object)
		{
			m_targetObject.push_back(ob.get());
		}
	}


	//IObserver
//�ʒm���ɌĂ΂��֐�
	void Notify(EventParams::EventType type, void* datas)  override;


	//���[���h���W���X�N���[�����W�ɕϊ�����
	DirectX::SimpleMath::Vector2 WorldToScreen(const DirectX::SimpleMath::Vector3& worldPos,
		const DirectX::SimpleMath::Matrix& worldMatrix,
		const DirectX::SimpleMath::Matrix& viewMatrix,
		const DirectX::SimpleMath::Matrix& projectionMatrix,
		int screenWidth, int screenHeight);


private:
	//�錾
// ���ʃ��\�[�X
	CommonResources* m_commonResources;

	std::unique_ptr<WataLib::DrawTexture> m_marker;


	WataLib::TPS_Camera* m_tpsCamera;
	//�\���Ă��邩
	bool m_isTargetMarker;
	//�͈͓��Ƀ^�[�Q�b�g�����邩�ǂ���
	bool m_isLockOn;

	std::vector<EnemyEntity*> m_targetObject;

	std::pair<int, int> m_windowSize;

	DirectX::SimpleMath::Vector3 m_target;


};
