#include "Object.h"

namespace kda
{
	void Object::Read(const rapidjson::Value& value) 
	{
		READ_DATA(value, name);
	}
}