#include "Audio/Audio.h"
#include "System/ResourceManager.h"

irrklang::ISoundEngine* AudioManager::soundEngine;

AudioSource::AudioSource() : irrklangSoundSource(nullptr) {}

void AudioSource::SetVolume(float volume)
{
	irrklangSoundSource->setDefaultVolume(volume);
}


std::shared_ptr<irrklang::ISoundSource> AudioSource::GetIrrklangSoundSource() const
{
	return irrklangSoundSource;
}

bool AudioSource::LoadFromFile(const std::string& filepath)
{
	irrklangSoundSource.reset(AudioManager::GetSoundEngine()->addSoundSourceFromFile(filepath.c_str()));
	if (irrklangSoundSource) return true;
	
	return false;
}

void AudioManager::Init()
{
	soundEngine = irrklang::createIrrKlangDevice();
}


void AudioManager::PlaySound2D(const std::string& resourceName, bool loop)
{
	soundEngine->play2D(ResourceManager::Get<AudioSource>(resourceName)->GetIrrklangSoundSource().get(), loop);
}

void AudioManager::SetSourceVolume(const std::string& resourceName, float volume)
{
	ResourceManager::Get<AudioSource>(resourceName)->SetVolume(volume);
}

void AudioManager::Close()
{
	//soundEngine->removeAllSoundSources();
	//soundEngine->drop();
}

irrklang::ISoundEngine* AudioManager::GetSoundEngine()
{
	return soundEngine;
}
