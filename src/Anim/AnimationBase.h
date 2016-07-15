#ifndef ANIMATION_BASE_H
#define ANIMATION_BASE_H

#include "SFML/Graphics.hpp"
#include <string>
#include <vector>
#include <stdio.h>
#include <stdlib.h>

//Want a single animation and an animation manager
//Single animation will hold the frames and the timing data
//animation manager will be accessable to higher level classes to control the animation as well as contain many animations, will act on sprites

//inputs from file would contain things like textures, indecies at which the frame occur, frame dimensions, etc

//this single animation objects will likely be created from parser functions which will simplify things


class Animation { //contains basic math/timing properties of a single animation

	public:
		
		Animation();
		~Animation();
	
		void AddFrame(const sf::IntRect frame); //Add a new frame
		void AddFrame(const sf::IntRect frame, unsigned int frameTime); //Add a new frame with a frame time
		void RemoveFrame(int pos); //remove a frame at this index (might not need this)

		void SetBaseFrameTime(float frameTime);  //set the base frame time
		void SetTexture(sf::Texture& texture);	
		void SetReversed(bool state); //set the animation's reversed flag
	
		float GetBaseFrameTime() const; //get the frame time
		const sf::IntRect& GetFrame(int pos) const; //get the frame at this index	
		unsigned int GetFrameTime(int pos) const; //get the frame time in frame counts
		float GetTotalFrameTime(int pos) const; //get the frame time in seconds
		unsigned int GetFrameCount() const; //get the number of frames
		sf::Texture* GetTexture() const;

		bool IsReversed() const; //is the animation order reversed?
	
	private:

		float _baseFrameTime; //default time each frame displays for
		std::vector<unsigned int> _frameTime; //vector of lengths of times the frames display for in units of the base frame time
		std::vector<sf::IntRect> _frames; //Array of IntRects designating frames	
		sf::Texture* _texture;

		//let's get some more animation properties going here
		//just for experimental purposes, brainstorming really
		bool _reversed; //should we play it backwards?  Managed in the GetFrame method

};

class MultiAnimation { //simple conatainer holding multiple animations, higher level classes will have one, need an animation registry too

	public:

			MultiAnimation();
			~MultiAnimation();

			void Add(std::string name, Animation& Animation); //Add an animation to the stack
			void Remove(std::string name); //Remove an animation

			Animation& Get(std::string name); //get a reference to an animation by name

	private:

		std::map<std::string, Animation> _animations; //Mapping of the different animations
};

class Animator { //animates a single animation
		
	public:

		Animator();
		Animator(const Animation& animation);
		~Animator();

		void Update(float elapsedTime); //update the animation
		void Play(); //set paused to false
		void Play(const Animation& animation); //set paused to false and set new animation
		void Pause(); //set puased to true
		void Stop(); //pause and reset animation

		bool FrameReady();  //is the next frame ready to be displayed?
		bool IsPaused() const;
		bool IsLooped() const;

		void SetLooped(bool looped); //set the animation to loop
		void SetAnimation(const Animation& animation);

		const Animation* GetAnimation() const;
		unsigned int GetCurrentIndex() const; //get the index of the current frame
		const sf::IntRect& GetCurrentFrame() const; //get the IntRect of the current Frame
		float GetElapsedTime() const; //get the amount of time that has passed

	private:

		bool _isPaused, _isLooped, _isReady; //is the animation paused?  Is is looping?	Is the frame ready?
		const Animation* _anim; //The Current animation
		float _elapsedTime; //how much time has elapsed since the last frame
		unsigned int _currentFrame; //the current frame
};

//we should also build some easy ways of building animations for common cases

//for example, when all the frames fit in a single row of a tile sheet with constant time frames
//Maybe create polymorphisms for total animation times, using columns instead, reverse animation order (that one might also become of method of the animation manager)
Animation RollingTileSheet(unsigned int width, unsigned int height, unsigned int row, unsigned int nframes);



#endif

