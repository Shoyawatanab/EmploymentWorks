#pragma once

class Params
{
public:


	static const float MOUSE_RADIUS;
	 
	//�d��
	static const float GRAVITY;
	//�e��Y���W
	static const float SHADOW_POSITION_Y;
	//�n�㖀�C��
	static const float GRAUND_FRICTION;

//�v���C��
   	//�v���C���̑傫��
	static const DirectX::SimpleMath::Vector3 PLAYER_SCALE;
	//�v���C���̍��W
	static const DirectX::SimpleMath::Vector3 PLAYER_POSITION;
	//�v���C���̉�]
	static const DirectX::SimpleMath::Quaternion PLAYER_ROTATION;
	//�v���C���̃{�b�N�X�̓����蔻��̑傫��
	static const DirectX::SimpleMath::Vector3 PLAYER_BOX_COLLIDER_SIZE;
	//�v���C���̃X�t�B�A�̓����蔻��̑傫��
	static const float PLAYER_SPHERE_COLLIDER_SIZE;
	//�v���C����HP
	static const int PLAYER_HP;
	//�v���C���̓����X�s�[�h
	static const float PLAYER_MOVE_SPEED;
	//�v���C���̉�]�X�s�[�h
	static const float PLAYER_ROTATION_SPEED;

	//�v���C���̉e�̑傫��
	static const float PLAYER_SHADOW_RADIUS;

	//�v���C����BODY�̑傫��
	static const DirectX::SimpleMath::Vector3 PLAYER_BODY_SCALE;
	//�v���C����BODY�̍��W
	static const DirectX::SimpleMath::Vector3 PLAYER_BODY_POSITION;
	//�v���C����BODY�̍��W
	static const DirectX::SimpleMath::Quaternion PLAYER_BODY_ROTATION;

	//�v���C����HEAD�̑傫��
	static const DirectX::SimpleMath::Vector3 PLAYER_HEAD_SCALE;
	//�v���C����HEAD�̍��W
	static const DirectX::SimpleMath::Vector3 PLAYER_HEAD_POSITION;
	//�v���C����HEAD�̍��W
	static const DirectX::SimpleMath::Quaternion PLAYER_HEAD_ROTATION;

	//�v���C����LEFRARM�̑傫��
	static const DirectX::SimpleMath::Vector3 PLAYER_LEFRARM_SCALE;
	//�v���C����LEFRARM�̍��W
	static const DirectX::SimpleMath::Vector3 PLAYER_LEFRARM_POSITION;
	//�v���C����LEFRARM�̍��W
	static const DirectX::SimpleMath::Quaternion PLAYER_LEFRARM_ROTATION;

	//�v���C����LEFRFEET�̑傫��
	static const DirectX::SimpleMath::Vector3 PLAYER_LEFRFEET_SCALE;
	//�v���C����LEFRFEET�̍��W
	static const DirectX::SimpleMath::Vector3 PLAYER_LEFRFEET_POSITION;
	//�v���C����LEFRFEET�̍��W
	static const DirectX::SimpleMath::Quaternion PLAYER_LEFRFEET_ROTATION;


	//�v���C����RIGHTARM�̑傫��
	static const DirectX::SimpleMath::Vector3 PLAYER_RIGHTARM_SCALE;
	//�v���C����RIGHTARM�̍��W
	static const DirectX::SimpleMath::Vector3 PLAYER_RIGHTARM_POSITION;
	//�v���C����RIGHTARM�̍��W
	static const DirectX::SimpleMath::Quaternion PLAYER_RIGHTARM_ROTATION;

	//�v���C����RIGHTFEET�̑傫��
	static const DirectX::SimpleMath::Vector3 PLAYER_RIGHTFEET_SCALE;
	//�v���C����RIGHTFEET�̍��W
	static const DirectX::SimpleMath::Vector3 PLAYER_RIGHTFEET_POSITION;
	//�v���C����RIGHTFEET�̍��W
	static const DirectX::SimpleMath::Quaternion PLAYER_RIGHTFEET_ROTATION;




//�u�[������
	//�u�[�������̑傫��
	static const DirectX::SimpleMath::Vector3 BOOMERANG_SCALE;
	//�u�[�������̍��W
	static const DirectX::SimpleMath::Vector3 BOOMERANG_POSITION;
	//�u�[�������̉�]
	static const DirectX::SimpleMath::Quaternion BOOMERANG_ROTATION;
	//�u�[�������̐�
	static int BOOMERANG_MAX_COUNT;
	//�u�[�������̈ړ��X�s�[�h
	static const float BOOMERANG_MOVE_SPEED;
	//�u�[�������̉���]�X�s�[�h
	static const float BOOMERANG_HORIZONTAL_ROTATION_SPEED;
	//�u�[�������̓����Ă鎞�̏��߂̉�]
	static const DirectX::SimpleMath::Quaternion BOOMERANG_THROW_START_ROTATION;
	//�u�[�������̓����Ă鎞�̒��Ԃ̉�]
	static const DirectX::SimpleMath::Quaternion BOOMERANG_THROW_MIDDLE_ROTATION;
	//�u�[�������̓����Ă鎞�̏I���̉�]
	static const DirectX::SimpleMath::Quaternion BOOMERANG_THROW_END_ROTATION;

	//�u�[�������̃{�b�N�X�̓����蔻��̑傫��
	static const DirectX::SimpleMath::Vector3 BOOMERANG_BOX_COLLIDER_SIZE;
	//�u�[�������̃X�t�B�A�̓����蔻��̑傫��
	static const float BOOMERANG_SPHERE_COLLIDER_SIZE;
	//�@�u�[�������̍U����
	static const int BOOMERANG_DAMAGE;


	//�u�[�������̉e�̑傫��
	static const float BOOMERANG_SHADOW_RADIUS;


	//�u�[��������IDLE��Ԃ̍��W
	static const DirectX::SimpleMath::Vector3 BOOMERANG_IDLE_POSITION;
	//�u�[��������IDLE��Ԃ̉�]
	static const DirectX::SimpleMath::Quaternion BOOMERANG_IDLE_ROTATION;
	//�u�[��������IDLE��Ԃ̑傫��
	static const DirectX::SimpleMath::Vector3 BOOMERANG_IDLE_SCALE;

	//�u�[��������GETREADY��Ԃ̍��W
	static const DirectX::SimpleMath::Vector3 BOOMERANG_GETREADY_POSITION;
	//�u�[��������GETREADY��Ԃ̉�]
	static const DirectX::SimpleMath::Quaternion BOOMERANG_GETREADY_ROTATION;


	//�u�[��������THROW��Ԃ̍��W
	static const DirectX::SimpleMath::Vector3 BOOMERANG_THROW_POSITION;
	//�u�[��������THROW��Ԃ̉�]
	static const DirectX::SimpleMath::Quaternion BOOMERANG_THROW_ROTATION;
	//�u�[�������̊�_�̉�]
	static const DirectX::SimpleMath::Quaternion BOOMERANG_THROW_POINT_ROTATE;


	//�G�̉�]�̋��e�͈�
	static const float ENEMY_PERMISSIBLE_ANGLE;

//�{�X�G
	//�{�X�G��HP
	static const int BOSSENEMY_MAX_HP;
	//�{�X�G�̓����X�s�[�h
	static const float BOSSENEMY_MOVE_SPEED;
	//�{�X�G�̉�]�X�s�[�h
	static const float BOSSENEMY_ROTATION_SPEED;


	//�{�X�̉e�̑傫��
	static const float BOSSENEMY_SHADOW_RADIUS;


	//�{�X�G�̃{�b�N�X�̓����蔻��̑傫��
	static const DirectX::SimpleMath::Vector3 BOSSENEMY_BOX_COLLIDER_SIZE;
	//�{�X�G�̃X�t�B�A�̓����蔻��̑傫��
	static const float BOSSENEMY_SPHERE_COLLIDER_SIZE;

	//�{�X�G�̃r�[���̔��ˈʒu
	static const DirectX::SimpleMath::Vector3 BOSSENEMY_BEAM_SHOT_POSITION;

	//�{�X�r�[���̑傫��
	static const DirectX::SimpleMath::Vector3 BOSSENEMY_BEAM_SCALE;
	//�{�X�r�[���̍��W
	static const DirectX::SimpleMath::Vector3 BOSSENEMY_BEAM_POSITION;
	//�{�X�r�[���̉�]
	static const DirectX::SimpleMath::Quaternion BOSSENEMY_BEAM_ROTATION;
	//�{�X�r�[���̃G�l���M�[�e�̃{�b�N�X�̓����蔻��̑傫��
	static const DirectX::SimpleMath::Vector3 BOSSENEMY_BEAM_BALL_BOX_COLLIDER_SIZE;
	//�{�X�r�[���̃G�l���M�[�e�̃X�t�B�A�̓����蔻��̑傫��
	static const float BOSSENEMY_BEAM_BALL_SPHERE_COLLIDER_SIZE;


	//�{�X�r�[���̏k������
	static const float BOSSENEMY_BEAM_SHRINK_TIME;
	//�{�X�r�[���̃G�l���M�[�e�̍ő�̑傫��
	static const DirectX::SimpleMath::Vector3 BOSSENEMY_BEAM_BALL_MAX_SCALE;
	//�{�X�r�[���̃G�l���M�[�e�̗\������̎���
	static const float BOSSENEMY_BEAM_BALL_PRELIMINARY_ACTION_TIME;
	//�{�X�r�[���̃G�l���M�[�e�̗��߂̎���
	static const float BOSSENEMY_BEAM_BALL_ACCUMULATIONTIME;
	//�{�X�r�[���̃G�l���M�[�e�̓����X�s�[�h
	static const float BOSSENEMY_BEAM_BALL_MOVE_SPPED;
	//�{�X�r�[���̌����̍ő�̑傫��
	static const DirectX::SimpleMath::Vector3 BOSSENEMY_BEAM_RAYS_MAX_SCALE;
	//�{�X�r�[���̃`���[�W�G�t�F�N�g�̐����Ԋu
	static const float BOSSENEMY_BEAM_CHARGE_EFFECT_CREATE_TIME;
	//�{�X�r�[���̃`���[�W�G�t�F�N�g�̓����X�s�[�h
	static const float BOSSENEMY_BEAM_CHARGE_EFFECT_MOVE_TIME;


	//�{�X�G��BODY�̑傫��
	static const  DirectX::SimpleMath::Vector3 BOSSENEMY_BODY_SCALE;
	//�{�X�G��BODY�̍��W
	static const  DirectX::SimpleMath::Vector3 BOSSENEMY_BODY_POSITION;
	//�{�X�G��BODY�̉�]
	static const  DirectX::SimpleMath::Quaternion BOSSENEMY_BODY_ROTATION;
	//�{�X�G��BODY�̃{�b�N�X�̓����蔻��̑傫��
	static const  DirectX::SimpleMath::Vector3 BOSSENEMY_BODY_BOX_COLLIDER_SIZE;
	//�{�X�G��BODY�̃X�t�B�A�̓����蔻��̑傫��
	static const  float BOSSENEMY_BODY_SPHERE_COLLIDER_SIZE;
	//�{�X�G��BODY��HP
	static const  int BOSSENEMY_BODY_HP;

	//�{�X�G��HEAD�̑傫��
	static const  DirectX::SimpleMath::Vector3 BOSSENEMY_HEAD_SCALE;
	//�{�X�G��HEAD�̍��W								  
	static const  DirectX::SimpleMath::Vector3 BOSSENEMY_HEAD_POSITION;
	//�{�X�G��HEAD�̉�]								  
	static const  DirectX::SimpleMath::Quaternion BOSSENEMY_HEAD_ROTATION;
	//�{�X�G��HEAD�̃{�b�N�X�̓����蔻��̑傫��		  
	static const  DirectX::SimpleMath::Vector3 BOSSENEMY_HEAD_BOX_COLLIDER_SIZE;
	//�{�X�G��HEAD�̃X�t�B�A�̓����蔻��̑傫��		  
	static const  float BOSSENEMY_HEAD_SPHERE_COLLIDER_SIZE;
	//�{�X�G��HEAD��HP									
	static const  int BOSSENEMY_HEAD_HP;


	//�{�X�G��LEFTARM�̑傫��
	static const  DirectX::SimpleMath::Vector3 BOSSENEMY_LEFTARM_SCALE;
	//�{�X�G��LEFTARM�̍��W								 
	static const  DirectX::SimpleMath::Vector3 BOSSENEMY_LEFTARM_POSITION;
	//�{�X�G��LEFTARM�̉�]								 
	static const  DirectX::SimpleMath::Quaternion BOSSENEMY_LEFTARM_ROTATION;
	//�{�X�G��LEFTARM�̃{�b�N�X�̓����蔻��̑傫��		 
	static const  DirectX::SimpleMath::Vector3 BOSSENEMY_LEFTARM_BOX_COLLIDER_SIZE;
	//�{�X�G��LEFTARM�̃X�t�B�A�̓����蔻��̑傫��		 
	static const  float BOSSENEMY_LEFTARM_SPHERE_COLLIDER_SIZE;
	//�{�X�G��LEFTARM��HP								 
	static const int BOSSENEMY_LEFTARM_HP;

	//�{�X�G��LEFTARMJOINT�̑傫��
	static const  DirectX::SimpleMath::Vector3 BOSSENEMY_LEFTARMJOINT_SCALE;
	//�{�X�G��LEFTARMJOINT�̍��W						 
	static const  DirectX::SimpleMath::Vector3 BOSSENEMY_LEFTARMJOINT_POSITION;
	//�{�X�G��LEFTARMJOINT�̉�]						 
	static const  DirectX::SimpleMath::Quaternion BOSSENEMY_LEFTARMJOINT_ROTATION;
	//�{�X�G��LEFTARMJOINT�̃{�b�N�X�̓����蔻��̑傫�� 
	static const  DirectX::SimpleMath::Vector3 BOSSENEMY_LEFTARMJOINT_BOX_COLLIDER_SIZE;
	//�{�X�G��LEFTARMJOINT�̃X�t�B�A�̓����蔻��̑傫�� 
	static const  float BOSSENEMY_LEFTARMJOINT_SPHERE_COLLIDER_SIZE;
	//�{�X�G��LEFTARMJOINT��HP							 
	static const  int BOSSENEMY_LEFTARMJOINT_HP;

	//�{�X�G��LEFTLEG�̑傫��
	static const  DirectX::SimpleMath::Vector3 BOSSENEMY_LEFTLEG_SCALE;
	//�{�X�G��LEFTLEG�̍��W						 		
	static const  DirectX::SimpleMath::Vector3 BOSSENEMY_LEFTLEG_POSITION;
	//�{�X�G��LEFTLEG�̉�]						 		 
	static const  DirectX::SimpleMath::Quaternion BOSSENEMY_LEFTLEG_ROTATION;
	//�{�X�G��LEFTLEG�̃{�b�N�X�̓����蔻��̑傫�� 	 
	static const  DirectX::SimpleMath::Vector3 BOSSENEMY_LEFTLEG_BOX_COLLIDER_SIZE;
	//�{�X�G��LEFTLEG�̃X�t�B�A�̓����蔻��̑傫�� 	 
	static const float BOSSENEMY_LEFTLEG_SPHERE_COLLIDER_SIZE;
	//�{�X�G��LEFTLEG��HP							 	 
	static const  int BOSSENEMY_LEFTLEG_HP;

	//�{�X�G��LEFTSHOULDER�̑傫��
	static const  DirectX::SimpleMath::Vector3 BOSSENEMY_LEFTSHOULDER_SCALE;
	//�{�X�G��LEFTSHOULDER�̍��W						
	static const  DirectX::SimpleMath::Vector3 BOSSENEMY_LEFTSHOULDER_POSITION;
	//�{�X�G��LEFTSHOULDER�̉�]						 
	static const  DirectX::SimpleMath::Quaternion BOSSENEMY_LEFTSHOULDER_ROTATION;
	//�{�X�G��LEFTSHOULDER�̃{�b�N�X�̓����蔻��̑傫�� 
	static const  DirectX::SimpleMath::Vector3 BOSSENEMY_LEFTSHOULDER_BOX_COLLIDER_SIZE;
	//�{�X�G��LEFTSHOULDER�̃X�t�B�A�̓����蔻��̑傫�� 
	static const  float BOSSENEMY_LEFTSHOULDER_SPHERE_COLLIDER_SIZE;
	//�{�X�G��LEFTSHOULDER��HP							 
	static const  int BOSSENEMY_LEFTSHOULDER_HP;


	//�{�X�G��LEFTTHIGH�̑傫��
	static const  DirectX::SimpleMath::Vector3 BOSSENEMY_LEFTTHIGH_SCALE;
	//�{�X�G��LEFTTHIGH�̍��W							 
	static const  DirectX::SimpleMath::Vector3 BOSSENEMY_LEFTTHIGH_POSITION;
	//�{�X�G��LEFTTHIGH�̉�]						 	 
	static const  DirectX::SimpleMath::Quaternion BOSSENEMY_LEFTTHIGH_ROTATION;
	//�{�X�G��LEFTTHIGH�̃{�b�N�X�̓����蔻��̑傫�� 	 
	static const  DirectX::SimpleMath::Vector3 BOSSENEMY_LEFTTHIGH_BOX_COLLIDER_SIZE;
	//�{�X�G��LEFTTHIGH�̃X�t�B�A�̓����蔻��̑傫�� 	 
	static const  float BOSSENEMY_LEFTTHIGH_SPHERE_COLLIDER_SIZE;
	//�{�X�G��LEFTTHIGH��HP							 	 
	static const int BOSSENEMY_LEFTTHIGH_HP;


	//�{�X�G��PELVIS�̑傫��
	static const  DirectX::SimpleMath::Vector3 BOSSENEMY_PELVIS_SCALE;
	//�{�X�G��PELVIS�̍��W							 	 
	static const  DirectX::SimpleMath::Vector3 BOSSENEMY_PELVIS_POSITION;
	//�{�X�G��PELVIS�̉�]						 	 	 
	static const  DirectX::SimpleMath::Quaternion BOSSENEMY_PELVIS_ROTATION;
	//�{�X�G��PELVIS�̃{�b�N�X�̓����蔻��̑傫�� 	 	 
	static const  DirectX::SimpleMath::Vector3 BOSSENEMY_PELVIS_BOX_COLLIDER_SIZE;
	//�{�X�G��PELVIS�̃X�t�B�A�̓����蔻��̑傫�� 	 	 
	static const  float BOSSENEMY_PELVIS_SPHERE_COLLIDER_SIZE;
	//�{�X�G��PELVIS��HP							 	 
	static const  int BOSSENEMY_PELVIS_HP;


	//�{�X�G��RIGHTARM�̑傫��
	static const  DirectX::SimpleMath::Vector3 BOSSENEMY_RIGHTARM_SCALE;
	//�{�X�G��RIGHTARM�̍��W							 
	static const  DirectX::SimpleMath::Vector3 BOSSENEMY_RIGHTARM_POSITION;
	//�{�X�G��RIGHTARM�̉�]						 	 
	static const  DirectX::SimpleMath::Quaternion BOSSENEMY_RIGHTARM_ROTATION;
	//�{�X�G��RIGHTARM�̃{�b�N�X�̓����蔻��̑傫�� 	 
	static const  DirectX::SimpleMath::Vector3 BOSSENEMY_RIGHTARM_BOX_COLLIDER_SIZE;
	//�{�X�G��RIGHTARM�̃X�t�B�A�̓����蔻��̑傫�� 	 
	static const  float BOSSENEMY_RIGHTARM_SPHERE_COLLIDER_SIZE;
	//�{�X�G��RIGHTARM��HP							 	 
	static const  int BOSSENEMY_RIGHTARM_HP;

	//�{�X�G��RIGHTARMJOINT�̑傫��
	static const  DirectX::SimpleMath::Vector3 BOSSENEMY_RIGHTARMJOINT_SCALE;
	//�{�X�G��RIGHTARMJOINT�̍��W						 
	static const  DirectX::SimpleMath::Vector3 BOSSENEMY_RIGHTARMJOINT_POSITION;
	//�{�X�G��RIGHTARMJOINT�̉�]						 
	static const  DirectX::SimpleMath::Quaternion BOSSENEMY_RIGHTARMJOINT_ROTATION;
	//�{�X�G��RIGHTARMJOINT�̃{�b�N�X�̓����蔻��̑傫��
	static const  DirectX::SimpleMath::Vector3 BOSSENEMY_RIGHTARMJOINT_BOX_COLLIDER_SIZE;
	//�{�X�G��RIGHTARMJOINT�̃X�t�B�A�̓����蔻��̑傫��
	static const  float BOSSENEMY_RIGHTARMJOINT_SPHERE_COLLIDER_SIZE;
	//�{�X�G��RIGHTARMJOINT��HP							 
	static const  int BOSSENEMY_RIGHTARMJOINT_HP;


	//�{�X�G��RIGHTLEG�̑傫��
	static const  DirectX::SimpleMath::Vector3 BOSSENEMY_RIGHTLEG_SCALE;
	//�{�X�G��RIGHTLEG�̍��W						 	 
	static const  DirectX::SimpleMath::Vector3 BOSSENEMY_RIGHTLEG_POSITION;
	//�{�X�G��RIGHTLEG�̉�]						 	 
	static const  DirectX::SimpleMath::Quaternion BOSSENEMY_RIGHTLEG_ROTATION;
	//�{�X�G��RIGHTLEG�̃{�b�N�X�̓����蔻��̑傫��	 
	static const  DirectX::SimpleMath::Vector3 BOSSENEMY_RIGHTLEG_BOX_COLLIDER_SIZE;
	//�{�X�G��RIGHTLEG�̃X�t�B�A�̓����蔻��̑傫��	 
	static const float BOSSENEMY_RIGHTLEG_SPHERE_COLLIDER_SIZE;
	//�{�X�G��RIGHTLEG��HP							 	 
	static const  int BOSSENEMY_RIGHTLEG_HP;

	//�{�X�G��RIGHTSHOULDER�̑傫��
	static const  DirectX::SimpleMath::Vector3 BOSSENEMY_RIGHTSHOULDER_SCALE;
	//�{�X�G��RIGHTSHOULDER�̍��W						 
	static const  DirectX::SimpleMath::Vector3 BOSSENEMY_RIGHTSHOULDER_POSITION;
	//�{�X�G��RIGHTSHOULDER�̉�]						 
	static const  DirectX::SimpleMath::Quaternion BOSSENEMY_RIGHTSHOULDER_ROTATION;
	//�{�X�G��RIGHTSHOULDER�̃{�b�N�X�̓����蔻��̑傫��
	static const  DirectX::SimpleMath::Vector3 BOSSENEMY_RIGHTSHOULDER_BOX_COLLIDER_SIZE;
	//�{�X�G��RIGHTSHOULDER�̃X�t�B�A�̓����蔻��̑傫��
	static const  float BOSSENEMY_RIGHTSHOULDER_SPHERE_COLLIDER_SIZE;
	//�{�X�G��RIGHTSHOULDER��HP							 
	static const  int BOSSENEMY_RIGHTSHOULDER_HP;


	//�{�X�G��RIGHTTHIGH�̑傫��
	static const  DirectX::SimpleMath::Vector3 BOSSENEMY_RIGHTTHIGH_SCALE;
	//�{�X�G��RIGHTTHIGH�̍��W						 	 
	static const  DirectX::SimpleMath::Vector3 BOSSENEMY_RIGHTTHIGH_POSITION;
	//�{�X�G��RIGHTTHIGH�̉�]						 	 
	static const  DirectX::SimpleMath::Quaternion BOSSENEMY_RIGHTTHIGH_ROTATION;
	//�{�X�G��RIGHTTHIGH�̃{�b�N�X�̓����蔻��̑傫��	 
	static const  DirectX::SimpleMath::Vector3 BOSSENEMY_RIGHTTHIGH_BOX_COLLIDER_SIZE;
	//�{�X�G��RIGHTTHIGH�̃X�t�B�A�̓����蔻��̑傫��	 
	static const  float BOSSENEMY_RIGHTTHIGH_SPHERE_COLLIDER_SIZE;
	//�{�X�G��RIGHTTHIGH��HP							 
	static const  int BOSSENEMY_RIGHTTHIGH_HP;


	//�{�X�G��TORSO�̑傫��
	static const  DirectX::SimpleMath::Vector3 BOSSENEMY_TORSO_SCALE;
	//�{�X�G��TORSO�̍��W						 	 	 
	static const  DirectX::SimpleMath::Vector3 BOSSENEMY_TORSO_POSITION;
	//�{�X�G��TORSO�̉�]						 	 	 
	static const  DirectX::SimpleMath::Quaternion BOSSENEMY_TORSO_ROTATION;
	//�{�X�G��TORSO�̃{�b�N�X�̓����蔻��̑傫��	 	 
	static const  DirectX::SimpleMath::Vector3 BOSSENEMY_TORSO_BOX_COLLIDER_SIZE;
	//�{�X�G��TORSO�̃X�t�B�A�̓����蔻��̑傫��	 	 
	static const  float BOSSENEMY_TORSO_SPHERE_COLLIDER_SIZE;
	//�{�X�G��TORSO��HP							 		 
	static const  int BOSSENEMY_TORSO_HP;


//���̓G
	//���̓G��HP
	static const int BIRDENEMY_HP;
	//���̓G�̃{�b�N�X�̓����蔻��̑傫��
	static const DirectX::SimpleMath::Vector3 BIRDENEMY_BOX_COLLIDER_SIZE;
	//���̓G�̃X�t�B�A�̓����蔻��̑傫��
	static const float BIRDENEMY_SPHERE_COLLIDER_SIZE;
	//���̓G�̉e�̑傫��
	static const float BIRDENEMY_SHADOW_RADIUS;

	//���̓G�̃r�[���̔��ˍ��W
	static const DirectX::SimpleMath::Vector3 BIRDENEMY_BEAM_SHOT_POSITION;
	//���̓G�̓����̂ɂ����鎞��
	static const float BIRDENEMY_MOVE_TIME;
	//���̓G�̍s���̍ŏ��Ԋu
	static const float BIRDENEMY_ACTIONS_MIN_TIME;
	//���̓G�̍s���̍ő�Ԋu
	static const float BIRDENEMY_ACTIONS_MAX_TIME;
	//���̓G�̍s�����a
	static const float BIRDENEMY_MOVE_RADIUS;
	//���̓G�̍U���̊m��
	static const float BIRDENEMY_ATTACK_RATIO;
	
	//���̓G��BODY�̑傫��
	static const DirectX::SimpleMath::Vector3 BIRDENEMY_BODY_SCALE;
	//���̓G��BODY�̍��W
	static const DirectX::SimpleMath::Vector3 BIRDENEMY_BODY_POSITION;
	//���̓G��BODY�̉�]
	static const DirectX::SimpleMath::Quaternion BIRDENEMY_BODY_ROTATION;

	//���̓G��LEFTFEATHER�̑傫��
	static const DirectX::SimpleMath::Vector3 BIRDENEMY_LEFTFEATHER_SCALE;
	//���̓G��LEFTFEATHER�̍��W						
	static const DirectX::SimpleMath::Vector3 BIRDENEMY_LEFTFEATHER_POSITION;
	//���̓G��LEFTFEATHER�̉�]						
	static const DirectX::SimpleMath::Quaternion BIRDENEMY_LEFTFEATHER_ROTATION;


	//���̓G��RIGHTFEATHER�̑傫��
	static const DirectX::SimpleMath::Vector3 BIRDENEMY_RIGHTFEATHER_SCALE;
	//���̓G��RIGHTFEATHER�̍��W						
	static const DirectX::SimpleMath::Vector3 BIRDENEMY_RIGHTFEATHER_POSITION;
	//���̓G��RIGHTFEATHER�̉�]						
	static const DirectX::SimpleMath::Quaternion BIRDENEMY_RIGHTFEATHER_ROTATION;


	//���̓G�̃G�l���M�[�e�̍ő�̑傫��
	static const DirectX::SimpleMath::Vector3 BIRDENEMY_BEAM_BALL_MAX_SIZE;
	//���̓G�̃G�l���M�[�e�̗��ߎ���
	static const float BIRDENEMY_BEAM_BALL_ACCUMULATIONTIME;

	//���̓G�̃G�l���M�[�e�̏����x
	static const float BIRDENEMY_BEAM_BALL_INITIAL_SPEED;
	//���̓G�̃G�l���M�[�e�̍ŏI���x
	static const float BIRDENEMY_BEAM_BALL_FAINAL_SPEED;
	//���̓G�̃G�l���M�[�e�̌�����
	static const float BIRDENEMY_BEAM_BALL_DECELERATION_TIME;

};

