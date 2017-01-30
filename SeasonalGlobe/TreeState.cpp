#include "TreeState.h"

TreeState::TreeState(void)
	:_currentState(None), _lighteningLife(0.5f), _curTime(0)
{
}


TreeState::~TreeState(void)
{
}

const bool TreeState::Initialize()
{
	vector<string> configLines;
	if(!Utility::Instance()->LoadConfigFile("Resources/Config/Config.txt", configLines))
		return false;

	map<string,string> configData;
	if(!Utility::Instance()->ReturnConfigField(configData, "Seasons", configLines))
		return false;

	float timePerSeason = (float)atof(configData["TimeBetween"].c_str());
	_branches.Initialize();

	if (configData["StartSeason"] == "Spring")
	{
		_leaves.Initialize(_branches.GetLeafMats(), false, timePerSeason);
		_currentState = Branch_Grow;
	}
	else if (configData["StartSeason"] == "Summer")
	{
		_leaves.Initialize(_branches.GetLeafMats(), false, timePerSeason);
		_currentState = Leaf_Grow;
	}
	else if (configData["StartSeason"] == "Autumn")
	{
		_leaves.Initialize(_branches.GetLeafMats(), true, timePerSeason);
		_currentState = Leaf_Die;
	}
	else if (configData["StartSeason"] == "Winter")
	{
		_leaves.Initialize(_branches.GetLeafMats(), false, timePerSeason);
		_currentState = None;
	}

	if(!Utility::Instance()->ReturnConfigField(configData, "Tree", configLines))
		return false;

	Utility::Instance()->StringToVector(configData["Position"], _position);

	_lightening.Initialize(_position);
}

const void TreeState::Update( const float dt, const float percSeason )
{
	switch (_currentState)
	{
	case None:
		break;
	case Branch_Grow:
		_branches.Grow(dt);
		break;
	case Leaf_Grow:
		_leaves.Grow(dt);
		break;
	case Leaf_Die:
		_leaves.Die(dt, percSeason);
		if (percSeason <= 50.0f)
		{
			NextState();
		}
		break;
	case Branch_Die:
		_branches.Shrink(dt);
		ParticleManager::Instance()->UpdateFire(dt);
		_curTime += dt;
		break;
	}
}

const void TreeState::Render(const Vector3f& camPos)
{
	glPushMatrix();
	glTranslatef(_position[0], _position[1], _position[2]);
	switch (_currentState)
	{
	case None:
		break;
	case Branch_Grow:
		_branches.Render();
		break;
	case Leaf_Grow:
		_branches.Render();
		_leaves.Render();
		break;
	case Leaf_Die:
		_branches.Render();
		_leaves.Render();
		break;
	case Branch_Die:
		_branches.Render();
		// Lightening
		ParticleManager::Instance()->StartRender();
		ParticleManager::Instance()->RenderFire(camPos);
		ParticleManager::Instance()->StopRender();
		break;
	}
	glPopMatrix();

	if (_currentState == Branch_Die)
	{
		if(_lighteningLife > _curTime)
			_lightening.Render();
	}
}
