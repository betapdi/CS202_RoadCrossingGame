#ifndef CSINGLETON_
#define CSINGLETON_

template<class T>
class CSingleton {
public:
	static T* getInstance() {
		if (!s_instance) {
			s_instance = new T();
		}
		return s_instance;
	}

	static bool hasInstance() {
		return s_instance != 0;
	}

	static void freeInstance() {
		if (s_instance) {
			delete s_instance;
		}
	}
protected:
	CSingleton() {

	}

	virtual ~CSingleton() {
		delete s_instance;
	}
private:
	static T* s_instance;
};

template<class T> T* CSingleton<T>::s_instance = nullptr;
#endif // !CSINGLETON_

