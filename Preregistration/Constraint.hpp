#pragma once
class Constraint
{
public:

	Constraint(bool input_hasComputer, bool input_hasSpeakers, bool input_hasHighEnergyParticleAccelerator);
	~Constraint();
	void setHasComputer(bool hasComputer);
	bool hasComputer();

	void setHasSpeakers(bool hasSpeakers);
	bool hasSpeakers();

	void setHasHighEnergyParticleAccelerator(bool hasHighEnergyParticleAccelerator);
	bool HasHighEnergyParticleAccelerator();

private:

	bool mHasComputer = false;
	bool mHasSpeakers = false;
	bool mHasHighEnergyParticleAccelerator = false;

};

	