#include "Object.h"

namespace kda
{
	bool Object::Read(const rapidjson::Value& value) 
	{
		READ_DATA(value, name);

		return true;
	}
}