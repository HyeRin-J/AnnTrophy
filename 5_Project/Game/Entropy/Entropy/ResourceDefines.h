#pragma once

///BGM
#define BGM_BRIGHT				   	 _T("bgm bright mood.wav")//타이틀,엔딩,튜토리얼 / 볼륨60
#define BGM1						 _T("bgm1.wav")//섹터1-1, 1-2 , 1-3/ 볼륨60
#define BGM2						 _T("bgm2.wav")//섹터1-4, 2-1 , 2-2/ 볼륨60
#define BGM3						 _T("bgm3.wav")//섹터2-3, 2-4 , 2-5/ 볼륨60
#define BGM4						 _T("bgm4.wav")//섹터2-6, 2-7 , 2-8/ 볼륨60
#define BGM_BOSS				 	 _T("bgm5 boss.wav")//보스 생성 이후/ 볼륨60

///system
#define CONVERT_0_SFX				 _T("convert_sfx.wav") // 컨버전 순 -> 역
#define CONVERT_1_SFX				 _T("convertInverse_sfx.wav")// 컨버전 역 -> 순
#define GAMEOVER_SFX				 _T("gameover_sfx.wav")// 게임오버
#define OVERLOAD_SFX				 _T("overload_sfx.wav")// 오버로딩 유지
#define OVERLOAD_END_SFX			 _T("overloadEnd_sfx.wav")// 오버로딩 종료
#define OVERLOAD_START_SFX			 _T("overloadStart_sfx.wav")// 오버로딩 시작
#define UPGRADE_CLEAR				 _T("upgradeClear.wav")// 강화 완료
#define UPGRADE_START				 _T("upgradeStart.wav")// 강화창, 스탯창 팝업

///Ann(PlayerCharactor)
//Defulat
#define ANN_ATTK_0					 _T("ann_attack1_sfx.wav")
#define ANN_ATTK_1					 _T("ann_attack2_sfx.wav")
#define ANN_ATTK_2				     _T("ann_attack3_sfx.wav")
#define ANN_ATTK_INVERSE_0	    	 _T("ann_attackInverse_sfx.wav")
#define ANN_ATTK_INVERSE_1		     _T("ann_attackInverse2_sfx.wav")
#define ANN_ATTK_OVERLOAD_NORMAL     _T("ann_attackOverload_sfx.wav")
#define ANN_ATTK_OVERLOAD_INVERSE	 _T("ann_AttackOverloadInverse_sfx.wav")
#define ANN_JUMP_NORMAL				 _T("ann_jump_sfx.wav")
#define ANN_JUMP_DOBLE				 _T("ann_doubleJump_sfx.wav")
#define ANN_JUMP_BELOW				 _T("ann_belowJump_sfx.wav")
#define ANN_DASH					 _T("ann_dash_sfx.wav")
#define ANN_DIE						 _T("ann_die_sfx.wav")
#define ANN_HIT						 _T("ann_hit_sfx.wav")
#define ANN_INTERACTION_PRESERVE	 _T("ann_interaction_sfx.wav")//유지
#define ANN_INTERACTION_START		 _T("ann_interactionStart_sfx.wav")//도입
#define ANN_LANDING					 _T("ann_landing_sfx.wav")
#define ANN_MOVE					 _T("ann_move_sfx.wav")

//Ann(Player) Voice  (스토리 대화창에 사용된다.)
#define ANN_VOICE_0					 _T("absolute.wav")
#define ANN_VOICE_1					 _T("AH.wav")
#define ANN_VOICE_2					 _T("AHH.wav")
#define ANN_VOICE_3					 _T("Amazing.wav")
#define ANN_VOICE_4					 _T("Damn it.wav")
#define ANN_VOICE_5					 _T("Enemy spotted.wav")
#define ANN_VOICE_6					 _T("follow me.wav")
#define ANN_VOICE_7					 _T("Groan.wav")
#define ANN_VOICE_8					 _T("hold here.wav")
#define ANN_VOICE_9					 _T("How much.wav")
#define ANN_VOICE_10				 _T("i cant do that.wav")
#define ANN_VOICE_11				 _T("i cant find it.wav")
#define ANN_VOICE_12				 _T("i must keep going.wav")
#define ANN_VOICE_13				 _T("i wonder where i can find that.wav")
#define ANN_VOICE_14				 _T("its locked.wav")
#define ANN_VOICE_15				 _T("Laugh 1.wav")
#define ANN_VOICE_16				 _T("laugh2.wav")
#define ANN_VOICE_17				 _T("laugh3.wav")
#define ANN_VOICE_18				 _T("leave them behind.wav")
#define ANN_VOICE_19				 _T("Ouch.wav")
#define ANN_VOICE_20				 _T("Ow.wav")
#define ANN_VOICE_21				 _T("what have you got.wav")
#define ANN_VOICE_22				 _T("yourwelcome.wav")

//Tropy(Gun) Voice  (스토리 대화창에 사용된다.)
#define TROPY_VOICE_0					 _T("tropy_voice1.wav")
#define TROPY_VOICE_1					 _T("tropy_voice2.wav")
#define TROPY_VOICE_2					 _T("tropy_voice3.wav")


//[[[[[------------Object------------]]]]]//

//--------EtcObject--------//
#define OBJECT_GATE_0				_T("gateOpen_sfx.wav") //스위치 해킹 완료 사운드 종료시 -> 스위치 해킹완료시 출력해야함
#define OBJECT_SWITCH_0				_T("SwitchOn_sfx.wav")//스위치 상호작용 시
#define OBJECT_SWITCH_1				_T("switchinteraction_sfx.wav")//스위치 게이지 최대 도달 시
#define OBJECT_GENERATOR_0			_T("generate_sfx.wav")//바리에이션 랜덤재생
#define OBJECT_VARIATION_0			_T("variation_sfx.wav")//바리에이션 랜덤재생

//Bullet
#define OBJECT_BULLET_0				_T("bullet_hit_sfx.wav")
#define OBJECT_BULLET_1				_T("bullet_hit2_sfx.wav")
#define OBJECT_BULLET_2				_T("bullet_hit3_sfx.wav")
#define OBJECT_BULLET_3				_T("bullet_hit4_sfx.wav")
#define OBJECT_BULLET_DEALY			_T("fire_delay_sfx.wav")
#define OBJECT_BULLET_SHILD			_T("shield_hit_sfx.wav")

//--------EnemyObject--------//

//곰돌쓰
#define ENEMY_BEAR_MOVE				_T("bear_walk_sfx.wav")//이동 (볼륨 작아야함)
#define ENEMY_BEAR_ATTK				_T("bear_die_sfx.wav")//공격
#define ENEMY_BEAR_RECOG			_T("bear_recog_sfx.wav")//인식
#define ENEMY_BEAR_DIE				_T("bear_attack_sfx.wav")//소멸

//터틀쓰
#define ENEMY_TUTLE_MOVE			_T("turtle_move_sfx.wav")//뭅
#define ENEMY_TUTLE_ATTK			_T("turtle_attack_sfx.wav")//공겨쿠
#define ENEMY_TUTLE_HIT				_T("turtle_attackHit_sfx.wav")//피격
#define ENEMY_TUTLE_RECOG			_T("turtle_recog_sfx.wav")//인식
#define ENEMY_TUTLE_DIE				_T("turtle_die_sfx.wav")//사망

//탕크
#define ENEMY_TANK_MOVE				_T("tank_move_sfx.wav")//이동
#define ENEMY_TANK_ATTK_0			_T("tank_attack1_sfx.wav")//권법1
#define ENEMY_TANK_ATTK_1			_T("tank_attack2_sfx.wav")//권법2
#define ENEMY_TANK_MOVE				_T("tank_move_sfx.wav")//이동
#define ENEMY_TANK_RECOG			_T("tank_recog_sfx.wav")//인식
#define ENEMY_TANK_DIE				_T("tank_die_sfx.wav")//다이

//두루미
#define ENEMY_CRANE_MOVE			_T("crane_move_sfx.wav")//이동
#define ENEMY_CRANE_ATTK			_T("crane_attack_sfx.wav")//공격
#define ENEMY_CRANE_JUMP			_T("crane_jump_sfx.wav")//점프
#define ENEMY_CRANE_RECOG			_T("crane_recog_sfx.wav")//인식 //
#define ENEMY_CRANE_DIE				_T("crane_die_sfx.wav")//쥬금 //

///boss

#define BOSS_VOICE_1				_T("boss voice1.wav")
#define BOSS_VOICE_2				_T("boss voice2.wav")
#define BOSS_VOICE_3				_T("boss voice3.wav")
//boss voice (스토리 대화창에 사용된다.)