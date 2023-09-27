/// BulletML �����s����
/**
 * �g�����F
 * BulletMLRunner ���p�����Ă������̏������z�֐�����������B
 */

#ifndef BULLETRUNNER_H_
#define BULLETRUNNER_H_

#include "bulletmltree.h"
#include "bulletmlcommon.h"

#include <vector>
#include <boost/smart_ptr.hpp>

class BulletMLParser;
class BulletMLNode;
class BulletMLRunnerImpl;

typedef std::vector<double> BulletMLParameter;

/// BulletMLRunner ����ԓ`�B�Ɏg�p����N���X
class BulletMLState {
public:
	DECLSPEC BulletMLState(BulletMLParser* bulletml,
						   const std::vector<BulletMLNode*>& node,
						   boost::shared_ptr<BulletMLParameter> para)
		: bulletml_(bulletml), node_(node.begin(), node.end()), para_(para) {}

	DECLSPEC BulletMLParser* getBulletML() { return bulletml_; }
	DECLSPEC const std::vector<BulletMLNode*>& getNode() const { return node_; }
	DECLSPEC boost::shared_ptr<BulletMLParameter> getParameter() { return para_; }

private:
	BulletMLParser* bulletml_;
	std::vector<BulletMLNode*> node_;
	boost::shared_ptr<BulletMLParameter> para_;

};

/// BulletML �����s����N���X
/**
 * <pre>
 * �g�����B
 *  1. ������p�����āABullet �����ۂɓ�������N���X�����B
 *  2. �������z�֐���S�Ď�������B
 *  3. �K�v�Ȃ�AchangeDirection �Ȃǂ̂��߂ɕK�v�ȉ��z�֐�����������B
 *  4. ���̃N���X�̃I�u�W�F�N�g�ɑ΂��āAcom_->run(); �ȂǂƂ���B
 * </pre>
 */

class BulletMLRunner {
public:
	DECLSPEC explicit BulletMLRunner(BulletMLParser* bulletml);
    DECLSPEC explicit BulletMLRunner(BulletMLState* state);
    DECLSPEC virtual ~BulletMLRunner();

	/// ���s����
    DECLSPEC void run();

public:
	/// ���s���I�����Ă��邩�ǂ���
	DECLSPEC bool isEnd() const;

public:
	// ----- ��Ύ������Ȃ���΂Ȃ�Ȃ��֐��Q�̎n�܂� -----
	//@{
	/// ���̒e�̊p�x�����߂�
	/**
	 * @return �p�x��x�P�ʂŁA����� 0 �Ŏ��v����ŕԂ�
	 */
	DECLSPEC virtual double getBulletDirection() =0;
	/// ���̒e���玩�@��_���p�x�����߂�
	/**
	 * @return �p�x��x�P�ʂŁA����� 0 �Ŏ��v����ŕԂ�
	 */
	DECLSPEC virtual double getAimDirection() =0;
	/// ���̒e�̑��x�����߂�
	DECLSPEC virtual double getBulletSpeed() =0;
	/// �f�t�H���g�̑��x�����߂�
	DECLSPEC virtual double getDefaultSpeed() =0;
	/// �����N�����߂�
	/**
	 * @return 0 ���� 1 �܂ł̎���
	 */
	DECLSPEC virtual double getRank() =0;
	/// action �������Ȃ��e�����
	DECLSPEC virtual void createSimpleBullet(double direction, double speed) =0;
	/// action �����e�����
	/**
	 * @param state
	 * �V�����e�� BulletMLRunner �̃R���X�g���N�^�ɓn�����ƁB
	 * �����n���Ȃ��̂ł���΁Adelete �ŉ�����Ȃ���΂Ȃ�Ȃ��B
	 */
	DECLSPEC virtual void createBullet(BulletMLState* state,
									   double direction, double speed) =0;
	/// �e�̊�ƂȂ�^�[���̒l��Ԃ��A�ʏ�̓t���[����
	/**
	 * @return
	 * �Q�[�����Ƃ̊�ŃI�[�_�[�͕ύX���č\���܂��񂪁A
	 * �����͋�����܂���B
	 * xml �f�[�^��ŁAwait �� term �̃I�[�_�[�������Ă���Ζ�肠��܂���B
	 */
	DECLSPEC virtual int getTurn() =0;
	/// ����
	DECLSPEC virtual void doVanish() =0;
	//@}
	// ----- ��Ύ������Ȃ���΂Ȃ�Ȃ��֐��Q�̏I��� -----

	// ----- �K�v������Ύ�������֐��Q�̎n�܂� -----
   	//@{
	/// �e�̕������w�肵�������ɕύX����
	DECLSPEC virtual void doChangeDirection(double) {}
	/// �e�̑��x���w�肵���l�ɕύX����
	DECLSPEC virtual void doChangeSpeed(double) {}
	/// accel �ɑ΂���C���^�[�t�F�C�X
	/**
	 * @todo
	 * horizontal, vertical �� type �͖������ł��B
	 * �ǂ�� absolute �ɂȂ��Ă��܂��܂��B
	 */
	DECLSPEC virtual void doAccelX(double) {}
	/// accel �ɑ΂���C���^�[�t�F�C�X
	/**
	 * @todo
	 * horizontal, vertical �� type �͖������ł��B
	 * �ǂ�� absolute �ɂȂ��Ă��܂��܂��B
	 */
	DECLSPEC virtual void doAccelY(double) {}
	/// �e�̑����� X ����������Ԃ��܂�
	/**
	 * accel ���g���ꍇ�̓I�[�o�[���C�h���ĉ�����
 	 */
	DECLSPEC virtual double getBulletSpeedX() { return 0; }
	/// �e�̑����� Y ����������Ԃ��܂�
	/**
	 * accel ���g���ꍇ�̓I�[�o�[���C�h���ĉ�����
 	 */
	DECLSPEC virtual double getBulletSpeedY() { return 0; }
    //@}
	// ----- �K�v������Ύ�������֐��Q�̏I��� -----

	/// ������Ԃ�
	/**
	 * ���Ă̂Ƃ���A�f�t�H���g�ł� std::rand ���p�����܂��B
	 */
	DECLSPEC virtual double getRand() { return (double)rand() / RAND_MAX; }

private:
	/// BulletMLRunnerImpl ���I�[�o�[���C�h����ꍇ�A������I�[�o�[���C�h����
	DECLSPEC virtual BulletMLRunnerImpl* makeImpl(BulletMLState* state);

protected:
	std::vector<BulletMLRunnerImpl*> impl_;

};

#endif // ! BULLETRUNNER_H_

