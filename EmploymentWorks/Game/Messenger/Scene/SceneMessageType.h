#pragma once


//��ԁE�E��ԑJ�ڂȂǂɎg�p
//�����E�E�ǂ�Ȃ��Ƃ����������@�N��������

//�Q�[���̎��
enum class SceneMessageType : int
{
	NONE = -1

	//�Q�[���̊���
	,GAME_CLEAR                                    //�Q�[���N���A
	,GAME_OVER									   //�Q�[���I�[�o�[
	,ENEMY_DAMAGE                                  //�G�̃_���[�W
	,EXPLOSITION_EFFECT                            //�����G�t�F�N�g
	,CREATE_CHARGE_EFFECT                          //�`���[�W�G�t�F�N�g�̍쐬
	,CREATE_PARTICLE_EFFECT                        //�p�[�e�B�N���̍쐬
	,PLAYER_PICKUP_POSSIBLE                        //�v���C���̉���\
	,PLAYER_PICKUP_IMPOSSIBLE                      //�v���C���̉���s�\

	//�Q�[���̏��



	//�v���C���̊���
	,PLAYER_GET_REDAY                              //�v���C���̍\���̊���
	,PLAYER_GET_REDAY_END                          //�v���C���̍\���I���̊���
	,PLAYER_DAMAGE                                 //�v���C���̃_���[�W

	//�v���C���̏��
	,PLAYER_IDLE_STATE                             //�v���C���̒ʏ���
	,PLAYER_BOOMERANG_ATTACK_STATE                 //�v���C���̃u�[�������U�����
	,PLAYER_BOOMERANG_GET_READY_STATE              //�v���C���̃u�[�������̍\�����

	//�u�[�������̊���
	, BOOMERANG_GET_READY                          //�u�[���������\���銈��
	, BOOMERANG_THROW                              //�u�[�������𓊂��銈��
	, BOOMERANG_THROW_STOP                         //�u�[�������𓊂���̂���߂銈��
	, BOOMERANG_CATCH                             //�u�[���������L���b�`���銈��


	//�u�[�������̏��
	,BOOMERANG_IDEL_STATE                         //�u�[�������̒ʏ���
	,BOOMERANG_GET_READY_STATE                    //�u�[�������̍\�����
	,BOOMERANG_THROW_STATE                        //�u�[�������̓������

	//�{�X�G�̊���
	,BOSS_DAMAGE                                 //�{�X���_���[�W���󂯂�����
	,BOSS_DEFEATED                               //�{�X��|��������
	,BOSS_BEAM_IMPACT                            //�{�X�r�[���̒��e

	,BOSS_JUMP_ANIMATION_START                   //�{�X�̃W�����v�A�j���[�V�����̃X�^�[�g

	//�{�X�e�L�̏��
	,BOSS_IDLE_STATE                              //�{�X�G�̒ʏ���
	,BOSS_BEAM_ATTACK_STATE                       //�{�X�G�̃r�[���U�����
	,BOSS_JUMP_ATTACK_STATE                       //�{�X�G�̃W�����v�U�����
	,BOSS_WAKING_STATE	                          //�{�X�G�̕������
	,BOSS_SWING_DOWN_STATE	                      //�{�X�G�̐U�艺�낵�U�����



};

//�G�̃_���[�W���̍\����
struct EnemyDamageDatas
{
	float Damage;
	DirectX::SimpleMath::Vector3 Position;
};

//�����G�t�F�N�g���̒ǉ��f�[�^�p�\����
struct  ExplosionEffectDatas
{
	DirectX::SimpleMath::Vector3 Scale;      //�傫��
	DirectX::SimpleMath::Vector3 Position;	 //���W
};

//�`���[�W�G�t�F�N�g�̒ǉ��f�[�^�\����
struct CreateChargeEffectDatas
{
	DirectX::SimpleMath::Vector3 Scale;      //�傫��
	DirectX::SimpleMath::Vector3 Position;	 //���W

};

/*
	���O�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�ǉ��f�[�^ (�^���E�p�r,�^���E�p�r�@�E�E�E�E)
	BOOMERANG_IDEL_STATE �@�@�@�@�@�@�@�@�@Boomerang  �ǂ̃u�[�������̃X�e�[�g��؂�ւ���̂�

	ENEMY_DAMAGE�@�@�@�@�@�@�@�@�@�@�@�@�@ EnemyDamageDatas�@�\����

	BOSS_DAMAGE�@�@�@�@�@�@�@�@�@�@�@�@�@�@float  �c��HP�����@
	
	EXPLOSITION_EFFECT�@�@�@�@�@�@�@�@�@�@ ExplosionEffectDatas�@�\����

	CREATE�QCHARGE_EFFECT                  CrateChargeEffectDtas �\����
	�@
*/













