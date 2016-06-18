#include "KEntitydef.h"

std::map<std::string, KBEDATATYPE_BASE*> EntityDef::datatypes;
std::map<uint16, KBEDATATYPE_BASE*> EntityDef::iddatatypes;
std::map<string, int32> EntityDef::datatype2id;
std::map<std::string, ScriptModule> EntityDef::moduledefs;
std::map<uint16, ScriptModule> EntityDef::idmoduledefs;
std::map<std::string, PropertyMap*> EntityDef::alldefpropertys;
std::map<std::string, PropertyMap*> EntityDef::defpropertys_;
std::map<uint16, PropertyMap*> EntityDef::iddefpropertys_;

bool EntityDef::__entityAliasID;
bool EntityDef::__entitydefAliasID;
