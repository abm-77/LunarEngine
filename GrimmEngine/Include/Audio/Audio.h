#pragma once
#include "System/ResourceManager.h"
#include <irrKlang.h>
#include <string>
#include <memory>

class AudioSource : public Resource
{
public:
	AudioSource();

	void SetVolume(float volume);

	std::shared_ptr<irrklang::ISoundSource> GetIrrklangSoundSource() const;
	bool LoadFromFile(const std::string&);

private:
	std::shared_ptr<irrklang::ISoundSource> irrklangSoundSource;
};


class AudioManager
{
public:
	static void Init();

	static void PlaySound2D(const std::string& resourceName, bool loop = false);
	static void SetSourceVolume(const std::string& resourceName, float volume);


	static void Close();

	static irrklang::ISoundEngine* GetSoundEngine();

private:
	static irrklang::ISoundEngine* soundEngine;
};