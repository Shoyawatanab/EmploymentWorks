/*
	�N���X��     : GlobalGameData
	����         : �V�[�����܂����Q�[���f�[�^
	�⑫�E���ӓ_ :
*/
#pragma once
#include "GameBase/WataLib/Singleton.h"

class GlobalGameData : public Singleton<GlobalGameData>
{
	friend class Singleton<GlobalGameData>;
public:

	//�I���X�e�[�W�ԍ��̃Z�b�g
	void SetSelectStateNumber(int number) { m_selectStageNumber = number; }
	//�X�e�[�W�ԍ��̎擾
	int GetSelectStageNumber() const { return m_selectStageNumber; }
	//�N���A�^�C���̎擾
	float GetClearTime() const { return m_clearTime; }
	//�N���A�^�C���̉��Z
	void SetClearTime(const float& time) { m_clearTime += time; }
	//�N���A�^�C���̃��Z�b�g
	void ResetClearTime() { m_clearTime = 0.0f; };
public:
	//�R���X�g���N
	GlobalGameData();
	//�f�X�g���N�^
	~GlobalGameData() override;


private:

	//�I�΂ꂽ�X�e�[�W�ԍ�
	int m_selectStageNumber;
	//�N���A�^�C��
	float m_clearTime;

};