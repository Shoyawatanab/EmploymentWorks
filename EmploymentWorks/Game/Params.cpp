#include "pch.h"
#include "Params.h"

using namespace DirectX::SimpleMath;

const float            Params::MOUSE_RADIUS = 1.0f;


//�d��
const float            Params::GRAVITY = -9.5;

const float            Params::SHADOW_POSITION_Y = 0.1f;

//�n�㖀�C��
const float            Params::GRAUND_FRICTION =  0.95f;

//�v���C���̑傫��
const Vector3          Params::PLAYER_SCALE = Vector3(0.2f, 0.2f, 0.2f);
//�v���C���̍��W
const Vector3          Params::PLAYER_POSITION = Vector3(0.0f,0.55f,5.0f);
//�v���C���̉�]
const Quaternion       Params::PLAYER_ROTATION = Quaternion::CreateFromYawPitchRoll(DirectX::XMConvertToRadians(0)
																			 ,DirectX::XMConvertToRadians(0)
																			 ,DirectX::XMConvertToRadians(0));

//�v���C���̉e�̑傫��
const float            Params::PLAYER_SHADOW_RADIUS = 0.5f;


//�v���C���̃{�b�N�X�̓����蔻��̑傫��
const Vector3          Params::PLAYER_BOX_COLLIDER_SIZE = Vector3(2.0f,3.0f,2.0f);
//�v���C���̃X�t�B�A�̓����蔻��̑傫��
const float            Params::PLAYER_SPHERE_COLLIDER_SIZE = 4.0f;
//�v���C����HP
const int              Params::PLAYER_HP = 3;
//�v���C���̓����X�s�[�h
const float            Params::PLAYER_MOVE_SPEED = 10.0f;
//�v���C���̉�]�X�s�[�h
const float            Params::PLAYER_ROTATION_SPEED = 10.0f;
//�v���C����BODY�̑傫��
const Vector3         Params::PLAYER_BODY_SCALE = Vector3::One;
//�v���C����BODY�̍��W
const Vector3         Params::PLAYER_BODY_POSITION = Vector3(0.0f,-0.28f,0.0f);
//�v���C����BODY�̍��W
const Quaternion      Params::PLAYER_BODY_ROTATION = Quaternion::CreateFromYawPitchRoll(DirectX::XMConvertToRadians(0)
																						, DirectX::XMConvertToRadians(0)
																						, DirectX::XMConvertToRadians(0));
//�v���C����HEAD�̑傫��
const Vector3         Params::PLAYER_HEAD_SCALE = Vector3::One;
//�v���C����HEAD�̍��W
const Vector3         Params::PLAYER_HEAD_POSITION = Vector3(0.0f, 2.4f, 0.0f);
//�v���C����HEAD�̍��W
const Quaternion      Params::PLAYER_HEAD_ROTATION = Quaternion::Identity;

//�v���C����LEFRARM�̑傫��
const Vector3         Params::PLAYER_LEFRARM_SCALE = Vector3::One;
//�v���C����LEFRARM�̍��W
 const Vector3        Params::PLAYER_LEFRARM_POSITION = Vector3(1.45f,0.8f,0.0f);
//�v���C����LEFRARM�̍��W
 const Quaternion     Params::PLAYER_LEFRARM_ROTATION = Quaternion::CreateFromYawPitchRoll(DirectX::XMConvertToRadians(0)
																						 , DirectX::XMConvertToRadians(0)
																						 , DirectX::XMConvertToRadians(3));
//�v���C����LEFRFEET�̑傫��
 const Vector3       Params::PLAYER_LEFRFEET_SCALE = Vector3::One;
//�v���C����LEFRFEET�̍��W
 const Vector3       Params::PLAYER_LEFRFEET_POSITION = Vector3(0.5f, -1.1f, 0.0f);
//�v���C����LEFRFEET�̍��W
 const Quaternion    Params::PLAYER_LEFRFEET_ROTATION = Quaternion::Identity;
//�v���C����RIGHTARM�̑傫��
 const Vector3      Params::PLAYER_RIGHTARM_SCALE = Vector3::One;
//�v���C����RIGHTARM�̍��W
 const Vector3      Params::PLAYER_RIGHTARM_POSITION = Vector3(-1.45f, 0.8f, 0.0f);
//�v���C����RIGHTARM�̍��W
 const Quaternion   Params::PLAYER_RIGHTARM_ROTATION = Quaternion::CreateFromYawPitchRoll(DirectX::XMConvertToRadians(180)
																						, DirectX::XMConvertToRadians(0)
																						, DirectX::XMConvertToRadians(3));
//�v���C����RIGHTFEET�̑傫��
 const Vector3      Params::PLAYER_RIGHTFEET_SCALE = Vector3::One;
//�v���C����RIGHTFEET�̍��W
 const Vector3      Params::PLAYER_RIGHTFEET_POSITION = Vector3(-0.5f, -1.1f, 0.0f);
//�v���C����RIGHTFEET�̍��W
 const Quaternion   Params::PLAYER_RIGHTFEET_ROTATION = Quaternion::Identity;



//�u�[�������̑傫��
const Vector3          Params::BOOMERANG_SCALE = Vector3(10.0f,10.0f,10.f);
//�u�[�������̍��W
const Vector3          Params::BOOMERANG_POSITION = Vector3(0.0f,0.5f,0.0f);
//�u�[�������̉�]
const Quaternion       Params::BOOMERANG_ROTATION = Quaternion::Identity;
//�u�[�������̐�
int Params::BOOMERANG_MAX_COUNT = 3;
//�u�[�������̈ړ��X�s�[�h
 const float Params::BOOMERANG_MOVE_SPEED = 8.0f;
//�u�[�������̉���]�X�s�[�h
 const float Params::BOOMERANG_HORIZONTAL_ROTATION_SPEED = 20.0f;
//�u�[�������̓����Ă鎞�̏��߂̉�]
 const  Quaternion Params::BOOMERANG_THROW_START_ROTATION = Quaternion::CreateFromYawPitchRoll(DirectX::XMConvertToRadians(0.0f)
																							 , DirectX::XMConvertToRadians(0.0f)
																							 , DirectX::XMConvertToRadians(45.0f));
 ;
//�u�[�������̓����Ă鎞�̒��Ԃ̉�]
 const  Quaternion Params::BOOMERANG_THROW_MIDDLE_ROTATION = Quaternion::CreateFromYawPitchRoll(DirectX::XMConvertToRadians(0.0f)
																							 , DirectX::XMConvertToRadians(0.0f)
																							 , DirectX::XMConvertToRadians(0.0f));
 ;
//�u�[�������̓����Ă鎞�̏I���̉�]
 const  Quaternion Params::BOOMERANG_THROW_END_ROTATION =  Quaternion::CreateFromYawPitchRoll(DirectX::XMConvertToRadians(0.0f)
																							 , DirectX::XMConvertToRadians(0.0f)
																							 , DirectX::XMConvertToRadians(-45.0f));

//�u�[�������̃{�b�N�X�̓����蔻��̑傫��
 const  Vector3 Params::BOOMERANG_BOX_COLLIDER_SIZE = Vector3(0.21f, 0.2f, 0.21f);
//�u�[�������̃X�t�B�A�̓����蔻��̑傫��
 const float Params::BOOMERANG_SPHERE_COLLIDER_SIZE = 0.4f;
//�@�u�[�������̍U����
 const int Params::BOOMERANG_DAMAGE = 10;

 //�u�[�������̉e�̑傫��
 const float Params::BOOMERANG_SHADOW_RADIUS = 0.5f ;

//�u�[��������IDLE��Ԃ̍��W
 const  Vector3 Params::BOOMERANG_IDLE_POSITION = Vector3(0.0f,0.5f,-1.1f);
//�u�[��������IDLE��Ԃ̉�]
 const  Quaternion Params::BOOMERANG_IDLE_ROTATION = Quaternion::CreateFromYawPitchRoll(DirectX::XMConvertToRadians(180.0f)
																						 , DirectX::XMConvertToRadians(90.0f)
																						 , DirectX::XMConvertToRadians(0.0f));
 //�u�[��������IDLE��Ԃ̑傫��
 const  Vector3 Params::BOOMERANG_IDLE_SCALE = Vector3(10.0f, 10.0f, 10.0f);


//�u�[��������GETREADY��Ԃ̍��W
 const  Vector3 Params::BOOMERANG_GETREADY_POSITION = Vector3(-1.5f,3.5f,0.5f);
//�u�[��������GETREADY��Ԃ̉�]
 const  Quaternion Params::BOOMERANG_GETREADY_ROTATION = Quaternion::CreateFromYawPitchRoll(DirectX::XMConvertToRadians(-90.0f)
																							 , DirectX::XMConvertToRadians(90.0f)
																							 , DirectX::XMConvertToRadians(0.0f));

//�u�[��������THROW��Ԃ̍��W
 const  Vector3 Params::BOOMERANG_THROW_POSITION;
//�u�[��������THROW��Ԃ̉�]
 const  Quaternion Params::BOOMERANG_THROW_ROTATION;
 //�u�[�������̊�_�̉�]
 const Quaternion Params::BOOMERANG_THROW_POINT_ROTATE = Quaternion::CreateFromYawPitchRoll(DirectX::XMConvertToRadians(180.0f)
																				 , DirectX::XMConvertToRadians(0.0f)
																				 , DirectX::XMConvertToRadians(0.0f));


 //�G�̉�]�̋��e�͈�
 const float Params::ENEMY_PERMISSIBLE_ANGLE = 5.0f;


 //�{�X�G
	 //�{�X�G��HP
 const int Params::BOSSENEMY_MAX_HP = 500;
 //�{�X�G�̓����X�s�[�h
 const float Params::BOSSENEMY_MOVE_SPEED = 2.0f;
 //�{�X�G�̉�]�X�s�[�h
 const float Params::BOSSENEMY_ROTATION_SPEED = 1.0f;

 //�{�X�̉e�̑傫��
 const float Params::BOSSENEMY_SHADOW_RADIUS = 3.5f;

 //�p�[�c���Ƃ�HP
  //�{�X�G��BODY��HP
 const  int Params::BOSSENEMY_BODY_HP			= 100;
 //�{�X�G��HEAD��HP						  			
 const  int Params::BOSSENEMY_HEAD_HP			= 100;
 //�{�X�G��LEFTARM��HP						  		 
 const  int Params::BOSSENEMY_LEFTARM_HP		= 100;
 //�{�X�G��LEFTARMJOINT��HP							 
 const  int Params::BOSSENEMY_LEFTARMJOINT_HP	= 100;
 //�{�X�G��LEFTLEG��HP							 	 
 const  int Params::BOSSENEMY_LEFTLEG_HP		= 100;
 //�{�X�G��LEFTSHOULDER��HP							 
 const  int Params::BOSSENEMY_LEFTSHOULDER_HP	= 100;
 //�{�X�G��LEFTTHIGH��HP							 	 
 const  int Params::BOSSENEMY_LEFTTHIGH_HP		= 100;
 //�{�X�G��PELVIS��HP							 	 
 const  int Params::BOSSENEMY_PELVIS_HP			= 100;
 //�{�X�G��RIGHTARM��HP							 	 
 const  int Params::BOSSENEMY_RIGHTARM_HP		= 100;
 //�{�X�G��RIGHTARMJOINT��HP							 
 const  int Params::BOSSENEMY_RIGHTARMJOINT_HP	= 10;
 //�{�X�G��RIGHTLEG��HP							 	 
 const  int Params::BOSSENEMY_RIGHTLEG_HP		= 100;
 //�{�X�G��RIGHTSHOULDER��HP							 
 const  int Params::BOSSENEMY_RIGHTSHOULDER_HP	= 100;
 //�{�X�G��RIGHTTHIGH��HP							 
 const  int Params::BOSSENEMY_RIGHTTHIGH_HP      = 100;
 //�{�X�G��TORSO��HP							 		 
 const  int Params::BOSSENEMY_TORSO_HP			= 100;







 //�{�X�G�̃{�b�N�X�̓����蔻��̑傫��
 const Vector3 Params::BOSSENEMY_BOX_COLLIDER_SIZE = Vector3(3.0f, 3.7f, 1.1f);
 //�{�X�G�̃X�t�B�A�̓����蔻��̑傫��
 const float Params::BOSSENEMY_SPHERE_COLLIDER_SIZE = 5.0f;

 //�{�X�G�̃r�[���̔��ˈʒu
 const  Vector3 Params::BOSSENEMY_BEAM_SHOT_POSITION = Vector3(-2.0f, 0.5f, 5.0);


 //�{�X�r�[���̑傫��
 const Vector3 Params::BOSSENEMY_BEAM_SCALE = Vector3::One;
 //�{�X�r�[���̍��W
 const Vector3 Params::BOSSENEMY_BEAM_POSITION = Vector3::Zero;
 //�{�X�r�[���̉�]
 const Quaternion Params::BOSSENEMY_BEAM_ROTATION = Quaternion::Identity;
 //�{�X�r�[���̃G�l���M�[�e�̃{�b�N�X�̓����蔻��̑傫��
 const Vector3  Params::BOSSENEMY_BEAM_BALL_BOX_COLLIDER_SIZE = Vector3(0.4f,0.4f,0.4f);
 //�{�X�r�[���̃G�l���M�[�e�̃X�t�B�A�̓����蔻��̑傫��
 const float  Params::BOSSENEMY_BEAM_BALL_SPHERE_COLLIDER_SIZE = 0.8f;



 //�{�X�r�[���̏k������
 const float Params::BOSSENEMY_BEAM_SHRINK_TIME = 0.8f;
 //�{�X�r�[���̃G�l���M�[�e�̍ő�̑傫��
 const Vector3 Params::BOSSENEMY_BEAM_BALL_MAX_SCALE = Vector3(1.5f,1.5f,1.5f);
 //�{�X�r�[���̃G�l���M�[�e�̗\������̎���
 const float Params::BOSSENEMY_BEAM_BALL_PRELIMINARY_ACTION_TIME = 2.0f;
 //�{�X�r�[���̃G�l���M�[�e�̗��߂̎���
 const float Params::BOSSENEMY_BEAM_BALL_ACCUMULATIONTIME = 3.0f;
 //�{�X�r�[���̃G�l���M�[�e�̓����X�s�[�h
 const float Params::BOSSENEMY_BEAM_BALL_MOVE_SPPED = 20.f;
 //�{�X�r�[���̌����̍ő�̑傫��
 const Vector3 Params::BOSSENEMY_BEAM_RAYS_MAX_SCALE = Vector3(1.5f,1.5f,0);
 //�{�X�r�[���̃`���[�W�G�t�F�N�g�̐����Ԋu
 const float Params::BOSSENEMY_BEAM_CHARGE_EFFECT_CREATE_TIME = 0.5f;
 //�{�X�r�[���̃`���[�W�G�t�F�N�g�̓����X�s�[�h
 const float Params::BOSSENEMY_BEAM_CHARGE_EFFECT_MOVE_TIME = 1.0f;


 //�{�X�G��BODY�̑傫��
  const  Vector3 Params::BOSSENEMY_BODY_SCALE = Vector3::One;
 //�{�X�G��BODY�̍��W
  const  Vector3 Params::BOSSENEMY_BODY_POSITION = Vector3(0.0f,-1.3f,0.0f);
 //�{�X�G��BODY�̉�]
  const  Quaternion Params::BOSSENEMY_BODY_ROTATION = Quaternion::Identity;
 //�{�X�G��BODY�̃{�b�N�X�̓����蔻��̑傫��
  const  Vector3 Params::BOSSENEMY_BODY_BOX_COLLIDER_SIZE = Vector3(0.57f,0.17f,0.37f);
 //�{�X�G��BODY�̃X�t�B�A�̓����蔻��̑傫��
  const  float Params::BOSSENEMY_BODY_SPHERE_COLLIDER_SIZE = 1.0f;

 //�{�X�G��HEAD�̑傫��
  const  Vector3 Params::BOSSENEMY_HEAD_SCALE = Vector3::One;
 //�{�X�G��HEAD�̍��W								  
  const  Vector3 Params::BOSSENEMY_HEAD_POSITION = Vector3(0.0f,2.1f,0.0f);
 //�{�X�G��HEAD�̉�]								  
  const  Quaternion Params::BOSSENEMY_HEAD_ROTATION = Quaternion::Identity;
 //�{�X�G��HEAD�̃{�b�N�X�̓����蔻��̑傫��		  
  const  Vector3 Params::BOSSENEMY_HEAD_BOX_COLLIDER_SIZE = Vector3(0.13f,0.13f,0.13f);
 //�{�X�G��HEAD�̃X�t�B�A�̓����蔻��̑傫��		  
  const  float Params::BOSSENEMY_HEAD_SPHERE_COLLIDER_SIZE = 0.3f;


 //�{�X�G��LEFTARM�̑傫��
  const  Vector3 Params::BOSSENEMY_LEFTARM_SCALE = Vector3::One;
 //�{�X�G��LEFTARM�̍��W								 
  const  Vector3 Params::BOSSENEMY_LEFTARM_POSITION = Vector3(0.0f,-1.3f,0.0f);
 //�{�X�G��LEFTARM�̉�]								 
  const  Quaternion Params::BOSSENEMY_LEFTARM_ROTATION = Quaternion::Identity;
 //�{�X�G��LEFTARM�̃{�b�N�X�̓����蔻��̑傫��		 
  const  Vector3 Params::BOSSENEMY_LEFTARM_BOX_COLLIDER_SIZE = Vector3(0.08f,0.11f,0.08f);
 //�{�X�G��LEFTARM�̃X�t�B�A�̓����蔻��̑傫��		 
  const  float Params::BOSSENEMY_LEFTARM_SPHERE_COLLIDER_SIZE = 0.2f;

 //�{�X�G��LEFTARMJOINT�̑傫��
  const  Vector3 Params::BOSSENEMY_LEFTARMJOINT_SCALE = Vector3::One;
 //�{�X�G��LEFTARMJOINT�̍��W						 
  const  Vector3 Params::BOSSENEMY_LEFTARMJOINT_POSITION = Vector3(0.0f,-1.7f,0.0f);
 //�{�X�G��LEFTARMJOINT�̉�]						 
  const  Quaternion Params::BOSSENEMY_LEFTARMJOINT_ROTATION = Quaternion::Identity;
 //�{�X�G��LEFTARMJOINT�̃{�b�N�X�̓����蔻��̑傫�� 
  const  Vector3 Params::BOSSENEMY_LEFTARMJOINT_BOX_COLLIDER_SIZE = Vector3(0.06f,0.1f,0.06f);
 //�{�X�G��LEFTARMJOINT�̃X�t�B�A�̓����蔻��̑傫�� 
  const  float Params::BOSSENEMY_LEFTARMJOINT_SPHERE_COLLIDER_SIZE = 0.15f ;

 //�{�X�G��LEFTLEG�̑傫��
  const  Vector3 Params::BOSSENEMY_LEFTLEG_SCALE = Vector3::One;
 //�{�X�G��LEFTLEG�̍��W						 		
  const  Vector3 Params::BOSSENEMY_LEFTLEG_POSITION = Vector3(0.0f,-0.6f,0.0f);
 //�{�X�G��LEFTLEG�̉�]						 		 
  const  Quaternion Params::BOSSENEMY_LEFTLEG_ROTATION = Quaternion::Identity;
 //�{�X�G��LEFTLEG�̃{�b�N�X�̓����蔻��̑傫�� 	 
  const  Vector3 Params::BOSSENEMY_LEFTLEG_BOX_COLLIDER_SIZE = Vector3(0.09f,0.09f,0.09f);
 //�{�X�G��LEFTLEG�̃X�t�B�A�̓����蔻��̑傫�� 	 
  const  float Params::BOSSENEMY_LEFTLEG_SPHERE_COLLIDER_SIZE = 0.2f;

 //�{�X�G��LEFTSHOULDER�̑傫��
  const  Vector3 Params::BOSSENEMY_LEFTSHOULDER_SCALE = Vector3::One;
 //�{�X�G��LEFTSHOULDER�̍��W						
  const  Vector3 Params::BOSSENEMY_LEFTSHOULDER_POSITION = Vector3(2.4f,1.0f,0.0f);
 //�{�X�G��LEFTSHOULDER�̉�]						 
  const  Quaternion Params::BOSSENEMY_LEFTSHOULDER_ROTATION = Quaternion::Identity;
 //�{�X�G��LEFTSHOULDER�̃{�b�N�X�̓����蔻��̑傫�� 
  const  Vector3 Params::BOSSENEMY_LEFTSHOULDER_BOX_COLLIDER_SIZE = Vector3(0.12f,0.2f,0.12f);
 //�{�X�G��LEFTSHOULDER�̃X�t�B�A�̓����蔻��̑傫�� 
  const  float Params::BOSSENEMY_LEFTSHOULDER_SPHERE_COLLIDER_SIZE = 0.5f;



 //�{�X�G��LEFTTHIGH�̑傫��
  const  Vector3 Params::BOSSENEMY_LEFTTHIGH_SCALE = Vector3::One;
 //�{�X�G��LEFTTHIGH�̍��W							 
  const  Vector3 Params::BOSSENEMY_LEFTTHIGH_POSITION = Vector3(0.9f,-0.7f,0.0f);
 //�{�X�G��LEFTTHIGH�̉�]						 	 
  const  Quaternion Params::BOSSENEMY_LEFTTHIGH_ROTATION = Quaternion::Identity;
 //�{�X�G��LEFTTHIGH�̃{�b�N�X�̓����蔻��̑傫�� 	 
  const  Vector3 Params::BOSSENEMY_LEFTTHIGH_BOX_COLLIDER_SIZE= Vector3(0.1f,0.13f,0.1f);
 //�{�X�G��LEFTTHIGH�̃X�t�B�A�̓����蔻��̑傫�� 	 
  const  float Params::BOSSENEMY_LEFTTHIGH_SPHERE_COLLIDER_SIZE = 0.2f;


 //�{�X�G��PELVIS�̑傫��
  const  Vector3 Params::BOSSENEMY_PELVIS_SCALE = Vector3::One;
 //�{�X�G��PELVIS�̍��W							 	 
  const  Vector3 Params::BOSSENEMY_PELVIS_POSITION = Vector3(0.0f,0.7f,0.0f);
 //�{�X�G��PELVIS�̉�]						 	 	 
  const  Quaternion Params::BOSSENEMY_PELVIS_ROTATION = Quaternion::Identity;
 //�{�X�G��PELVIS�̃{�b�N�X�̓����蔻��̑傫�� 	 	 
  const  Vector3 Params::BOSSENEMY_PELVIS_BOX_COLLIDER_SIZE = Vector3(0.3f,0.1f,0.25f);
 //�{�X�G��PELVIS�̃X�t�B�A�̓����蔻��̑傫�� 	 	 
  const  float Params::BOSSENEMY_PELVIS_SPHERE_COLLIDER_SIZE = 0.5f;


 //�{�X�G��RIGHTARM�̑傫��
  const  Vector3 Params::BOSSENEMY_RIGHTARM_SCALE = Vector3::One;
 //�{�X�G��RIGHTARM�̍��W							 
  const  Vector3 Params::BOSSENEMY_RIGHTARM_POSITION = Vector3(0.0f,-1.3f,0.0f);
 //�{�X�G��RIGHTARM�̉�]						 	 
  const  Quaternion Params::BOSSENEMY_RIGHTARM_ROTATION = Quaternion::Identity;
 //�{�X�G��RIGHTARM�̃{�b�N�X�̓����蔻��̑傫�� 	 
  const  Vector3 Params::BOSSENEMY_RIGHTARM_BOX_COLLIDER_SIZE = Vector3(0.08f,0.11f,0.08f);
 //�{�X�G��RIGHTARM�̃X�t�B�A�̓����蔻��̑傫�� 	 
  const  float Params::BOSSENEMY_RIGHTARM_SPHERE_COLLIDER_SIZE = 0.2f;

 //�{�X�G��RIGHTARMJOINT�̑傫��
  const  Vector3 Params::BOSSENEMY_RIGHTARMJOINT_SCALE = Vector3::One;
 //�{�X�G��RIGHTARMJOINT�̍��W						 
  const  Vector3 Params::BOSSENEMY_RIGHTARMJOINT_POSITION = Vector3(0.0f,-1.7f,0.0f);
 //�{�X�G��RIGHTARMJOINT�̉�]						 
  const  Quaternion Params::BOSSENEMY_RIGHTARMJOINT_ROTATION = Quaternion::Identity;
 //�{�X�G��RIGHTARMJOINT�̃{�b�N�X�̓����蔻��̑傫��
  const  Vector3 Params::BOSSENEMY_RIGHTARMJOINT_BOX_COLLIDER_SIZE = Vector3(0.06f,0.1f,0.06f);
 //�{�X�G��RIGHTARMJOINT�̃X�t�B�A�̓����蔻��̑傫��
  const  float Params::BOSSENEMY_RIGHTARMJOINT_SPHERE_COLLIDER_SIZE = 0.15f;


 //�{�X�G��RIGHTLEG�̑傫��
  const  Vector3 Params::BOSSENEMY_RIGHTLEG_SCALE = Vector3::One;
 //�{�X�G��RIGHTLEG�̍��W						 	 
  const  Vector3 Params::BOSSENEMY_RIGHTLEG_POSITION = Vector3(0.0f,-0.6f,0.0f);
 //�{�X�G��RIGHTLEG�̉�]						 	 
  const  Quaternion Params::BOSSENEMY_RIGHTLEG_ROTATION = Quaternion::Identity;
 //�{�X�G��RIGHTLEG�̃{�b�N�X�̓����蔻��̑傫��	 
  const  Vector3 Params::BOSSENEMY_RIGHTLEG_BOX_COLLIDER_SIZE = Vector3(0.09f,0.09f,0.09f);
 //�{�X�G��RIGHTLEG�̃X�t�B�A�̓����蔻��̑傫��	 
  const  float Params::BOSSENEMY_RIGHTLEG_SPHERE_COLLIDER_SIZE = 0.2f;

 //�{�X�G��RIGHTSHOULDER�̑傫��
  const  Vector3 Params::BOSSENEMY_RIGHTSHOULDER_SCALE = Vector3::One;
 //�{�X�G��RIGHTSHOULDER�̍��W						 
  const  Vector3 Params::BOSSENEMY_RIGHTSHOULDER_POSITION = Vector3(-2.4f,1.0f,0.0f);
 //�{�X�G��RIGHTSHOULDER�̉�]						 
  const  Quaternion Params::BOSSENEMY_RIGHTSHOULDER_ROTATION = Quaternion::Identity;
 //�{�X�G��RIGHTSHOULDER�̃{�b�N�X�̓����蔻��̑傫��
  const  Vector3 Params::BOSSENEMY_RIGHTSHOULDER_BOX_COLLIDER_SIZE = Vector3(0.12f,0.2f,0.12f);
 //�{�X�G��RIGHTSHOULDER�̃X�t�B�A�̓����蔻��̑傫��
  const  float Params::BOSSENEMY_RIGHTSHOULDER_SPHERE_COLLIDER_SIZE = 0.5f;


 //�{�X�G��RIGHTTHIGH�̑傫��
  const  Vector3 Params::BOSSENEMY_RIGHTTHIGH_SCALE = Vector3::One;
 //�{�X�G��RIGHTTHIGH�̍��W						 	 
  const  Vector3 Params::BOSSENEMY_RIGHTTHIGH_POSITION = Vector3(-0.9f,-0.7f,0.0f);
 //�{�X�G��RIGHTTHIGH�̉�]						 	 
  const  Quaternion Params::BOSSENEMY_RIGHTTHIGH_ROTATION = Quaternion::Identity;
 //�{�X�G��RIGHTTHIGH�̃{�b�N�X�̓����蔻��̑傫��	 
  const  Vector3 Params::BOSSENEMY_RIGHTTHIGH_BOX_COLLIDER_SIZE = Vector3(0.1f,0.13f,0.1f);
 //�{�X�G��RIGHTTHIGH�̃X�t�B�A�̓����蔻��̑傫��	 
  const  float Params::BOSSENEMY_RIGHTTHIGH_SPHERE_COLLIDER_SIZE = 0.2f;

 //�{�X�G��TORSO�̑傫��
  const  Vector3 Params::BOSSENEMY_TORSO_SCALE = Vector3::One;
 //�{�X�G��TORSO�̍��W						 	 	 
  const  Vector3 Params::BOSSENEMY_TORSO_POSITION = Vector3(0.0f,1.7f,0.0f);
 //�{�X�G��TORSO�̉�]						 	 	 
  const  Quaternion Params::BOSSENEMY_TORSO_ROTATION = Quaternion::Identity;
 //�{�X�G��TORSO�̃{�b�N�X�̓����蔻��̑傫��	 	 
  const  Vector3 Params::BOSSENEMY_TORSO_BOX_COLLIDER_SIZE = Vector3(0.4f,0.35f,0.2f);
 //�{�X�G��TORSO�̃X�t�B�A�̓����蔻��̑傫��	 	 
  const  float Params::BOSSENEMY_TORSO_SPHERE_COLLIDER_SIZE = 0.6f;


  //���̓G
	//���̓G��HP
  const int Params::BIRDENEMY_HP = 40;
  //���̓G�̃{�b�N�X�̓����蔻��̑傫��
  const  Vector3 Params::BIRDENEMY_BOX_COLLIDER_SIZE = Vector3(0.7f,0.3f,0.7f);
  //���̓G�̃X�t�B�A�̓����蔻��̑傫��
  const float Params::BIRDENEMY_SPHERE_COLLIDER_SIZE = 1.0f;
  //���̓G�̉e�̑傫��
  const float Params::BIRDENEMY_SHADOW_RADIUS = 0.5f;

  //���̓G�̃r�[���̔��ˍ��W
  const  Vector3 Params::BIRDENEMY_BEAM_SHOT_POSITION = Vector3(0.0f,0.0f,1.8f);

  //���̓G�̓����̂ɂ����鎞��
  const float Params::BIRDENEMY_MOVE_TIME = 0.1f;
  //���̓G�̍s���̍ŏ��Ԋu
  const float Params::BIRDENEMY_ACTIONS_MIN_TIME = 1.0f;
  //���̓G�̍s���̍ő�Ԋu
  const float Params::BIRDENEMY_ACTIONS_MAX_TIME = 5.0f;
  //���̓G�̍s�����a
  const float Params::BIRDENEMY_MOVE_RADIUS = 2.0f;
  //���̓G�̍U���̊m��
  const float Params::BIRDENEMY_ATTACK_RATIO = 20.0f;



  //���̓G��BODY�̑傫��
  const  Vector3 Params::BIRDENEMY_BODY_SCALE = Vector3::One;
  //���̓G��BODY�̍��W
  const  Vector3 Params::BIRDENEMY_BODY_POSITION = Vector3::Zero;
  //���̓G��BODY�̉�]
  const  Quaternion Params::BIRDENEMY_BODY_ROTATION = Quaternion::Identity;

  //���̓G��LEFTFEATHER�̑傫��
  const  Vector3 Params::BIRDENEMY_LEFTFEATHER_SCALE = Vector3::One;
  //���̓G��LEFTFEATHER�̍��W						
  const  Vector3 Params::BIRDENEMY_LEFTFEATHER_POSITION = Vector3(-0.5f,0.0f,0.0f);
  //���̓G��LEFTFEATHER�̉�]						
  const  Quaternion Params::BIRDENEMY_LEFTFEATHER_ROTATION = Quaternion::Identity;


  //���̓G��RIGHTFEATHER�̑傫��
    const  Vector3 Params::BIRDENEMY_RIGHTFEATHER_SCALE = Vector3::One;
  //���̓G��RIGHTFEATHER�̍��W						
    const  Vector3 Params::BIRDENEMY_RIGHTFEATHER_POSITION = Vector3(0.5f,0.0f,0.0f);
  //���̓G��RIGHTFEATHER�̉�]						
    const  Quaternion Params::BIRDENEMY_RIGHTFEATHER_ROTATION = Quaternion::CreateFromYawPitchRoll(DirectX::XMConvertToRadians(0), 
																									DirectX::XMConvertToRadians(0), 
																									DirectX::XMConvertToRadians(180));


	//���̓G�̃G�l���M�[�e�̍ő�̑傫��
	const Vector3 Params::BIRDENEMY_BEAM_BALL_MAX_SIZE = Vector3(0.5f,0.5f,0.5f); 

	//���̓G�̃G�l���M�[�e�̗��ߎ���
	const float Params::BIRDENEMY_BEAM_BALL_ACCUMULATIONTIME = 2.0f;

	///���̓G�̃r�[���e�̏����x
	const float Params::BIRDENEMY_BEAM_BALL_INITIAL_SPEED = 4.0f;
	///���̓G�̃r�[���e�̍ŏI���x
	const float Params::BIRDENEMY_BEAM_BALL_FAINAL_SPEED = 1.5f;
	//���̓G�̃G�l���M�[�e�̌�����
	const float Params::BIRDENEMY_BEAM_BALL_DECELERATION_TIME = 0.3f;



