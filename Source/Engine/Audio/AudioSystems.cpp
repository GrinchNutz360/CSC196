#include "AudioSystem.h"
#include <fmod_errors.h>
#include <iostream>

namespace viper {
	/// <summary>
	/// Checks if an FMOD operation was successful and logs an error message if it failed.
	/// </summary>
	/// <param name="result">The FMOD_RESULT value returned by an FMOD function call.</param>
	/// <returns>True if the FMOD operation was successful (FMOD_OK); false otherwise.</returns>
	bool AudioSystem::CheckFMODResult(FMOD_RESULT result) {
		if (result != FMOD_OK) {
			std::cerr << FMOD_ErrorString(result) << std::endl;
			return false; // Failed to create FMOD system
		}
		return true;
	}

	/// <summary>
	/// Initializes the audio system using FMOD.
	/// </summary>
	/// <returns>True if the audio system was successfully initialized; otherwise, false.</returns>
	bool AudioSystem::Initialize() {

		FMOD_RESULT result = FMOD::System_Create(&m_system);
		if (!CheckFMODResult(result)) return false;

		void* extradriverdata = nullptr;
		result = m_system->init(32, FMOD_INIT_NORMAL, extradriverdata);
		if (!CheckFMODResult(result)) return false;

		return true;
	}
	void AudioSystem::Shutdown() {
		CheckFMODResult(m_system->release());
	}

	void AudioSystem::Update() {
		CheckFMODResult(m_system->update());
	}
	bool AudioSystem::AddSound(const std::string& filename, const std::string& name)
	{
		//    audio->createSound("bass.wav", FMOD_DEFAULT, 0, &sound);

		return false;
	}
	bool AudioSystem::PlaySound(const std::string& name)
	{
		return false;
	}
}