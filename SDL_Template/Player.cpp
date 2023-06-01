#include "Player.h"
#include "BoxCollider.h"
#include "PhysicsManager.h"

void Player::HandleMovement() {
	Position(mInput->MousePosition());
	//Position with nothing in () returns the position
	//Position with something in () sets the position

}

void Player::HandleFiring() {
	if (mInput->KeyPressed(SDL_SCANCODE_SPACE)) {

	}
}

Player::Player() {
	mTimer = Timer::Instance();
	mInput = InputManager::Instance();
	mAudio = AudioManager::Instance();

	mVisible = false;
	mAnimating = false;
	mWasHit = false;

	mScore = 0;
	mLives = 2;

	mTarget = new GLTexture("Target.png", 0, 0, 130, 130);
	mTarget->Scale(Vector2(0.3f, 0.3f));
	mTarget->Parent(this);
	mTarget->Position(Vec2_Zero);

	mMoveSpeed = 300.0f;
	mMoveBounds = Vector2(0.0f, 1920.0f);

	AddCollider(new BoxCollider(Vector2(16.0f, 67.0f)));
	AddCollider(new BoxCollider(Vector2(20.0f, 37.0f)), Vector2(18.0f, 10.0f));
	AddCollider(new BoxCollider(Vector2(20.0f, 37.0f)), Vector2(-18.0f, 10.0f));

	mId = PhysicsManager::Instance()->RegisterEntity(this, PhysicsManager::CollisionLayers::Friendly);

	Visible(true);
}

Player::~Player() {
	mTimer = nullptr;
	mInput = nullptr;
	mAudio = nullptr;

	delete mTarget;
	mTarget = nullptr;
	delete mTargetSpawn;
	mTargetSpawn = nullptr;

}

void Player::Visible(bool visible) {
	mVisible = visible;
}

bool Player::IsAnimating() {
	return mAnimating;
}

int Player::Score() {
	return mScore;
}

int Player::Lives() {
	return mLives;
}

void Player::AddScore(int change) {
	mScore += change;
}

bool Player::IgnoreCollisions()
{
	return !mVisible || mAnimating;
}

void Player::Hit(PhysEntity* other) {
	mLives -= 1;
	mAnimating = true;
	mAudio->PlaySFX("SFX/PlayerExplosion.wav");
	mWasHit = true;
}

bool Player::WasHit() {
	return mWasHit;
}

void Player::Update() {

	if (mAnimating) {

		if (mWasHit) {
			mWasHit = false;
		}

	}
	else {
		if (Active()) {
			HandleMovement();
			HandleFiring();
		}
	}

	std::cout << "Position: " << Position().x << ", " << Position().y << std::endl;

}

void Player::Render() {

	if (mVisible) {
		if (mAnimating) {

		}
		else {
			mTarget->Render();

		}
	}

	PhysEntity::Render();
}