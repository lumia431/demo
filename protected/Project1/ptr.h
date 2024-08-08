#pragma once
template <class T>
class ConstPtr
{

public:

	ConstPtr(const T* ptr = 0);
	ConstPtr(const ConstPtr<T>& mp);
	~ConstPtr();
	const T* operator->() const;
	const T* rawPtr() const;

protected:

	void operator=(const ConstPtr<T>& mp);
	const T* rawPtr_;

};

template <class T>
class Ptr : public ConstPtr<T> {

public:

	Ptr(T* ptr = 0);
	Ptr(const Ptr<T>& mp);
	void operator=(const Ptr<T>& mp);
	const T* operator->() const;
	T* operator->();
	T* rawPtr();
	const T* rawPtr() const;


};

template<class T>
ConstPtr<T>::ConstPtr(const T* ptr)
{
	if (ptr)
	{
		this->rawPtr_ = new T;
		memcpy((T*)this->rawPtr_,ptr,sizeof(T));
	}
	else
	{
		this->rawPtr_ = nullptr;
	}
}

template<class T>
ConstPtr<T>::~ConstPtr()
{
	if (this->rawPtr_)
	{
		delete this->rawPtr_;
	}
}

template<class T>
Ptr<T>::Ptr(T* ptr) :ConstPtr<T>(ptr)
{

}

template <class T>
void Ptr<T>::operator=(const Ptr<T>& mp)
{
	if (this != &mp)
	{
		if (this->rawPtr_)
		{
			delete this->rawPtr_;
		}
		if (mp.rawPtr_)
		{
			this->rawPtr_ = new T(*mp.rawPtr());
		}
		else
		{
			this->rawPtr_ = nullptr;
		}
	}
}

template <class T>
const T* Ptr<T>::operator->() const
{
	return this->rawPtr_;
}

template <class T>
T* Ptr<T>::operator->()
{
	return const_cast<T*>(this->rawPtr_);
}

template <class T>
T* Ptr<T>::rawPtr()
{
	return const_cast<T*>(this->rawPtr_);
}

template <class T>
const T* Ptr<T>::rawPtr() const
{
	return this->rawPtr_;
}