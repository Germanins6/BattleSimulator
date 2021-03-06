#pragma once

#include "p2Defs.h"

// -- Tools
#include <string>
#include <fstream>
#include <iomanip>
#include "JSON/json.hpp"

//Namespaces
using json = nlohmann::json;
using namespace std;

class Serializer {

public:

	Serializer();
	~Serializer();

	void Save(const char* file) const;
	void Load(const char* file);

	//-- Serialize
	
	//-------------
	void AddString(string name, string value);
	void AddInt(string name, int value);
	void AddUnsignedInt(string name, uint value);
	void AddFloat(string name, float value);
	void AddBool(string name, bool value);
	
	//Objects
	void AddStringObj(string name, string value, string obj_name = "");
	void AddIntObj(string name, int value, string obj_name = "");
	void AddUnsignedIntObj(string name, uint value, string obj_name = "");
	void AddFloatObj(string name, float value, string obj_name = "");
	void AddBoolObj(string name, bool value, string obj_name = "");

	//-- Deserialize

	//-------------
	inline string GetString(string name) { return Object[name].get<string>(); };
	inline int GetInt(string name) { return Object[name].get<int>(); };
	inline uint GetUnsignedInt(string name) { return Object[name].get<uint>(); };
	inline float GetFloat(string name) { return Object[name].get<float>(); };
	inline bool GetBool(string name) { return Object[name].get<bool>(); };

	//Objects
	inline string GetStringObj(string name, string obj_name = "") { return Object[obj_name][name].get<string>(); };
	inline int GetIntObj(string name, string obj_name = "") { return Object[obj_name][name].get<int>(); };
	inline uint GetUnsignedIntObj(string name, string obj_name = "") { return Object[obj_name][name].get<uint>(); };
	inline float GetFloatObj(string name, string obj_name = "") { return Object[obj_name][name].get<float>(); };
	inline bool GetBoolObj(string name, string obj_name = "") { return Object[obj_name][name].get<bool>(); };

public: 
	
	json Object;
};