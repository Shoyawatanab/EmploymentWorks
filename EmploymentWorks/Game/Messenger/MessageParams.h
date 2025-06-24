#pragma once
#include <variant>


//��ԁE�E��ԑJ�ڂȂǂɎg�p
//�����E�E�ǂ�Ȃ��Ƃ����������@�N��������

//�Q�[���̎��
enum class MessageType : int
{
	NONE = -1
	//�V�[���؂�ւ�
	,CHANGE_TITLE_SCENE                           //t�^�C�g���V�[���ɐ؂�ւ�
	,CHANGE_SELECT_SCENE						  //�Z���N�g�V�[���ɐ؂�ւ�
	,CHANGE_PLAY_SCENE							  //�v���C�V�[���ɐ؂�ւ�


	//�Q�[���̊���
	,GAME_CLEAR                                    //�Q�[���N���A
	,GAME_OVER									   //�Q�[���I�[�o�[
	,ENEMY_DAMAGE                                  //�G�̃_���[�W

	//�Q�[���̏��



	//�v���C���̊���
	,PLAYER_GET_REDAY                              //�v���C���̍\���̊���
	,PLAYER_GET_REDAY_END                          //�v���C���̍\���I���̊���

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

	//�{�X�e�L�̏��
	,BOSS_IDLE_STATE                              //�{�X�G�̒ʏ���
	,BOSS_BEAM_ATTACK_STATE                       //�{�X�G�̃r�[���U�����
	,BOSS_JUMP_ATTACK_STATE                       //�{�X�G�̃W�����v�U�����
	,BOSS_WAKING_STATE	                          //�{�X�G�̕������
	,BOSS_SWING_DOWN_STATE	                      //�{�X�G�̐U�艺�낵�U�����


	//���G�̊���



	//���G�̏��
	,BIRD_IDLE_STATE                              //���G�̒ʏ���
	,BIRD_MOVE_STATE							  //���G�̓������
	,BIRD_BEAM_ATTACK_STATE						  //���G�̃r�[���U�����

	//���G�̒e�̊���



	//���G�̒e�̏��
	, BIRD_BULLET_IDLE_STATE                              //���G�̒e�̒ʏ���
	, BIRD_BULLET_CHAGE_STATE							  //���G�̒e�̃`���[�W���
	, BIRD_BULLET_SHOT_STATE						      //���G�̒e�̃V���b�g���

};





/*
	���O�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�ǉ��f�[�^ (�^���E�p�r,�^���E�p�r�@�E�E�E�E)
	BOOMERANG_IDEL_STATE �@�@�@�@�@�@�@�@�@Boomerang  �ǂ̃u�[�������̃X�e�[�g��؂�ւ���̂�

	BOSS_DAMAGE�@�@�@�@�@�@�@�@�@�@�@�@�@�@float  �c��HP�����@
	
*/













