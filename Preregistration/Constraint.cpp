#include "Constraint.hpp"



Constraint::Constraint()
{
}


Constraint::~Constraint()
{
}

void Constraint::setHasComputer(bool hasComputer)
{
	mHasComputer = hasComputer;
}

bool Constraint::hasComputer()
{
	return mHasComputer;
}

void Constraint::setHasSpeakers(bool hasSpeakers)
{
	mHasSpeakers = hasSpeakers;
}

bool Constraint::hasSpeakers()
{
	return mHasSpeakers;
}

void Constraint::setHasHighEnergyParticleAccelerator(bool hasHighEnergyParticleAccelerator)
{
	mHasHighEnergyParticleAccelerator = hasHighEnergyParticleAccelerator;
}

bool Constraint::HasHighEnergyParticleAccelerator()
{
	return mHasHighEnergyParticleAccelerator;
}

bool Constraint::matchingConstraint(Constraint * constraint)
{
	if (this->hasComputer() != constraint->hasComputer())
		return false;

	if (this->hasSpeakers() != constraint->hasSpeakers())
		return false;

	if (this->HasHighEnergyParticleAccelerator() != constraint->HasHighEnergyParticleAccelerator())
		return false;

	return true;
}
