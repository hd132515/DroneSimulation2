#pragma once

#include <thread>
#include <mutex>
#include <condition_variable>
#include <list>
#include <unordered_map>
#include <string>
#include "Body.h"

class PhysicsThread
{
public:
	PhysicsThread();
	~PhysicsThread();
private:
	static PhysicsThread instance;
	std::mutex object_accessor;
	std::unordered_map<std::string, Body*> objects;
	std::list<float> frame_dur;

	bool ready;
	float update_time;
	float thread_execution;

	int render_target_frame;

	std::thread* handler;
	std::thread* manager;

	float render_time;
	float old_time;

private:
	void physics_updater();
	void frame_manager();

public:
	static PhysicsThread& get_instance();

	void register_object(std::string& name, Body* obj);

	void start();
	void stop();

	bool is_physics_enabled();
	void notice_render();
	void end_render();

	Body* get_object(std::string& name);

	int get_render_target_frame();

	float get_render_time();
	int get_frame();
};