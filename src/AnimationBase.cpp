
#include "Anim/AnimationBase.h"
#include <stdio.h>

//Base animation container
Animation::Animation(void) {

	_reversed = false;
	_baseFrameTime = 1/60.0;
}

Animation::~Animation(void) {}

void Animation::AddFrame(const sf::IntRect frame) {

	_frames.push_back(frame);
	_frameTime.push_back(1);
}

void Animation::AddFrame(const sf::IntRect frame, unsigned int frameTime) {

	_frames.push_back(frame);
	_frameTime.push_back(frameTime);
}

void Animation::RemoveFrame(int pos) {
	
	_frames.erase(_frames.begin()+pos);
	_frameTime.erase(_frameTime.begin()+pos);	
}

void Animation::SetBaseFrameTime(float frameTime) {

	_baseFrameTime = frameTime;
}

void Animation::SetTexture(sf::Texture& texture) {

	_texture = &texture;
}

void Animation::SetReversed(bool state) {

	_reversed = state;
}

float Animation::GetBaseFrameTime(void) const { return _baseFrameTime; }

const sf::IntRect& Animation::GetFrame(int pos) const { 

	return (!IsReversed() ) ? _frames[pos] : _frames[GetFrameCount() - pos - 1];
}

unsigned int Animation::GetFrameTime(int pos) const { return _frameTime[pos]; }

float Animation::GetTotalFrameTime(int pos) const { return _frameTime[pos]*_baseFrameTime; }

unsigned int Animation::GetFrameCount(void) const { return _frames.size(); }

sf::Texture* Animation::GetTexture(void) const { return _texture; }

bool Animation::IsReversed(void) const { return _reversed; }

//Multiple Animation container

MultiAnimation::MultiAnimation(void) {}

MultiAnimation::~MultiAnimation(void) {}

void MultiAnimation::Add(std::string name, Animation& animation) {

	_animations.insert(std::make_pair<std::string, Animation>(name, animation));
}

void MultiAnimation::Remove(std::string name) {
	
	std::map<std::string, Animation>::iterator item = _animations.find(name);
	if (item != _animations.end() ) {
		_animations.erase(item);
	}
}

Animation& MultiAnimation::Get(std::string name) {

	std::map<std::string, Animation>::iterator item = _animations.find(name);
	if (item != _animations.end() ) 
		return item->second;
}

//Animator animation manager

Animator::Animator(void) : _isPaused(true), _isLooped(false), _elapsedTime(0.0), _currentFrame(0), _anim(NULL) {

}

Animator::Animator(const Animation& animation) : _isPaused(true), _isLooped(false), _elapsedTime(0.0), _currentFrame(0) {

	_anim = &animation;
}

Animator::~Animator(void) {} 

void Animator::Update(float elapsedTime) {

	if ( IsPaused() ) {} 
	else {
		_elapsedTime += elapsedTime;
		if ( _elapsedTime > _anim->GetTotalFrameTime(_currentFrame) ) {
			_isReady = true;
			//_elapsedTime -= _anim->GetBaseFrameTime();
			_elapsedTime = 0;
			if (++_currentFrame >= _anim->GetFrameCount()) {
				if (IsLooped())
					_currentFrame = 0;
				else
					Stop();
			}
		}	
	}
}

void Animator::Play(void) {

	_isPaused = false;
}

void Animator::Play(const Animation& animation) {

	SetAnimation(animation);
	Play();
}

void Animator::Pause(void) {

	_isPaused = true;
}

void Animator::Stop(void) {

	_isPaused = true;
	_isReady = true; //careful of the isReady boolean.  We want the animation to update to the first frame
	_currentFrame = 0;
}

bool Animator::FrameReady(void) { //careful, this can only be called once!  This is checked after update 
	if (_isReady) {
		_isReady = false;
		return true; 
	}
	else
		return false;
}

bool Animator::IsPaused(void) const { return _isPaused; }

bool Animator::IsLooped(void) const { return _isLooped; }

void Animator::SetLooped(bool looped) {

	_isLooped = looped;
}

void Animator::SetAnimation(const Animation& animation) {

	if (_anim != &animation) {
		_anim = &animation;
		_currentFrame = 0;
		_isReady = true; //make sure we know the next frame is ready!
	}
}

const Animation* Animator::GetAnimation(void) const { return _anim; }

unsigned int Animator::GetCurrentIndex(void) const { return _currentFrame; }

const sf::IntRect& Animator::GetCurrentFrame(void) const { return _anim->GetFrame(_currentFrame); }

float Animator::GetElapsedTime(void) const { return _elapsedTime; }


Animation RollingTileSheet(unsigned int width, unsigned int height, unsigned int row, unsigned int nframes) {

	Animation anim;
	float top = row*height;
	for (int i = 0; i < nframes; ++i) 
		anim.AddFrame(sf::IntRect(i*width, top, width, height));
	return anim;
}






