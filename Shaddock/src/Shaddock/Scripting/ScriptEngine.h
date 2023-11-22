#pragma once
#include <filesystem>
#include <string>

extern "C" {
	typedef struct _MonoClass MonoClass;
	typedef struct _MonoObject MonoObject;
	typedef struct _MonoMethod MonoMethod;
}

namespace Shaddock {

	class ScriptEngine
	{
	public:
		static void Init();
		static void Shutdown();
		static void LoadAssembly(const std::filesystem::path& filepath);
		static MonoObject* InstantiateClass(MonoClass* monoClass);
	private:
		static void InitMono();
		static void ShutdownMono();
		friend class ScriptClass;
	};

	class ScriptClass
	{
	public: 
		ScriptClass() = default;
		ScriptClass(const std::string& classNamespace, const std::string& className);

		MonoObject* Instantiate();
		MonoMethod* GetMethod(const std::string& name, int parameterCount);
		MonoObject* InvokeMethod(MonoObject* instance, MonoMethod* method, void** parameter = nullptr);
	private:
		std::string m_ClassNamespace, m_ClassName;
		MonoClass* m_MonoClass = nullptr;
	};

}