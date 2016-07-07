
#include "Anim/AnimationBase.h"
#include <stdio.h>

//animation container
AnimationContainer::AnimationContainer(void) {

	_baseFrameTime = 1/60.0;
}

AnimationContainer::AnimationContainer(std::vector<const sf::IntRect*> frames) {

	_baseFrameTime = 1/60.0;
	_frames = frames;
}

AnimationContainer::~AnimationContainer(void) {}

void AnimationContainer::AddFrame(const sf::IntRect* frame) {

	_frames.push_back(frame);
	_frameTimeMultiplier.push_back(1);
}

void AnimationContainer::AddFrame(const sf::IntRect* frame, unsigned int frameTime) {

	_frames.push_back(frame);
	_frameTimeMultiplier.push_back(frameTime);
}

void AnimationContainer::RemoveFrame(int pos) {
	
	_frames.erase(_frames.begin()+pos);
	_frameTimeMultiplier.erase(_frameTimeMultiplier.begin()+pos);	
}

void AnimationContainer::SetBaseFrameTime(float frameTime) {

	_baseFrameTime = frameTime;
}

unsigned int AnimationContainer::GetFrameMultiplier(int pos) const { return _frameTimeMultiplier[pos]; }


float AnimationContainer::GetBaseFrameTime(void) const { return _baseFrameTime; }

std::size_t AnimationContainer::GetFrameCount(void) const { return _frames.size(); }

const sf::IntRect AnimationContainer::GetFrame(int pos) const { return *_frames[pos]; }

//Animation base class

Animation::Animation(void) : _isPaused(true), _isLooped(false), _elapsedTime(0.0), _currentFrame(0) {

}

Animation::Animation(const AnimationContainer& animation) : _isPaused(true), _isLooped(false), _elapsedTime(0.0), _currentFrame(0) {

	_animCont = &animation;
}

Animation::~Animation(void) {} 

void Animation::Update(float elapsedTime) {

	if (IsPaused()) {} 
	else {
		_elapsedTime += elapsedTime;
		if (_elapsedTime > _animCont->GetFrameMultiplier(_currentFrame)*_animCont->GetBaseFrameTime()) {
			_elapsedTime = 0;
			if (_currentFrame+1 < _animCont->GetFrameCount())
				_currentFrame++;
			else if (IsLooped())
				_currentFrame = 0;
		}	
	}
}

void Animation::Play(void) {

	_isPaused = false;
}

void Animation::Play(const AnimationContainer& animation) {

	if (_animCont != &animation) {
		SetAnimationContainer(animation);
		_currentFrame = 0;
	}
	Play();
}

void Animation::Pause(void) {

	_isPaused = true;
}

void Animation::Stop(void) {

	_isPaused = true;
	_currentFrame = 0;
}

bool Animation::IsPaused(void) const { return _isPaused; }

bool Animation::IsLooped() const { return _isLooped; }

void Animation::SetLooped(bool looped) {

	_isLooped = looped;
}

void Animation::SetAnimationContainer(const AnimationContainer& animation) {

	_animCont = &animation;
}

const AnimationContainer* Animation::GetAnimationContainer(void) const { return _animCont; }

unsigned int Animation::GetCurrentFrame() const { return _currentFrame; }

