#include "Serialization.h"


Serializer::Serializer() {

}

Serializer::~Serializer(){

}

void Serializer::Save(const char* file) const{

	ofstream stream(file, ofstream::out);
	stream << setw(2) << Object << endl;
	stream.close();
}

void Serializer::Load(const char* file) {

	this->Object = nullptr;

	//Open file
	ifstream stream(file, ifstream::in);

	//Write data into new json
	this->Object = json::parse(stream);
}

//Serialize functions

//----------------
void Serializer::AddString(string name, string value) {
	Object[name] = value;
}

void Serializer::AddInt(string name, int value) {
	Object[name] = value;
}

void Serializer::AddUnsignedInt(string name, uint value) {
	Object[name] = value;
}

void Serializer::AddFloat(string name, float value) {
	Object[name] = value;
}

void Serializer::AddBool(string name, bool value) {
	Object[name] = value;
}

//Objects
void Serializer::AddStringObj(string name, string value, string obj_name) {
	Object[obj_name][name] = value;
}

void Serializer::AddIntObj(string name, int value, string obj_name) {
	Object[obj_name][name] = value;
}

void Serializer::AddUnsignedIntObj(string name, uint value, string obj_name) {
	Object[obj_name][name] = value;
}

void Serializer::AddFloatObj(string name, float value, string obj_name) {
	Object[obj_name][name] = value;
}

void Serializer::AddBoolObj(string name, bool value, string obj_name) {
	Object[obj_name][name] = value;
}