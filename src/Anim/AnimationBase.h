#ifndef ANIMATION_BASE_H
#define ANIMATION_BASE_H

#include "SFML/Graphics.hpp"
#include <vector>
#include <stdio.h>
#include <stdlib.h>

class AnimationContainer { //Base class for creating animations
	//commenting out timing features for now
	public:

		AnimationContainer();
		AnimationContainer(std::vector<const sf::IntRect*> frames);
		~AnimationContainer();

		void AddFrame(const sf::IntRect* frame); //Add a new frame
		void AddFrame(const sf::IntRect* frame, unsigned int frameTime); //Add a new frame with a frame time
		void RemoveFrame(int pos); //remove a frame at this index

		void SetBaseFrameTime(float frameTime);  //set the base frame time


		unsigned int GetFrameMultiplier(int pos) const;
		float GetBaseFrameTime() const; //get the frame time
		std::size_t GetFrameCount() const; //get the number of frames

		const sf::IntRect GetFrame(int pos) const;

	private:

		float _baseFrameTime; //default time each frame displays for
		std::vector<unsigned int> _frameTimeMultiplier; //vector of lengths of times the frames display for in units of the base frame time

		std::vector<const sf::IntRect*> _frames; //Array of IntRects designating frames	


};

class Animation {
		
	public:

		Animation();
		Animation(const AnimationContainer& animation);
		~Animation();

		void Update(float elapsedTime); //update the animation
		void Play(); //set paused to false
		void Play(const AnimationContainer& animation); //set paused to false and set new animation
		void Pause(); //set puased to true
		void Stop(); //pause and reset animation
		

		bool IsPaused() const;
		bool IsLooped() const;

		void SetLooped(bool looped); //set the animation to loop
		void SetAnimationContainer(const AnimationContainer& animation);

		const AnimationContainer* GetAnimationContainer() const;
		unsigned int GetCurrentFrame() const;

	private:

		bool _isPaused, _isLooped; //is the animation paused?  Is is looping?	
		const AnimationContainer* _animCont; //the animation container	
		float _elapsedTime; //how much time has elapsed since the last frame
		unsigned int _currentFrame; //the current frame
};

#endif

