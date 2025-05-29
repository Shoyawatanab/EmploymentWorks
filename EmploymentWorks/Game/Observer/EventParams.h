#pragma once
//�Q�[���̎��
enum class GamePlayMessageType
{
	None = -1
	, BOOMERANG_GET_READY    //�u�[���������\����
	, BOOMERANG_GET_READY_END  //�u�[�������̍\�����I���
	, BOOMERANG_THTROW      //�u�[�������𓊂���
	, GET_BOOMERANG        //�u�[�������̎擾
	, GAME_CLEAR
	, GAME_OVER
	, DEFEATED_All_ENEMIES  // �S�Ă̓G��|������
	, PLAYER_DAMAGE
	, BOSS_BEAM_ATTACK_END
	, CREATE_EXPLOSION
	, CREATE_PARTICLE  
	, CREATE_HIT_EFFECT
	, CREATE_CHAGE_EFFECT
	, BOSS_BEAM_HIT  
	,CHARGE_BOOMERANG_THROW_STATE
	,MOUSE_WHEEL_UP
	,MOUSE_WHEEL_DOWN
	,BOOMERANG_RECOVERBLE  //�u�[������������\
	, BOOMERANG_NOT_RECOVERBLE  //�u�[������������s��
	,CAMERA_SHAKE  //�J������h�炷
	,NEXT_SCENE  //���̃V�[����
	,CHANGE_THROW_COUNT                      //�u�[���������܂Ƃ߂ĂȂ��邩�ǂ����̐؂�ւ�


};

//�G�̃C�x���g�̎��
enum class EnemyMessageType
{
	NONE
	, IDLING            //�ʏ���
	, WALKING           //����
	, JUMP_ATTACK	    //�W�����v�U��
	, BARRIER_DEFENSE   //�o���A�h��
	, BEAM_ATTACK	    //�r�[���U��
	, SWING_DOWN	    //�U�艺�낵�U��
	, MOVEING           //����
};

//�p�[�c�̒ʒm�̎�ށ@�G�@�v���C���ȂǍ����@��������
enum class PartMessageType
{
	PART_DESTRUCTION     //�p�[�c�j��
};

struct CreateHitEffectDatas
{
	DirectX::SimpleMath::Vector3 Position;
	DirectX::SimpleMath::Vector3 Scale;
	int Damage;
};

struct CreateChargeEffectDatas
{
	DirectX::SimpleMath::Vector3 Position;
	DirectX::SimpleMath::Vector3 Scale;

};


struct  UnknownDataTwo
{
	void* data1;
	void* data2;
};

struct  UnknownDataThree
{
	void* data1;
	void* data2;
	void* data3;
};




/*
	CreateHitEffectDatas
		data1�����W
	�@�@data2���傫��
		data3���_���[�W


*/




