#include "stdafx.h"
#include "PhysicsThread.h"

using namespace std::chrono_literals;

PhysicsThread PhysicsThread::instance;

PhysicsThread& PhysicsThread::get_instance()
{
	return instance;
}


PhysicsThread::PhysicsThread():
update_time(0.001f), thread_execution(0.f), render_target_frame(0), ready(false),
old_time(-1.f), render_time(0.f), manager(nullptr)
{
}

PhysicsThread::~PhysicsThread()
{
	for (auto elem : objects)
	{
		delete elem.second;
	}
}

void PhysicsThread::register_object(std::string& name, Body* obj)
{
	std::unique_lock<std::mutex> lock(object_accessor);

	objects[name] = obj;
}

void PhysicsThread::physics_updater()
{
	{
		std::unique_lock<std::mutex> objlock(object_accessor);
		for (auto elem : objects)
		{
			elem.second->start();
		}
	}

	{
		while (ready)
		{
			while (ready && frame_dur.size() > 100);

			frame_dur.push_back(thread_execution);

			double start = clock();

			{
				std::unique_lock<std::mutex> objlock(object_accessor);
				for (auto elem : objects)
				{
					elem.second->update(update_time);
				}
			}

			thread_execution += update_time;

			double end = clock();
			float dur = (end - start) / CLOCKS_PER_SEC;
			if (dur > update_time)
				update_time = dur * 1.5f;
		}
	}

	frame_dur.clear();
}

void PhysicsThread::frame_manager()
{
	for (int i = 0; i < render_target_frame; i++)
	{
		frame_dur.pop_front();
	}

	for (auto elem : objects)
	{
		elem.second->clean_frames(render_target_frame);
	}

	render_target_frame = 0;
}

void PhysicsThread::start()
{
	if (!ready)
	{
		ready = true;
		handler = new std::thread([this]() {physics_updater(); });
	}
}

void PhysicsThread::stop()
{
	if (ready)
	{
		ready = false;
		handler->join();
		delete handler;
		if (manager != nullptr)
		{
			manager->join();
			delete manager;
			manager = nullptr;
		}

		old_time = -1.f;
		update_time = 0.001f;
		thread_execution = 0.f;
		render_time = 0.f;

		frame_dur.clear();
		for (auto elem : objects)
		{
			elem.second->clean_frames(-1);
		}
		render_target_frame = 0;
	}
}

bool PhysicsThread::is_physics_enabled()
{
	return ready;
}

void PhysicsThread::notice_render()
{
	if (old_time == -1.f)
	{
		old_time = (float)clock();
		return;
	}
	float new_time = (float)clock();
	render_time = (float)((new_time - old_time) / CLOCKS_PER_SEC);

	if (manager != nullptr)
	{
		manager->join();
		delete manager;
		manager = nullptr;
	}

	for (auto durperfr : frame_dur)//reason2
	{
		if (durperfr > render_time)
		{
			break;
		}
		else
			render_target_frame++;
	}
}

void PhysicsThread::end_render()
{
	if (manager != nullptr)
	{
		AfxMessageBox(L"Don't make sense");
		PostQuitMessage(-1);
	}
	manager = new std::thread([this]() {frame_manager(); });
}

Body* PhysicsThread::get_object(std::string& name)
{
	return objects[name];
}

int PhysicsThread::get_render_target_frame()
{
	return render_target_frame;
}

float PhysicsThread::get_render_time()
{
	return render_time;
}

int PhysicsThread::get_frame()
{
	return frame_dur.size();
}