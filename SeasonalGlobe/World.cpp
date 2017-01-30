#include "World.h"
#include "Lights.h"

World::World(void)
	: _curSeason(Spring), _curTime(0), _timePerSeason(0)
{
}


World::~World(void)
{
}

const bool World::CreateWorld()
{
	Lights::Instance()->CreateLights("Resources/Config/Config.txt");
	ParticleManager::Instance()->InitAll();

	if(!_base.Initialize())
		return false;
	if(!_globe.Initialize())
		return false;
	if(!_house.Initialize())
		return false;
	if(!_lake.Initialize())
		return false;
	if(!_terrain.Initialize())
		return false;
	if(!_tree.Initialize())
		return false;

	vector<string> configLines;
	Utility::Instance()->LoadConfigFile("Resources/Config/Config.txt", configLines);

	map<string,string> configData;
	Utility::Instance()->ReturnConfigField(configData, "Seasons", configLines);

	_timePerSeason = (float)atof(configData["TimeBetween"].c_str());

	if(configData["StartSeason"] == "Spring")
	{
		_curSeason = Spring;
	}
	else if (configData["StartSeason"] == "Summer")
	{
		_curSeason = Summer;
	}
	else if(configData["StartSeason"] == "Autumn")
	{
		_curSeason = Autumn;
	}
	else if (configData["StartSeason"] == "Winter")
	{
		_curSeason = Winter;
	}

	return true;
}

const void World::Render(const bool insideGlobe, const Vector3f& camPos)
{
	glClearStencil(0);
	glDisable(GL_DEPTH_TEST);
	glColorMask(0, 0, 0, 0);
	glDisable(GL_LIGHTING);
	glEnable(GL_STENCIL_TEST);
	glStencilFunc(GL_ALWAYS,1,1);
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

	_lake.Render(true);

	glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);
	glColorMask(1, 1, 1, 1);
	glStencilFunc(GL_EQUAL, 1, 1);
	glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);

	glPushMatrix();
	glScalef(1.0,-1.0,1.0);
	glTranslatef(0,0.03f,0);
	glEnable(GL_NORMALIZE);
	glCullFace(GL_FRONT);

	Lights::Instance()->ReflectLight();

	_tree.Render(camPos);
	_house.Render(true);

	if (_curSeason == Winter)
	{
		ParticleManager::Instance()->StartRender();
		ParticleManager::Instance()->RenderSnow(camPos);
		ParticleManager::Instance()->RenderSmoke(camPos);
		ParticleManager::Instance()->StopRender();
	}

	glDisable(GL_NORMALIZE);
	glCullFace(GL_BACK);
	glPopMatrix();
	glDisable(GL_STENCIL_TEST);

	Lights::Instance()->ReflectLight();

	_lake.Render(true);
	_base.Render(true);
	
	_house.Render(true);
	_terrain.Render(true);
	_tree.Render(camPos);
	if (_curSeason == Winter)
	{
		ParticleManager::Instance()->StartRender();
		ParticleManager::Instance()->RenderSnow(camPos);
		ParticleManager::Instance()->RenderSmoke(camPos);
		ParticleManager::Instance()->StopRender();
	}

	if(insideGlobe)
		glCullFace(GL_FRONT);
	_globe.Render(true);

	if(insideGlobe)
		glCullFace(GL_BACK);
}

const void World::Update( const float dt )
{
	_curTime += dt;
	if(_curTime >= _timePerSeason)
	{
#ifdef _DEBUG
		cout << "Season Updated" << endl;
#endif // _DEBUG
		if (_curSeason == Winter)
		{
			ParticleManager::Instance()->ResetSmoke();
			ParticleManager::Instance()->ResetSnow();
		}
		UpdateSeason();
		_tree.NextState();
		_curTime = 0.0f;
	}

	_tree.Update(dt, (((_timePerSeason - _curTime) / _timePerSeason) * 100.0f));
	Lights::Instance()->UpdateSunPosition(dt);

	if (_curSeason == Winter)
	{
		ParticleManager::Instance()->UpdateSnow(dt);
		ParticleManager::Instance()->UpdateSmoke(dt);
		_terrain.PercThroughSeason(1.0f - ((_timePerSeason - _curTime) / _timePerSeason));
		_house.PercThroughSeason(1.0f - ((_timePerSeason - _curTime) / _timePerSeason));
	}
	else if(_curSeason == Spring)
	{
		_terrain.PercThroughSeason((((_timePerSeason/2.0f) - _curTime) / _timePerSeason));
		_house.ReducePercThroughSeason((_timePerSeason * 0.01f) * dt);
	}
}
